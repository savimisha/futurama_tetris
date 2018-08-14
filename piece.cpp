#include "piece.h"

static const int coordsTable[7][4][2] = {
    { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
    { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
    { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
    { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
    { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
    { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
    { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
};

static const QColor colors[7] = {
    QColor(255,35,45), QColor(103,226,75), QColor(0,229,242), QColor(140,65,218), QColor(254,232,7), QColor(253,172,20), QColor(63,128,232)
};

Piece::Piece(PieceShape shape)
{
    x = BLOCK_SIZE * (BOARD_WIDTH / 2);
    y = 0;
    this->shape = shape;

    for (int i = 0; i < 4; i++)
    {
        cells[i].setPosition(lx() + coordsTable[shape][i][0], ly() + coordsTable[shape][i][1]);
        cells[i].setVisible(true);
        cells[i].setColor(colors[shape]);
    }
}

void Piece::addX(int diff)
{
    x += diff;

    for (int i = 0; i < 4; i++)
    {
        cells[i].setX(cells[i].x() + diff);
    }
}

void Piece::addY(int diff)
{
    y += diff;

    for (int i = 0; i < 4; i++)
    {
        cells[i].setY(cells[i].y() + diff);
    }
}

void Piece::rotateLeft()
{
    for (int i = 0; i < 4; i++)
    {
        int xx = (cells[i].x() - x);
        int yy = (cells[i].y() - y);
        cells[i].setPos(x + yy, y - xx);
    }
}

void Piece::rotateRight()
{
    for (int i = 0; i < 4; i++)
    {
        int xx = (cells[i].x() - x);
        int yy = (cells[i].y() - y);
        cells[i].setPos(x - yy, y + xx);
    }
}
