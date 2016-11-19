//#include "TextureBuilder.h"
#include <iostream>
#include <stdio.h>
#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <math.h>
using namespace std; //for using std::out and similar features

// Function signatures
// Modeling
void createBullet();
void createGrenade();
void createShurikenPart();
void createShuriken();
void createWall();
void createRoom();
void createTarget();
// Gameplay
void drawCharacters();
void initGame();
void endGame();
// environment configurations
void setUpLights();
void setUpCamera();
// I/O
void passM(int x,int y);
void keyUp(unsigned char k, int x,int y);
// basic openGL
void Display();
void Anim();
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
typedef struct quadraple {
    float a;
    float x;
    float y;
    float z;
    quadraple(float a, float x, float y, float z){
        this-> a = a;
        this->x = x;
        this->y = y;
        this->z =z;
    }
    quadraple(){
        this-> a = 0;
        this->x = 0;
        this->y = 0;
        this->z =0;
    }
    std::string toString(){
        return "["+ std::to_string(a) + ", "+ std::to_string(x) + ", "+ std::to_string(y) + std::to_string(z)+"]" ;
    }
}quadraple;
typedef struct rgbColor {
    float r;
    float g;
    float b;
    rgbColor(float r, float g, float b){
        this->r = r;
        this->g = g;
        this->b =b;
    }
    rgbColor(){
        this->r = 1;
        this->g = 1;
        this->b =1;
    }
}rgbColor;
typedef struct character {
    vector *translation;
    quadraple *rotation;
    character(vector *translation, quadraple *rotation){
        this->translation = translation;
        this->rotation = rotation;
    }
    void setTranslation(vector toTranslate){
        translation->x = toTranslate.x;
        translation->y = toTranslate.y;
        translation->z = toTranslate.z;
    }
}character;

typedef struct mainCamera {

}mainCamera;


//global variables
//double r=1;
//int rd=1;

// mian characters
vector grenadeTranslation(0,3,0);
quadraple grenadeRotation(0,0,0,0);
character grenade(&grenadeTranslation, &grenadeRotation);

vector bulletTranslation(0,3,0);
quadraple bulletRotation(0,0,0,0);
character bullet(&bulletTranslation, &bulletRotation);


vector shurikenTranslation(0,3,0);
quadraple shurikenRotation(0,0,0,0);
character shuriken(&shurikenTranslation, &shurikenRotation);


vector targetTranslation(0,0,1);

bool gameOver = false;

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


//end of initializations

void createBullet (character* thisCharacter){
    glPushMatrix();
    glRotated(rotAngle, 1, 0,0); //REMOVE
    glRotated(thisCharacter->rotation->a ,thisCharacter->rotation->x, thisCharacter->rotation->y, thisCharacter->rotation->z);
    glTranslated(thisCharacter->translation->x, thisCharacter->translation->y, thisCharacter->translation->z);
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    GLUquadricObj * qobj4;
    qobj4 = gluNewQuadric();
    gluCylinder(qobj4, 0.2, 2, 3, 100,100);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(0, 0, 3);
    GLUquadricObj * qobj3;
    qobj3 = gluNewQuadric();
    gluCylinder(qobj3, 2, 2, 5, 100,100);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(0, 0, 5+3);
    GLUquadricObj * qobj2;
    qobj2 = gluNewQuadric();
    gluCylinder(qobj2, 2, 3, 4, 100,100);
    glPopMatrix();
    
    
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(0, 0, 5+4+3);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    gluCylinder(qobj, 3, 3, 7, 100,100);
    glPopMatrix();
    
    
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glTranslated(0, 0, 7+5+4+3);
    gluDisk(qobj, 0.001, 3, 32, 32);
    glPopMatrix();
    
    
    glPopMatrix();
    
}


void createGrenade (character* thisCharacter){
    // I swear these numbers are puuure luck, I don't understand anything in this course.
    //Oh and p.s: the learning objective of this is probably how to waste time mowahahaha
    glPushMatrix();
    glRotated(rotAngle, 1, 0, 0); //REMOVE
    glRotated(thisCharacter->rotation->a ,thisCharacter->rotation->x, thisCharacter->rotation->y, thisCharacter->rotation->z);
    glTranslated(thisCharacter->translation->x, thisCharacter->translation->y, thisCharacter->translation->z);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();

    glPushMatrix();
    glColor3f(0,0.5,0.3);
    glTranslated(0, 0, -12);
    gluDisk(qobj, 0.001, 3, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0.4,0.2);
    glTranslated(0, 0, -12);
    gluCylinder(qobj, 3, 3, 3, 100,100);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,0.4,0.2);
    glutSolidTorus(1, 10, 32, 100);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0.8,0.3);
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

void createShuriken(character* thisCharacter){
    glPushMatrix();
    glRotated(thisCharacter->rotation->a ,thisCharacter->rotation->x, thisCharacter->rotation->y, thisCharacter->rotation->z);
    glTranslated(thisCharacter->translation->x, thisCharacter->translation->y, thisCharacter->translation->z);
    glPushMatrix();
    glRotated(90, 1, 0, 0);
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
    glColor3f(0,0.6,1);
    createWall();
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.8,0.4,0.4);
    glTranslated(35, 0, 0);
    glRotated(90, 0, 1, 0);
    createWall();
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0.8,0.4,0.4);
    glTranslated(-35, 0, 0);
    glRotated(90, 0, 1, 0);
    createWall();
    glPopMatrix();
    
    //ceiling
    glPushMatrix();
    glColor3f(0.9,0.5,0.3);
    glTranslated(0, 35, 0);
    glRotated(90, 1, 0, 0);
    createWall();
    glPopMatrix();
    
    //floor
    glPushMatrix();
    glColor3f(0.9,0.5,0.3);
    glTranslated(0, -35, 0);
    glRotated(90, 1, 0, 0);
    createWall();
    glPopMatrix();
    
}


void createTarget (vector* translation){
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    glPushMatrix();
    glTranslated(translation->x, translation->y, translation->z);
    
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

void drawCharacters(){
    createRoom();
    createTarget(&targetTranslation);
//        createBullet(&bullet);
    //    createGrenade(&grenade);
        createShuriken(&shuriken);
}

void initGame(){
}

void endGame(){
    glutReshapeWindow(1080,720);
    gameOver = true;
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
    
    if(!gameOver){
        setupCamera();
        setupLights();
    
        drawCharacters();
    }
    
    glPopMatrix();
    glFlush();
}

void anim()
{
    glutPostRedisplay();
}

void passM(int x,int y){

}


void keyUp(unsigned char k, int x,int y)//keyboard up function is called whenever the keyboard key is released
{
    if(k==27){
        endGame();
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
    if(k=='o'){
        rotAngle-=3;
    }
    if(k=='p'){
        rotAngle+=3;
    }
    glutPostRedisplay();//redisplay to update the screen with the changed
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Aim and Shoot");
    glutFullScreen();
    glutDisplayFunc(Display);
    glutIdleFunc(anim);
    glutPassiveMotionFunc(passM); // call passive motion function for mouse movements
    glutKeyboardUpFunc(keyUp);		//call the keyboard up function
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
    
    initGame();
    
    glutMainLoop();
    return 0;
}
