extern int gameTick;
extern Pacman pacman;
extern bool frighten;
extern int eatenCount;
typedef enum {SCATTER, CHASE, FRIGHTEN, LEAVE, DEATH, PEN} movement;
typedef enum {RED, BLUE, PINK, YELLOW} colour;
direction tempDir = NONE;

class Ghost {
public:
    float ghostX;
    float ghostY;
    direction currentDir;
    colour ghostColour;
    movement moveType;
    float speed;
    bool eaten;

/**
 * Ham setMode
 * @param x: thiet lap vi tri x cua ghost
 * @param y: thiet lap vi tri y cua ghost
 * @param ghost: thiet lap mau sac cua ghost
 */
    Ghost(float x, float y, colour ghost) {
        ghostX = x;
        ghostY = y;
        switch (ghost) {
            case RED:
                currentDir = LEFT;
                moveType = SCATTER;
                break;
            case PINK:
                currentDir = DOWN;
                moveType = PEN;
                break;
            case BLUE:
                currentDir = UP;
                moveType = PEN;
                break;
            case YELLOW:
                currentDir = UP;
                moveType = PEN;
                break;
        }
        eaten = false;
        ghostColour = ghost;
        setSpeed();
    }

    /**
     * Ve diem duoc them vao tro choi khi pacman an ma Dieu nay duoc ve tai vi tri x va y cua ma vao thoi diem an
     * and the score also depends on how many ghosts, if any, had been eaten before it
     * @param x vi tri X cua ma vao thoi diem bi an
     * @param y vi tri Y cua ma vao thoi diem bi an
     */
    void drawEatScore(float x, float y)
    {
        glPushMatrix();



        unsigned int eat_score_tex;

        switch(eatenCount) { // Chon texture de ve tuy thuoc vao con ma nao dang bi an
            case 1: eat_score_tex = score_200_tex;
                break;
            case 2: eat_score_tex = score_400_tex;
                break;
            case 3: eat_score_tex = score_800_tex;
                break;
            case 4: eat_score_tex = score_1600_tex;
                break;
        }

        translateBottomLeft();
        translateToMazeCoords(x, y); //  Dich den phan dung tren man hinh de ve
        glTranslatef(-2.0f, 0.0f, 0.0f);

        if(eatenCount != 0) { // Chi ve ma neu da bi an 
            drawTex(eat_score_tex, 10, 8, 0);
        }

        glPopMatrix();
    }

    /**
     * Phuong thuc de ve ma voi texture dung va mat huong ve huong dung 
     */
    void draw() {
        glPushMatrix();

        unsigned int ghost_tex;
        unsigned int ghost_eye_tex;

        if (moveType != FRIGHTEN && moveType != DEATH) { // Mien la ma khong o trong che do death hoac frighten gan texture tuong ung cua no
            int tickDiv = gameTick % 20;
            if (tickDiv % 20 < 10) {
                switch (ghostColour) { // Kiem tra mau cua ma de xac dinh tep tex nao duoc su dung
                    case RED:
                        ghost_tex = ghost_r_0_tex;
                        break;
                    case BLUE:
                        ghost_tex = ghost_b_0_tex;
                        break;
                    case PINK:
                        ghost_tex = ghost_p_0_tex;
                        break;
                    case YELLOW:
                        ghost_tex = ghost_y_0_tex;
                        break;
                }
            } else {
                switch (ghostColour) {
                    case RED:
                        ghost_tex = ghost_r_1_tex;
                        break;
                    case BLUE:
                        ghost_tex = ghost_b_1_tex;
                        break;
                    case PINK:
                        ghost_tex = ghost_p_1_tex;
                        break;
                    case YELLOW:
                        ghost_tex = ghost_y_1_tex;
                        break;
                }
            }

            switch (currentDir) { //  Vi tri ma tep cua mat phu thuoc vao huong ma dang di chuyen
                case LEFT:
                    ghost_eye_tex = eye_left_tex;
                    break;
                case UP:
                    ghost_eye_tex = eye_up_tex;
                    break;
                case RIGHT:
                    ghost_eye_tex = eye_right_tex;
                    break;
                case DOWN:
                    ghost_eye_tex = eye_down_tex;
                    break;
            }
        } else if(moveType == FRIGHTEN){ //  Neu ma dang so hai gan cho no mot texture tuong ung
            int tickDiv = gameTick % 40;
            if (tickDiv % 40 < 10) {
                ghost_tex = ghost_scared_0_tex;
            } else if (tickDiv % 40 < 20) {
                ghost_tex = ghost_scared_1_tex;
            } else if (tickDiv % 40 < 30) {
                ghost_tex = ghost_scared_2_tex;
            } else {
                ghost_tex = ghost_scared_3_tex;
            }
        } else  if(moveType == DEATH) {
            switch (currentDir) { //  Vi tri mat va tep texture phu thuoc vao huong ma ma dang di chuyen
                case LEFT:
                    ghost_eye_tex = eye_left_tex;
                    break;
                case UP:
                    ghost_eye_tex = eye_up_tex;
                    break;
                case RIGHT:
                    ghost_eye_tex = eye_right_tex;
                    break;
                case DOWN:
                    ghost_eye_tex = eye_down_tex;
                    break;
            }
        }


        translateBottomLeft(); // Dich sang goc duoi ben trai cua man hinh
        translateToMazeCoords(ghostX, ghostY);

        glTranslatef(-3.0f, -3.0f, 0.0f);

        if(moveType != DEATH) { // Neu con ma khong chet thi ve texture cua co the cua no
            drawTex(ghost_tex, 14, 14, 0);
        }

        if (moveType != FRIGHTEN) { // Neu con ma khong so hai thi ve texture cua mat
            drawTex(ghost_eye_tex, 14, 14, 0);
        }

        glPopMatrix();

    }

    /**
    Phuong thuc de dat lai cac con ma ve vi tri cai dat ban dau cua chung khi tro choi duoc khoi dong lai
     */
    void reset() {
        switch (ghostColour) { 
            case RED:
                ghostX = 13.5f;
                ghostY = 19.0f;
                currentDir = LEFT;
                moveType = SCATTER;
                break;
            case BLUE:
                ghostX = 11.5f;
                ghostY = 16.0f;
                currentDir = UP;
                if (pills <= 163) {
                    moveType = LEAVE;
                } else {
                    moveType = PEN;
                }
                break;
            case YELLOW:
                ghostX = 15.5f;
                ghostY = 16.0f;
                currentDir = UP;
                if (pills <= 214) {
                    moveType = LEAVE;
                } else {
                    moveType = PEN;
                }
                break;
            case PINK:
                ghostX = 13.5f;
                ghostY = 16.0f;
                currentDir = DOWN;
                moveType = LEAVE;
                break;
        }
        eaten = false; // reset no ghost da bi an 
    }

    /**
     *  Phuong thuc xac dinh che do cua cac con ma va thiet lap toc do tuong ung
     */
    void setSpeed() {
        if (moveType == FRIGHTEN) { // Di chuyen cham neu dang bi hoang so 
            speed = 0.05f;
        } else {
            speed = 0.1f;
        }
    }

    /**
     *  Phuong thuc xac dinh mau cua con ma va gan ky thuat di chuyen tuong ung cho moi con ma
     *  @param ghost Bien duoc su dung neu mot con ma can su dung vi tri cua mot con ma khac trong ky thuat di chuyen cua no
     */
    void move(Ghost ghost) {
        setSpeed();
        switch (ghostColour) {
            case RED:
                redGhostMove(ghost);
                break;
            case BLUE:
                blueGhostMove(ghost);
                break;
            case PINK:
                pinkGhostMove(ghost);
                break;
            case YELLOW:
                yellowGhostMove(ghost);
                break;
        }
    }

    int getGhostX() {
        return (int) floor(ghostX);
    }

    int getGhostY() {
        return (int) floor(ghostY);
    }

    int checkJuncs(float x, float y) {
        int exit = 0;
        if (!isWall(LEFT)) { 
            exit++;
        }
        if (!isWall(UP)) {
            exit++;
        }
        if (!isWall(RIGHT)) {
            exit++;
        }
        if (!isWall(DOWN)) {
            exit++;
        }

        return exit;
    }

    tile getTile(float x, float y) {
        return maze[(int) floor(x)][(int) floor(y)];
    }

    tile getFollowingTile(direction dir) {
        switch (dir) {
            case LEFT:
                return getTile(getGhostX() - 1, getGhostY());
            case UP:
                return getTile(getGhostX(), getGhostY() + 1);
            case RIGHT:
                return getTile(getGhostX() + 1, getGhostY());
            case DOWN:
                return getTile(getGhostX(), getGhostY() - 1);
            default:
                return getTile(getGhostX(), getGhostY());
        }
    }

    bool isAtCenter() {
        return (int) (ghostY * 10.0f) % 10 == 0 && (int) (ghostX * 10.0f) % 10 == 0;
    }

    float getDistance(int x, int y, colour ghostCol, Ghost ghost) {
        std::vector<int> v = getTargetTile(ghostCol);
        int targetX = v.at(0);
        int targetY = v.at(1);

        if (ghostCol == BLUE && moveType == CHASE) {
            float tempX = ghost.getGhostX() - targetX;
            float tempY = ghost.getGhostY() - targetY;
            targetX = ghost.getGhostX() + 2 * tempX;
            targetY = ghost.getGhostY() + 2 * tempY;
        }

        return (sqrt(((targetX - x) * (targetX - x)) + ((targetY - y) * (targetY - y))));
    }

    void cornerHandler() {
        if (isAtCenter()) { 
            if (isWall(currentDir)) { 
                if (!isWall(LEFT) && currentDir != RIGHT) { 
                    currentDir = LEFT;
                } else if (!isWall(UP) && currentDir != DOWN) {
                    currentDir = UP;
                } else if (!isWall(RIGHT) && currentDir != LEFT) {
                    currentDir = RIGHT;
                } else {
                    currentDir = DOWN;
                }
            }
        }
    }


    void moveToPen()
    {
        if (ghostX <= 13.55 && ghostX >= 13.45) { 
            if (ghostY >= 18.95f) { 
                currentDir = DOWN;
            } else if (ghostY <= 17.0f){
                moveType = LEAVE;
            }
        } else { 
            if (ghostX < 13.5f) { 
                currentDir = RIGHT;
            } else if (ghostX > 13.5f) {
                currentDir = LEFT;
            }
        }
        switch (currentDir) {
            case LEFT:
                ghostX -= speed;
                break;
            case UP:
                ghostY += speed;
                break;
            case RIGHT:
                ghostX += speed;
                break;
            case DOWN:
                ghostY -= speed;
                break;
        }
    }

    void setDeath(colour colGhost, Ghost ghost)
    {
        float distance = 999.0f;
        bool move = true;
        if(ghostX <= 13.55 && ghostX >= 13.45 && ghostY >= 15.5f && ghostY <= 20.0f) {
            moveToPen();
        } else {
            if (checkJuncs(ghostX, ghostY) >= 3 && isAtCenter()) {
                if (currentDir != DOWN && !isOnlyWall(UP)) {
                    float d = getDistance(getGhostX(), getGhostY() + 1, colGhost, ghost);
                    if (d < distance) {
                        tempDir = UP;
                        distance = d;
                    }
                }
                if (currentDir != LEFT && !isOnlyWall(RIGHT)) {
                    float d = getDistance(getGhostX() + 1, getGhostY(), colGhost, ghost);
                    if (d < distance) {
                        tempDir = RIGHT;
                        distance = d;
                    }
                }
                if (currentDir != RIGHT && !isOnlyWall(LEFT)) {
                    float d = getDistance(getGhostX() - 1, getGhostY(), colGhost, ghost);
                    if (d < distance) {
                        tempDir = LEFT;
                        distance = d;
                    }
                }
                if (currentDir != UP && !isOnlyWall(DOWN)) {
                    float d = getDistance(getGhostX(), getGhostY() - 1, colGhost, ghost);
                    if (d < distance) {
                        tempDir = DOWN;
                        distance = d;
                    }
                }
                currentDir = tempDir;
            } else {
                cornerHandler();
            }

            if(move) {
                switch (currentDir) {
                    case LEFT:
                        ghostX -= speed;
                        ghostY = round(ghostY);
                        break;
                    case UP:
                        ghostY += speed;
                        ghostX = round(ghostX);
                        break;
                    case RIGHT:
                        ghostX += speed;
                        ghostY = round(ghostY);
                        break;
                    case DOWN:
                        ghostY -= speed;
                        ghostX = round(ghostX);
                        break;
                }
            }
        }


    };

    void moveTargetTile(colour colGhost, Ghost ghost)
    {
        float distance = 999.0f;
        if (checkJuncs(ghostX, ghostY) >= 3 && isAtCenter()) {
            if (currentDir != DOWN && !isWall(UP)) {
                float d = getDistance(getGhostX(), getGhostY()+1, colGhost, ghost);
                if(d < distance){
                    tempDir = UP;
                    distance = d;
                }
            }
            if (currentDir != LEFT && !isWall(RIGHT)) {
                float d = getDistance(getGhostX()+1, getGhostY(), colGhost, ghost);
                if(d < distance){
                    tempDir = RIGHT;
                    distance = d;
                }
            }
            if (currentDir != RIGHT && !isWall(LEFT) ) {
                float d = getDistance(getGhostX()-1, getGhostY(), colGhost, ghost);
                if(d < distance){
                    tempDir = LEFT;
                    distance = d;
                }
            }
            if (currentDir != UP && !isWall(DOWN)) {
                float d = getDistance(getGhostX(), getGhostY()-1, colGhost, ghost);
                if(d < distance){
                    tempDir = DOWN;
                    distance = d;
                }
            }
            currentDir = tempDir;
        } else {
            cornerHandler();
        }


        switch (currentDir) {
            case LEFT:
                ghostX -= speed;
                ghostY = round(ghostY);
                break;
            case UP:
                ghostY += speed;
                ghostX = round(ghostX);
                break;
            case RIGHT:
                ghostX += speed;
                ghostY = round(ghostY);
                break;
            case DOWN:
                ghostY -= speed;
                ghostX = round(ghostX);
                break;
        }
    }

    void setFrighten()
    {
        direction chosenDir = NONE;
        if (checkJuncs(ghostX, ghostY) >= 3) { 
            do {
                int randNum = rand() % checkJuncs(ghostX, ghostY) - 1; 
                if(randNum == 0 && currentDir != RIGHT) {
                    chosenDir = LEFT;
                } else if(randNum == 1 && currentDir != DOWN) {
                    chosenDir = UP;
                } else if(randNum == 2 && currentDir != LEFT) {
                    chosenDir = RIGHT;
                } else if(currentDir != UP){
                    chosenDir = DOWN;
                }
            } while (isWall(chosenDir) && currentDir != NONE); 
        } else {
            cornerHandler();
        }

        if(isAtCenter() && chosenDir != NONE) {
            if(!isWall(chosenDir)){
                currentDir = chosenDir; 
            }
        }


        switch (currentDir) { 
            case LEFT:
                ghostX -= speed;
                ghostY = round(ghostY);
                break;
            case UP:
                ghostY += speed;
                ghostX = round(ghostX);
                break;
            case RIGHT:
                ghostX += speed;
                ghostY = round(ghostY);
                break;
            case DOWN:
                ghostY -= speed;
                ghostX = round(ghostX);
                break;
        }
    }

    void setMove(colour col, Ghost ghost)
    {
        float distance = getDistance(ghostX, ghostY, RED, ghost); 
        switch(col) {
            case RED:
                moveTargetTile(RED, ghost);
                break;
            case PINK:
                moveTargetTile(RED, ghost);
                break;
            case YELLOW:
                if (distance >= 8.0f) { 
                    moveTargetTile(RED, ghost);
                } else {
                    moveTargetTile(YELLOW, ghost);
                }
                break;
            case BLUE:
                moveTargetTile(BLUE, ghost);
                break;
        }
    }

    void redGhostMove(Ghost ghost)
    {
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(RED, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(RED, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH:
                setDeath(RED, ghost);
                break;
            case LEAVE:
                leaveMove();
                break;
        }
    }


    void blueGhostMove(Ghost ghost)
    {
        if(pills == 163){
            moveType = LEAVE;
        }
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(BLUE, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(BLUE, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH:
                setDeath(BLUE, ghost);
                break;
            case LEAVE:
                leaveMove();
                break;
            case PEN: penMove();
                break;
        }
    }

    void yellowGhostMove(Ghost ghost)
    {
        if(pills == 214){
            moveType = LEAVE;
        }
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(YELLOW, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(YELLOW, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH: setDeath(YELLOW, ghost);
                break;
            case LEAVE: leaveMove();
                break;
            case PEN: penMove();
                break;
        }
    }

    void pinkGhostMove(Ghost ghost)
    {
        switch(moveType){
            case SCATTER:
                portalCheck();
                setMove(PINK, ghost);
                break;
            case CHASE:
                portalCheck();
                setMove(PINK, ghost);
                break;
            case FRIGHTEN:
                portalCheck();
                setFrighten();
                break;
            case DEATH: setDeath(PINK, ghost);
                break;
            case LEAVE: leaveMove();
                break;
            case PEN: penMove();
                break;
        }
    }

    bool isWall(direction dir)
    {
        if (getFollowingTile(dir) == W || getFollowingTile(dir) == G) {
            return true;
        }

        return false;
    }

    bool isOnlyWall(direction dir)
    {
        if (getFollowingTile(dir) == W) {
            return true;
        }

        return false;
    }

    void penMove()
    {
        if(ghostY <= 15.5f && currentDir == DOWN) {
            if(ghostColour == PINK && moveType == PEN) {
                moveType = LEAVE;
            } else {
                currentDir = UP;
            }
        } else if(ghostY >= 16.5f && currentDir == UP) {
            currentDir = DOWN;
        }

        switch (currentDir) {
            case UP:
                ghostY += speed;
                break;
            case DOWN:
                ghostY -= speed;
                break;
        }
    }

    void portalCheck()
    {
        switch(getTile(ghostX, ghostY)){
            case P: if(getGhostX() >= 26.5) {
                        ghostX = 1.0f;
                    } else {
                        ghostX = 26.5;
                }
        }
    }

    void leaveMove()
    {
        if (ghostX <= 13.55 && ghostX >= 13.45) { 
            if (ghostY < 19.0f) { 
                currentDir = UP;
            }
        } else { 
            if (ghostX < 13.5f) { 
                currentDir = RIGHT;
            } else if (ghostX > 13.5f) {
                currentDir = LEFT;
            }
        }

        if(ghostY >= 19.0f) {
            currentDir = LEFT;
            if(isAtCenter()){
                moveType = SCATTER;
            }
        }

        if(moveType == LEAVE) { //Vi trong cuoc goi cuoi cung den phuong thuc nay moveType duoc thay doi nen chung van co the di chuyen 0 1f theo mot huong khi khong can thiet do do can kiem tra moveType
            switch (currentDir) {
                case LEFT:
                    ghostX -= speed;
                    break;
                case UP:
                    ghostY += speed;
                    break;
                case RIGHT:
                    ghostX += speed;
                    break;
                case DOWN:
                    ghostY -= speed;
                    break;
            }
        }
    }

    /**
     * Tao cac vector cho cac o muc tieu tuong ung tuy thuoc vao che do cua ma va cung nhu mau sac cua ma
     * @param ghostCol mau cua ma
     * @return vector chua toa do x va y cua o muc tieu
     */
    std::vector<int> getTargetTile(colour ghostCol)
    {
        std::vector<int> v;
        switch(moveType) {
            case CHASE:
                        switch (ghostCol) {
                            case RED:
                                v.push_back(pacman.getPacX());
                                v.push_back(pacman.getPacY());
                                break;
                            case BLUE:
                                switch(pacman.currentDir) {
                                    case LEFT:
                                        v.push_back(pacman.getPacX() - 2);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case UP:
                                        v.push_back(pacman.getPacX() );
                                        v.push_back(pacman.getPacY() + 2);
                                        break;
                                    case RIGHT:
                                        v.push_back(pacman.getPacX() + 2);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case DOWN:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY() - 2);
                                        break;
                                    default:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY());
                                }
                                break;
                            case YELLOW:
                                v.push_back(0);
                                v.push_back(0);
                                break;
                            case PINK:
                                switch(pacman.currentDir) {
                                    case LEFT:
                                        v.push_back(pacman.getPacX() - 4);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case UP:
                                        v.push_back(pacman.getPacX() );
                                        v.push_back(pacman.getPacY() + 4);
                                        break;
                                    case RIGHT:
                                        v.push_back(pacman.getPacX() + 4);
                                        v.push_back(pacman.getPacY());
                                        break;
                                    case DOWN:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY() - 4);
                                        break;
                                    default:
                                        v.push_back(pacman.getPacX());
                                        v.push_back(pacman.getPacY());
                                }
                                break;
                        }
                break;
            case SCATTER:
                    switch (ghostColour) {
                        case RED:
                            v.push_back(100);
                            v.push_back(100);
                            break;
                        case BLUE:
                            v.push_back(20);
                            v.push_back(0);
                            break;
                        case YELLOW:
                            v.push_back(0);
                            v.push_back(0);
                            break;
                        case PINK:
                            v.push_back(0);
                            v.push_back(100);
                            break;
                    }
                break;
            case DEATH:
                v.push_back(13.5);
                v.push_back(19);
                break;
        }

        return v;
    }

};
