#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //========================
    // POINT
    //========================
    glPointSize(8);
    glBegin(GL_POINTS);
        glColor3f(1.0,0.0,0.0);
        glVertex2f(-0.8,0.8);
    glEnd();

    //========================
    // LINE
    //========================
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex2f(-0.8,0.5);
        glVertex2f(-0.2,0.5);
    glEnd();

    //========================
    // TRIANGLE
    //========================
    glBegin(GL_TRIANGLES);
        glColor3f(0.0,0.0,1.0);
        glVertex2f(0.2,0.7);
        glVertex2f(0.0,0.3);
        glVertex2f(0.4,0.3);
    glEnd();

    //========================
    // QUADRILATERAL
    //========================
    glBegin(GL_QUADS);
        glColor3f(1.0,1.0,0.0);
        glVertex2f(-0.8,-0.1);
        glVertex2f(-0.3,-0.1);
        glVertex2f(-0.3,-0.6);
        glVertex2f(-0.8,-0.6);
    glEnd();

    //========================
    // PENTAGON (Polygon)
    //========================
    glBegin(GL_POLYGON);
        glColor3f(1.0,0.0,1.0);
        glVertex2f(0.2,-0.2);
        glVertex2f(0.45,-0.05);
        glVertex2f(0.6,-0.3);
        glVertex2f(0.5,-0.6);
        glVertex2f(0.25,-0.55);
    glEnd();

    glFlush();
}

void init()
{
    glClearColor(0.0,0.0,0.0,1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0,1.0,-1.0,1.0);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(700,700);
    glutInitWindowPosition(200,100);

    glutCreateWindow("Lab 2 - Basic 2D Shapes");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
