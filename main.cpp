// Pong Game using GLUT and OpenGL
// Author: Chris Jenkins

#include <windows.h>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <DirectTraceAPI.h>
#include <iostream>

// boolean for ending the game 
bool quit = false;
bool playerReady = false;
// Values for Player 1's paddle in 3D
int p1PosX = 0;
int p1PosY = 0;
int p1PosZ = 13;

// Values for Player 2's paddle in 3D
// Positions it directly opposite P1
int p2PosX = 0;
//int p2PosY = -5;
int p2PosY = 32;
int p2PosZ = -13;

// Values for the Ball's position in 3D
// Positions it in the center of the scene
float ballPosX = 0;
float ballPosY = 0;
float ballPosZ = 0;

// value for movement along the x axis 
float xMovement = 1.0f;

// faces of the paddle (cuboid)
GLint faces[6][4] = {
		{ 0, 1, 3, 2 }, { 4, 5, 7, 6 }, //Back face and front 
		{ 0, 4, 6, 2 }, { 1, 3, 7, 5 }, //Left face and right face
		{ 0, 1, 5, 4 }, { 2, 3, 7, 6 }, //Bottom face and top face
};

// vertexes for the drawing of the paddle
GLfloat vertexes[8][3];  // array to store vertexes.

/*
* draws a paddle which can then be rendered in the display method
*/
void drawPaddle()
{
	for (int i = 0; i < 6; i++){

		glBegin(GL_QUADS);
		//glNormal3fv(n[i]);
		for (int j = 0; j<4; j++){
			GLfloat g[3] = { vertexes[faces[i][j]][0] * 2.0,
				vertexes[faces[i][j]][1] * 4.0,
				vertexes[faces[i][j]][2] * 1.0 };
			glVertex3fv(g);
		}
		glEnd();
	}
}

/*
* draws a ball which can then be rendered in the display method
*/
void drawBall(double r, int lats, int longs) {
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
		}
		glEnd();
	}
}

/*
* the display method that renders the scene
* (paddle 1, paddle 2 and the ball)
*/
void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* ball render starts*/
	glPushMatrix();
	//assigns green to the ball
	glColor3f(0.0, 1.0, 0.0);

	//allows the ball to be given a position in 3D space
	//the ball can be moved by modifying these values
	glTranslatef(ballPosX, ballPosY, ballPosZ);

	//draws the ball
	drawBall(1.0, 10, 10);
	glPopMatrix();
	/* ball render ends*/

	/* Player 1's paddle starts*/
	glPushMatrix();
	//assigns blue to Player 1's paddle
	glColor3f(0.0, 0.0, 1.0);

	//allows Player 1's paddle to be positioned in 3D
	//space and moved when keys are pressed
	glTranslatef(p1PosX, p1PosY, p1PosZ);

	//draws Player 1's paddle
	drawPaddle();
	glPopMatrix();
	/* Player 1's paddle ends*/

	/* Player 2's paddle starts*/
	glPushMatrix();
	//assigns red to Player 2's paddle
	glColor3f(1.0, 0.0, 0.0);

	//allows Player 2's paddle to be positioned in 3D
	//space and moved when keys are pressed
	glTranslatef(p2PosX, p2PosY, p2PosZ);

	//draws Player 2's paddle
	drawPaddle();
	glPopMatrix();
	/* Player 2's paddle ends*/
	glutSwapBuffers();
}

/*
* Initializes OpenGL and renders the camera
*/
void initGL()
{
	for (int i = 0; i < 8; i++)
	{
		//Set the x, y and z coordinates for the paddle
		vertexes[i][0] = (i & 1) * 2 - 1;
		vertexes[i][1] = (i >> 1 & 1) * 2 - 1;
		vertexes[i][2] = (i >> 2 & 1) * 2 - 1;
	}

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(100.0, //Field of view
		1.0, // Aspect ratio
		1.0, // Distance to the near clipping frame (z near)
		50.0);// Distance to the far clipping frame (z far)

	glMatrixMode(GL_MODELVIEW);

	gluLookAt(0.0, 0.0, 20.0,  // position of the eye point
		0.0, 0.0, 0.0,  // position of the reference point (center)
		0.0, 1.0, 0.);  // direction of the up vector

	// Rotates the world so that the paddle is correctly positioned 
	// the parameters are angle, x, y, z
	glRotatef(-20, 1.0, 0.0, .0);
	glRotatef(-90, 0.0, 0.0, 1.0);
	glRotatef(90, 0.0, 1.0, .0);

}

/*
* takes in Player 1 and 2's key presses and
* applies them to the game
*/
void keyboardInput(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_RIGHT: // Moves Player 1's paddle right 
		p1PosY += xMovement;
		std::cout << p1PosY;
		if (p1PosY >= 12){
			p1PosY = 12;
		}
		break;

	case GLUT_KEY_LEFT: // Moves Player 1's paddle left 
		p1PosY -= xMovement;
		std::cout << p1PosY;
		if (p1PosY <= -12){
			p1PosY = -12;
		}

		break;

	case GLUT_KEY_UP: // Quits the application when pressed
		quit = true;
		exit(0);
		break;

	case GLUT_KEY_PAGE_UP: // Moves Player 2's paddle right
		p2PosY += xMovement;
		if (p2PosY >= 24){
			p2PosY = 24;
		}
		break;

	case GLUT_KEY_PAGE_DOWN: // Moves Player 2's paddle left
		p2PosY -= xMovement;
		if (p2PosY <= -24){
			p2PosY = -24;
		}
		break;

		// repositions the camera
	case GLUT_KEY_F6:
		gluLookAt(0.0, 0.0, -20.0,  // position of the eye point
			0.0, 0.0, 0.0,  // position of the reference point (center)
			0.0, -1.0, 0.); // direction of the up vector
		break;

		// repositions the camera
	case GLUT_KEY_F7:
		gluLookAt(20.0, 0.0, 0.0,  // position of the eye point
			0.0, 0.0, 0.0,  // position of the reference point (center)
			0.2, 1.0, 1.9);  // direction of the up vector
		break;

		// repositions the camera
	case GLUT_KEY_F8:
		gluLookAt(0.0, 0.0, 20.0,  // position of the eye point
			0.0, 0.0, 0.0,  // position of the reference point (center)
			0.2, 1.0, 1.9);  // direction of the up vector
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

//{

//}

/*
*	Creates the window and loads the game
*/
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Pong Game");
	glutReshapeWindow(640, 480);
	glutDisplayFunc(display); //renders the scene
	glutIdleFunc(display); // updates the rendered scene 
	initGL();
	glutSpecialFunc(keyboardInput);


	// positions the ball where a collision with 
	// Player 1's paddle would occur 
	//do{

	//for (int i = 0; i < 12; i--){
	//ballPosY = i;
	//ballPosZ = i;
	//}
	//} while (quit = false);

	glutMainLoop();
	return 0;
}
