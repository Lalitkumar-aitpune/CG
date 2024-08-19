// DDA algoritm For line
#include <iostream>
#include <GL/glut.h>  // OpenGL and GLUT headers
#include <stdlib.h>
#include <stdio.h>

using namespace std;

double x1, y1, x2, y2;

class Line {
public:
    void lineDDA() {
        cout << "DDA" << endl;
        float dx, dy, step, x, y, k, xin, yin;
        dx = x2 - x1;
        dy = y2 - y1;
        if (abs(dx) > abs(dy)) {
            step = abs(dx);
        } else {
            step = abs(dy);
        }
        xin = dx / step;
        yin = dy / step;
        x = x1;
        y = y1;
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        for (k = 1; k <= step; k++) {
            x = x + xin;
            y = y + yin;
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
        glutPostRedisplay();
        glFlush();
    }
};

void Init() {
    glClearColor(0.0, 0.0, 0.2, 0.0);
    glViewport(0, 0, 500, 500);  // Adjusted viewport size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500, 500, -500, 500);  // Changed to gluOrtho2D for 2D projection
}

void display() {
    Line myLine;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);  // Set line color to white
    myLine.lineDDA();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter First coordinate \n";
    cin >> x1 >> y1;
    cout << "Enter the second coordinate \n";
    cin >> x2 >> y2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Line Generation");

    Init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
