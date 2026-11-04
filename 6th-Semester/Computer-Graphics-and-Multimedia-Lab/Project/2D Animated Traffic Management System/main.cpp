#include <GL/glut.h>
#include <cmath>

const int W = 800, H = 600;

#include <vector>

struct Car {
    float x, y;
    float speed;
    int dir;            // 0=right, 1=left, 2=up, 3=down
    float r, g, b;
};

std::vector<Car> cars;

// ---------- Helper functions ----------
void drawRect(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}

void drawCircle(float cx, float cy, float rad, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);                       // center
        for (int i = 0; i <= 360; i += 10) {
            float a = i * 3.14159265f / 180.0f;   // degrees -> radians
            glVertex2f(cx + rad * cos(a), cy + rad * sin(a));
        }
    glEnd();
}

void drawBuilding(float x, float y, float w, float h, float r, float g, float b) {
    drawRect(x, y, w, h, r, g, b);
    // windows: two loops make a grid
    for (float wx = x + 10; wx < x + w - 15; wx += 25)
        for (float wy = y + 10; wy < y + h - 15; wy += 30)
            drawRect(wx, wy, 12, 16, 1.0f, 0.95f, 0.5f);
}

void drawTree(float x, float y) {
    drawRect(x - 5, y, 10, 30, 0.4f, 0.25f, 0.1f);   // trunk
    drawCircle(x, y + 45, 25, 0.0f, 0.45f, 0.1f);    // leaves
}

void drawRoads() {
    drawRect(0, 250, W, 100, 0.3f, 0.3f, 0.3f);      // horizontal road
    drawRect(350, 0, 100, H, 0.3f, 0.3f, 0.3f);      // vertical road

    // dashed white center lines (skip the intersection 350-450 / 250-350)
    for (int x = 0; x < W; x += 40)
        if (x < 340 || x > 450) drawRect(x, 298, 20, 4, 1, 1, 1);
    for (int y = 0; y < H; y += 40)
        if (y < 240 || y > 350) drawRect(398, y, 4, 20, 1, 1, 1);
}

void drawScene() {
    drawRoads();
    drawBuilding(50, 400, 100, 150, 0.6f, 0.3f, 0.3f);
    drawBuilding(190, 400, 90, 120, 0.3f, 0.4f, 0.7f);
    drawBuilding(520, 400, 120, 160, 0.5f, 0.5f, 0.5f);
    drawBuilding(60, 40, 120, 130, 0.7f, 0.5f, 0.2f);
    drawTree(300, 440);
    drawTree(700, 120);
    drawTree(250, 100);
}

void drawCar(float x, float y, int dir, float r, float g, float b) {
    glPushMatrix();                      // save current transform
    glTranslatef(x, y, 0);               // TRANSLATION: move to (x, y)

    if (dir == 1) {                      // moving left
        glTranslatef(60, 0, 0);
        glScalef(-1, 1, 1);              // SCALING: -1 flips the car horizontally
    }
    else if (dir == 2) glRotatef(90, 0, 0, 1);    // ROTATION: face up
    else if (dir == 3) glRotatef(-90, 0, 0, 1);   // ROTATION: face down

    // car is drawn at the origin, facing right
    drawRect(0, 0, 60, 20, r, g, b);                    // body
    drawRect(15, 20, 30, 14, r * 0.8f, g * 0.8f, b * 0.8f);   // roof
    drawRect(19, 22, 10, 10, 0.7f, 0.9f, 1.0f);         // window 1
    drawRect(32, 22, 10, 10, 0.7f, 0.9f, 1.0f);         // window 2
    drawCircle(14, 0, 7, 0.05f, 0.05f, 0.05f);          // wheel 1
    drawCircle(46, 0, 7, 0.05f, 0.05f, 0.05f);          // wheel 2

    glPopMatrix();                       // restore, so other objects are unaffected
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawScene();
    for (auto &c : cars)
        drawCar(c.x, c.y, c.dir, c.r, c.g, c.b);
    glutSwapBuffers();
}
void init() {
    glClearColor(0.2f, 0.7f, 0.2f, 1);       // grass green background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, W, 0, H);                  // pixel coordinates
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    for (auto &c : cars) {
        if (c.dir == 0) c.x += c.speed;
        if (c.dir == 1) c.x -= c.speed;
        if (c.dir == 2) c.y += c.speed;
        if (c.dir == 3) c.y -= c.speed;

        // wrap-around when leaving the screen
        if (c.x > W + 60)  c.x = -60;
        if (c.x < -60)     c.x = W;
        if (c.y > H + 60)  c.y = -60;
        if (c.y < -60)     c.y = H + 60;
    }
    glutPostRedisplay();           // ask GLUT to call display() again
    glutTimerFunc(16, update, 0);  // call update() again in 16 ms (~60 FPS)
}

void initCars() {
    cars.push_back({0,   262, 2.0f, 0, 1.0f, 0.1f, 0.1f});   // red, right
    cars.push_back({700, 306, 2.5f, 1, 0.1f, 0.3f, 1.0f});   // blue, left
    cars.push_back({425, 0,   2.0f, 2, 1.0f, 0.8f, 0.0f});   // yellow, up
    cars.push_back({365, 600, 1.5f, 3, 0.6f, 0.1f, 0.8f});   // purple, down
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(W, H);
    glutCreateWindow("2D Animated Traffic Management System");
    init();
    initCars();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);   // start the animation loop
    glutMainLoop();
}
