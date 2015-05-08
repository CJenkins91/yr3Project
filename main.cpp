/*!
*Pong Game using GLUT and OpenGL
* Author: Chris Jenkins
*@file 3DPongGame.cpp
*@brief
*/

#include <windows.h>
#include <glut.h>
#include <time.h>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <DirectTraceAPI.h>
#include <irrKlang.h>
#include <iostream>
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")
//texture stuff
//left, right
int xBoundaries[2] = {18,-18};
//up, down
int zBoundaries[2] = {15,-15};

boolean collisionDetection = false;
boolean p1collisionDetection = false;
boolean p2collisionDetection = false;

//values for glutTimerFunction
int value = 0;
int milliseconds = 3;
//int x, y;
//left, right
int leftBoundary = 18;
int rightBoundary = -18;

int radius = 1;

int ballPosX = -12;
int ballPosY = 0;//-5
int ballPosZ = -5;

int p1PosX = 0;
int p1PosY = 0;
int p1PosZ = 15;

int p2PosX = 0;
int p2PosY = 0;
int p2PosZ = -15;

int closestX;
int closestZ;

GLUquadricObj *quadratic = NULL;

int xMovement1 = 1;
int xMovement = 1;
int zMovement = 1;

int p1Score = 0;
int p2Score = 0;

ISoundEngine* engine = createIrrKlangDevice();

// faces of the paddle (cuboid)
GLint faces[6][4] = {
		{ 0, 1, 3, 2 }, { 4, 5, 7, 6 }, //Back face and front 
		{ 0, 4, 6, 2 }, { 1, 3, 7, 5 }, //Left face and right face
		{ 0, 1, 5, 4 }, { 2, 3, 7, 6 }, //Bottom face and top face
};
GLfloat n[6][3] = {   // Normals
		{ 0, 0, -1 }, { 0, 0, 1 },  //Back and front
		{ 1, 0, 0 }, { -1, 0, 0 },   //Left and right
		{ 0, 1, 0 }, { 0, -1, 0 } }; //Bottom and top

// vertexes for the drawing of the paddle
GLfloat vertexes[8][3];  // array to store vertexes.


/*!
* draws a paddle which can then be rendered in the display method
*/
void drawPaddle()
{
	
	for (int i = 0; i < 6; i++){

		glBegin(GL_QUADS);
		glNormal3fv(n[i]);
		for (int j = 0; j<4; j++){
			GLfloat g[3] = { 
				//width
				//vertexes[faces[i][j]][0] * 2.0,
				//height
				//vertexes[faces[i][j]][1] * 4.0,
				//depth
				//vertexes[faces[i][j]][2] * 1.0 
				//width
				vertexes[faces[i][j]][0] * 5.0,
				//height
				vertexes[faces[i][j]][1] * 3.5,
				//depth
				vertexes[faces[i][j]][2] * 0.5
			};
			glVertex3fv(g);
		}
		glEnd();
	}
}

/*!
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

	glTranslatef(ballPosX, ballPosY, ballPosZ);
	
	gluSphere(quadratic, 1.0, 20, 16);
	//allows the ball to be given a position in 3D space
	//the ball can be moved by modifying these values
	
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

void setP1PaddlePosRight(){
	p1PosX -= xMovement1;
	if (p1PosX <= -18){
		p1PosX = -18;
	}
}

void setP1PaddlePosLeft(){
	p1PosX += xMovement1;
	if (p1PosX >= 18){
		p1PosX = 18;
	}
}

void setP2PaddlePosLeft(){
	p2PosX += xMovement1;
	if (p2PosX >= 18){
		p2PosX = 18;
	}
}

void setP2PaddlePosRight(){
	p2PosX -= xMovement1;
	if (p2PosX <= -18){
		p2PosX = -18;
	}
}


/*!
* takes in Player 1 and 2's key presses and
* applies them to the game
*@param int key;
*@param int x;
*@param int y;
*/
void keyboardInput(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_RIGHT: // Moves Player 1's paddle right 
		setP1PaddlePosRight();
		break;

	case GLUT_KEY_LEFT: // Moves Player 1's paddle left 
		setP1PaddlePosLeft();
		break;

	case GLUT_KEY_DOWN: // Quits the application when pressed
		exit(0);
		break;

	case GLUT_KEY_PAGE_UP: // Moves Player 2's paddle right
		setP2PaddlePosRight();
		break;

	case GLUT_KEY_PAGE_DOWN: // Moves Player 2's paddle left
		setP2PaddlePosLeft();
		break;

	default:
		break;
	}
	glutPostRedisplay();
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

	quadratic = gluNewQuadric();         // Create A Pointer To The Quadric Object  
	gluQuadricTexture(quadratic, GL_TRUE);      // Create Texture Coords  
	gluQuadricNormals(quadratic, GLU_SMOOTH);   // Create Smooth Normals  

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(200.0, //Field of view
		1.0, // Aspect ratio
		1.0, // Distance to the near clipping frame (z near)
		100.0);// Distance to the far clipping frame (z far)

	glMatrixMode(GL_MODELVIEW);
	
	gluLookAt(0.0, 0.0, 20.0,  // position of the eye point
		0.0, 0.0, 0.0,  // position of the reference point (center)
		0.0, 3.0, 0.);  // direction of the up vector
}

float getBallPosX(){
	return ballPosX;
}

float getBallPosZ(){
	return ballPosZ;
}

int getP1PaddlePosX(){
	return p1PosX;
}

int getP1PaddlePosZ(){
	return p1PosZ;
}

int getP2PaddlePosX(){
	return p2PosX;
}

int getP2PaddlePosZ(){
	return p2PosZ;
}

/*
* Applies movement to the ball 
*/
void ballMovement(){
	ballPosZ += zMovement;
	ballPosX += xMovement;

	if (p1collisionDetection == true){
		//std::cout << "wow it actually worked";
		zMovement -= zMovement;
		//std::cout << "collision occurred";
		xMovement -= xMovement;
		collisionDetection = false;
	}
	else{
		//std::cout << "nope";
	}
	if (p2collisionDetection == true){
		//std::cout << "wow it actually worked";
		zMovement -= zMovement;
		//std::cout << "collision occurred";
		xMovement += 4 * xMovement;
		collisionDetection = false;
	}
	else{
		//std::cout << "nope";
	}
}

void p1DetectionCollision(){
	int sphereCenter[2] = { getBallPosX(), getBallPosZ() }; //The centre of the sheet
	int boxCenter[2] = { getP1PaddlePosZ(), getP1PaddlePosZ() }; //The centre of the box
	int sphereCenterRelBox[2] = { (sphereCenterRelBox[0] = sphereCenter[0] - boxCenter[0]),
		(sphereCenterRelBox[1] = sphereCenter[1] - boxCenter[1]) };
	//difference between sphereCentre and boxCentre   
	int boxPoint[2] = {}; //nearest point on the box to the sphere
	int p1Width = 8; //width of player 1's paddle
	int p1Length = 3; //length of player 1's paddle

	//if the right side of the paddle is less than the difference
	if (sphereCenterRelBox[0] < -p1Width / 2.0){ boxPoint[0] = -p1Width / 2.0; }
	//else if the left side of the paddle is less than the difference
	else if (sphereCenterRelBox[0] > p1Width / 2.0){ boxPoint[0] = p1Width / 2.0; }
	//else the nearest point is the difference
	else{ boxPoint[0] = sphereCenterRelBox[0]; }
	//if the depth of the paddle is less than the difference 

	if (sphereCenterRelBox[1] < -p1Length / 2.0){ boxPoint[1] = -p1Length / 2.0; }
	//else if the depth of the paddle is more than the difference
	else if (sphereCenterRelBox[1] > p1Length / 2.0){ boxPoint[1] = p1Length / 2.0; }
	//else the nearest point is the difference
	else{ boxPoint[1] = sphereCenterRelBox[1]; }
	//distance is the difference between the relative distance and the nearest point  
	int distance[2] = { (distance[0] = sphereCenterRelBox[0] - boxPoint[0]),
		(distance[1] = sphereCenterRelBox[1] - boxPoint[1]) };
	//if the total distance is less than the radius squared then a collision has occurred
	if (distance[0] * distance[0] + distance[1] * distance[1] < radius*radius){
		engine->play2D("C:/Users/Chris/Desktop/collision.wav");
		zMovement = -zMovement;
		ballPosX = ballPosX + 4 * xMovement;
		ballPosZ = ballPosZ + 4 * zMovement;
	}
	//otherwise a collision has not occurred
	else{ p1collisionDetection = false; 
	if (ballPosZ > getP1PaddlePosZ()){
		engine->play2D("C:/Users/Chris/Desktop/pointScored.wav");
		p1Score += 1;
		std::cout << "p1Score = ";
		std::cout << p1Score;
		ballPosX = 0;
		ballPosZ = 0;
	}
	}
}

void p2DetectionCollision(){
	int sphereCenter[2] = { getBallPosX(), getBallPosZ() }; //The centre of the sheet
	int boxCenter[2] = { getP2PaddlePosX(), getP2PaddlePosZ() }; //The centre of the box
	int sphereCenterRelBox[2] = { (sphereCenterRelBox[0] = sphereCenter[0] - boxCenter[0]),
		(sphereCenterRelBox[1] = sphereCenter[1] - boxCenter[1]) };
	//difference between sphereCentre and boxCentre   
	int boxPoint[2] = {}; //nearest point on the box to the sphere
	int p2Width = 8; //width of player 1's paddle
	int p2Length = 3; //length of player 1's paddle

	//if the right side of the paddle is less than the difference
	if (sphereCenterRelBox[0] < -p2Width / 2.0){ boxPoint[0] = -p2Width / 2.0; }
	//else if the left side of the paddle is less than the difference
	else if (sphereCenterRelBox[0] > p2Width / 2.0){ boxPoint[0] = p2Width / 2.0; }
	//else the nearest point is the difference
	else{ boxPoint[0] = sphereCenterRelBox[0]; }
	//if the depth of the paddle is less than the difference 

	if (sphereCenterRelBox[1] < -p2Length / 2.0){ boxPoint[1] = -p2Length / 2.0; }
	//else if the depth of the paddle is more than the difference
	else if (sphereCenterRelBox[1] > p2Length / 2.0){ boxPoint[1] = p2Length / 2.0; }
	//else the nearest point is the difference
	else{ boxPoint[1] = sphereCenterRelBox[1]; }
	//distance is the difference between the relative distance and the nearest point  
	int distance[2] = { (distance[0] = sphereCenterRelBox[0] - boxPoint[0]),
		(distance[1] = sphereCenterRelBox[1] - boxPoint[1]) };
	//if the total distance is less than the radius squared then a collision has occurred
	if (distance[0] * distance[0] + distance[1] * distance[1] < radius*radius){
		engine->play2D("C:/Users/Chris/Desktop/collision.wav");
		zMovement = -zMovement;
		ballPosX = ballPosX - 4 * xMovement;
		ballPosZ = ballPosZ + 4 * zMovement;
	}
	//otherwise a collision has not occurred
	else{
		p2collisionDetection = false;
		if (getBallPosZ() < getP2PaddlePosZ()){
			engine->play2D("C:/Users/Chris/Desktop/collision.wav");
			p2Score += 1;
			std::cout << "p2Score = ";
			std::cout << p2Score;
			ballPosX = 0;
				ballPosZ = 0;
		}
	}
}	/* loops through ball movement and collisions
	*/
	void updateHandler(int seconds){
		ballMovement();
		p1DetectionCollision();
		p2DetectionCollision();

		if (rightBoundary <= getBallPosX()){
			xMovement -= xMovement;
			//engine->play2D("C:/Users/Chris/Desktop/collision.wav");
			Sleep(500);
		}
		else if (leftBoundary >= getBallPosX()){
			xMovement += xMovement;
			//engine->play2D("C:/Users/Chris/Desktop/collision.wav");
			Sleep(500);

		}
		if (p1Score >= 5){
			std::cout << "\np1 wins!";
			Sleep(1000);
			exit(0);

		}
		else if (p2Score >= 5){
			std::cout << "\np2 wins!";
			Sleep(1000);
			exit(0);
		}
		glutTimerFunc(milliseconds, &updateHandler, value);
		glutPostRedisplay();
	}

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

	glutTimerFunc(milliseconds, &updateHandler, value);
	initGL();
	glutSpecialFunc(keyboardInput);
	glutMainLoop();
	return 0;
}
