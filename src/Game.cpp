#include "raylib.h"
#include "Game.h"
#include "Constants.h"
#include "Tetromino.h"
#include <string>
// {I, O, T, S, Z, J, L}

// int m_Board[COL][ROW];
// Tetromino m_CurrentTetrmonio = Tetromino();
// Tetromino m_NextTetrmonio = Tetromino();

// Tetromino m_HeldTetrmonio;



Game::Game(){
    m_CurrentTetrmonio = Tetromino();
    m_NextTetrmonio = Tetromino();
    m_NextTetrmonio.SetDisabled(true);
    m_NextTetrmonio.SetPos(12, 1);

    
    m_HeldTetrmonio = Tetromino();
    m_HeldTetrmonio.SetPos(-3, -10);
    m_HeldTetrmonio.SetDisabled(true);
}

void Game::SetNext(){
    m_CurrentTetrmonio = m_NextTetrmonio;
    m_CurrentTetrmonio.SetDisabled(false);
    m_CurrentTetrmonio.SetPos(5, 0);

    m_NextTetrmonio.GetNewTetromino();
    m_NextTetrmonio.SetDisabled(true);
    m_NextTetrmonio.SetPos(12, 1);
}

void Game::Update(){
    m_CurrentTetrmonio.Update(m_FallSpeed);
    
    if (IsKeyPressed(KEY_H)){
        Hold();    
    }
}   

void Game::Hold(){
    if(!m_CanHold) return;
    if (!m_HasHeldPiece){
        m_HeldTetrmonio = m_CurrentTetrmonio;
        m_HeldTetrmonio.SetPos(-5, 1);
        m_HasHeldPiece = true;
        SetNext();
        m_CanHold = false;
    }
    else{
        Tetromino temp = m_CurrentTetrmonio;
        m_CurrentTetrmonio = m_HeldTetrmonio;
        m_CurrentTetrmonio.SetPos(5, 0);
        m_HeldTetrmonio = temp;
        m_HeldTetrmonio.SetPos(-5, 1);
         m_CanHold = false;
        
    }
    
    
    
    
    
}


void Game::Draw(){ 
    DrawRectangleLines(X_OFFSET, Y_OFFSET, COL * BS, ROW * BS, WHITE);
    m_CurrentTetrmonio.Draw();
    DrawGrid();

    int nextWindowX = X_OFFSET + (COL * BS) + BS;
    DrawRectangleLines(nextWindowX, Y_OFFSET, BS * 5, BS * 5.5, WHITE);
    m_NextTetrmonio.Draw();

    DrawRectangleLines(X_OFFSET - (BS * 6), Y_OFFSET, BS * 5, BS * 5.5, WHITE);
    m_HeldTetrmonio.Draw();

    std::string s = "Lines:" + std::to_string(m_ClearedLines);
    DrawText(s.c_str(), nextWindowX, Y_OFFSET + BS * 7, 50, WHITE);
    

}


void Game::DrawGrid(){
    for (size_t c = 0; c < COL; c++){
        for (size_t r = 0; r < ROW; r++){
            if (m_Board[c][r].filled){
                DrawRectangle(c * BS + X_OFFSET, r * BS + Y_OFFSET, BS, BS, m_Board[c][r].color);
                DrawRectangleLines(c * BS + X_OFFSET, r * BS + Y_OFFSET, BS, BS, BLACK);
            }
        }
    }
    if(m_Gameover){
        DrawText("Game Over!!", GAME_WIDTH / 2 - (11 * 50), GAME_HEIGHT / 2, 50, WHITE);
    }
    
        
}


void Game::SetTetromnio(Tetromino t){
     m_CanHold = true;
    int col = t.GetCol();
    int row = t.GetRow();
    int rot  = t.GetRotation();
    int type = t.GetType();
    Color color = t.GetColor();


    for (size_t i = 0; i < 4; i++){
        int c = col + SHAPES[type][rot][i].x;
        int r = row + SHAPES[type][rot][i].y;
        m_Board[c][r].color = color;
        m_Board[c][r].filled = true;

    }
    ClearLines();
    

}

void Game::Gameover(){
    m_Gameover = true;
   
}

void Game::ClearLines() {
    for (int r = ROW - 1; r >= 0; r--) {

        bool full = true;

        // Is this row full?
        for (int c = 0; c < COL; c++) {
            if (!m_Board[c][r].filled) {
                full = false;
                break;
            }
        }

        if (full) {

            // Move every row above down one
            for (int y = r; y > 0; y--) {
                for (int c = 0; c < COL; c++) {
                    m_Board[c][y] = m_Board[c][y - 1];
                }
            }

            // Clear the new top row
            for (int c = 0; c < COL; c++) {
                m_Board[c][0].filled = false;
                m_Board[c][0].color = BLANK;
            }

            // Check this row again because new blocks fell into it
            r++;
            m_ClearedLines ++;
        }
    }
}


int Game::GetClearedLines(){
    return m_ClearedLines;
}


Cell (&Game::GetGrid())[COL][ROW] {
    return m_Board;
}
    
Game game;




        
