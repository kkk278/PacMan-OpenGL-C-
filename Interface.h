extern int score;
extern int lives;

void drawScore(int scorePrint)
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(16.5, 32.5); 
    drawTex(score_tex, 45, 15, 0); 
    translateToMazeCoords(4, -1.0); 
    std::string str = std::to_string(scorePrint); 

    for(int i = str.length() -1; i>=0 ; i--) { 
        switch(str[i]) {
            case '0':
                drawTex(num_0_tex, 8, 8, 0);
                break;
            case '1':
                drawTex(num_1_tex, 8, 8, 0);
                break;
            case '2':
                drawTex(num_2_tex, 8, 8, 0);
                break;
            case '3':
                drawTex(num_3_tex, 8, 8, 0);
                break;
            case '4':
                drawTex(num_4_tex, 8, 8, 0);
                break;
            case '5':
                drawTex(num_5_tex, 8, 8, 0);
                break;
            case '6':
                drawTex(num_6_tex, 8, 8, 0);
                break;
            case '7':
                drawTex(num_7_tex, 8, 8, 0);
                break;
            case '8':
                drawTex(num_8_tex, 8, 8, 0);
                break;
            case '9':
                drawTex(num_9_tex, 8, 8, 0);
                break;
        }
        translateToMazeCoords(-1, 0); 
    }
    glPopMatrix();
}

void drawLives(int liveCount)
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(2, -2); 
    for(int i = 0; i < liveCount - 1; i++) { 
        drawTex(pac_1_tex, 14, 14, 0);
        translateToMazeCoords(2, 0); 
    }
    glPopMatrix();
}

int getHighScore()
{
    int highScore;
    std::fstream scoreFile("high_score.txt"); 
    if(scoreFile.good()) { 
        scoreFile >> highScore;
        scoreFile.close(); 
        return highScore; 
    } else { 
        std::ofstream highScoreFile("high_score.txt"); 
        highScoreFile << 0; 
        scoreFile.close(); 
        highScoreFile.close();
    }
    return 0; 
}

void setHighScore(int score)
{
    int currentHigh = getHighScore(); 
    if(currentHigh < score) { 
        std::ofstream highFile("high_score.txt"); 
        highFile.clear(); 
        highFile << score; 
        highFile.close(); 
    }
}

void drawHigh()
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(6.0, 32.5); 
    drawTex(high_tex, 36, 15, 0); 
    translateToMazeCoords(3, -1.0); 
    std::string str = std::to_string(getHighScore()); 

    for(int i = str.length() -1; i>=0 ; i--) { 
        switch(str[i]) {
            case '0':
                drawTex(num_0_tex, 8, 8, 0);
                break;
            case '1':
                drawTex(num_1_tex, 8, 8, 0);
                break;
            case '2':
                drawTex(num_2_tex, 8, 8, 0);
                break;
            case '3':
                drawTex(num_3_tex, 8, 8, 0);
                break;
            case '4':
                drawTex(num_4_tex, 8, 8, 0);
                break;
            case '5':
                drawTex(num_5_tex, 8, 8, 0);
                break;
            case '6':
                drawTex(num_6_tex, 8, 8, 0);
                break;
            case '7':
                drawTex(num_7_tex, 8, 8, 0);
                break;
            case '8':
                drawTex(num_8_tex, 8, 8, 0);
                break;
            case '9':
                drawTex(num_9_tex, 8, 8, 0);
                break;
        }
        translateToMazeCoords(-1, 0); 
    }
    glPopMatrix();
}

void drawReady()
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(11.5f, 13.0f); 
    drawTex(ready_tex,40, 8, 0);
    glPopMatrix();
}

void drawGameOver()
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(10.0f, 12.00f); 
    drawTex(gameover_tex,65, 20, 0);
    glPopMatrix();
}

void drawRestart()
{
    glPushMatrix();
    translateBottomLeft();
    translateToMazeCoords(7.0f, 8.5f); 
    drawTex(restart_tex, 115, 30, 0); 
    glPopMatrix();
} 

void drawInterface()
{
    drawHigh();
    drawScore(score);
    drawLives(lives);
}
