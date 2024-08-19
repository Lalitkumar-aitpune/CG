#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

int xc, yc, r;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

void midpointCircleAlgo() {
    int x = 0;
    int y = r;
    int d = 1 - r;

    plot(x, y);
    while (y > x) {
        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        plot(x, y);
    }
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);

    midpointCircleAlgo();
    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter the coordinate of the center (0 to 500 range): " << endl;
    cout << "X-coordinate: ";
    cin >> xc;
    cout << "Y-coordinate: ";
    cin >> yc;
    cout << "Radius: ";
    cin >> r;

    if (xc - r < 0 || xc + r > 500 || yc - r < 0 || yc + r > 500) {
        cerr << "Error: Circle out of bounds." << endl;
        return 1;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Algorithm");

    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(myDisplay);

    glutMainLoop();

    return 0;
}
