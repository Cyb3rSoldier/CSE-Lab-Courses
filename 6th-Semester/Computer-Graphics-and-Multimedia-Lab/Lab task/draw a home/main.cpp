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
    // Sun
    //========================

    glPointSize(40);
    glBegin(GL_POINTS);
    glColor3f(4.0,2.0,0.0);
    glVertex2f(-0.7,0.7);
    glEnd();

    //========================
    // roof ventilator
    //========================

    glBegin(GL_QUADS);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(0.2,0.5);
    glVertex2f(0.3,0.5);
    glVertex2f(0.3,0.2);
    glVertex2f(0.2,0.2);
    glEnd();

    //========================
    // Top of the home
    //========================
    glBegin(GL_TRIANGLES);
    glColor3f(5.0,0.0,0.3);
    glVertex2f(-0.4,0.2);
    glVertex2f(0.4,0.2);
    glVertex2f(0,0.4);
    glEnd();

    //========================
    // Body of the home
    //========================
    glBegin(GL_QUADS);
    glColor3f(3.0,3.0,0.8);
    glVertex2f(-0.3,-0.2);
    glVertex2f(0.3,-0.2);
    glVertex2f(0.3,0.2);
    glVertex2f(-0.3,0.2);
    glEnd();

    //========================
    // door
    //========================

    glBegin(GL_QUADS);
    glColor3f(0.3,0.1,0.0);
    glVertex2f(-0.1,-0.2);
    glVertex2f(0.1,-0.2);
    glVertex2f(0.1,0.1);
    glVertex2f(-0.1,0.1);
    glEnd();

    //========================
    // door line
    //========================
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(-0.007,0.1);
    glVertex2f(-0.007,-0.2);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(8.6,0.6,0.0);
    glVertex2f(0.007,0.1);
    glVertex2f(0.007,-0.2);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(8.6,0.6,0.0);
    glVertex2f(0.007,-0.02);
    glVertex2f(0.025,-0.02);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(8.6,0.6,0.0);
    glVertex2f(0.025,-0.08);
    glVertex2f(0.007,-0.08);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(8.6,0.6,0.0);
    glVertex2f(0.025,-0.02);
    glVertex2f(0.025,-0.08);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(8.6,0.6,0.0);
    glVertex2f(0.025,-0.05);
    glVertex2f(0.007,-0.05);
    glEnd();



    //========================
    // left window
    //========================
    glBegin(GL_QUADS);
    glColor3f(1.0,0.2,0.1);
    glVertex2f(-0.27,-0.01);
    glVertex2f(-0.15,-0.01);
    glVertex2f(-0.15,0.15);
    glVertex2f(-0.27,0.15);
    glEnd();

    //========================
    // left window lines
    //========================

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(-0.24,-0.01);
    glVertex2f(-0.24,0.15);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(-0.21,-0.01);
    glVertex2f(-0.21,0.15);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(-0.18,-0.01);
    glVertex2f(-0.18,0.15);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(-0.27,0.03);
    glVertex2f(-0.15,0.03);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(-0.27,0.07);
    glVertex2f(-0.15,0.07);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(-0.27,0.11);
    glVertex2f(-0.15,0.11);
    glEnd();


    //========================
    // right window
    //========================

    glBegin(GL_QUADS);
    glColor3f(1.0,0.2,0.1);
    glVertex2f(0.27,-0.01);
    glVertex2f(0.15,-0.01);
    glVertex2f(0.15,0.15);
    glVertex2f(0.27,0.15);
    glEnd();

    //========================
    // right window lines
    //========================

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(0.24,-0.01);
    glVertex2f(0.24,0.15);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(0.21,-0.01);
    glVertex2f(0.21,0.15);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(0.18,-0.01);
    glVertex2f(0.18,0.15);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(0.27,0.03);
    glVertex2f(0.15,0.03);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(0.27,0.07);
    glVertex2f(0.15,0.07);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(1.6,0.6,0.0);
    glVertex2f(0.27,0.11);
    glVertex2f(0.15,0.11);
    glEnd();



    glFlush();
}

void init()
{
    glClearColor(0.5, 0.8, 0.9, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-1.0,1.0,-1.0,1.0);
}

int main(int argc,char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800,700);
    glutInitWindowPosition(300,100);

    glutCreateWindow("Sweet Home!");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
