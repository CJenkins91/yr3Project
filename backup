/*!
*@file 3DPongGame.cpp
*Author: Chris Jenkins
*@brief - A 3D Pong Game using GLUT and OpenGL for
* rendering and irrKlang for sound effects.
*/

#include <windows.h>
#include <glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <DirectTraceAPI.h>
#include <irrKlang.h>
#include <iostream>
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

/**
* booleans for collisions against player 1 and 2's paddles
*/
boolean p1collisionDetection = false;
boolean p2collisionDetection = false;

//values for glutTimerFunction
int value = 0;
int milliseconds = 1;

//left and right boundaries
int leftBoundary = 18;
int rightBoundary = -18;

/*variables for the ball's x,y and z positions*/
int ballPosX = -12;
int ballPosY = 0;//-5
int ballPosZ = -5;
/*variables for player 1's x,y and z positions*/
int p1PosX = 0;
int p1PosY = 0;
int p1PosZ = 15;
/*variables for player 2's x,y and z positions*/
int p2PosX = 0;
int p2PosY = 0;
int p2PosZ = -15;

GLUquadricObj *ballQuadratic = NULL;

// radius of the ball
int radius = 1;
//value for the paddles' x movement
int paddleXMovement = 1;
// value for the ball's x movement
int xMovement = 1;
// value for the ball's z movement
int zMovement = 1;
// variables for player 1 and 2's scores 
int p1Score = 0;
int p2Score = 0;

// creates an instance of irrKlang
ISoundEngine* soundEngine = createIrrKlangDevice();


/**
*	values for rendering of the paddle,
*	reference - Single Cube  example - http://www.progzoo.net/wiki/C%2B%2B:Cuboids_Tutorial
*/
GLint faces[6][4] = { // faces of the paddle
		{ 0, 1, 3, 2 }, { 4, 5, 7, 6 }, //back face, front face, 
		{ 0, 4, 6, 2 }, { 1, 3, 7, 5 }, //left face, right face,
		{ 0, 1, 5, 4 }, { 2, 3, 7, 6 }, //bottom face, top face
};
GLfloat n[6][3] = {   // normals for the paddle
		{ 0, 0, -1 }, { 0, 0, 1 },  //back normal, front normal,
		{ 1, 0, 0 }, { -1, 0, 0 },   //left normal, right normal,
		{ 0, 1, 0 }, { 0, -1, 0 } }; //bottom normal, top normal

// vertexes for the drawing of the paddle
GLfloat vertexes[8][3];


/*!
* draws a paddle which can then be rendered in the display method
* reference - Single Cube  example - http://www.progzoo.net/wiki/C%2B%2B:Cuboids_Tutorial
*/
void drawPaddle()
{
	for (int i = 0; i < 6; i++){

		glBegin(GL_QUADS);
		glNormal3fv(n[i]);
		for (int j = 0; j<4; j++){
			GLfloat g[3] = {
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

/**
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
	gluSphere(ballQuadratic, 1.0, 20, 16);
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

/**
*	sets player 1's paddle right position and prevents
*	the paddle from moving beyond the game field
*/

void setP1PaddlePosRight(){
	p1PosX -= paddleXMovement;
	if (p1PosX <= -18){
		p1PosX = -18;
	}
}

/**
*	sets player 2's paddle left position and prevents
*	the paddle from moving beyond the game field
*/

void setP1PaddlePosLeft(){
	p1PosX += paddleXMovement;
	if (p1PosX >= 18){
		p1PosX = 18;
	}
}

/**
*	sets player 2's paddle left position and prevents
*	the paddle from moving beyond the game field
*/

void setP2PaddlePosLeft(){
	p2PosX += paddleXMovement;
	if (p2PosX >= 18){
		p2PosX = 18;
	}
}

/**
*	sets player 2's paddle right position and prevents
*	the paddle from moving beyond the game field
*/

void setP2PaddlePosRight(){
	p2PosX -= paddleXMovement;
	if (p2PosX <= -18){
		p2PosX = -18;
	}
}


/**
* takes in Player 1's key presses and
* applies them to the game
*@param int key;
*@param int x;
*@param int y;
*/
void glutKeyboardInput(int key, int x, int y)
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

void extraKeyboardInput(unsigned char otherKey, int x, int y)
{
	if (otherKey == 'w'){ // Moves Player 2's paddle right
		setP2PaddlePosRight();
	}

	if (otherKey == 'q'){ // Moves Player 2's paddle left
		setP2PaddlePosLeft();
	}
}

/**
* Initializes OpenGL and renders the camera
*/
void initGL()
{
	/**
	* sets the x,y and z coordinates of the paddles so
	* they can be drawn
	* reference - Single Cube  example - http://www.progzoo.net/wiki/C%2B%2B:Cuboids_Tutorial
	*/
	for (int i = 0; i < 8; i++)
	{

		vertexes[i][0] = (i & 1) * 2 - 1;
		vertexes[i][1] = (i >> 1 & 1) * 2 - 1;
		vertexes[i][2] = (i >> 2 & 1) * 2 - 1;
	}

	/*
	* sets up the quadratic for the ball, this would allow it
	* to have lighting effects applied to it.
	*/
	ballQuadratic = gluNewQuadric();
	gluQuadricTexture(ballQuadratic, GL_TRUE);
	gluQuadricNormals(ballQuadratic, GLU_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_PROJECTION);
	gluPerspective(200.0, 1.0, 1.0, 100.0);

	/**
	*gluPerspective(200.0, 1.0, 1.0, 100.0);
	*/

	glMatrixMode(GL_MODELVIEW);

	
	//close to new view
	/*
	gluLookAt(0.0, 0.0, 0.0,
		3.0, 0.0, 0.0,
		0.0, 0.0, 20.);
	*/



	//original camera
	
	gluLookAt(0.0, 0.0, 20.0,
		0.0, 0.0, 0.0,
		0.0, 3.0, 0.);
		
}

/**
*	gets the ball's x position
*/
float getBallPosX(){
	return ballPosX;
}

/**
*	gets the ball's z position
*/
float getBallPosZ(){
	return ballPosZ;
}

/**
*	gets player 1's x position
*/
int getP1PaddlePosX(){
	return p1PosX;
}

/**
*	gets player 1's z position
*/
int getP1PaddlePosZ(){
	return p1PosZ;
}

/**
*	gets player 2's x position
*/
int getP2PaddlePosX(){
	return p2PosX;
}

/**
*	gets player 2's z position
*/
int getP2PaddlePosZ(){
	return p2PosZ;
}

/**
* Applies movement to the ball
*/
void ballMovement(){
	ballPosZ += zMovement;
	ballPosX += xMovement;

	if (p1collisionDetection == true){
		zMovement -= zMovement;
		xMovement -= 4 * xMovement;
		if (ballPosZ == -15)
		{
			p1collisionDetection = false;
		}
	}

	if (p2collisionDetection == true){
		zMovement -= zMovement;
		xMovement += 4 * xMovement;

		if (ballPosZ == 15){
			p2collisionDetection = false;
		}
	}
}

/**
* Tests for collisions between the ball and player 1's paddle
* reference - http://www.gamedev.net/topic/335465-is-this-the-simplest-sphere-aabb-collision-test/
*/
void p1DetectionCollision(){
	int sphereCenter[2] = { getBallPosX(), getBallPosZ() }; //The centre of the sheet
	int boxCenter[2] = { getP1PaddlePosZ(), getP1PaddlePosZ() }; //The centre of the box
	int sphereCenterRelBox[2] = { (sphereCenterRelBox[0] = sphereCenter[0] -
		boxCenter[0]), (sphereCenterRelBox[1] = sphereCenter[1] - boxCenter[1]) };
	//difference between sphereCentre and boxCentre   
	int boxPoint[2] = {}; //nearest point on the box to the sphere
	int p1Width = 8; //width of player 1's paddle
	int p1Length = 3; //length of player 1's paddle

	if (getP1PaddlePosZ() > getBallPosZ()){
		return;
	}
	if (getP1PaddlePosX() - 4 < getBallPosX() && getP1PaddlePosX() + 4 > getBallPosX()){
		zMovement = -zMovement;

	}

	return;
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
		soundEngine->play2D("C:/Users/Chris/Documents/Visual Studio 2013/Projects/OpenGLProject1/OpenGLProject1/Collision.wav");
		zMovement += zMovement;
		ballPosX = ballPosX - 4 * xMovement;
		ballPosZ = ballPosZ - 4 * zMovement;
		p1collisionDetection = true;
	}
	//otherwise a collision has not occurred
	else{
		p1collisionDetection = false;
		if (ballPosZ > 25){
			soundEngine->play2D("C:/Users/Chris/Documents/Visual Studio 2013/Projects/OpenGLProject1/OpenGLProject1/PointScored.wav");
			p2Score += 1;
			std::cout << "Player 2 Score = ";
			std::cout << p2Score;
			ballPosX = 0;
			ballPosZ = 0;
		}
	}
}

/**
* Tests for collisions between the ball and player 2's paddle
* reference - http://www.gamedev.net/topic/335465-is-this-the-simplest-sphere-aabb-collision-test/
*/
void p2DetectionCollision(){
	int sphereCenter[2] = { getBallPosX(), getBallPosZ() }; //The centre of the sheet
	int boxCenter[2] = { getP2PaddlePosX(), getP2PaddlePosZ() }; //The centre of the box
	int sphereCenterRelBox[2] = { (sphereCenterRelBox[0] = sphereCenter[0] -
		boxCenter[0]), (sphereCenterRelBox[1] = sphereCenter[1] - boxCenter[1]) };
	//difference between sphereCentre and boxCentre   
	int boxPoint[2] = {}; //nearest point on the box to the sphere
	int p2Width = 8; //width of player 1's paddle
	int p2Length = 3; //length of player 1's paddle

	if (getP2PaddlePosZ() < getBallPosZ()){
		return;
	}
	if (getP2PaddlePosX()-4 < getBallPosX() && getP2PaddlePosX()+4 > getBallPosX()){
		zMovement = -zMovement;
	}





	return;
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
		soundEngine->play2D("C:/Users/Chris/Documents/Visual Studio 2013/Projects/OpenGLProject1/OpenGLProject1/Collision.wav");
		zMovement -= zMovement;
		ballPosX = ballPosX + 4 * xMovement;
		ballPosZ = ballPosZ + 4 * zMovement;
		p2collisionDetection = true;
	}
	//otherwise a collision has not occurred
	else{
		p2collisionDetection = false;
		if (ballPosZ < -25){
			soundEngine->play2D("C:/Users/Chris/Documents/Visual Studio 2013/Projects/OpenGLProject1/OpenGLProject1/PointScored.wav");
			p1Score += 1;
			std::cout << "Player 1 Score = ";
			std::cout << p1Score;
			ballPosX = 0;
			ballPosZ = 0;
		}
	}
}
/**
* updateHandler
* runs through the game loop
*/
void updateHandler(int milliseconds){
	//calls the ball movement and collision 
	//methods every iteration
	ballMovement();
	p1DetectionCollision();
	p2DetectionCollision();

	// If the ball collides with the right side of the game field
	if (rightBoundary <= getBallPosX()){
		xMovement -= xMovement;
		//soundEngine->play2D("C:/Users/Chris/Documents/Visual Studio 2013/Projects/OpenGLProject1/OpenGLProject1/Collision.wav");
		Sleep(500);
	}
	// If the ball collides with the left side of the game field
	else if (leftBoundary >= getBallPosX()){
		xMovement += xMovement;
		//soundEngine->play2D("C:/Users/Chris/Documents/Visual Studio 2013/Projects/OpenGLProject1/OpenGLProject1/Collision.wav");
		Sleep(500);

	}
	// If player 1's score equals 5 they win
	if (p1Score >= 5){
		std::cout << "\nPlayer 1 wins!";
		Sleep(3000);
		exit(0);

	}
	// If player 2's score equals 5 they win
	else if (p2Score >= 5){
		std::cout << "\nPlayer 2 wins!";
		Sleep(3000);
		exit(0);
	}
	glutTimerFunc(milliseconds, &updateHandler, value);
	glutPostRedisplay();
}

/**
*	Creates the window and loads the game, uses glut methods
*/
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Pong Game"); //sets the windows title
	glutReshapeWindow(640, 480); //sets the windows dimensions
	glutDisplayFunc(display); //initially renders the scene
	glutIdleFunc(display); // updates the rendered scene
	glutTimerFunc(milliseconds, &updateHandler, value); // runs the game loop
	initGL();
	glutKeyboardFunc(extraKeyboardInput);
	glutSpecialFunc(glutKeyboardInput); //gets keyboard input from the user
	glutMainLoop();
	return 0;
}
