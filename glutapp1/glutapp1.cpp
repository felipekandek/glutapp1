/*
 * GL01Hello.cpp: Test OpenGL/GLUT C/C++ Setup
 * Tested under Eclipse CDT with MinGW/Cygwin and CodeBlocks with MinGW
 * To compile with -lfreeglut -lglu32 -lopengl32
 */
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <iostream>
#include <chrono>
#include <thread>

 /* Handler for window-repaint event. Call back when the window first appears and
	whenever the window needs to be re-painted. */
#define SQUARES 10

float sx[SQUARES];
float sy[SQUARES];
float ssize[SQUARES];
float sxspeed[SQUARES];
float syspeed[SQUARES];
float red[SQUARES];
float green[SQUARES];
float blue[SQUARES];
int numberofsquares = 4;
boolean animation = FALSE;


void setsquarevalues() {
	sx[1] = 0.5;
	sy[1] = 0.5;
	ssize[1] = 0.02;
	sxspeed[1] = 0.01;
	syspeed[1] = 0.01;

	red[1] = ((float)rand() / (RAND_MAX));
	blue[1] = ((float)rand() / (RAND_MAX));
	green[1] = ((float)rand() / (RAND_MAX));
	
	sx[2] = 0.3;
	sy[2] = 0.3;
	ssize[2] = 0.04;
	sxspeed[2] = -0.01;
	syspeed[2] = -0.01;

	red[2] = ((float)rand() / (RAND_MAX));
	blue[2] = ((float)rand() / (RAND_MAX));
	green[2] = ((float)rand() / (RAND_MAX));

	sx[3] = 0.0;
	sy[3] = 0.0;
	ssize[3] = 0.07;
	sxspeed[3] = 0.01;
	syspeed[3] = 0.01;

	red[3] = ((float)rand() / (RAND_MAX));
	blue[3] = ((float)rand() / (RAND_MAX));
	green[3] = ((float)rand() / (RAND_MAX));

	sx[4] = -0.5;
	sy[4] = -0.5;
	ssize[4] = 0.09;
	sxspeed[4] = 0.01;
	syspeed[4] = 0.01;

	red[4] = ((float)rand() / (RAND_MAX));
	blue[4] = ((float)rand() / (RAND_MAX));
	green[4] = ((float)rand() / (RAND_MAX));

	
}

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

void colorsquare(float x, float y, float size, float red, float green, float blue) {
	
	
	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_QUADS); // Each set of 4 vertices form a quad

	glColor3f(red, green, blue);
	
	glVertex2f(x, y);    // x, y
	glVertex2f(x + size, y);
	glVertex2f(x + size, y + size);
	glVertex2f(x, y + size);
	glEnd();
}


void display() {
	int i;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
	//square(-0.5, -0.5, 0.01);
	//square(-1.0, 0, 0.02);

	for (i = 1; i <= numberofsquares; i++) {
		colorsquare(sx[i], sy[i], ssize[i], red[i], green[i], blue[i]);
	}

	
	glFlush();  // Render now
}

//Checking for collisions (https://www.quora.com/How-do-I-compare-two-floats-in-C++)
//C++ has inaccuracies in the doubles when comparing numbers
boolean floatequal(float f1, float f2) {
	return (fabs(f1 - f2) < f1 * .001);
}


boolean collisiondetection(float x, float y, float size, float x2, float y2, float size2) {
	//x2 <= x + size, y2 <= y + size, x2 >= x, y2 >= y;
	
	std::cout << x << ' ' << y << ' ' << size << ' ' << x2 << ' ' << y2 << ' ' << size2 << "\n";
	
	//This checks whether square 2 is within square 1
	
	
	if (x2 <= x + size && y2 <= y + size && x2 >= x && y2 >= y) {
		return true;
	}
	else { //This checks whether square 1 is within square 2
	if (x <= x2 + size2 && y <= y2 + size2 && x >= x2 && y >= y2) {
		return true;
		}
		else {
			return false;
		}
	}
	
}

void outofbounds() {
	int i;
	//Square i runs from 1 to the number of squares
	for (i = 1; i <= numberofsquares; i = i + 1) {
		if (sx[i] > 1.0) {
			sx[i] = -1.0;
		}
		if (sx[i] < -1.0) {
			sx[i] = 1.0;
		}
		if (sy[i] > 1.0) {
			sy[i] = -1.0;
		}
		if (sy[i] < -1.0) {
			sy[i] = 1.0;
		}
	}
}

void keyboard(unsigned char key, int xmouse, int ymouse) {

	if (key == ' ') {
		animation = !animation;
	}
	//When a gets pressed square 1 is moved one speed unit up and to the right
	if (key == 'a') {
		sx[1] = sx[1] + sxspeed[1];
		sy[1] = sy[1] + syspeed[1];
	}
	//When s gets pressed square 1 is moved one speed unit down and to the left
	if (key == 's') {
		sx[1] = sx[1] - sxspeed[1];
		sy[1] = sy[1] - syspeed[1];
	}

	//When d gets pressed square 2 is moved one speed unit up and to the right
	if (key == 'd') {
		sx[2] = sx[2] + sxspeed[2];
		sy[2] = sy[2] + syspeed[2];
	}
	//When f gets pressed square 2 is moved one speed unit down and to the left
	if (key == 'f') {
		sx[2] = sx[2] - sxspeed[2];
		sy[2] = sy[2] - syspeed[2];
	}

	//When g gets pressed square 3 is moved one speed unit up and to the right
	if (key == 'g') {
		sx[3] = sx[3] + sxspeed[3];
		sy[3] = sy[3] + syspeed[3];
	}
	//When f gets pressed square 3 is moved one speed unit down and to the left
	if (key == 'h') {
		sx[3] = sx[3] - sxspeed[3];
		sy[3] = sy[3] - syspeed[3];
	}

	//Checking for collisions
	int i;
	int j;
	boolean detection = FALSE;
	for (i = 1; i <= numberofsquares; i++) {
		for (j = 1; j <= numberofsquares; j++) {
			if (i != j) {
				if (!detection && collisiondetection(sx[i], sy[i], ssize[i], sx[j], sy[j], ssize[j])) {
					std::cout << i << " " << j << " collision detected \n";
					sxspeed[i] = sxspeed[i] * -1;
					sxspeed[j] = sxspeed[j] * -1;
					detection = TRUE;


				}
			}
		}
	}
	outofbounds();
	glutPostRedisplay(); //request display() call ASAP
}


void squareanimation() {
	int i, j;
	if (animation) {
		for (i = 1; i <= numberofsquares; i++) {
			sx[i] = sx[i] + sxspeed[i];
			sy[i] = sy[i] + syspeed[i];
		}
	}

	//Checking for collisions
	boolean detection = FALSE;
	for (i = 1; i <= numberofsquares; i++) {
		for (j = 1; j <= numberofsquares; j++) {
			if (i != j) {
				if (!detection && collisiondetection(sx[i], sy[i], ssize[i], sx[j], sy[j], ssize[j])) {
					std::cout << i << " " << j << " collision detected \n";
					sxspeed[i] = sxspeed[i] * -1;
					sxspeed[j] = sxspeed[j] * -1;
					detection = TRUE;


				}
			}
		}
	}
	outofbounds();
	glutPostRedisplay();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	setsquarevalues();
	glutInit(&argc, argv);                 // Initialize GLUT
	glutCreateWindow("Collision Detection"); // Create a window with the given title
	glutInitWindowSize(320, 320);   // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutKeyboardFunc(keyboard);
	glutIdleFunc(squareanimation);
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}