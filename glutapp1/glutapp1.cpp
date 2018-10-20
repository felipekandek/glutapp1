/*
 * GL01Hello.cpp: Test OpenGL/GLUT C/C++ Setup
 * Tested under Eclipse CDT with MinGW/Cygwin and CodeBlocks with MinGW
 * To compile with -lfreeglut -lglu32 -lopengl32
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

 /* Handler for window-repaint event. Call back when the window first appears and
	whenever the window needs to be re-painted. */



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
	square(-0.5, -0.5, 0.01);
	square(-1.0, 0, 0.02);
	colorsquare(0.5, 0.5, 0.04, 'b');
	glFlush();  // Render now
}




/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("Collision Detection"); // Create a window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}