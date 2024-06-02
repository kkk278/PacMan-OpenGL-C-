int pacTick = 0;

extern int score;
extern int pills;
extern int deathTick;
extern bool dead;
extern int eatenCount;
extern int fruitCounter;

bool begin = true;

typedef enum {LEFT, UP, RIGHT, DOWN, NONE} direction;

class Pacman
{
public:
    float pacmanX;
    float pacmanY;
    direction currentDir;
    direction dirStore;
    float angle;


    Pacman()
    {
        pacmanX = 13.5f;
        pacmanY =  7.0f;
        currentDir = NONE;
        dirStore = NONE;
    }

    void draw()
    {
        glPushMatrix();

        unsigned int pac_tex;
        int tickDiv;

        if(!dead) {
            tickDiv = pacTick % 30;
        }
        if(currentDir == NONE) {
            tickDiv = 0;
        }
        if(gameTick < 150) { 
            pac_tex = pac_2_tex;
        } else {
            if (tickDiv % 30 < 10) {
                pac_tex = pac_0_tex;
            } else if (tickDiv % 30 < 20) {
                pac_tex = pac_1_tex;
            } else {
                pac_tex = pac_2_tex;
            }
        }

        switch(currentDir){ 
            case LEFT: angle = 0.0f;
                break;
            case UP: angle = 270.0f;
                break;
            case RIGHT: angle = 180.0f;
                break;
            case DOWN: angle = 90.0f;
                break;
            default: currentDir = NONE;
        }

        translateBottomLeft(); 
        translateToMazeCoords(pacmanX, pacmanY);

        glTranslatef(-3.0f, -3.0f, 0.0f); 

        drawTex(pac_tex, 14, 14, angle);

        glPopMatrix();

        pacTick++;

    }

    void reset()
    {
        pacmanX = 13.5f;
        pacmanY =  7.0f;
        currentDir = NONE;
        dirStore = NONE;
        angle = 0.0f;
        begin = true;
        dead = false;
        eatenCount = 0;
    }

    void death()
    {
        glPushMatrix();

        unsigned int pac_tex;


        if (deathTick < 10) {                  
            pac_tex = dead_0_tex;
        } else if (deathTick % 110 < 20) {
            pac_tex = dead_1_tex;
        } else if (deathTick % 110 < 30) {
            pac_tex = dead_2_tex;
        } else if (deathTick % 110 < 40) {
            pac_tex = dead_3_tex;
        } else if (deathTick % 110 < 50) {
            pac_tex = dead_4_tex;
        } else if (deathTick % 110 < 60) {
            pac_tex = dead_5_tex;
        } else if (deathTick % 110 < 70) {
            pac_tex = dead_6_tex;
        } else if (deathTick % 110 < 80) {
            pac_tex = dead_7_tex;
        } else if (deathTick % 110 < 90) {
            pac_tex = dead_8_tex;
        } else if (deathTick % 110 < 100) {
            pac_tex = dead_9_tex;
        } else {
            pac_tex = dead_10_tex;
        }
        translateBottomLeft();  
        translateToMazeCoords(pacmanX, pacmanY);
        glTranslatef(-3.0f, -3.0f, 0.0f);
        drawTex(pac_tex, 14, 14, 0);
        glPopMatrix();

    }

    void checkTile()
    {
        switch(getTile(pacmanX, pacmanY)) {
            case o:                                                     
                maze[(int) floor(pacmanX)][(int) floor(pacmanY)] = e;
                score += 10;
                pills--;
                break;
            case O:                                                     
                maze[(int) floor(pacmanX)][(int) floor(pacmanY)] = E;
                score += 50;
                pills--;
                break;
            case P:
                if (getPacX() >=
                    26.5) {                             
                    pacmanX = 1.0f;
                } else {
                    pacmanX = 26.5f;
                }
                break;
            case F:                                     
                maze[(int) floor(pacmanX)][(int) floor(pacmanY)] = e;
                fruitCounter++; 
                if(fruitCounter == 1) { 
                    score += 100;
                } else {
                    score += 300;
                }

        }
    }
    
    int getPacX()
    {
        return (int)floor(pacmanX);
    }

    int getPacY()
    {
        return (int)floor(pacmanY);
    }

    tile getTile(float x, float y)
    {
        return maze[(int)floor(x)][(int)floor(y)];
    }

    tile getFollowingTile(direction dir)
    {
        switch(dir) {
            case LEFT: return getTile(getPacX() - 1, getPacY());
            case UP: return getTile(getPacX(), getPacY() + 1);
            case RIGHT: return getTile(getPacX() +1, getPacY());
            case DOWN: return getTile(getPacX(), getPacY() - 1);
            default: return getTile(getPacX(), getPacY());
        }
    }

    bool isAtCenter()
    {
        return (int)(pacmanY * 10.0f) % 10 == 0 && (int)(pacmanX * 10.0f) % 10 == 0;
    }

    void setDirStore(direction pressedDir)
    {
        dirStore = pressedDir;
    }

    bool isWall(direction dir)
    {
        if (getFollowingTile(dir) == W || getFollowingTile(dir) == G) {
            return true;
        }

        return false;
    }

    void move()
    {
        if(isAtCenter()) { 
            if (!isWall(dirStore)) { 
                currentDir = dirStore;
            } else if (isWall(currentDir)) {
                currentDir = NONE; 
            }
        }
        if(!isAtCenter() && dirStore != NONE && begin && !isWall(dirStore)){ 
            currentDir = dirStore;
            begin = false;
        }

        switch (currentDir) {
            case LEFT:
                pacmanX -= 0.1f;
                pacmanY = round(pacmanY);
                break;
            case UP:
                pacmanY += 0.1f;
                pacmanX = round(pacmanX);
                break;
            case RIGHT:
                pacmanX += 0.1f;
                pacmanY = round(pacmanY);
                break;
            case DOWN:
                pacmanY -= 0.1f;
                pacmanX = round(pacmanX);
                break;
            default:
                if(!begin) { 
                    pacmanX = round(pacmanX);
                    pacmanY = round(pacmanY);
                }
        }
    }
};
