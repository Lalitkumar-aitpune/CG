#include <GL/glut.h>
#include <vector>
#include <algorithm>
#include <iostream>

int windowWidth = 800;
int windowHeight = 600;

struct Point {
    int x, y;
};

// Global variables for rhombus vertices and color
Point rhombus[4];
bool filled[800][600] = { false }; // Screen buffer for filled areas
GLubyte fillColor[3] = { 255, 0, 0 }; // Default fill color (Red)

// Function to draw a line between two points
void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2i(p1.x, p1.y);
    glVertex2i(p2.x, p2.y);
    glEnd();
}

// Function to fill the rhombus using scan-line algorithm
void fillRhombus(int x, int y, GLubyte color[3]) {
    // Simple scan-line filling algorithm
    for (int i = 0; i < windowHeight; ++i) {
        std::vector<int> intersections;
        for (int j = 0; j < 4; ++j) {
            Point p1 = rhombus[j];
            Point p2 = rhombus[(j + 1) % 4];
            if ((p1.y <= i && p2.y > i) || (p2.y <= i && p1.y > i)) {
                int x_intersection = p1.x + (i - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
                intersections.push_back(x_intersection);
            }
        }

        std::sort(intersections.begin(), intersections.end());

        for (size_t k = 0; k < intersections.size(); k += 2) {
            int x_start = intersections[k];
            int x_end = intersections[k + 1];
            for (int x = x_start; x <= x_end; ++x) {
                if (!filled[x][i]) {
                    glBegin(GL_POINTS);
                    glColor3ub(color[0], color[1], color[2]);
                    glVertex2i(x, i);
                    glEnd();
                    filled[x][i] = true;
                }
            }
        }
    }
    glFlush();
}

// Function to handle mouse click for color filling
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = windowHeight - y; // Convert y coordinate to match window coordinate system
        fillRhombus(x, y, fillColor);
    }
}

// Function to display the rhombus
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0); // Set color to black for the outline
    for (int i = 0; i < 4; ++i) {
        drawLine(rhombus[i], rhombus[(i + 1) % 4]);
    }
    glFlush();
}

// Initialization function
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set background color to white
    glColor3f(0.0, 0.0, 0.0); // Set default line color to black
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}

// Function to get user input for rhombus vertices and fill color
void getUserInput() {
    std::cout << "Enter the coordinates of the 4 vertices of the rhombus (format: x y):\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "Vertex " << i + 1 << ": ";
        std::cin >> rhombus[i].x >> rhombus[i].y;
    }

    std::cout << "Enter the fill color (R G B, each between 0 and 255): ";
    std::cin >> fillColor[0] >> fillColor[1] >> fillColor[2];
}

int main(int argc, char **argv) {
    // Get user input
    getUserInput();

    // Initialize GLUT and OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rhombus Filling with Scan Line Algorithm");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
