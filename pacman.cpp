#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <fstream>

#include "load_and_bind_texture.h"
#include "textures.h"
#include "maze.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Interface.h"

int gameTick = 0;
int deathTick = 0;
int frightenTick = 0;
int timestamp;
int score = 0;
int pills = 244;
int lives = 3;
int eatenCount = 0;
bool frighten;
float eatenX;
float eatenY;
int eatStamp;
Pacman pacman;
bool paused = false;
bool dead = false;

int fruitCounter = 0;
int tempFruitCounter = 0;
int eatFruitStamp = 0;
int eatenFruitX;
int eatenFruitY;
int fruitSpawned = 0;

Ghost ghosts[4] = {
        Ghost(13.5f, 19.0f, RED),
        Ghost(11.5f, 16.0f, BLUE),
        Ghost(13.5f, 16.0f, PINK),
        Ghost(15.5f, 16.0f, YELLOW),
};

typedef enum {BEGIN, PLAY, DIE, OVER} gameState; 

gameState stateGame = BEGIN; 


void detectPill()
{
    if(pacman.getTile(pacman.pacmanX, pacman.pacmanY) == O) {
        frighten = true; 
        frightenTick = 0; 
        for(int i = 0; i < 4; i++) {
            if(ghosts[i].moveType == CHASE || ghosts[i].moveType == SCATTER) { 
                ghosts[i].eaten = false;
                ghosts[i].moveType = FRIGHTEN;
                if(ghosts[i].currentDir == LEFT) { 
                    ghosts[i].currentDir = RIGHT;
                } else if(ghosts[i].currentDir == UP) {
                    ghosts[i].currentDir = DOWN;
                } else if(ghosts[i].currentDir == RIGHT) {
                    ghosts[i].currentDir = LEFT;
                } else {
                    ghosts[i].currentDir = UP;
                }
            }
        }
    } else if(pacman.getTile(pacman.pacmanX, pacman.pacmanY) == F) {
        eatenFruitX = pacman.pacmanX;
        eatenFruitY = pacman.pacmanY;
    }
}

void detectGhost()
{
    for(int i = 0; i < 4; i++) { 
        if(pacman.getPacX() == ghosts[i].getGhostX() && pacman.getPacY() == ghosts[i].getGhostY()) { 
            if(ghosts[i].moveType != FRIGHTEN && ghosts[i].moveType != DEATH) { 
                stateGame = DIE; 
                timestamp = gameTick;
            } else {
                if(!ghosts[i].eaten) { 
                    eatenCount++;
                    eatStamp = gameTick;
                    switch(eatenCount){ 
                        case 1: score += 200;
                            break;
                        case 2: score += 400;
                            break;
                        case 3: score += 800;
                            break;
                        case 4: score += 1600;
                            break;
                    }
                    eatenX = ghosts[i].ghostX; 
                    eatenY = ghosts[i].ghostY;
                    ghosts[i].eaten = true; 
                }
                ghosts[i].moveType = DEATH; 
            }
        }
    }
    if(stateGame == DIE && !dead) { 
        lives--;
        dead = true;
    }
}

void setMode()
{
    if(gameTick >= 4450) {
        for (int i = 0; i < 4; i++) {
            if (ghosts[i].moveType != PEN && ghosts[i].moveType != LEAVE && !frighten && ghosts[i].moveType != DEATH) { 
                ghosts[i].moveType = CHASE; 
            }
        }
    } else if(gameTick >= 4200) {
        for(int i = 0; i < 4; i++) {
            if(ghosts[i].moveType != PEN && ghosts[i].moveType != LEAVE && !frighten && ghosts[i].moveType != DEATH) {
                ghosts[i].moveType = SCATTER;
            }
        }
    } else if(gameTick >= 3200) {
        for(int i = 0; i < 4; i++) {
            if(ghosts[i].moveType != PEN && ghosts[i].moveType != LEAVE && !frighten && ghosts[i].moveType != DEATH) {
                ghosts[i].moveType = CHASE;
            }
        }
    } else if(gameTick >= 2950) {
        for(int i = 0; i < 4; i++) {
            if(ghosts[i].moveType != PEN && ghosts[i].moveType != LEAVE && !frighten && ghosts[i].moveType != DEATH) {
                ghosts[i].moveType = SCATTER;
            }
        }
    } else if(gameTick >= 1950) {
        for(int i = 0; i < 4; i++) {
            if(ghosts[i].moveType != PEN && ghosts[i].moveType != LEAVE && !frighten && ghosts[i].moveType != DEATH) {
                ghosts[i].moveType = CHASE;
            }
        }
    } else if (gameTick >= 1600) {
        for(int i = 0; i < 4; i++) {
            if(ghosts[i].moveType != PEN && ghosts[i].moveType != LEAVE && !frighten && ghosts[i].moveType != DEATH) {
                ghosts[i].moveType = SCATTER;
            }
        }
    } else if(gameTick >= 600) {
        for(int i = 0; i < 4; i++) {
            if(ghosts[i].moveType != PEN && ghosts[i].moveType != LEAVE && !frighten && ghosts[i].moveType != DEATH) {
                ghosts[i].moveType = CHASE;
            }
        }
    }
}

void idle(int)
{
    if(!paused) { 
        switch (stateGame) { 
            case BEGIN:
                if (gameTick >= 150) { 
                    stateGame = PLAY;
                }
                break;
            case PLAY:
                setMode(); 
                detectPill(); 
                pacman.checkTile(); 
                detectGhost(); 
                pacman.move(); 
                detectGhost();
                for (int i = 0; i < 4; i++) { 
                    ghosts[i].move(ghosts[0]);
                }
                detectGhost();
                if (frightenTick <= 450 && frighten) { 
                    frightenTick++;
                } else if (frighten) { 
                    frighten = false;
                    eatenCount = 0;
                    frightenTick = 0;
                    for (int i = 0; i < 4; i++) {
                        if (ghosts[i].moveType == FRIGHTEN) {
                            ghosts[i].eaten = false;
                        }
                    }
                    setMode(); 
                }
                if (pills <= 0) { 
                    fruitReset();
                    resetMaze();
                    pacman.reset();
                    pills = 244;
                    fruitSpawned = 0;
                    fruitCounter = 0;
                    tempFruitCounter = 0;
                    for (int i = 0; i < 4; i++) {
                        ghosts[i].reset();
                    }
                    gameTick = 0;
                    stateGame = BEGIN;
                }
                break;
            case DIE:
                if (gameTick - timestamp >= 100) { 
                    deathTick++;
                }
                break;

        }
        glutTimerFunc(10, idle, 0); 
        gameTick++;
        glutPostRedisplay(); 
    }
}


void special(int key, int, int)
{
    switch (key)
    {
        case GLUT_KEY_LEFT: pacman.setDirStore(LEFT); 
            break;
        case GLUT_KEY_UP: pacman.setDirStore(UP); 
            break;
        case GLUT_KEY_RIGHT: pacman.setDirStore(RIGHT); 
            break;
        case GLUT_KEY_DOWN: pacman.setDirStore(DOWN); 
            break;
    }
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 300, 0, 300);
    loadAndBindTextures();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glutIgnoreKeyRepeat(GL_TRUE);
    glEnable(GL_TEXTURE_2D);
}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT);
    switch(stateGame){ 
        case BEGIN:
            drawMaze();
            pacman.draw();
            for(int i = 0; i < 4; i++){
                ghosts[i].draw();
            }
            drawInterface();
            drawReady();
            break;
        case PLAY:
            drawMaze();
            pacman.draw();
            if(pills <= 174 && fruitSpawned == 0) {
                locationFruit();
            }
            if(pills <= 74 && fruitSpawned == 1) {
                locationFruit();
            }
            if(fruitCounter > tempFruitCounter) {
                eatFruitStamp = gameTick;
            }
            if(gameTick - eatFruitStamp <= 200) {
                eatFruitScore(eatenFruitX, eatenFruitY);
            }
            for(int i = 0; i < 4; i++){
                ghosts[i].draw();
                if(frighten && gameTick - eatStamp <= 200) {
                    ghosts[i].drawEatScore(eatenX, eatenY);
                }
            }
            drawInterface();
            tempFruitCounter = fruitCounter;
            break;
        case DIE:
            fruitReset();
            drawMaze();
            if(gameTick - timestamp < 70) { 
                pacman.draw();
                for(int i = 0; i < 4; i++){
                    ghosts[i].draw();
                }
            }
            if(gameTick - timestamp >= 30  && deathTick < 80) { 
                pacman.death();
            }
            if(gameTick - timestamp >= 280) { 
                pacman.reset();
                for(int i = 0; i < 4; i++){
                    ghosts[i].reset(); 
                }
                gameTick = 0;
                eatFruitStamp = -999999999;
                deathTick = 0;
                if(lives > 0) { 
                    stateGame = BEGIN;
                } else { 
                    setHighScore(score); 
                    stateGame = OVER;
                }
            }
            drawInterface();

            break;
        case OVER:
            drawMaze();
            drawInterface();
            drawGameOver();
            drawRestart();
    }

    glutSwapBuffers(); 
}

void resetGame()
{
    gameTick = 0;
    deathTick = 0;
    score = 0;
    lives = 3;
    pills = 244;
    fruitCounter = 0;
    fruitSpawned = 0;
    tempFruitCounter = 0;
    stateGame = BEGIN;
}

void keyboard(unsigned char key, int, int)
{
    switch (key)
    {
        case 'q': exit(1); 
        case 'p':
            if(paused) {
                paused = false;
            } else {
                paused = true;
            }
            break;
        case 'r':
            if(stateGame == OVER) {
                resetGame();
                pacman.reset();
                fruitReset();
                resetMaze();
                for(int i = 0; i < 4; i++) {
                    ghosts[i].reset(); 
                }
            }
            break;
    }
    glutPostRedisplay(); 
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - 720) >> 1;
    int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - 720) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(720,720);
    glutCreateWindow("Pacman"); 
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutTimerFunc(0, idle, 0);
    init();
    glutMainLoop(); 
    return 0; 
}

