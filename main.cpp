// Pong Game using GLUT and OpenGL
// Author: Chris Jenkins


#include <windows.h>
#include <glut.h>
#include <time.h>
#include <string>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
//#include <DirectTraceAPI.h>
#include <iostream>

//texture stuff
//left, right
int xBoundaries[2] = {18,-18};
//up, down
int zBoundaries[2] = {15,-15};

boolean collisionDetection = false;
boolean p1collisionDetection = false;
boolean p2collisionDetection = false;



boolean positive = true;
boolean negative = false;

#define MILLISECONDS_PER_FRAME 20
int x, y;
//left, right
int leftBoundary = 18;
int rightBoundary = -18;
//down, up
int downBoundary = 20;
int upBoundary = -20;

int radius = 1;


int ballPosX = -12;
int ballPosY = 0;//-5
int ballPosZ = -5;


char* s = "fps: 30";
char *string = "fps: ";
int loseTimer;

//char[] fpsstring;

bool notCollision = false;

int mouseX;
int mouseY;
float orientationMatrix[16];

// boolean for ending the game 
bool quit = false;
bool playerReady = false;
// Values for Player 1's paddle in 3D


int p1PosX = 0;
int p1PosY = 0;
int p1PosZ = 15;


int p2PosX = 0;
int p2PosY = 0;
int p2PosZ = -15;

int p1PaddleFront = p1PosZ;
int p1PaddleLeft = p1PosX+8;
int p1PaddleRight = p1PosX-8;
int p1PaddleBack = p1PosZ + 3;

int p2PaddleFront = p2PosZ;
int p2PaddleLeft = p2PosX+8;
int p2PaddleRight = p2PosX-8;
int p2PaddleBack = p2PosZ - 3;

int ballFront = ballPosZ - 1;
int ballLeft = ballPosX + 1;
int ballRight = ballPosX - 1;
int ballDown = ballPosZ + 1;

//int ballXYZ[3] = {ballPosX,ballPosY,ballPosZ};
//int p1XYZ[3] = {p1PosX,p1PosY,p1PosZ};
//int p2XYZ[3] = {p2PosX,p2PosY,p2PosZ};

int closestX;
int closestZ;

int frame = 0;
int currentTime = 0;
int oldTime = 0;
int font = (int)GLUT_BITMAP_8_BY_13;

GLUquadricObj *quadratic = NULL;

float r = 0.5;
float s1 = 0.5;
float s2 = 0.5;
// Values for Player 2's paddle in 3D
// Positions it directly opposite P1


// Values for the Ball's position in 3D
// Positions it in the center of the scene


float LiPosX = 7; //9
float LiPosY = 0;
float LiPosZ = 4; //6

float LiPosX1 = 7; //9
float LiPosY1 = 0;
float LiPosZ1 = -2; //0

float LiPosX2 = 7; //9
float LiPosY2 = 0;
float LiPosZ2 = -4; //-6

float LiPosX3 = -2; //0
float LiPosY3 = 0;
float LiPosZ3 = 4; //6

float LiPosX4 = -7; //-9
float LiPosY4 = 0;
float LiPosZ4 = -4; //-6

float LiPosX5 = -7; //-9
float LiPosY5 = 0;
float LiPosZ5 = -2; //0

float LiPosX6 = -7; //-9
float LiPosY6 = 0;
float LiPosZ6 = 4; //6

float LiPosX7 = -2; //0
float LiPosY7 = 0;
float LiPosZ7 = 4; //6



int fps = 0;

float deltaTime = 0.5;
// value for movement along the x axis 
int xMovement1 = 1;
//float xMovement1 = 3.0f;
//float xMovement = 0.2f;
int xMovement = 1;
int zMovement = 1;
bool startGame = false;
int futureBallPosX = 0;
int currentBallPosX = ballPosX;
int direction[2] = { currentBallPosX, futureBallPosX};

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

void mouse(int button, int state, int x, int y)
{
	//Record the mouse location when a button is pushed down
	mouseX = x;
	mouseY = y;
}


/*
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

void updateFPS(){
	frame++;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	if (currentTime - oldTime > 1000){
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (currentTime - oldTime));
		//fps = frame*1000.0 / (currentTime - oldTime);
		oldTime = currentTime;;
		frame = 0;
	}
}

/*void renderBitmapString(float x, float y, void *font)
{
	//std::string fullString = s;
	glRasterPos2f(x, y);
	for (int c = 0; c < sizeof(s); c++)
	{
		//std::cout << c;
		glutBitmapCharacter(font, s[c]);
	}
}
*/
/*
void displayFPS(){
	renderBitmapString(30, 35, (void*)font, s);
}
*/


/*
* the display method that renders the scene
* (paddle 1, paddle 2 and the ball)
*/
void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1, 1, 1, 1);
	/*
	frame++;
	currentTime = glutGet(GLUT_ELAPSED_TIME);
	if (currentTime - oldTime > 1000){
		sprintf(s, "FPS:%4.2f", frame*1000.0 / (currentTime - oldTime));
		oldTime = currentTime;;
		frame = 0;
	}



	glPushMatrix();
	//glLoadIdentity();
	//glColor3f(0.0f, 1.0f, 1.0f);
	renderBitmapString(30, 35, (void*)font, s);
	glPopMatrix();

	glutSwapBuffers();
	*/
	/* ball render starts*/
	glPushMatrix();
	//assigns green to the ball
	glColor3f(0.0, 1.0, 0.0);
	//drawBall(r, s1, s2, quad);
	//glutWireSphere(r, s1, s2);
	
	
	
	//glTranslatef(ballPosX, ballPosY, ballPosZ);
	glTranslatef(ballPosX, ballPosY, ballPosZ);
	
	
	
	//drawBall(1.0,5,5);
	//Sphere(5);
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
	//glPushMatrix();
							//renderBitmapString(110, -105, (void*)font);
	//glPopMatrix();
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

/*
* takes in Player 1 and 2's key presses and
* applies them to the game
*/
void keyboardInput(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_RIGHT: // Moves Player 1's paddle right 
		setP1PaddlePosRight();
		//ballPosX -= xMovement;
		break;

	case GLUT_KEY_LEFT: // Moves Player 1's paddle left 
		setP1PaddlePosLeft();
		//ballPosX += xMovement;
		break;

	case GLUT_KEY_UP: // Quits the application when pressed
		//quit = true;
		//exit(0);
		//ballPosY -= xMovement;
		break;

	case GLUT_KEY_DOWN: // Quits the application when pressed
		quit = true;
		exit(0);
		break;

	case GLUT_KEY_PAGE_UP: // Moves Player 2's paddle right
		setP2PaddlePosRight();

		break;

	case GLUT_KEY_PAGE_DOWN: // Moves Player 2's paddle left
		setP2PaddlePosLeft();
		break;

		// repositions the camera
	case GLUT_KEY_F6:
		/*
		gluLookAt(0.0, 0.0, -20.0,  // position of the eye point
			0.0, 0.0, 0.0,  // position of the reference point (center)
			0.0, -1.0, 0.); // direction of the up vector
		*/
		//LiPosX += 10;
		break;

		// repositions the camera
	case GLUT_KEY_F7:
		/*
		gluLookAt(20.0, 0.0, 0.0,  // position of the eye point
			0.0, 0.0, 0.0,  // position of the reference point (center)
			0.2, 1.0, 1.9);  // direction of the up vector
		*/
		//LiPosX -= 10;
		//glDisable(GL_LIGHT2);
		break;

		// repositions the camera
	case GLUT_KEY_F8:
		/*
		gluLookAt(0.0, 0.0, 20.0,  // position of the eye point
			0.0, 0.0, 0.0,  // position of the reference point (center)
			0.2, 1.0, 1.9);  // direction of the up vector
		*/
		//LiPosY += 10;
		//glEnable(GL_LIGHT2);
		playerReady = true;
		mouseX -= 1;
		mouseY -= 1;
		break;

	case GLUT_KEY_F9:
		mouseX += 1;
		mouseY += 1;
		//LiPosY -= 10;
		break;

	case GLUT_KEY_F10:
		//Turn light off
		//glDisable(GL_LIGHT0);
		//startGame = false;
		
		/*
		if (ballPosZ > p1PosZ){
			std::cout << "Player 2 gets a point/n";
		}
		*/
		break;

	case GLUT_KEY_F11:
		//Turn light on
		//glEnable(GL_LIGHT0);
		//startGame = true;
		ballPosX -= xMovement;
		ballPosZ -= xMovement;
		/*
		if (ballPosZ < p2PosZ){
			std::cout << "Player 1 gets a point/n";
		}
		*/
		break;

	default:
		break;
	}
	glutPostRedisplay();
}

void InitMatrix(float *m)
{
	int i;
	for (i = 0; i<16; i++)
		m[i] = 0;
	m[0] = m[5] = m[10] = m[15] = 1.;
}



void motion(int x, int y)
{
	//Perform a rotation. The new orientation matrix should be  m_orientation=m_orientation*m_mouse_interaction
	//Where m_mouse_interaction is representative of the mouse interactions in the image plane
	//This part was quickly coded. Improvement could be done with quaternions...

	glMatrixMode(GL_MODELVIEW);//Use OpenGL capabilites to multiply matrices. The modelview Matrix is used here
	glLoadIdentity();
	glRotatef(sqrt((float)((x - mouseX)*(x - mouseX) + (y - mouseY)*(y - mouseY))), (y - mouseY), (x - mouseX), 0); //Rotation around an inclined axis
	glMultMatrixf(orientationMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, orientationMatrix); //Get the multiplied matrix
	mouseX = x;	//Reinitialize the new position	
	mouseY = y;
	glutPostRedisplay();// Generates a refresh event (which will call draw)
}

//{

//}

//int distance = 0;


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

	/*
	void subdivide(float *v1, float *v2, float *v3)
	{
		GLfloat v12[3], v23[3], v31[3];
		GLint i;

		for (i = 0; i < 3; i++) {
			v12[i] = v1[i] + v2[i];
			v23[i] = v2[i] + v3[i];
			v31[i] = v3[i] + v1[i];
		}
		normalize(v12);
		normalize(v23);
		normalize(v31);
		drawtriangle(v1, v12, v31);
		drawtriangle(v2, v23, v12);
		drawtriangle(v3, v31, v23);
		drawtriangle(v12, v23, v31);
	}

	for (int i = 0; i < 20; i++) {
		subdivide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0]);
	}
	*/
	glEnable(GL_DEPTH_TEST);
	

	//glutMouseFunc(mouse);
	//glutMotionFunc(motion);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(200.0, //Field of view
		1.0, // Aspect ratio
		1.0, // Distance to the near clipping frame (z near)
		100.0);// Distance to the far clipping frame (z far)

	glMatrixMode(GL_MODELVIEW);
	
	gluLookAt(0.0, 0.0, 20.0,  // position of the eye point
		0.0, 0.0, 0.0,  // position of the reference point (center)
		0.0, 3.0, 0.);  // direction of the up vector
		
	
	
	// Rotates the world so that the paddle is correctly positioned 
	// the parameters are angle, x, y, z
	//glRotatef(-20, 1.0, 0.0, .0);
	//glRotatef(-90, 0.0, 0.0, 1.0);
	//glRotatef(90, 0.0, 1.0, .0);

}

void passiveMotionFunc(void(*func)(int button, int state, int x, int y)){
	p1PosX = x;
	p1PosY = y;
}

void setPlusBallPosZ(){

	std::cout << "ballPosZ = ";
	std::cout << ballPosZ;
	Sleep(500);
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

void setMinusBallPosX()
{
	ballPosX -= xMovement;
}

void setMinusBallPosZ()
{
	ballPosZ -= xMovement;
}

void setPlusBallPosX(){
	}


void ballMovement(){
	if (p1collisionDetection == true){
		//std::cout << "wow it actually worked";
		zMovement -= zMovement;
		std::cout << "collision occurred";
		xMovement += 4 * xMovement;
		collisionDetection = false;
	}
	else{
		std::cout << "nope";
	}
	/*
	else if (collisionDetection == false){
		xMovement += xMovement;
		zMovement += zMovement;
	}
	*/
	if (p2collisionDetection == true){
		//std::cout << "wow it actually worked";
		zMovement -= zMovement;
		std::cout << "collision occurred";
		xMovement += 4 * xMovement;
		collisionDetection = false;
	}
	else{
		std::cout << "nope";
	}
	if (rightBoundary >= ballPosX ){
		xMovement += xMovement;
		
		//play sound
	}
	else if (leftBoundary <= ballPosX){
		xMovement -= xMovement;
		
		//play sound
	}


	ballPosZ += zMovement;
	ballPosX += xMovement;
	std::cout << zMovement;
	std::cout << xMovement;
}

void p1DetectionCollision(){
	int sphereCenter[2] = { ballPosX, ballPosZ }; //The centre of the sheet
	int boxCenter[2] = { p1PosX, p1PosZ }; //The centre of the box
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
		zMovement = -zMovement;
		ballPosX = ballPosX + 4 * xMovement;
		ballPosZ = ballPosZ + 4 * zMovement;
		//collisionDetection = true;
		std::cout << "ballPosX: ";
		std::cout << ballPosX;
		std::cout << "ballPosZ: ";
		std::cout << ballPosZ;
	}
	//otherwise a collision has not occurred
	else{ p1collisionDetection = false; }
}

void p2DetectionCollision(){
	int sphereCenter[2] = { ballPosX, ballPosZ }; //The centre of the sheet
	int boxCenter[2] = { p2PosX, p2PosZ }; //The centre of the box
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
		zMovement = -zMovement;
		ballPosX = ballPosX + 4 * xMovement;
		ballPosZ = ballPosZ + 4 * zMovement;
		//collisionDetection = true;
		std::cout << "ballPosX: ";
		std::cout << ballPosX;
		std::cout << "ballPosZ: ";
		std::cout << ballPosZ;
	}
	//otherwise a collision has not occurred
	else{ p2collisionDetection = false; }
}

	void updateHandler(int seconds){
		ballMovement();
		p1DetectionCollision();
		p2DetectionCollision();
		//checkPaddleCollisions();
		//checkOtherCollisions();
		//handleCollision();
		//collisionDetection();
		
		
		if (rightBoundary <= ballPosX){
			xMovement -= xMovement;
			//std::cout << xMovement;
			Sleep(500);
			//play sound
		}
		else if (leftBoundary >= ballPosX){
			xMovement -= xMovement;
			//std::cout << xMovement;
			Sleep(500);
			//play sound
		}


		ballPosZ += zMovement;
		//std::cout << zMovement;

	
		bool p1Collision = false;
		bool p2Collision = false;

		//ballPosX += xMovement;
		
		//ballPosZ += zMovement;
		

		 
		
		
	glutTimerFunc(3, &updateHandler, 0);
	glutPostRedisplay();
}

/*
*	Creates the window and loads the game
*/
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(s);
	glutReshapeWindow(640, 480);
	glutDisplayFunc(display); //renders the scene
	glutIdleFunc(display); // updates the rendered scene

	glutTimerFunc(3, &updateHandler, 0);
	initGL();
	glutSpecialFunc(keyboardInput);
	InitMatrix(orientationMatrix);
	updateFPS();
	glutMainLoop();
	return 0;
}
