#include "glad.h"
#include "glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using glm::dvec3;
using glm::mat4;
using glm::vec3;

constexpr float PI          = 3.14159265358979323846f;
constexpr float ARC_RADIUS  = 1.003f;   // edges float slightly above the surface (no z-fighting)
constexpr int   ARC_SEGMENTS = 64;      // samples along each geodesic
constexpr int   MAX_LEVEL   = 8;

// ----------------------------------------------------------------------------
//  Spherical math helpers
// ----------------------------------------------------------------------------
static vec3 anyPerpendicular(const vec3& a)
{
    vec3 axis = (std::fabs(a.x) < 0.9f) ? vec3(1, 0, 0) : vec3(0, 1, 0);
    return glm::normalize(glm::cross(a, axis));
}

// Normalise p+q (arc midpoint direction); safe for (nearly) antipodal inputs.
static vec3 sphereMidpoint(const vec3& p, const vec3& q)
{
    vec3 s = p + q;
    if (glm::length(s) < 1e-6f) return anyPerpendicular(p);
    return glm::normalize(s);
}

// Great-circle interpolation (spherical linear interpolation).
static vec3 slerp(const vec3& p, const vec3& q, float t)
{
    float d = glm::clamp(glm::dot(p, q), -1.0f, 1.0f);
    if (d > 0.9995f) return glm::normalize(glm::mix(p, q, t));
    if (d < -0.99999f) {                       // antipodal: choose any half-circle
        float a = PI * t;
        return p * std::cos(a) + anyPerpendicular(p) * std::sin(a);
    }
    float th = std::acos(d);
    return (std::sin((1.0f - t) * th) * p + std::sin(t * th) * q) / std::sin(th);
}

// Interior angle at P between the geodesics P->Q and P->R, measured in the
// tangent plane at P.
static double angleAt(const dvec3& P, const dvec3& Q, const dvec3& R)
{
    dvec3 t1 = Q - glm::dot(P, Q) * P;
    dvec3 t2 = R - glm::dot(P, R) * P;
    double l = glm::length(t1) * glm::length(t2);
    if (l < 1e-14) return 0.0;
    return std::acos(glm::clamp(glm::dot(t1, t2) / l, -1.0, 1.0));
}

// Area of a spherical triangle on the unit sphere (Van Oosterom & Strackee):
//   tan(Omega/2) = |a.(b x c)| / (1 + a.b + b.c + c.a)
static double triArea(const dvec3& a, const dvec3& b, const dvec3& c)
{
    double det = std::fabs(glm::dot(a, glm::cross(b, c)));
    double den = 1.0 + glm::dot(a, b) + glm::dot(b, c) + glm::dot(c, a);
    return 2.0 * std::atan2(det, den);
}

struct Stats {
    double ang[3];     // interior angles A,B,C (radians)
    double excess;     // A+B+C-pi
    double areaVO;     // independent area (Van Oosterom formula)
};

static Stats computeStats(const vec3 c[3])
{
    dvec3 A(c[0]), B(c[1]), C(c[2]);
    Stats s;
    s.ang[0] = angleAt(A, B, C);
    s.ang[1] = angleAt(B, C, A);
    s.ang[2] = angleAt(C, A, B);
    s.excess = s.ang[0] + s.ang[1] + s.ang[2] - (double)PI;
    s.areaVO = triArea(A, B, C);
    return s;
}

static const double RAD2DEG = 180.0 / 3.14159265358979323846;

// Returns "" if OK, otherwise a human readable reason.  Normalises a,b,c.
static std::string validateTriangle(vec3& a, vec3& b, vec3& c)
{
    if (glm::length(a) < 1e-6f || glm::length(b) < 1e-6f || glm::length(c) < 1e-6f)
        return "zero-length vector";
    a = glm::normalize(a); b = glm::normalize(b); c = glm::normalize(c);
    const float eps = 1e-6f;
    if (glm::dot(a, b) > 1 - eps || glm::dot(b, c) > 1 - eps || glm::dot(c, a) > 1 - eps)
        return "two vertices coincide";
    if (glm::dot(a, b) < -1 + eps || glm::dot(b, c) < -1 + eps || glm::dot(c, a) < -1 + eps)
        return "antipodal vertices (geodesic between them is not unique)";
    if (std::fabs(glm::dot(a, glm::cross(b, c))) < 1e-4f)
        return "collinear vertices (all three lie on one great circle)";
    return "";
}

// ----------------------------------------------------------------------------
//  Indexed mesh built by recursive subdivision + projection onto the sphere.
//  A shared midpoint cache guarantees every edge midpoint is created once, so
//  there are no duplicated vertices:
//     vertices = (2^n + 1)(2^n + 2) / 2,   triangles = 4^n
// ----------------------------------------------------------------------------
struct Mesh {
    std::vector<vec3>     pos;
    std::vector<unsigned> idx;
    std::unordered_map<unsigned long long, unsigned> cache;

    unsigned midpoint(unsigned i, unsigned j)
    {
        unsigned lo = std::min(i, j), hi = std::max(i, j);
        unsigned long long key = ((unsigned long long)lo << 32) | hi;
        auto it = cache.find(key);
        if (it != cache.end()) return it->second;
        vec3 m = sphereMidpoint(pos[i], pos[j]);      // projection onto unit sphere
        pos.push_back(m);
        unsigned id = (unsigned)pos.size() - 1;
        cache[key] = id;
        return id;
    }

    void subdivide(unsigned a, unsigned b, unsigned c, int depth)
    {
        if (depth == 0) { idx.push_back(a); idx.push_back(b); idx.push_back(c); return; }
        unsigned ab = midpoint(a, b), bc = midpoint(b, c), ca = midpoint(c, a);
        subdivide(a,  ab, ca, depth - 1);
        subdivide(ab, b,  bc, depth - 1);
        subdivide(ca, bc, c,  depth - 1);
        subdivide(ab, bc, ca, depth - 1);
    }

    void build(const vec3& A, const vec3& B, const vec3& C, int level)
    {
        pos.clear(); idx.clear(); cache.clear();
        size_t side = (size_t)1 << level;
        pos.reserve((side + 1) * (side + 2) / 2);
        idx.reserve(3 * side * side);
        pos.push_back(A); pos.push_back(B); pos.push_back(C);
        subdivide(0, 1, 2, level);
    }

    // Sum of the areas of all mesh triangles (should equal the excess).
    double area() const
    {
        double s = 0;
        for (size_t i = 0; i < idx.size(); i += 3)
            s += triArea(dvec3(pos[idx[i]]), dvec3(pos[idx[i + 1]]), dvec3(pos[idx[i + 2]]));
        return s;
    }
};

// ----------------------------------------------------------------------------
//  Shader utilities
// ----------------------------------------------------------------------------
static std::string readFile(const std::string& name)
{
    const char* prefixes[] = { "shaders/", "../shaders/", "../../shaders/", "" };
    for (const char* p : prefixes) {
        std::ifstream f(std::string(p) + name);
        if (f) { std::stringstream ss; ss << f.rdbuf(); return ss.str(); }
    }
    std::cerr << "Cannot open shader file: " << name << "\n";
    std::exit(EXIT_FAILURE);
}

static GLuint compile(GLenum type, const std::string& src, const std::string& name)
{
    GLuint s = glCreateShader(type);
    const char* c = src.c_str();
    glShaderSource(s, 1, &c, nullptr);
    glCompileShader(s);
    GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[2048]; glGetShaderInfoLog(s, 2048, nullptr, log);
        std::cerr << "Shader compile error (" << name << "):\n" << log << "\n";
        std::exit(EXIT_FAILURE);
    }
    return s;
}

static GLuint makeProgram(const std::string& vs, const std::string& fs)
{
    GLuint v = compile(GL_VERTEX_SHADER,   readFile(vs), vs);
    GLuint f = compile(GL_FRAGMENT_SHADER, readFile(fs), fs);
    GLuint p = glCreateProgram();
    glAttachShader(p, v); glAttachShader(p, f);
    glLinkProgram(p);
    GLint ok; glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[2048]; glGetProgramInfoLog(p, 2048, nullptr, log);
        std::cerr << "Program link error:\n" << log << "\n";
        std::exit(EXIT_FAILURE);
    }
    glDeleteShader(v); glDeleteShader(f);
    return p;
}

static void setMat4(GLuint p, const char* n, const mat4& m)
{ glUniformMatrix4fv(glGetUniformLocation(p, n), 1, GL_FALSE, glm::value_ptr(m)); }
static void setVec3(GLuint p, const char* n, const vec3& v)
{ glUniform3fv(glGetUniformLocation(p, n), 1, glm::value_ptr(v)); }

// ----------------------------------------------------------------------------
//  Application state
// ----------------------------------------------------------------------------
struct App {
    // geometry
    vec3 corner[3];                       // current triangle (changes during morph)
    vec3 from[3], to[3];                  // morph endpoints
    bool   morphing = false;
    double morphStart = 0;
    double morphDuration = 2.0;           // seconds

    int  level = 5;
    bool wire = false, flat = false, grid = true, dirty = true;
    Mesh mesh;

    // camera
    mat4  rot = mat4(1.0f);
    float dist = 3.6f;
    bool  dragging = false;
    vec3  lastArc = vec3(0, 0, 1);

    // window
    int winW = 900, winH = 800, fbW = 900, fbH = 800;

    // picking
    std::vector<vec3> picks;
    std::string message;

    // GL objects
    GLuint surfProg = 0, lineProg = 0;
    GLuint surfVAO = 0, surfVBO = 0, surfEBO = 0;
    GLuint arcVAO = 0,  arcVBO = 0;
    GLuint gridVAO = 0, gridVBO = 0;
    GLuint markVAO = 0, markVBO = 0;
    int gridLineVerts = 0, axisVerts = 0;
    std::vector<vec3> arcs;
    Stats stats;
    double meshArea = 0;
};

static App app;

static const vec3 OCT[3] = { vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1) };

static void resetView()
{
    // orient the camera so the triangle centre faces the viewer
    vec3 c = glm::normalize(app.corner[0] + app.corner[1] + app.corner[2]);
    if (glm::length(app.corner[0] + app.corner[1] + app.corner[2]) < 1e-4f) c = vec3(0, 0, 1);
    vec3 axis = glm::cross(c, vec3(0, 0, 1));
    float ang = std::acos(glm::clamp(glm::dot(c, vec3(0, 0, 1)), -1.0f, 1.0f));
    app.rot = (glm::length(axis) < 1e-6f) ? mat4(1.0f) : glm::rotate(mat4(1.0f), ang, glm::normalize(axis));
    app.dist = 3.6f;
}

static void printStats(const char* label)
{
    printf("\n[%s]\n", label);
    printf("  A=(%.4f,%.4f,%.4f)  B=(%.4f,%.4f,%.4f)  C=(%.4f,%.4f,%.4f)\n",
           app.corner[0].x, app.corner[0].y, app.corner[0].z,
           app.corner[1].x, app.corner[1].y, app.corner[1].z,
           app.corner[2].x, app.corner[2].y, app.corner[2].z);
    printf("  angles: A=%.4f  B=%.4f  C=%.4f deg\n",
           app.stats.ang[0] * RAD2DEG, app.stats.ang[1] * RAD2DEG, app.stats.ang[2] * RAD2DEG);
    printf("  spherical excess E = A+B+C-pi = %.6f rad (= area on unit sphere)\n", app.stats.excess);
    printf("  independent area (Van Oosterom) = %.6f | sum of mesh-triangle areas = %.6f\n",
           app.stats.areaVO, app.meshArea);
}

static void verifyOctant()
{
    Stats s = computeStats(OCT);
    bool ok = true;
    for (int i = 0; i < 3; ++i) ok &= std::fabs(s.ang[i] - PI / 2.0) < 1e-6;
    ok &= std::fabs(s.excess - PI / 2.0) < 1e-6;
    ok &= std::fabs(s.areaVO - PI / 2.0) < 1e-6;
    printf("Octant check: angles = %.4f, %.4f, %.4f deg; excess = %.6f (pi/2 = %.6f); area = %.6f -> %s\n",
           s.ang[0] * RAD2DEG, s.ang[1] * RAD2DEG, s.ang[2] * RAD2DEG,
           s.excess, PI / 2.0, s.areaVO, ok ? "PASS" : "FAIL");
}

// ----------------------------------------------------------------------------
//  GPU buffers
// ----------------------------------------------------------------------------
static void makeVec3VAO(GLuint& vao, GLuint& vbo)
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
}

static void initGL()
{
    app.surfProg = makeProgram("surface.vert", "surface.frag");
    app.lineProg = makeProgram("line.vert", "line.frag");

    // surface VAO: interleaved position + normal, indexed
    glGenVertexArrays(1, &app.surfVAO);
    glGenBuffers(1, &app.surfVBO);
    glGenBuffers(1, &app.surfEBO);
    glBindVertexArray(app.surfVAO);
    glBindBuffer(GL_ARRAY_BUFFER, app.surfVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app.surfEBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    makeVec3VAO(app.arcVAO,  app.arcVBO);
    makeVec3VAO(app.gridVAO, app.gridVBO);
    makeVec3VAO(app.markVAO, app.markVBO);

    // reference grid: 6 great circles through the poles + 5 latitude circles,
    // slightly inside the sphere so it never fights with the patch; then axes.
    std::vector<vec3> g;
    const int N = 96;
    const float R = 0.995f;
    for (int m = 0; m < 6; ++m) {
        float lon = PI * m / 6.0f;
        vec3 u(std::cos(lon), 0, std::sin(lon)), v(0, 1, 0);
        for (int i = 0; i < N; ++i) {
            float t0 = 2 * PI * i / N, t1 = 2 * PI * (i + 1) / N;
            g.push_back(R * (std::cos(t0) * u + std::sin(t0) * v));
            g.push_back(R * (std::cos(t1) * u + std::sin(t1) * v));
        }
    }
    for (int k = -2; k <= 2; ++k) {
        float lat = k * PI / 6.0f;
        float r = R * std::cos(lat), y = R * std::sin(lat);
        for (int i = 0; i < N; ++i) {
            float t0 = 2 * PI * i / N, t1 = 2 * PI * (i + 1) / N;
            g.push_back(vec3(r * std::cos(t0), y, r * std::sin(t0)));
            g.push_back(vec3(r * std::cos(t1), y, r * std::sin(t1)));
        }
    }
    app.gridLineVerts = (int)g.size();
    const float L = 1.5f;
    g.push_back(vec3(-L, 0, 0)); g.push_back(vec3(L, 0, 0));
    g.push_back(vec3(0, -L, 0)); g.push_back(vec3(0, L, 0));
    g.push_back(vec3(0, 0, -L)); g.push_back(vec3(0, 0, L));
    app.axisVerts = 6;
    glBindBuffer(GL_ARRAY_BUFFER, app.gridVBO);
    glBufferData(GL_ARRAY_BUFFER, g.size() * sizeof(vec3), g.data(), GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_PROGRAM_POINT_SIZE);
}

// Rebuild mesh + edge arcs and upload (called on level change / during morph).
static void rebuild()
{
    app.mesh.build(app.corner[0], app.corner[1], app.corner[2], app.level);

    std::vector<float> vb;
    vb.reserve(app.mesh.pos.size() * 6);
    for (const vec3& p : app.mesh.pos) {
        vec3 n = glm::normalize(p);           // exact normal of a unit sphere = position
        vb.insert(vb.end(), { p.x, p.y, p.z, n.x, n.y, n.z });
    }
    glBindVertexArray(app.surfVAO);
    glBindBuffer(GL_ARRAY_BUFFER, app.surfVBO);
    glBufferData(GL_ARRAY_BUFFER, vb.size() * sizeof(float), vb.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, app.surfEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, app.mesh.idx.size() * sizeof(unsigned),
                 app.mesh.idx.data(), GL_DYNAMIC_DRAW);

    // great-circle edges: sample slerp(P,Q,t), NOT the straight chord
    app.arcs.clear();
    for (int e = 0; e < 3; ++e) {
        const vec3& P = app.corner[e];
        const vec3& Q = app.corner[(e + 1) % 3];
        for (int k = 0; k <= ARC_SEGMENTS; ++k)
            app.arcs.push_back(slerp(P, Q, (float)k / ARC_SEGMENTS) * ARC_RADIUS);
    }
    glBindBuffer(GL_ARRAY_BUFFER, app.arcVBO);
    glBufferData(GL_ARRAY_BUFFER, app.arcs.size() * sizeof(vec3), app.arcs.data(), GL_DYNAMIC_DRAW);

    app.stats = computeStats(app.corner);
    app.meshArea = app.mesh.area();
}

// ----------------------------------------------------------------------------
//  Morph / picking (Q2)
// ----------------------------------------------------------------------------
static void startMorph(const vec3 target[3])
{
    for (int i = 0; i < 3; ++i) { app.from[i] = app.corner[i]; app.to[i] = target[i]; }
    app.morphing = true;
    app.morphStart = glfwGetTime();
}

static void handlePick(double mx, double my)
{
    // cursor (window coords) -> NDC
    float x = 2.0f * (float)mx / app.winW - 1.0f;
    float y = 1.0f - 2.0f * (float)my / app.winH;

    mat4 view  = glm::translate(mat4(1.0f), vec3(0, 0, -app.dist));
    mat4 proj  = glm::perspective(glm::radians(45.0f), (float)app.fbW / app.fbH, 0.1f, 50.0f);
    mat4 inv   = glm::inverse(proj * view * app.rot);      // clip -> object space

    glm::vec4 n = inv * glm::vec4(x, y, -1.0f, 1.0f); n /= n.w;   // point on near plane
    glm::vec4 f = inv * glm::vec4(x, y,  1.0f, 1.0f); f /= f.w;   // point on far plane
    vec3 o = vec3(n), d = glm::normalize(vec3(f) - vec3(n));

    // ray-sphere intersection with the unit sphere centred at the origin
    float b = glm::dot(o, d), c = glm::dot(o, o) - 1.0f;
    float disc = b * b - c;
    if (disc < 0.0f) { app.message = "click missed the sphere"; return; }
    float t = -b - std::sqrt(disc);
    if (t < 0.0f) t = -b + std::sqrt(disc);
    if (t < 0.0f) return;
    vec3 hit = glm::normalize(o + t * d);

    app.picks.push_back(hit);
    printf("Picked point %zu: (%.4f, %.4f, %.4f)\n", app.picks.size(), hit.x, hit.y, hit.z);
    app.message = "picked " + std::to_string(app.picks.size()) + "/3";

    if (app.picks.size() == 3) {
        vec3 a = app.picks[0], b2 = app.picks[1], c2 = app.picks[2];
        std::string err = validateTriangle(a, b2, c2);
        if (!err.empty()) {
            app.message = "REJECTED: " + err;
            printf("Degenerate input rejected: %s\n", err.c_str());
        } else {
            vec3 target[3] = { a, b2, c2 };
            startMorph(target);
            app.message = "morphing...";
        }
        app.picks.clear();
    }
}

// ----------------------------------------------------------------------------
//  Input callbacks
// ----------------------------------------------------------------------------
static vec3 arcballVector(double x, double y)
{
    float px = 2.0f * (float)x / app.winW - 1.0f;
    float py = 1.0f - 2.0f * (float)y / app.winH;
    float l2 = px * px + py * py;
    if (l2 <= 1.0f) return vec3(px, py, std::sqrt(1.0f - l2));
    return glm::normalize(vec3(px, py, 0.0f));
}

static void mouseButtonCb(GLFWwindow* w, int button, int action, int)
{
    double x, y; glfwGetCursorPos(w, &x, &y);
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        app.dragging = (action == GLFW_PRESS);
        if (app.dragging) app.lastArc = arcballVector(x, y);
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if (app.morphing) return;
        handlePick(x, y);
    }
}

static void cursorCb(GLFWwindow*, double x, double y)
{
    if (!app.dragging) return;
    vec3 cur = arcballVector(x, y);
    vec3 axis = glm::cross(app.lastArc, cur);
    if (glm::length(axis) > 1e-6f) {
        float ang = std::acos(glm::clamp(glm::dot(app.lastArc, cur), -1.0f, 1.0f));
        app.rot = glm::rotate(mat4(1.0f), ang, glm::normalize(axis)) * app.rot;
    }
    app.lastArc = cur;
}

static void scrollCb(GLFWwindow*, double, double yoff)
{
    app.dist *= std::pow(0.9f, (float)yoff);
    app.dist = glm::clamp(app.dist, 1.5f, 12.0f);
}

static void resizeCb(GLFWwindow* w, int, int)
{
    glfwGetWindowSize(w, &app.winW, &app.winH);
    glfwGetFramebufferSize(w, &app.fbW, &app.fbH);
    glViewport(0, 0, app.fbW, app.fbH);
}

static void keyCb(GLFWwindow* w, int key, int, int action, int)
{
    if (action != GLFW_PRESS) return;
    switch (key) {
    case GLFW_KEY_ESCAPE: glfwSetWindowShouldClose(w, 1); break;
    case GLFW_KEY_W: app.wire = !app.wire; break;
    case GLFW_KEY_F: app.flat = !app.flat; break;
    case GLFW_KEY_G: app.grid = !app.grid; break;
    case GLFW_KEY_UP:
        if (app.level < MAX_LEVEL) { ++app.level; app.dirty = true; }
        break;
    case GLFW_KEY_DOWN:
        if (app.level > 0) { --app.level; app.dirty = true; }
        break;
    case GLFW_KEY_R: resetView(); break;
    case GLFW_KEY_C: app.picks.clear(); app.message = "picks cleared"; break;
    case GLFW_KEY_O:
        if (!app.morphing) { startMorph(OCT); app.message = "morphing to octant..."; }
        break;
    }
    if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
        size_t side = (size_t)1 << app.level;
        printf("Subdivision level %d: %zu vertices, %zu triangles\n",
               app.level, (side + 1) * (side + 2) / 2, side * side);
    }
}

// ----------------------------------------------------------------------------
//  Rendering
// ----------------------------------------------------------------------------
static void drawLines(GLuint vao, GLenum mode, int first, int count, const vec3& col, float ptSize = 1.0f)
{
    glUniform3fv(glGetUniformLocation(app.lineProg, "color"), 1, glm::value_ptr(col));
    glUniform1f(glGetUniformLocation(app.lineProg, "pointSize"), ptSize);
    glBindVertexArray(vao);
    glDrawArrays(mode, first, count);
}

static void render()
{
    glClearColor(0.10f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 model = app.rot;
    mat4 view  = glm::translate(mat4(1.0f), vec3(0, 0, -app.dist));
    mat4 proj  = glm::perspective(glm::radians(45.0f), (float)app.fbW / app.fbH, 0.1f, 50.0f);

    // ---- reference grid + axes
    glUseProgram(app.lineProg);
    setMat4(app.lineProg, "model", model);
    setMat4(app.lineProg, "view", view);
    setMat4(app.lineProg, "projection", proj);
    if (app.grid) {
        drawLines(app.gridVAO, GL_LINES, 0, app.gridLineVerts, vec3(0.45f, 0.45f, 0.5f));
        drawLines(app.gridVAO, GL_LINES, app.gridLineVerts, app.axisVerts, vec3(0.8f, 0.8f, 0.8f));
    }

    // ---- surface (Blinn-Phong); polygon offset pushes it back so edges win the depth test
    glUseProgram(app.surfProg);
    setMat4(app.surfProg, "model", model);
    setMat4(app.surfProg, "view", view);
    setMat4(app.surfProg, "projection", proj);
    glUniformMatrix3fv(glGetUniformLocation(app.surfProg, "normalMatrix"), 1, GL_FALSE,
                       glm::value_ptr(glm::mat3(glm::transpose(glm::inverse(model)))));
    setVec3(app.surfProg, "lightPos", vec3(3.0f, 4.0f, 6.0f));
    setVec3(app.surfProg, "viewPos", vec3(0.0f, 0.0f, app.dist));
    setVec3(app.surfProg, "baseColor", vec3(0.15f, 0.45f, 0.95f));
    glUniform1i(glGetUniformLocation(app.surfProg, "flatShading"), app.flat ? 1 : 0);

    glPolygonMode(GL_FRONT_AND_BACK, app.wire ? GL_LINE : GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0f, 1.0f);
    glBindVertexArray(app.surfVAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)app.mesh.idx.size(), GL_UNSIGNED_INT, nullptr);
    glDisable(GL_POLYGON_OFFSET_FILL);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // ---- geodesic edges + vertex markers
    glUseProgram(app.lineProg);
    const int S = ARC_SEGMENTS + 1;
    drawLines(app.arcVAO, GL_LINE_STRIP, 0 * S, S, vec3(1.0f, 0.25f, 0.25f));
    drawLines(app.arcVAO, GL_LINE_STRIP, 1 * S, S, vec3(0.3f, 1.0f, 0.3f));
    drawLines(app.arcVAO, GL_LINE_STRIP, 2 * S, S, vec3(1.0f, 0.95f, 0.2f));

    std::vector<vec3> marks;
    for (int i = 0; i < 3; ++i) marks.push_back(app.corner[i] * (ARC_RADIUS + 0.002f));
    for (const vec3& p : app.picks) marks.push_back(p * (ARC_RADIUS + 0.002f));
    glBindVertexArray(app.markVAO);
    glBindBuffer(GL_ARRAY_BUFFER, app.markVBO);
    glBufferData(GL_ARRAY_BUFFER, marks.size() * sizeof(vec3), marks.data(), GL_DYNAMIC_DRAW);
    drawLines(app.markVAO, GL_POINTS, 0, 3, vec3(1.0f, 1.0f, 1.0f), 9.0f);
    if (!app.picks.empty())
        drawLines(app.markVAO, GL_POINTS, 3, (int)app.picks.size(), vec3(1.0f, 0.3f, 1.0f), 11.0f);
}

static void updateTitle(GLFWwindow* w, double fps)
{
    char buf[512];
    size_t side = (size_t)1 << app.level;
    std::snprintf(buf, sizeof(buf),
        "L%d (%zuv/%zut) | A=%.2f B=%.2f C=%.2f deg | E=%.4f rad (area %.4f) | %s%s | %.0f FPS%s%s",
        app.level, (side + 1) * (side + 2) / 2, side * side,
        app.stats.ang[0] * RAD2DEG, app.stats.ang[1] * RAD2DEG, app.stats.ang[2] * RAD2DEG,
        app.stats.excess, app.mesh.area(),
        app.wire ? "wire" : "solid", app.flat ? "/flat" : "/smooth", fps,
        app.message.empty() ? "" : " | ", app.message.c_str());
    glfwSetWindowTitle(w, buf);
}

// ----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    // --- initial triangle: octant or 9 command-line floats
    for (int i = 0; i < 3; ++i) app.corner[i] = OCT[i];
    if (argc == 10) {
        vec3 v[3];
        for (int i = 0; i < 3; ++i)
            v[i] = vec3(std::atof(argv[1 + 3 * i]), std::atof(argv[2 + 3 * i]), std::atof(argv[3 + 3 * i]));
        std::string err = validateTriangle(v[0], v[1], v[2]);
        if (!err.empty()) {
            std::cerr << "Invalid input triangle: " << err << "\nFalling back to the octant.\n";
        } else {
            for (int i = 0; i < 3; ++i) app.corner[i] = v[i];   // validate() normalised them
        }
    } else if (argc != 1) {
        std::cerr << "Usage: " << argv[0] << " [ax ay az bx by bz cx cy cz]\n";
    }

    verifyOctant();

    if (!glfwInit()) { std::cerr << "GLFW init failed\n"; return EXIT_FAILURE; }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);   // required on macOS
    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* win = glfwCreateWindow(app.winW, app.winH, "Spherical Triangle", nullptr, nullptr);
    if (!win) { std::cerr << "Window creation failed\n"; glfwTerminate(); return EXIT_FAILURE; }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "GLAD init failed\n"; return EXIT_FAILURE;
    }
    glfwSetMouseButtonCallback(win, mouseButtonCb);
    glfwSetCursorPosCallback(win, cursorCb);
    glfwSetScrollCallback(win, scrollCb);
    glfwSetKeyCallback(win, keyCb);
    glfwSetFramebufferSizeCallback(win, resizeCb);
    resizeCb(win, 0, 0);

    initGL();
    resetView();
    rebuild();
    printStats("initial triangle");
    printf("\nControls: left-drag rotate | scroll zoom | UP/DOWN level | W wireframe | F flat/smooth |\n"
           "          G grid | right-click pick 3 points | O morph to octant | C clear | R reset view\n");

    double lastTitle = 0; int frames = 0; double fps = 0;
    while (!glfwWindowShouldClose(win)) {
        double now = glfwGetTime();

        if (app.morphing) {
            double t = (now - app.morphStart) / app.morphDuration;
            if (t >= 1.0) t = 1.0;
            float s = (float)(t * t * (3.0 - 2.0 * t));            // smoothstep easing
            for (int i = 0; i < 3; ++i)
                app.corner[i] = (t >= 1.0) ? app.to[i] : slerp(app.from[i], app.to[i], s);
            app.dirty = true;
            if (t >= 1.0) {
                app.morphing = false;
                app.message.clear();
                rebuild(); app.dirty = false;
                printStats("morph finished");
            }
        }
        if (app.dirty) { rebuild(); app.dirty = false; }

        render();
        glfwSwapBuffers(win);
        glfwPollEvents();

        ++frames;
        if (now - lastTitle > 0.5) {
            fps = frames / (now - lastTitle);
            frames = 0; lastTitle = now;
            updateTitle(win, fps);
        }
    }
    glfwTerminate();
    return 0;
}
