/*
 * GL01Hello.cpp: Test OpenGL/GLUT C/C++ Setup
 * Tested under Eclipse CDT with MinGW/Cygwin and CodeBlocks with MinGW
 * To compile with -lfreeglut -lglu32 -lopengl32
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>

 /* Handler for window-repaint event. Call back when the window first appears and
	whenever the window needs to be re-painted. */


float s1x = 0.5;
float s1y = 0.5;
float s1size = 0.02;
float s2x = 0.3;
float s2y = 0.3;
float s2size = 0.04;

void square(float x, float y, float size) {
	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex2f(x, y);    // x, y
	glVertex2f(x + size, y);
	glVertex2f(x + size, y + size);
	glVertex2f(x, y + size);
	glEnd();
}

void colorsquare(float x, float y, float size, char color) {
	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_QUADS); // Each set of 4 vertices form a quad
	if (color == 'r') {
		glColor3f(1.0f, 0.0f, 0.0f);
	}

	if (color == 'g') {
		glColor3f(0.0f, 1.0f, 0.0f);
	}

	if (color == 'b') {
		glColor3f(0.0f, 0.0f, 1.0f);
	}
	
	glVertex2f(x, y);    // x, y
	glVertex2f(x + size, y);
	glVertex2f(x + size, y + size);
	glVertex2f(x, y + size);
	glEnd();
}


void display() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
	//square(-0.5, -0.5, 0.01);
	//square(-1.0, 0, 0.02);
	colorsquare(s1x, s1y, s1size, 'g');
	colorsquare(s2x, s2y, s2size, 'r');
	glFlush();  // Render now
}

void keyboard(unsigned char key, int xmouse, int ymouse)
{
	if (key == 'a') {
		s1x = s1x + 0.01;
		s1y = s1y + 0.01;
	}
	if (key == 's') {
		s1x = s1x - 0.01;
		s1y = s1y - 0.01;
	}

	if (key == 'd') {
		s2x = s2x + 0.01;
		s2y = s2y + 0.01;
	}
	if (key == 'f') {
		s2x = s2x - 0.01;
		s2y = s2y - 0.01;
	}
	//colorsquare(s1x, s1y, s1size, 'g');
	//colorsquare(s2x, s2y, s2size, 'r');
	std::cout << s1x << ' ' << s1y << ' ' << s2x << ' ' << s2y << "\n";

	//Checking for collisions (https://www.quora.com/How-do-I-compare-two-floats-in-C++)
	//C++ has inaccuracies in the doubles when comparing numbers
	if ((fabs(s1x - s2x) < s1x * .001) && (fabs(s1y - s2y) < s1y * .001)) {
		std::cout << "collision detected \n";
	}

	if (s1x > 1.0) {
		s1x = -1.0;
	}
	if (s1x < -1.0) {
		s1x = 1.0;
	}
	if (s1y > 1.0) {
		s1y = -1.0;
	}		
	if (s1y < -1.0) {
		s1y = 1.0;		
	}


	if (s2x > 1.0) {
		s2x = -1.0;
	}
	if (s2x < -1.0) {
		s2x = 1.0;
	}
	if (s2y > 1.0) {
		s2y = -1.0;
	}
	if (s2y < -1.0) {
		s2y = 1.0;
	}

	glutPostRedisplay(); //request display() call ASAP
}





/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("Collision Detection"); // Create a window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutKeyboardFunc(keyboard);
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}