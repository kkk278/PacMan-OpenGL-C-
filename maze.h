extern unsigned int maze_tex;
extern unsigned int pill_tex;
extern unsigned int bigPill_tex;
extern int gameTick;
extern int fruitSpawned;
extern int fruitCounter;


typedef enum {W, G, P, u, o, e, O, E, F} tile;

tile maze[28][31] =
        {
                {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W},
                {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                {W,o,W,W,W,W,W,u,W,W,W,W,W,u,W,u,u,u,G,u,W,W,W,W,W,o,W,W,W,W,W},
                {W,o,o,o,o,W,W,o,o,o,o,W,W,u,W,u,u,u,W,u,u,u,o,W,W,o,o,o,o,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,u,u,u,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,W,u,W,W,W,W,W,u,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,u,u,u,u,u,u,u,u,u,W,W,o,o,o,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,u,W,W,W,W,W,W,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,W,u,W,W,W,W,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,W,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,o,o,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,W,W,o,W,W,o,W,W,o,W,u,u,u,W,u,W,u,u,u,W,o,W,W,o,W,W,W,o,W},
                {W,o,o,o,o,W,W,O,o,o,o,W,u,u,u,W,u,W,u,u,u,W,o,o,o,o,O,o,o,o,W},
                {W,W,W,W,W,W,W,W,W,W,W,W,u,u,u,W,P,W,u,u,u,W,W,W,W,W,W,W,W,W,W}
        };

void translateToMazeCoords(float x, float y)
{
    glTranslatef(x * 8, y * 8, 0.0f);
}


void translateBottomLeft()
{
    glTranslatef(38.0f, 26.0f, 0.0f);
}

tile getTile(float x, float y)
{
    return maze[(int) floor(x)][(int) floor(y)];
}

void eatFruitScore(int x, int y)
{
    glPushMatrix();


    unsigned int eat_score_tex;

    switch(fruitCounter) { 
        case 1: eat_score_tex = score_100_tex;
            break;
        case 2: eat_score_tex = score_300_tex;
            break;
    }

    translateBottomLeft();
    translateToMazeCoords(x, y); 
    glTranslatef(-2.0f, 0.0f, 0.0f);

    if(fruitCounter != 0) { 
        drawTex(eat_score_tex, 15, 8, 0);
    }

    glPopMatrix();
}

void fruitReset()
{
    for(int x=0;x<28;x++) {            
        for(int y=0;y<31;y++) {
            switch(maze[x][y]) {
                case F:
                    maze[x][y] = e; 
                    break;
            }
        }
    }
}


void locationFruit()
{
    int x, y;
    do {
        x = rand() % 27;
        y = rand() % 12;
    } while(getTile(x, y) != e);

    maze[(int) floor(x)][(int) floor(y)] = F; 
    fruitSpawned++; 
}


void drawFruit()
{
    glTranslatef(-2.0f, -2.0f, 0.0f); 
                                        
    if(fruitCounter == 0) { 
        drawTex(cherry_tex, 14, 14, 0);
    } else {
        drawTex(strawberry_tex, 14, 14, 0);
    }
    glTranslatef(2.0f, 2.0f, 0.0f); 
}

void drawMaze()
{
    glPushMatrix();

    translateBottomLeft();              
    drawTex(maze_tex, 224, 248, 0);     
    for(int x=0;x<28;x++) {             
        glPushMatrix();

        for(int y=0;y<31;y++) {
            switch(maze[x][y]) {
                case o:                 
                    drawTex(pill_tex, 8, 8, 0);
                    break;
                case O:                 
                    if(gameTick % 30 <= 15) {
                        drawTex(bigPill_tex, 8, 8, 0);
                    }
                    break;
                case F:
                    drawFruit();
                    break;
            }

            glTranslatef(0.0f, 8.0f, 0.0f); 
        }
        glPopMatrix();

        glTranslatef(8.0f, 0.0f, 0.0f);    
    }
    glPopMatrix();
}

void resetMaze()
{
    for(int x=0;x<28;x++) {             
        for (int y = 0; y < 31; y++) {
            switch (maze[x][y]) {
                case e:                 
                    maze[x][y] = o;
                    break;
                case E:               
                    maze[x][y] = O;
                    break;
            }
        }
    }
}
