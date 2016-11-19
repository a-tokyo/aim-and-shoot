//#include "TextureBuilder.h"
#include <iostream>
#include <stdio.h>
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <math.h>
using namespace std; //for using std::out and similar features

//global structs
typedef struct vector {
    float x;
    float y;
    float z;
    vector(float x, float y, float z){
        this->x = x;
        this->y = y;
        this->z =z;
    }
    vector(){
        this->x = 0;
        this->y = 0;
        this->z =0;
    }
    std::string toString(){
        return "["+ std::to_string(x) + ", "+ std::to_string(y) + ", "+std::to_string(z)+"]" ;
    }
    vector unitVector(){
        float magnitude = sqrtf(pow(x,2)+pow(y,2)+pow(z,2));
        vector unitVector(x/magnitude,y/magnitude,z/magnitude);
        return unitVector;
    }
    float magnitude(){
        return sqrtf(pow(x,2)+pow(y,2)+pow(z,2));
    }
}vector;

//function signatures
void Display();
void Anim();
void setupCamera();

//global variables
//double r=1;
//int rd=1;

vector targetTranslation(0,0,1);

//double rw=1;
//double rl=1;

//bool w =true;
//bool rwb=false;
//bool rlb=false;

bool s=true;
bool l=true;
bool tex=true;

GLuint texEarthID;

//trials

int rotAngle = 0;

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
    glRotated(rotAngle, 1, 0,0);
    
    glPushMatrix();
    glColor3f(1, 0, 1);
    GLUquadricObj * qobj4;
    qobj4 = gluNewQuadric();
    gluCylinder(qobj4, 0.2, 2, 4, 100,100);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslated(0, 0, 4);
    GLUquadricObj * qobj3;
    qobj3 = gluNewQuadric();
    gluCylinder(qobj3, 2, 2, 8, 100,100);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0, 0, 8+4);
    GLUquadricObj * qobj2;
    qobj2 = gluNewQuadric();
    gluCylinder(qobj2, 2, 3, 5, 100,100);
    glPopMatrix();
    
    
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(0, 0, 5+8+4);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluCylinder(qobj, 3, 3, 12, 100,100);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(1,0.5,1);
    glTranslated(0, 0, 12+5+8+4);
    gluDisk(qobj, 0.001, 3, 32, 32);
    glPopMatrix();
    
    
    glPopMatrix();
    
}


void createGrenade (){
    // I swear these numbers are puuure luck, I don't understand anything in this course.
    //Oh and p.s: the learning objective of this is probably how to waste time mowahahaha
    glPushMatrix();
    glRotated(rotAngle, 1, 0, 0);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();

    glPushMatrix();
    glColor3f(1,0,0);
    glTranslated(0, 0, -12);
    gluDisk(qobj, 0.001, 3, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslated(0, 0, -12);
    gluCylinder(qobj, 3, 3, 3, 100,100);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1,1,0);
    glutSolidTorus(1, 10, 32, 100);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,0,1);
    glutSolidSphere(10, 100, 100);
    glPopMatrix();
    
    glPopMatrix();
}

void createShurikenPart (){
    glPushMatrix();
    
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 1);
    glVertex3f(5, 10, 0);
    glVertex3f(20, 20, 0.0f);
    glVertex3f(10,10, 3);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3f(10,10, 3);
    glVertex3f(20, 20, 0);
    glVertex3f(10, 5, 0.0f);
    
    glEnd();
    glPopMatrix();
    
    glPushMatrix();// square shape matrix
    glBegin(GL_POLYGON);
    glColor3f(0.6, 1, 0.3);
    glVertex3f(5, 5, 0);
    glVertex3f(10, 5, 0.0f);
    glVertex3f(10,10, 3);
    glVertex3f(5,10,0);
    glEnd();
    glPopMatrix();
    
    
    
    
    
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 1);
    glVertex3f(5, 10, 0);
    glVertex3f(20, 20, 0.0f);
    glVertex3f(10,10, -3);
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3f(10,10, -3);
    glVertex3f(20, 20, 0);
    glVertex3f(10, 5, 0.0f);
    
    glEnd();
    glPopMatrix();
    
    glPushMatrix();// square shape matrix
    glBegin(GL_POLYGON);
    glColor3f(0.6, 1, 0.3);
    glVertex3f(5, 5, 0);
    glVertex3f(10, 5, 0.0f);
    glVertex3f(10,10, -3);
    glVertex3f(5,10,0);
    glEnd();
    glPopMatrix();

    
    glPopMatrix();

}

void createShuriken(){
    glPushMatrix();
    glRotated(rotAngle, 1, 0, 0);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();

    glPushMatrix();
    createShurikenPart();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(240, 0, 0, 1);
    createShurikenPart();
    glPopMatrix();
    
    glPushMatrix();
    glRotated(120, 0, 0, 1);
    createShurikenPart();
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(0.4,0.4,0.4);
    glutSolidTorus(2, 5, 32, 100);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1,0,0);
    glRotated(60, 1, 1, 0);
    glutSolidCube(5);
    glPopMatrix();
    
    
    glPopMatrix();
}

void createWall (){
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(-70, -70, 0);
    glVertex3f(70, -70, 0.0f);
    glVertex3f(70,70, 0);
    glVertex3f(-70,70, 0);
    glEnd();
    glPopMatrix();
}

void createRoom (){
    //face
    glPushMatrix();
    glColor3f(1, 1, 0);
    createWall();
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 0, 1);
    glTranslated(35, 0, 0);
    glRotated(90, 0, 1, 0);
    createWall();
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0, 1, 1);
    glTranslated(-35, 0, 0);
    glRotated(90, 0, 1, 0);
    createWall();
    glPopMatrix();
    
    //ceiling
    glPushMatrix();
    glColor3f(0, 1, 0);
    glTranslated(0, 35, 0);
    glRotated(90, 1, 0, 0);
    createWall();
    glPopMatrix();
    
    //floor
    glPushMatrix();
    glColor3f(0.5, 0.5, 0);
    glTranslated(0, -35, 0);
    glRotated(90, 1, 0, 0);
    createWall();
    glPopMatrix();
    
}


void createTarget (){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    glPushMatrix();

    glPushMatrix();
    glColor3f(1, 0, 1);
    gluDisk(qobj, 0.001, 3, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluDisk(qobj, 3, 8, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0, 1, 1);
    gluDisk(qobj, 8, 15, 32, 32);
    glPopMatrix();
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
    gluPerspective(80, 640 / 480, 0.001, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 100, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glPushMatrix();
    setupCamera();
    setupLights();
    createRoom();
    
    glPushMatrix();
    glTranslated(targetTranslation.x, targetTranslation.y, targetTranslation.z);
    createTarget();
    glPopMatrix();


//    createBullet();
//    createGrenade();
//    createShuriken();
    
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
    if(k=='w'){
        targetTranslation.z++;
    }
    if(k=='s'){
        if(targetTranslation.z!=1)
            targetTranslation.z--;
    }
    if(k=='a'){
        targetTranslation.x--;
    }
    if(k=='d'){
        targetTranslation.x++;
    }
    glutPostRedisplay();//redisplay to update the screen with the changed
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Aim and Shoot");
    glutDisplayFunc(Display);
    glutIdleFunc(anim);
    glutKeyboardUpFunc(keyUp);		//call the keyboard up function
    glutFullScreen();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    
    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHT1);
//    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);
//    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_SMOOTH);
    //	glEnable(GL_TEXTURE_2D);
    //	loadBMP(&texEarthID, "textures/earth.bmp", false);
    
    
    
    glutMainLoop();
    return 0;
}
