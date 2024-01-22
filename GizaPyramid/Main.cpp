#include <glut.h>
#include <math.h>

//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

double objR = 0.0;
double sceneX = 0.0;
double sceneZ = 0.0;
double rotateSceneY = 0.0;

constexpr float PI = 3.14159265358979323846;

//Vertices of the objects
float vertices[][3] = {
{1,1,-1},{-1,1,-1},{-1,1,1},{1,1,1}, //Cube coordinates
{1,-1,-1},{1,-1,1},{-1,-1,1},{-1,-1,-1},
{0,1,0},                              //Pyramid apex
{1,0,-1},{0,1,-1},{-1,0,-1},{0,-1,-1},//3D octagon coordinates
{-1,1,0},{-1,0,1},{-1,-1,0},
{0,-1,1},{1,0,1},{0,1,1},
{1,1,0},{1,-1,0}
};

void drawGrid() {
	GLfloat step = 1.0f;
	GLint line;

	glBegin(GL_LINES);
	for (line = -20; line <= 20; line += step) {
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);

		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
	}
	glEnd();
}

void drawAxes() {

	glBegin(GL_LINES);

	glLineWidth(1.5);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -200, 0);
	glVertex3f(0, 200, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -200);
	glVertex3f(0, 0, 200);

	glEnd();
}

void init(void) {
	glClearColor(0.14, 0.58, 0.75, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

void setLighting() {
	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Set lighting intensity and color
	// Set lighting intensity and color for sunlight-like effect
	GLfloat qaAmbientLight[] = { 0.7, 0.7, 0.6, 1.0 };  // Slightly warm ambient light
	GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.7, 1.0 };  // Diffuse light with a warm tint
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };  // White specular light


	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position
	GLfloat qaLightPosition[] = { -500.0, -100.0, -400.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	//set light 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);

	//Set the light position
	GLfloat qaLightPosition2[] = { -500.0, -500.0, -400.0, 0.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition2);

}

//Draw a quandrangle surface
void surface4(int v1, int v2, int v3, int v4) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glVertex3fv(vertices[v4]);
	glEnd();
}

//Draw a triangle surface
void surface3(int v1, int v2, int v3) {
	glBegin(GL_POLYGON);
	glVertex3fv(vertices[v1]);
	glVertex3fv(vertices[v2]);
	glVertex3fv(vertices[v3]);
	glEnd();
}

//Draw a pyramid
void drawPyramid() {
	//Base (square)
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0); // Normal for the base
	glVertex3fv(vertices[4]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[5]);
	glEnd();

	//4 sides (triangles)
	glBegin(GL_TRIANGLES);
	glNormal3f(0, 0, -1); // Normal for the front face
	glVertex3fv(vertices[8]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[5]);

	glNormal3f(1, 0, 0); // Normal for the right face
	glVertex3fv(vertices[8]);
	glVertex3fv(vertices[6]);
	glVertex3fv(vertices[7]);

	glNormal3f(0, 0, 1); // Normal for the back face
	glVertex3fv(vertices[8]);
	glVertex3fv(vertices[7]);
	glVertex3fv(vertices[4]);

	glNormal3f(-1, 0, 0); // Normal for the left face
	glVertex3fv(vertices[8]);
	glVertex3fv(vertices[5]);
	glVertex3fv(vertices[4]);
	glEnd();
}

void drawLand() {
	GLint line;

	glBegin(GL_POLYGON);
	glColor3f(0.14, 0.58, 0.74);
	for (line = -20; line <= 20; line += 20) {
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);
		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
	}
	glEnd();

}

void drawPyramidWithLighting() {
	glShadeModel(GL_FLAT);

	// Set material properties
	GLfloat qaPyramid_light[] = { 0.76,0.59,0.36,1.0 };
	GLfloat qaPyramid[] = { 0.47,0.3,0.14 };
	GLfloat qaLowAmbient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaFullAmbient[] = { 1.0, 1.0, 1.0, 1.0 };


	//Set, ambient, diffuse and specular lighting. Set ambient to 20%.
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaPyramid);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, qaPyramid);
	glMaterialfv(GL_FRONT, GL_SPECULAR, qaPyramid_light);
	glMaterialf(GL_FRONT, GL_SHININESS, 10.0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaLowAmbient);
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaLowAmbient);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	for (int iIndex = 0; iIndex < 6; ++iIndex) {

		glPushMatrix();
		float translate = 2.0;
		float translate_addition = iIndex * 4;


		glRotated(objR, 0.0, 1.0, 0.0);
		
		if (iIndex < 3) {
			glTranslatef(3.0 + (translate_addition), 2.0, -2.0 - (translate_addition / 2.2));
			glScaled(2.5, 2.2, 2.5);
			
			if (iIndex == 1) {
				glTranslatef(0.0, 0.5, 0.0);
				glScaled(1.4, 1.4, 1.4);
			}
			if (iIndex == 2) {
				glTranslatef(1.0, 0.0, 0.5);
			}
		}
		else {
			glTranslated(-8.0 + (translate_addition/1.5), 0.5, 1.3);
		}
	
		drawPyramid();
		glPopMatrix();
	}

	glPushMatrix();
	drawLand();
	glPopMatrix();

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(-2.0, 2.0 + camY, 6.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);

	////draw a grid on the xz plane
	glColor3f(1, 1, 1);
	drawGrid();
	////draw the three axes
	drawAxes();

	setLighting();
	glPushMatrix();
	drawPyramidWithLighting();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w/1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Define the Perspective projection frustum
	// (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
	gluPerspective(120.0, aspect_ratio, 1.0, 100.0);
}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camY += 1;

	if (key == GLUT_KEY_DOWN)
		camY -= 1;

	if (key == GLUT_KEY_RIGHT)
		sceTX += 1;

	if (key == GLUT_KEY_LEFT)
		sceTX -= 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	//obj rotate clockwise
	if (key == 'l') {
		objR++;
	}
	//obj rotate anti-clockwise
	if (key == 'r') {
		objR--;
	}

	if (key == 'z') {
		sceneZ++;
	}
	if (key == 'Z') {
		sceneZ--;
	}

	if (key == 'y') {
		camY++;
	}
	if (key == 'Y') {
		camY--;
	}

	if (key == 'v') {
		rotateSceneY++;
	}
	if (key == 'V') {
		rotateSceneY--;
	}


	glutPostRedisplay();
}


int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Complex 3D Shapes");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}