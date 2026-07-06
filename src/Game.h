#pragma once
#include "raylib.h"
#include "Tetromino.h"
#include "Constants.h"

struct Cell
{
    bool filled = false;
    Color color = BLANK;
};

class Game{
    public:
        Game();
        void Update();
        void Draw();
        void DrawGrid();
        void SetTetromnio(Tetromino t);
        Cell (&GetGrid())[COL][ROW];
        void Gameover();
        void SetNext();
        int GetClearedLines();

    private:
        int m_FallSpeed = 5;
        Cell m_Board[COL][ROW];
        bool m_Gameover = false;
        Tetromino m_CurrentTetrmonio;
        Tetromino m_NextTetrmonio;
        Tetromino m_HeldTetrmonio;
        bool m_HasHeldPiece = false;
        bool m_CanHold = true;
        void ClearLines();
        void Hold();
        int m_ClearedLines = 0;

};
extern Game game;