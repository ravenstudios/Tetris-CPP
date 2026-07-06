#include "Tetromino.h"
#include "Constants.h"
#include <iostream>
#include <string>
#include "Game.h"
#include <random>


float currentDropDelay = 0;
Color colors[7] = {SKYBLUE, YELLOW, PURPLE, GREEN, RED, BLUE, ORANGE};

Tetromino::Tetromino(){
    GetNewTetromino();
}


void Tetromino::Update(int fallSpeed){
    UpdateDropSpeed();
    HandleKeys();  
    Drop();
}


void Tetromino::UpdateDropSpeed(){
    int level = game.GetClearedLines() / 10;

    float normalDelay = 0.5f - (level * 0.05f);

    if (normalDelay < 0.05f)
        normalDelay = 0.05f;

    if (IsKeyDown(KEY_DOWN))
        m_DropDelay = 0.05f;
    else
        m_DropDelay = normalDelay;
}


void Tetromino::Drop(){
    m_DropTimer += GetFrameTime();

    if (m_DropTimer >= m_DropDelay){
        if (!CanMove(0, 0)){
            game.Gameover();
            return;
        }

        if(CanMove(0, 1)){
            m_Row += 1;  
            m_DropTimer = 0.0f;
        }
        else{
            game.SetTetromnio(*this);
            game.SetNext();
        }  
        
           
    }
}

bool Tetromino::CanMove(int dx, int dy) {
    Cell (&grid)[COL][ROW] = game.GetGrid();

    int type = (int)m_TetrominoType;
    int rot = m_RotatePos;

    for (int i = 0; i < 4; i++) {
        int x = m_Col + SHAPES[type][rot][i].x + dx;
        int y = m_Row + SHAPES[type][rot][i].y + dy;

        if (x < 0 || x >= COL || y < 0 || y >= ROW) {
            return false;
        }

        if (grid[x][y].filled) {
            return false;
        }
    }

    return true;
}

void Tetromino::GhostTetromino(){
    int ghostRow = 1;
    while (CanMove(0, ghostRow)){
        ghostRow++;
    }
    
    for (size_t i = 0; i < 4; i++)
    {
        int x = SHAPES[(int)m_TetrominoType][m_RotatePos][i].x + m_Col;
        int y = SHAPES[(int)m_TetrominoType][m_RotatePos][i].y + m_Row + ghostRow - 1;
        DrawRectangle(x * BS + X_OFFSET, y * BS + Y_OFFSET, BS, BS, {255, 255, 255, 175});
        DrawRectangleLines(x * BS + X_OFFSET, y * BS + Y_OFFSET, BS, BS, BLACK);
    }
}


void Tetromino::instantDrop(){
    int ghostRow = 1;
    while (CanMove(0, ghostRow)){
        ghostRow++;
    }
    m_Row += ghostRow - 1;
}


void Tetromino::HandleKeys(){
    if (IsKeyPressed(KEY_SPACE)){
        Rotate();
    }

    if (IsKeyPressed(KEY_LEFT)){
        if (CanMove(-1, 0)){
            m_Col --;  
        }     
    }

    if (IsKeyPressed(KEY_RIGHT)){
        if (CanMove(1, 0)){
            m_Col ++;  
        }
    }
    
    if (IsKeyPressed(KEY_UP)){
        instantDrop();
    }
}


void Tetromino::GetNewTetromino() {
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_int_distribution<int> dist(0, 6);

    int index = dist(rng);

    m_TetrominoType = static_cast<TetrominoType>(index);
    m_Color = colors[index];

    
    // m_Row = 0;
    // m_Col = 5;
}

void Tetromino::Draw(){
    GhostTetromino();
    for (size_t i = 0; i < 4; i++)
    {
        int x = SHAPES[(int)m_TetrominoType][m_RotatePos][i].x + m_Col;
        int y = SHAPES[(int)m_TetrominoType][m_RotatePos][i].y + m_Row;
        DrawRectangle(x * BS + X_OFFSET, y * BS + Y_OFFSET, BS, BS, m_Color);
        DrawRectangleLines(x * BS + X_OFFSET, y * BS + Y_OFFSET, BS, BS, BLACK);
    }
    
}



bool Tetromino::CanFit(int col, int row, int rotation){
    for (int i = 0; i < 4; i++){
        Point p = SHAPES[(int)m_TetrominoType][rotation][i];

        int boardCol = col + p.x;
        int boardRow = row + p.y;

        if (boardCol < 0) return false;
        if (boardCol >= COL) return false;
        if (boardRow < 0) return false;
        if (boardRow >= ROW) return false;
    }

    return true;
}


void Tetromino::Rotate(){
    int newRotation = (m_RotatePos + 1) % 4;

    int kicks[] = {0, -1, 1, -2, 2};

    for (int i = 0; i < 5; i++){
        int testCol = m_Col + kicks[i];

        if (CanFit(testCol, m_Row, newRotation)){
            m_Col = testCol;
            m_RotatePos = newRotation;
            return;
        }
    }
}

void Tetromino::SetDisabled(bool b){
    m_Disabled = b;
}

void Tetromino::SetPos(int c, int r){
    m_Col = c;
    m_Row = r;
}

int Tetromino::GetCol(){return m_Col;}
int Tetromino::GetRow(){return m_Row;}
int Tetromino::GetRotation(){return m_RotatePos;}
int Tetromino::GetType(){return (int)m_TetrominoType;}
Color Tetromino::GetColor(){return m_Color;}



