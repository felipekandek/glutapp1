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
float s1xspeed = 0.01;
float s1yspeed = 0.01;
float s2xspeed = 0.01;
float s2yspeed = 0.01;

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

//Checking for collisions (https://www.quora.com/How-do-I-compare-two-floats-in-C++)
//C++ has inaccuracies in the doubles when comparing numbers
boolean floatequal(float f1, float f2) {
	return (fabs(f1 - f2) < f1 * .001);
}


boolean collisiondetection(float x, float y, float size, float x2, float y2, float size2) {
	//x2 <= x + size, y2 <= y + size, x2 >= x, y2 >= y;

	if (x2 <= x + size && y2 <= y + size && x2 >= x && y2 >= y) {
		return true;
	}
	else {
		return false;
	}
	
//	if (floatequal(x, x2) && floatequal(y, y2)) {
	//	return true;
	//}
	//else {
		//return false;
	//}
}

void keyboard(unsigned char key, int xmouse, int ymouse)
{
	//When a gets pressed square 1 is moved one speed unit up and to the right
	if (key == 'a') {
		s1x = s1x + s1xspeed;
		s1y = s1y + s1yspeed;
	}
	//When s gets pressed square 2 is moved one speed unit down and to the left
	if (key == 's') {
		s1x = s1x - s1xspeed;
		s1y = s1y - s1yspeed;
	}
	//When d gets pressed square 2 is moved one speed unit up and to the right
	if (key == 'd') {
		s2x = s2x + s2xspeed;
		s2y = s2y + s2yspeed;
	}
	//When f gets pressed square 2 is moved one speed unit down and to the left
	if (key == 'f') {
		s2x = s2x - s2xspeed;
		s2y = s2y - s2yspeed;
	}

	std::cout << s1x << ' ' << s1y << ' ' << s2x << ' ' << s2y << "\n";

	
	//Checking for collisions
	if (collisiondetection(s1x, s1y, s1size, s2x, s2y, s2size)) {
		std::cout << "collision detected \n";
		s1xspeed = s1xspeed * -1;
		s2xspeed = s2xspeed * -1;
	}

	//Keeps the squares within the display screen. If the square moves off screen the program wraps it
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

	//Same for the second square
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