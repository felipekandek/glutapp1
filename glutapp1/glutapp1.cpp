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
struct square {
	float x;
	float y;
	float size;
	float xspeed;
	float yspeed;
	float red;
	float green;
	float blue;
};

square box[SQUARES];
int numberofsquares = 4;
boolean animation = FALSE;


void setsquarevalues() {
	box[1].x = 0.5;
	box[1].y = 0.5;
	box[1].size = 0.02;
	box[1].xspeed = 0.01;
	box[1].yspeed = 0.01;

	box[1].red = ((float)rand() / (RAND_MAX));
	box[1].blue = ((float)rand() / (RAND_MAX));
	box[1].green = ((float)rand() / (RAND_MAX));
	
	box[2].x = 0.3;
	box[2].y = 0.3;
	box[2].size = 0.04;
	box[2].xspeed = -0.01;
	box[2].yspeed = -0.01;

	box[2].red = ((float)rand() / (RAND_MAX));
	box[2].blue = ((float)rand() / (RAND_MAX));
	box[2].green = ((float)rand() / (RAND_MAX));

	box[3].x = 0.0;
	box[3].y = 0.0;
	box[3].size = 0.07;
	box[3].xspeed = 0.01;
	box[3].yspeed = 0.01;

	box[3].red = ((float)rand() / (RAND_MAX));
	box[3].blue = ((float)rand() / (RAND_MAX));
	box[3].green = ((float)rand() / (RAND_MAX));

	box[4].x = -0.5;
	box[4].y = -0.5;
	box[4].size = 0.09;
	box[4].xspeed = 0.01;
	box[4].yspeed = 0.01;

	box[4].red = ((float)rand() / (RAND_MAX));
	box[4].blue = ((float)rand() / (RAND_MAX));
	box[4].green = ((float)rand() / (RAND_MAX));

	
}

void colorsquare(square s) {
	// Draw a Red 1x1 Square centered at origin
	glBegin(GL_QUADS); // Each set of 4 vertices form a quad
	glColor3f(s.red, s.green, s.blue);
	glVertex2f(s.x, s.y);    // x, y
	glVertex2f(s.x + s.size, s.y);
	glVertex2f(s.x + s.size, s.y + s.size);
	glVertex2f(s.x, s.y + s.size);
	glEnd();
};


void display() {
	int i;

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)
	for (i = 1; i <= numberofsquares; i++) {
		colorsquare(box[i]);
	}
	glFlush();  // Render now
}

//Checking for collisions (https://www.quora.com/How-do-I-compare-two-floats-in-C++)
//C++ has inaccuracies in the doubles when comparing numbers
boolean floatequal(float f1, float f2) {
	return (fabs(f1 - f2) < f1 * .001);
}


boolean collisiondetection(square s1, square s2) {
	
	std::cout << s1.x << ' ' << s1.y << ' ' << s1.size << ' ' << s2.x << ' ' << s2.y << ' ' << s2.size << "\n";
	
	//This checks whether square 2 is within square 1
	if (s2.x <= s1.x + s1.size && s2.y <= s1.y + s1.size && s2.x >= s1.x && s2.y >= s1.y) {
		return true;
	}
	else { //This checks whether square 1 is within square 2
		if (s1.x <= s2.x + s2.size && s1.y <= s2.y + s2.size && s1.x >= s2.x && s1.y >= s2.y) {
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
		if (box[i].x > 1.0) {
			box[i].x = -1.0;
		}
		if (box[i].x < -1.0) {
			box[i].x = 1.0;
		}
		if (box[i].y > 1.0) {
			box[i].y = -1.0;
		}
		if (box[i].y < -1.0) {
			box[i].y = 1.0;
		}
	}
}

void keyboard(unsigned char key, int xmouse, int ymouse) {

	if (key == ' ') {
		animation = !animation;
	}
	//When a gets pressed square 1 is moved one speed unit up and to the right
	if (key == 'a') {
		box[1].x = box[1].x + box[1].xspeed;
		box[1].y = box[1].y + box[1].yspeed;
	}
	//When s gets pressed square 1 is moved one speed unit down and to the left
	if (key == 's') {
		box[1].x = box[1].x - box[1].xspeed;
		box[1].y = box[1].y - box[1].yspeed;
	}

	//When d gets pressed square 2 is moved one speed unit up and to the right
	if (key == 'd') {
		box[2].x = box[2].x + box[2].xspeed;
		box[2].y = box[2].y + box[2].yspeed;
	}
	//When f gets pressed square 2 is moved one speed unit down and to the left
	if (key == 'f') {
		box[2].x = box[2].x - box[2].xspeed;
		box[2].y = box[2].y - box[2].yspeed;
	}

	//When g gets pressed square 3 is moved one speed unit up and to the right
	if (key == 'g') {
		box[3].x = box[3].x + box[3].xspeed;
		box[3].y = box[3].y + box[3].yspeed;
	}
	//When f gets pressed square 3 is moved one speed unit down and to the left
	if (key == 'h') {
		box[3].x = box[3].x - box[3].xspeed;
		box[3].y = box[3].y - box[3].yspeed;
	}

	//Checking for collisions
	int i;
	int j;
	boolean detection = FALSE;
	for (i = 1; i <= numberofsquares; i++) {
		for (j = 1; j <= numberofsquares; j++) {
			if (i != j) {
				if (!detection && collisiondetection(box[i], box[j])) {
					std::cout << i << " " << j << " collision detected \n";
					box[i].xspeed = box[i].xspeed * -1;
					box[j].xspeed = box[j].xspeed * -1;
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
			box[i].x = box[i].x + box[i].xspeed;
			box[i].y = box[i].y + box[i].yspeed;
		}
	}

	//Checking for collisions
	boolean detection = FALSE;
	for (i = 1; i <= numberofsquares; i++) {
		for (j = 1; j <= numberofsquares; j++) {
			if (i != j) {
				if (!detection && collisiondetection(box[i], box[j])) {
					std::cout << i << " " << j << " collision detected \n";
					box[i].xspeed = box[i].xspeed * -1;
					box[j].xspeed = box[j].xspeed * -1;
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