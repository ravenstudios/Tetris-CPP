#pragma once
#include "raylib.h"
#include "Constants.h"

struct Block{
    int x;
    int y;
};



enum class TetrominoType{I, O, T, S, Z, J, L};

class Tetromino{
    public:
        Tetromino();
        void Update(int fallSpeed);
        void Draw();

        int GetCol();
        int GetRow();
        int GetRotation();
        int GetType();
        Color GetColor();
        void SetDisabled(bool b);
        void SetPos(int c, int r);
        void GetNewTetromino();

    private:
        void Drop();
        void HandleKeys();
        bool CanFit(int col, int row, int rotation);
        void Rotate();
        void UpdateDropSpeed();
        bool CanMove(int dx, int dy);
        void GhostTetromino();
        void instantDrop();
        Color m_Color;
        int m_Col = 5;
        int m_Row = 0;

        float m_DropTimer = 0.0f;
        float m_DropDelay = 0.5f;

        bool m_Disabled = false;
        TetrominoType m_TetrominoType;

        int m_RotatePos = 0;
};