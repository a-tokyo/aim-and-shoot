#include <OpenGl/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std; //for using std::out and similar features
#define PI 3.14159265
#define toDeg 57.2957795131

//global structs
typedef struct vector {
    float x;
    float y;
    float z;
    vector(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z =z;
    }
    vector() {
        this->x = 0;
        this->y = 0;
        this->z =0;
    }
    std::string toString() {
        return "["+ std::to_string(x) + ", "+ std::to_string(y) + ", "+std::to_string(z)+"]" ;
    }
    vector unitVector() {
        float magnitude = sqrtf(pow(x,2)+pow(y,2)+pow(z,2));
        vector unitVector(x/magnitude,y/magnitude,z/magnitude);
        return unitVector;
    }
    void set(float newx, float newy, float newz) {
        x = newx;
        y = newy;
        z = newz;
    }
    void set(vector* vector) {
        x = vector->x;
        y = vector->y;
        z = vector->z;
    }
    float magnitude() {
        return sqrtf(pow(x,2)+pow(y,2)+pow(z,2));
    }
} vector;
typedef struct quadraple {
    float a;
    float x;
    float y;
    float z;
    quadraple(float a, float x, float y, float z) {
        this-> a = a;
        this->x = x;
        this->y = y;
        this->z =z;
    }
    quadraple() {
        this-> a = 0;
        this->x = 0;
        this->y = 0;
        this->z =0;
    }
    void set(float a, float x, float y, float z) {
        this-> a = a;
        this->x = x;
        this->y = y;
        this->z =z;
    }
    void set(quadraple* quadraple) {
        this-> a = quadraple->a;
        this->x = quadraple->x;
        this->y = quadraple->y;
        this->z = quadraple->z;
    }
    std::string toString() {
        return "["+ std::to_string(a) + ", "+ std::to_string(x) + ", "+ std::to_string(y) + std::to_string(z)+"]" ;
    }
} quadraple;
typedef struct character {
    vector *translation;
    quadraple *rotation;
    quadraple *deepRotation;
    vector *firingInitialTranslation;
    quadraple *firingInitialRotation;
    bool isFiring;
    bool hasFired;
    float bezierTranslation;
    vector bezierTranslationPoints [4];
    character(vector *translation, quadraple *rotation, quadraple *deepRotation, vector *firingInitialTranslation, quadraple *firingInitialRotation) {
        this->translation = translation;
        this->rotation = rotation;
        this->deepRotation = deepRotation;
        this->firingInitialTranslation = firingInitialTranslation;
        this->firingInitialRotation = firingInitialRotation;
        this->isFiring = false;
        this->hasFired = false;
    }
    void setTranslation(vector toTranslate) {
        translation->x = toTranslate.x;
        translation->y = toTranslate.y;
        translation->z = toTranslate.z;
    }
    void setRotation(quadraple toRotate) {
        rotation->a = toRotate.a;
        rotation->x = toRotate.x;
        rotation->y = toRotate.y;
        rotation->z = toRotate.z;
    }
    void setRotation(float a, float x, float y, float z) {
        rotation->a = a;
        rotation->x = x;
        rotation->y = y;
        rotation->z = z;
    }
    void resetAttrs() {
        this->bezierTranslation = 0;
        this->isFiring = false;
        this->hasFired = false;
    }
} character;

typedef struct scoreBoardTarget {
    vector *translation;
    double radius;
    scoreBoardTarget(vector *translation, double radius) {
        this->translation = translation;
        this->radius = radius;
    }
} scoreBoardTarget;

typedef struct gameStatus {
    std::string gameMode;
    int currCharacter;
    bool gameOver;
    bool inGameControls;
    bool isReplayMode;
    bool replaying;
    int replayCam;
    gameStatus(std::string gameMode, int currCharacter) {
        this->gameMode = gameMode;
        this->currCharacter = currCharacter;
        this->gameOver = false;
        this->inGameControls = true;
        this->isReplayMode = false;
        this->replayCam = 0;
        this->replaying = false;
    }
    void switchCharacter() {
        ++currCharacter%=3;
    }
    void toggleReplayCam() {
        ++replayCam%=2;
    }
    void reset() {
        inGameControls = true;
        gameOver = false;
        isReplayMode = false;
        replayCam = 0;
        this->replaying = false;
    }
} gameStatus;
typedef struct gameCamera {
    double eyeX;
    double eyeY;
    double eyeZ;
    double centerX;
    double centerY;
    double centerZ;
    double upX;
    double upY;
    double upZ;
    vector DefaultEye;
    vector DefaultCenter;
    vector DefaultUp;
    gameCamera(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ) {
        this->eyeX = eyeX;
        this->eyeY = eyeY;
        this->eyeZ = eyeZ;
        this->centerX = centerX;
        this->centerY = centerY;
        this->centerZ = centerZ;
        this->upX = upX;
        this->upY = upY;
        this->upZ = upZ;
        vector DefaultEye(eyeX,eyeY,eyeZ);
        vector DefaultCenter(centerX,centerY,centerZ);
        vector DefaultUp(upX,upY,upZ);
        this->DefaultEye = DefaultEye;
        this->DefaultCenter = DefaultCenter;
        this->DefaultUp = DefaultUp;
    }
    void incrementEye(double eyeX, double eyeY, double eyeZ) {
        this->eyeX += eyeX;
        this->eyeY += eyeY;
        this->eyeZ += eyeZ;
    }
    void setEye(double eyeX, double eyeY, double eyeZ) {
        this->eyeX = eyeX;
        this->eyeY = eyeY;
        this->eyeZ = eyeZ;
    }
    void setCenter(double centerX, double centerY, double centerZ) {
        this->centerX = centerX;
        this->centerY = centerY;
        this->centerZ = centerZ;
    }
    void set(double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ, double upX, double upY, double upZ) {
        this->eyeX = eyeX;
        this->eyeY = eyeY;
        this->eyeZ = eyeZ;
        this->centerX = centerX;
        this->centerY = centerY;
        this->centerZ = centerZ;
        this->upX = upX;
        this->upY = upY;
        this->upZ = upZ;
    }
    void reset(){
        this->eyeX = DefaultEye.x;
        this->eyeY = DefaultEye.y;
        this->eyeZ = DefaultEye.z;
        this->centerX = DefaultCenter.x;
        this->centerY = DefaultCenter.y;
        this->centerZ = DefaultCenter.z;
        this->upX = DefaultUp.x;
        this->upY = DefaultUp.y;
        this->upZ = DefaultUp.z;
    }
    std::string eyeToString() {
        return "[" + std::to_string(eyeX) + ", " + std::to_string(eyeY) + ", " + std::to_string(eyeZ) + "]" ;
    }
} gameCamera;


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
void drawGame();
bool hitTarget(character* character);
void initGame();
void endGame();
void replay();
// Motion
int* bezier(float t, int* p0,int* p1,int* p2,int* p3);
void changeCharacterTrajectoryAimLogic(int direction);
void fireCharacter();
void fireBullet(character* bulletCharacter);
void fireBulletRotation(character* bulletCharacter);
void characterHit();
void fireGrenade(character* grenadeCharacter);
void fireGrenadeStart(character* grenadeCharacter);
void fireGrenadeLogic(character* grenadeCharacter);
void fireShuriken(character* shurikenCharacter);
// Replay
void replay();
void replayFiringCamLogic();
// environment configurations
void setUpLights();
void setUpCamera();
// I/O
void passM(int x,int y);
void keyUp(unsigned char k, int x,int y);
// basic openGL
void Display();
void Anim();
void setupCamera();
void setupLights();
// END Function signatures

//global variables
//double r=1;
//int rd=1;

//Basic game state

gameStatus gameStat("basic", 0); //0 for bullet, 1 for grenade, 2 for shuriken
gameCamera gameCam(0, 0, 120, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

vector mainCharacterTranslation(0,0,68);
vector mainCharacterInitialTranslation(0,0,68);
quadraple mainCharacterRotation(0,0,0,0);
quadraple mainCharacterInitialRotation(0,0,0,0);
quadraple mainCharacterDeepRotation(0,0,0,0);
character mainCharacter(&mainCharacterTranslation, &mainCharacterRotation, &mainCharacterDeepRotation,&mainCharacterInitialTranslation ,&mainCharacterInitialRotation);

vector targetTranslation(0,0,0);
scoreBoardTarget target(&targetTranslation, 20);

int windowHeight = 720;
int windowWidth = 1080;

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

void createBullet (character* thisCharacter) {
    glPushMatrix();
    glRotated(thisCharacter->rotation->a ,thisCharacter->rotation->x, thisCharacter->rotation->y, thisCharacter->rotation->z);
    glTranslated(thisCharacter->translation->x, thisCharacter->translation->y, thisCharacter->translation->z);
    glRotated(thisCharacter->deepRotation->a ,thisCharacter->deepRotation->x, thisCharacter->deepRotation->y, thisCharacter->deepRotation->z);
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
    
    glPushMatrix();
    glTranslated(0, 0, 7+5+4+3);
    glColor3f(0.4, 0.4, 0.4);
    glutSolidTorus(0.2,3.2, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(0, 0, 7+5+4+3+0.01);
    glColor3f(0.4, 0.4, 0.4);
    glutSolidTorus(0.2,1.8, 32, 32);
    glPopMatrix();
    
    
    glPopMatrix();
    
}


void createGrenade (character* thisCharacter) {
    // I swear these numbers are puuure luck, I don't understand anything in this course.
    //Oh and p.s: the learning objective of this is probably how to waste time mowahahaha
    glPushMatrix();
    glRotated(thisCharacter->rotation->a ,thisCharacter->rotation->x, thisCharacter->rotation->y, thisCharacter->rotation->z);
    glRotated(rotAngle ,1, 0,0);
    glTranslated(thisCharacter->translation->x, thisCharacter->translation->y, thisCharacter->translation->z);
    glRotated(thisCharacter->deepRotation->a ,thisCharacter->deepRotation->x, thisCharacter->deepRotation->y, thisCharacter->deepRotation->z);
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    glPushMatrix();
    glRotated(90, 1, 0, 0); //REMOVE
    glScaled(0.3, 0.3, 0.3); // scaling must be done here
    glPushMatrix();
    glColor3f(0,0.5,0.3);
    glTranslated(0, 0, -12);
    gluDisk(qobj, 0.001, 3, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0.4,0.2);
    glTranslated(0, 0, -12);
    gluCylinder(qobj, 3, 3, 3, 32,32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0.4,0.2);
    glutSolidTorus(1, 10, 32, 32);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0,0.8,0.3);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glutSolidSphere(10, 32, 32);
    glPopMatrix();
    glPopMatrix();

    
    glPopMatrix();
}

void createShurikenPart () {
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

void createShuriken(character* thisCharacter) {
    glPushMatrix();
    glRotated(rotAngle, 1, 0, 0);
    glRotated(thisCharacter->rotation->a ,thisCharacter->rotation->x, thisCharacter->rotation->y, thisCharacter->rotation->z);
    glTranslated(thisCharacter->translation->x, thisCharacter->translation->y, thisCharacter->translation->z);
    
    glPushMatrix();
    glRotated(90, 1, 0, 0);
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


void createWall () {
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex3f(-70, -70, 0);
    glVertex3f(70, -70, 0.0f);
    glVertex3f(70,70, 0);
    glVertex3f(-70,70, 0);
    glEnd();
    glPopMatrix();
}

void createRoom () {
    //face
    glPushMatrix();
    glNormal3f(0, 0, 1);
    glColor3f(0,0.6,1);
    glTranslated(0, 0, -70);
    createWall();
    glPopMatrix();
    
    glPushMatrix();
    glNormal3f(-1, 0, 0);
    glColor3f(0.8,0.4,0.4);
    glTranslated(70, 0, 0);
    glRotated(90, 0, 1, 0);
    createWall();
    glPopMatrix();
    
    glPushMatrix();
    glNormal3i(1, 0, 0);
    glColor3f(0.8,0.4,0.4);
    glTranslated(-70, 0, 0);
    glRotated(90, 0, 1, 0);
    createWall();
    glPopMatrix();
    
    //ceiling
    glPushMatrix();
    glNormal3f(0, -1, 0);
    glColor3f(0.9,0.5,0.3);
    glTranslated(0, 70, 0);
    glRotated(90, 1, 0, 0);
    createWall();
    glPopMatrix();
    
    //floor
    glPushMatrix();
    glNormal3f(0, 1, 0);
    glColor3f(0.9,0.5,0.3);
    glTranslated(0, -70, 0);
    glRotated(90, 1, 0, 0);
    createWall();
    glPopMatrix();
    
}


void createTarget (scoreBoardTarget* target) {
    GLUquadricObj * qobj;
    qobj = gluNewQuadric();
    glPushMatrix();
    glTranslated(target->translation->x, target->translation->y, target->translation->z);
    glPushMatrix();
    glTranslated(0, 0, 0);
    
    glPushMatrix();
    glColor3f(1, 0, 1);
    gluDisk(qobj, 0.001, 4, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glColor3f(1, 1, 0);
    gluDisk(qobj, 4, 13, 32, 32);
    glPopMatrix();
    glPushMatrix();
    glColor3f(0, 1, 1);
    gluDisk(qobj, 13, 20, 32, 32);
    glPopMatrix();
    glPopMatrix();
    
    glPopMatrix();
    
}

void drawGame(scoreBoardTarget* target ,character* character) {
    createRoom();
    createTarget(target);
    switch(gameStat.currCharacter) {
        case 0:
            createBullet(character);
            break;
        case 1:
            createGrenade(character);
            break;
        case 2:
            createShuriken(character);
            break;
    }
}

//Motion Logic

//Aiming

void changeCharacterTrajectoryAimLogic(int direction) {
    bool canIncrease = true;
    bool canDecrease = true;
    switch (gameStat.currCharacter) {
        case 0:
            if(mainCharacter.rotation->a == 48)
                canIncrease = false;
            if(mainCharacter.rotation->a == -48)
                canDecrease = false;
            break;
        case 1:
            if(mainCharacter.rotation->a == 40)
                canIncrease = false;
            if(mainCharacter.rotation->a == -40)
                canDecrease = false;
            break;
    }
    if(direction == 0 && canDecrease)
        mainCharacter.setRotation(mainCharacter.rotation->a-2, 0,1,0);
    if(direction == 1 && canIncrease)
        mainCharacter.setRotation(mainCharacter.rotation->a+2, 0,1,0);
    
}


// Firing

void fireCharacter() {
    // Save initial firing values for replay later.
    if(!mainCharacter.isFiring){
        mainCharacter.firingInitialTranslation->set(mainCharacter.translation);
        mainCharacter.firingInitialRotation->set(mainCharacter.rotation);
    }
    // Call character firing function based on the current active character
    switch(gameStat.currCharacter) {
        case 0:
            fireBullet(&mainCharacter);
            break;
        case 1:
            fireGrenade(&mainCharacter);
            break;
        case 2:
            fireShuriken(&mainCharacter);
            break;
    }
    if(gameStat.isReplayMode && gameStat.replaying){
        replayFiringCamLogic();
    }
}

void replayFiringCamLogic(){
    if (mainCharacter.isFiring) {
        switch (gameStat.replayCam) {
            case 0:
                switch (gameStat.currCharacter) {
                    case 0:
                        gameCam.setCenter(mainCharacter.translation->x, mainCharacter.translation->y, mainCharacter.translation->z);
                        break;
                    case 1:
                        gameCam.setCenter(mainCharacter.translation->x, mainCharacter.translation->y>0?mainCharacter.translation->y-12:mainCharacter.translation->y+25, mainCharacter.translation->z>0?mainCharacter.translation->z-10:mainCharacter.translation->z+10);
                        break;
                }
                break;
            case 1:
                switch (gameStat.currCharacter) {
                    case 0:
                        gameCam.setEye(mainCharacter.translation->x, mainCharacter.translation->y, mainCharacter.translation->z);
                        break;
                    case 1:
                        break;
                }
                break;
        }
    }else{
//        switch (gameStat.replayCam) {
//            case 0:
//                switch (gameStat.currCharacter) {
//                    case 1:
//                        gameCam.setCenter(0, 0, 0);
//                        break;
//                }
//                break;
//            case 1:
//                gameCam.setEye(0, 0, 100);
//                break;
//        }
        gameCam.reset();

    }
}

void fireBullet(character* bulletCharacter) {
    bulletCharacter->isFiring = true;
    // Rotation of bullet around its axis
    fireBulletRotation(bulletCharacter);
    // Z axis default translation
    bulletCharacter->translation->z -= 1*0.5;
    // X axis conditional translation
    if (bulletCharacter->rotation->a != 0) {
        if(bulletCharacter->rotation->a < 0) {
            float slope = tan ((180+bulletCharacter->rotation->a) * toDeg);
            bulletCharacter->translation->x += slope*0.005;
        } else {
            float slope = tan ((180-bulletCharacter->rotation->a) * toDeg);
            bulletCharacter->translation->x -= slope*0.005;
        }
    }
    // hit or miss logic
    if(hitTarget(bulletCharacter)) {
        bulletCharacter->isFiring = false;
        characterHit();
    }
    // if bullet hit the back wall // if bullet
    if(bulletCharacter->translation->z<=-69 || bulletCharacter->translation->x<-60 || bulletCharacter->translation->x>60) {
        bulletCharacter->isFiring = false;
        characterHit();
    }
}

void fireBulletRotation(character* bulletCharacter) {
    bulletCharacter->deepRotation->a +=2;
    bulletCharacter->deepRotation->z= 1;
    //    cout << "Bullet around its axis rotation angle is: "<< bulletCharacter->deepRotation->a<<"\n";
}

void fireGrenade(character* grenadeCharacter) {
    if(!grenadeCharacter->isFiring) {
        fireGrenadeStart(grenadeCharacter);
    } else {
        fireGrenadeLogic(grenadeCharacter);
    }
}

void fireGrenadeStart(character* grenadeCharacter) {
    grenadeCharacter->bezierTranslationPoints [0] = vector(grenadeCharacter->translation->x,grenadeCharacter->translation->y,grenadeCharacter->translation->z);
    grenadeCharacter->bezierTranslationPoints [1] = vector(0,grenadeCharacter->translation->y+40,grenadeCharacter->translation->z);
    grenadeCharacter->bezierTranslationPoints [2] = vector(0,grenadeCharacter->translation->y+40,0);
    grenadeCharacter->bezierTranslationPoints [3] = vector(0,-60,-50); // -60 in Y is floor, since floor is at -70 and radius of grenade is 10
    grenadeCharacter->isFiring = true;
    
}

void fireGrenadeLogic(character* grenadeCharacter) {
    int p0[2] = {static_cast<int>(grenadeCharacter->bezierTranslationPoints [0].z), static_cast<int>(grenadeCharacter->bezierTranslationPoints [0].y)};
    int p1[2] = {static_cast<int>(grenadeCharacter->bezierTranslationPoints [1].z), static_cast<int>(grenadeCharacter->bezierTranslationPoints [1].y)};
    int p2[2] = {static_cast<int>(grenadeCharacter->bezierTranslationPoints [2].z), static_cast<int>(grenadeCharacter->bezierTranslationPoints [2].y)};
    int p3[2] = {static_cast<int>(grenadeCharacter->bezierTranslationPoints [3].z),static_cast<int>(grenadeCharacter->bezierTranslationPoints [3].y)};
    
    if (!(grenadeCharacter->bezierTranslation>1)) {
        grenadeCharacter->deepRotation->a+=10;
        grenadeCharacter->deepRotation->z=1;
        grenadeCharacter->deepRotation->y=1;
        grenadeCharacter->bezierTranslation+=0.03;
        int* p =bezier(grenadeCharacter->bezierTranslation,p0,p1,p2,p3);
        grenadeCharacter->translation->z = p[0];
        grenadeCharacter->translation->y = p[1];
        if (hitTarget(grenadeCharacter)) {
            grenadeCharacter->isFiring = false;
            characterHit();
            cout << "The grenade hit the target \n";
        }
    } else {
        //hitting floor condition // as end of bezier is floor - radius
        grenadeCharacter->isFiring = false;
        characterHit();
        cout << "The grenade hit the floor "<< grenadeCharacter->translation->toString()<<"\n";
    }
}

void fireShuriken(character* shurikenCharacter) {
    // TODO
}

bool hitTarget(character* character) {
    switch (gameStat.currCharacter) {
        case 0:
            return character->translation->z == target.translation->z && character->translation->x > target.translation->x - target.radius
            && character->translation->x < target.translation->x + target.radius;
        case 1:
            return character->translation->z <= target.translation->z+5
            && character->translation->z >= target.translation->z
            && character->translation->y > target.translation->y - target.radius
            && character->translation->y < target.translation->y + target.radius
            && character->translation->x > target.translation->x - target.radius
            && character->translation->x < target.translation->x + target.radius;
            break;
        case 2:
            break;
    }
    return false;
}

//Bezier
int* bezier(float t, int* p0,int* p1,int* p2,int* p3)
{
    int res [2];
    res[0]=pow((1-t),3)*p0[0]+3*t*pow((1-t),2)*p1[0]+3*pow(t,2)*(1-t)*p2[0]+pow(t,3)*p3[0];
    res[1]=pow((1-t),3)*p0[1]+3*t*pow((1-t),2)*p1[1]+3*pow(t,2)*(1-t)*p2[1]+pow(t,3)*p3[1];
    return res;
}

void characterHit() {
    gameStat.inGameControls = false;
    gameStat.isReplayMode = true;
}

void replay(){
    if(!gameStat.inGameControls){
        mainCharacter.resetAttrs();
        mainCharacter.translation->set(mainCharacter.firingInitialTranslation);
        mainCharacter.rotation->set(mainCharacter.firingInitialRotation);
        mainCharacter.deepRotation->set(0,0,0,0);
        gameStat.replaying = true;
        fireCharacter();
    }
}

void initGame() {
    gameCam.set(0, 0, 120, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gameStat.reset();
    mainCharacter.translation->set(0, 0, 68);
    mainCharacter.rotation->set(0,0,0,0);
    mainCharacter.deepRotation->set(0,0,0,0);
    mainCharacter.resetAttrs();
    target.translation->set(0, 0, 0);
}

void endGame() {
    gameStat.gameOver = true;
    exit (0);
}

//OPENGL FUNCS

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    if(!gameStat.gameOver) {
        setupCamera();
        setupLights();
        drawGame(&target, &mainCharacter);
    }
    
    glPopMatrix();
    glFlush();
}

void anim()
{
    if(mainCharacter.isFiring) {
        fireCharacter();
    }
    glutPostRedisplay();
}

void passM(int x,int y) {
    float mappedX = (x - (windowWidth/2));
    if(mappedX>-windowWidth/4.2 && mappedX < windowWidth/4.2)
        gameCam.eyeX = mappedX*0.2;
}


void keyUp(unsigned char k, int x,int y)//keyboard up function is called whenever the keyboard key is released
{
    if(gameStat.inGameControls){
        switch (k) {
            case 'w':
                target.translation->z++;
                break;
            case 's':
                if(target.translation->z!=1) {
                    target.translation->z--;
                }
                break;
            case 'd':
                if(target.translation->x!=(29)) {
                    target.translation->x++;
                }
                break;
            case 'a':
                if(target.translation->x!=(-29)) {
                    target.translation->x--;
                }
                break;
            case 32:
                if(!mainCharacter.hasFired)
                    fireCharacter();
                break;
            case 48:
                gameStat.switchCharacter();
                break;
            case 49:
                changeCharacterTrajectoryAimLogic(0);
                break;
            case 50:
                changeCharacterTrajectoryAimLogic(1);
                break;
            case 'o':
                rotAngle-=3;
                break;
                
            case 'p':
                rotAngle+=3;
                break;
        }
    }
    switch (k) {
        case 27:
            endGame();
            break;
        case 'n':
            initGame();
            break;
        case 'r':
            replay();
            break;
        case 9:
            gameStat.toggleReplayCam();
            break;
    }
    glutPostRedisplay();//redisplay to update the screen with the changed
}

void setupCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(1, 1, -1, 1, -1, 1);
    gluPerspective(80, 640 / 480, 0.001, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(gameCam.eyeX, gameCam.eyeY, gameCam.eyeZ, gameCam.centerX, gameCam.centerY, gameCam.centerZ, gameCam.upX, gameCam.upY, gameCam.upZ);
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

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutCreateWindow("Aim and Shoot");
    glutInitWindowSize(windowWidth, windowHeight);
    glutFullScreen();
    glutDisplayFunc(Display);
    glutIdleFunc(anim);
    glutPassiveMotionFunc(passM); // call passive motion function for mouse movements
    glutKeyboardUpFunc(keyUp);		//call the keyboard up function
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
    glEnable(GL_DEPTH_TEST);
    //        glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    
    glShadeModel(GL_SMOOTH);
    //	glEnable(GL_TEXTURE_2D);
    //	loadBMP(&texEarthID, "textures/earth.bmp", false);
    
    initGame();
    
    glutMainLoop();
    return 0;
}
