//#include "TextureBuilder.h"
#include <iostream>
#include <stdio.h>
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
using namespace std; //for using std::out and similar features

//global structs

//function signatures
void Display();
void Anim();
void setupCamera();

//global variables
//double r=1;
//int rd=1;

//double rw=1;
//double rl=1;

//bool w =true;
//bool rwb=false;
//bool rlb=false;

bool s=true;
bool l=true;
bool tex=true;

GLuint texEarthID;

//end of

//void drawWall(double w) {
//	glPushMatrix();
//	glScaled(w, w, 0.2);
//	glTranslated(0.5, 0.5, 0.5);
//	glutSolidCube(1);
//	glPopMatrix();
//}

void createBullet (){
    glPushMatrix();
//    glTranslated(0, 0 ,1.0); // cylinder at (0,0,1)
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj,GLU_LINE);  //GLU_FILL, GLU_SILHOUETTE ,GLU_POINT
    gluCylinder(qobj, 2, 2, 4, 100,100);
    glPopMatrix();
    
}

void setupLights() {
    
    
    GLfloat lmodel_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    
    GLfloat l0Diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat l0Ambient[] = { 0.1f, 0.0f, 0.0f, 1.0f };
    GLfloat l0Position[] = { 10.0f, 0.0f, 0.0f, static_cast<GLfloat>(s) };
    GLfloat l0Direction[] = { -1.0, 0.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
    glLightfv(GL_LIGHT0,GL_AMBIENT, l0Ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);
    
    GLfloat l1Diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    GLfloat l1Ambient[] = { 0.0f, 0.1f, 0.0f, 1.0f };
    GLfloat l1Position[] = { 0.0f, 10.0f, 0.0f, static_cast<GLfloat>(s) };
    GLfloat l1Direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_DIFFUSE, l1Diffuse);
    glLightfv(GL_LIGHT1,GL_AMBIENT, l1Ambient);
    glLightfv(GL_LIGHT1, GL_POSITION, l1Position);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 90.0);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1Direction);
    
    GLfloat l2Diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat l2Ambient[] = { 0.0f, 0.0f, 0.1f, 1.0f };
    GLfloat l2Position[] = { 0.0f, 0.0f, 10.0f, static_cast<GLfloat>(s) };
    GLfloat l2Direction[] = { 0.0, 0.0, -1.0 };
    glLightfv(GL_LIGHT2, GL_DIFFUSE, l2Diffuse);
    glLightfv(GL_LIGHT2,GL_AMBIENT, l2Ambient);
    glLightfv(GL_LIGHT2, GL_POSITION, l2Position);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 90.0);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, l2Direction);
    
    
}

void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
    gluPerspective(80, 640 / 480, 0.001, 100);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 10, 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    setupCamera();
//    setupLights();
    createBullet();
    
    glPopMatrix();
    
    
    
    glFlush();
}

void anim()
{
    glutPostRedisplay();
}

void keyUp(unsigned char k, int x,int y)//keyboard up function is called whenever the keyboard key is released
{
    if(k==27){
        glutReshapeWindow(1080,720);
    }
    glutPostRedisplay();//redisplay to update the screen with the changed
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(50, 50);
    
    glutCreateWindow("Aim and Shoot");
    glutDisplayFunc(Display);
    glutIdleFunc(anim);
    glutKeyboardUpFunc(keyUp);		//call the keyboard up function
    glutFullScreen();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_SMOOTH);
    //	glEnable(GL_TEXTURE_2D);
    //	loadBMP(&texEarthID, "textures/earth.bmp", false);
    
    
    
    glutMainLoop();
    return 0;
}
