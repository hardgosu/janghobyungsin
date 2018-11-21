#include "stdafx.h"


GLfloat xRotated, yRotated, zRotated;
GLdouble radius = 2;
GLfloat qaBlack[] = { 0.0, 0.0, 0.0, 1.0 }; //Black Color
GLfloat qaGreen[] = { 0.0, 1.0, 0.0, 1.0 }; //Green Color
GLfloat qaWhite[] = { 1.0, 1.0, 1.0, 1.0 }; //White Color
GLfloat qaRed[] = { 1.0, 0.0, 0.0, 1.0 }; //White Color

										  // Set lighting intensity and color
GLfloat qaAmbientLight[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat qaDiffuseLight[] = { 1, 1, 1, 1.0 };
GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat emitLight[] = { 0.9, 0.9, 0.9, 0.01 };
GLfloat Noemit[] = { 0.0, 0.0, 0.0, 1.0 };
// Light source position
GLfloat qaLightPosition[] = { 0, 0, 0, 1 };

void display(void);
void reshape(int x, int y);
void TimerFunc(int);
void DrawCube(void);

GLdouble sibal[16]

{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

void idleFunc(void)
{
	if (zRotated > 360.0) {
		zRotated -= 360.0*floor(zRotated / 360.0);   // Don't allow overflow
	}

	if (yRotated > 360.0) {
		yRotated -= 360.0*floor(yRotated / 360.0);   // Don't allow overflow
	}
	zRotated += 0.01;
	yRotated += 0.01;
	display();


}
void initLighting()
{

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Set lighting intensity and color
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	//glDisable(GL_LIGHTING);
	//glDisable(GL_LIGHT0);

}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(350, 350);
	glutCreateWindow("Solid Sphere");
	initLighting();

	xRotated = yRotated = zRotated = 0.0;

	glutIdleFunc(idleFunc);
	//glutTimerFunc(100,TimerFunc,1);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void display(void)
{


	glMatrixMode(GL_MODELVIEW);
	// clear the drawing buffer.
	glClear(GL_COLOR_BUFFER_BIT);
	// clear the identity matrix.
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -20.0);


	// 
	glPushMatrix();


	glTranslatef(0.0, 0.0, 0);
	// Set material properties
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, qaGreen);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, qaGreen);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, qaWhite);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.2);

	glutSolidSphere(radius, 25, 25);


	glPopMatrix();
	glPushMatrix();





	glRotatef(yRotated, 0.0, 1.0, 0.0);
	glTranslatef(5.0, 0.0, 0.0);

	// Set the light position
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emitLight);   // Make sphere glow (emissive) 
	glutSolidSphere(radius / 6, 25, 25);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, Noemit);



	glPopMatrix();
	glPushMatrix();




	glRotatef(yRotated - 20, 0.0, 1.0, 0.0);
	glTranslatef(-3.0, 0.0, 0.0);


	glutSolidCube(0.8);
	glPopMatrix();
	glPushMatrix();








	glPopMatrix();
	glPushMatrix();

	glTranslated(-0.5, -0.5, 0);
	glLoadMatrixd(sibal);

	glutWireCube(0.8);

	glPopMatrix();
	glPushMatrix();


	//DrawCube();



	glFlush();
	glutSwapBuffers();

}

void reshape(int x, int y)
{
	if (y == 0 || x == 0) return;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	printf("%d %d\n", x, y);

	gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.6, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering
}

void TimerFunc(int value) {
	printf("d");
	glutPostRedisplay();

	glutTimerFunc(1000 / 60, TimerFunc, 1);
}


void DrawCube(void)
{
	// Colour cube data.
	static GLuint polyList = 0;
	float fSize = 50.0f; //이 수치를 조정하면 큐브 사이즈를 바꿀 수 있다.
	long f, i;
	const GLfloat cube_vertices[8][3] = {
		{ 1.0, 1.0, 1.0 },{ 1.0, -1.0, 1.0 },{ -1.0, -1.0, 1.0 },{ -1.0, 1.0, 1.0 },
	{ 1.0, 1.0, -1.0 },{ 1.0, -1.0, -1.0 },{ -1.0, -1.0, -1.0 },{ -1.0, 1.0, -1.0 } };
	const GLfloat cube_vertex_colors[8][3] = {
		{ 1.0, 1.0, 1.0 },{ 1.0, 1.0, 0.0 },{ 0.0, 1.0, 0.0 },{ 0.0, 1.0, 1.0 },
	{ 1.0, 0.0, 1.0 },{ 1.0, 0.0, 0.0 },{ 0.0, 0.0, 0.0 },{ 0.0, 0.0, 1.0 } };
	GLint cube_num_faces = 6;
	const short cube_faces[6][4] = {
		{ 3, 2, 1, 0 },{ 2, 3, 7, 6 },{ 0, 1, 5, 4 },{ 3, 0, 4, 7 },{ 1, 2, 6, 5 },{ 4, 5, 6, 7 } };

	if (!polyList) {
		polyList = glGenLists(1);
		glNewList(polyList, GL_COMPILE);
		glBegin(GL_QUADS);
		for (f = 0; f < cube_num_faces; f++)
			for (i = 0; i < 4; i++) {
				glColor3f(cube_vertex_colors[cube_faces[f][i]][0], cube_vertex_colors[cube_faces[f][i]][1], cube_vertex_colors[cube_faces[f][i]][2]);
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
			}
		glEnd();
		glColor3f(0.0, 0.0, 0.0);
		for (f = 0; f < cube_num_faces; f++) {
			glBegin(GL_LINE_LOOP);
			for (i = 0; i < 4; i++)
				glVertex3f(cube_vertices[cube_faces[f][i]][0] * fSize, cube_vertices[cube_faces[f][i]][1] * fSize, cube_vertices[cube_faces[f][i]][2] * fSize);
			glEnd();
		}
		glEndList();
	}

	glPushMatrix(); // Save world coordinate system.
	glTranslatef(0.0, 0.0, 0.5); // Place base of cube on marker surface.
								 //glRotatef(gDrawRotateAngle, 0.0, 0.0, 1.0); // Rotate about z axis.
	glDisable(GL_LIGHTING); // Just use colours.
	glCallList(polyList); // Draw the cube.
	glPopMatrix(); // Restore world coordinate system.

}
