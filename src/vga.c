/*
putPixel() / getPixel(): routines used to write a pixel to the VGA or retrieve a pixel from the VGA buffer.
scroll(): a routine that changes from which line in the buffer the VGA starts drawing
(check lecture 6 for more details)
clearScreen(): a routine that sets the screen to black (=0)
drawSprite(): a routine that draws a sprite to the screen at some location
(what is a sprite? Check hereLinks to an external site.)
*/

#include <stdint.h>
#include <stdlib.h>

// #include "altera_up_avalon_character_buffer.h"
//  Documentation talks about this on page 17 but i need the header file somehow

const int screenWidth = 320;
const int screenHeigth = 240;
const int bufferHeigth = 480;

const int tileSize = 8;

const int borderLength = tileSize * 10;
const int borderHeigth = tileSize * 20;
const int borderThickness = 2;
const int horizontalPadding = (screenWidth - borderLength) / 2;
const int verticalPadding = (screenHeigth - borderHeigth) / 2;

// add variables for background, border, tiles etc. colors

const int colorWhite = 255;
const int colorDarkGrey = 36;

volatile char *VGA = (volatile char *)0x08000000;
volatile int *VGACTRl = (volatile int *)0x04000100;

// change name?
unsigned int y_ofs = 0;

// need a color maker
// 8 bits of color gives 256 colors including black and white
// https://en.wikipedia.org/wiki/List_of_monochrome_and_RGB_color_formats
// According to wikipedia a popular 8 bit way is 3 red 3 green 2 blue
// and is used for VGA built-in output of the Digilent Inc. NEXYS 2, NEXYS 3 and BASYS2 FPGA boards

uint8_t colorMapper(int r, int g, int b)
{
    uint8_t color = 0b00000000;
    if (r >= 0 && r <= 7 && g >= 0 && g <= 7 && b >= 0 && b <= 3)
    {
        r = r << 5;
        g = g << 2;
        color = r + g + b;
        return color;
    }
    return 0;
}

void putPixel(int x, int y, uint8_t color)
{
    // Check that x and y are not too big
    if (x < screenWidth && y < bufferHeigth)
    {
        VGA[y * screenWidth + x] = color;
    }
}

// kolla return typ
int getPixel(int x, int y)
{
    return VGA[y * screenWidth + x];
}

void scroll()
{
    return;
}

void clearBuffer()
{
    for (int i = 0; i < screenWidth; i++)
    {
        for (int j = 0; j < bufferHeigth; j++)
        {
            putPixel(i, j, 0);
        }
    }
}

void drawRect(int x0, int y0, int width, int heigth, uint8_t color)
{
    for (int i = x0; i < x0 + width; i++)
    {
        for (int j = y0; j < y0 + heigth; j++)
        {
            putPixel(i, j, color);
        }
    }
}

void drawBorder(int yOffset)
{
    // horizontal
    drawRect(horizontalPadding, verticalPadding - borderThickness + yOffset, borderLength, borderThickness, 255);
    drawRect(horizontalPadding, verticalPadding + borderHeigth + yOffset, borderLength, borderThickness, 255);

    // vertical
    drawRect(horizontalPadding - borderThickness, verticalPadding - borderThickness + yOffset, borderThickness, borderHeigth + 4, 255);
    drawRect(horizontalPadding + borderLength, verticalPadding - borderThickness + yOffset, borderThickness, borderHeigth + 4, 255);
}

void drawTileOnGame(int horizontalTile, int verticalTile, int tileColor)
{
    int x = (horizontalTile * tileSize) + horizontalPadding;
    int y = (verticalTile * tileSize) + verticalPadding;

    // refactor color code
    switch (tileColor)
    {
    case 0:
        // inner square
        drawRect(x + 1, y + 1, tileSize - 2, tileSize - 2, 63);
        // highlight
        putPixel(x + 1, y + 1, 255);
        putPixel(x + 2, y + 2, 255);
        putPixel(x + 2, y + 3, 255);
        putPixel(x + 3, y + 2, 255);
        // horizontal border
        drawRect(x, y, tileSize, 1, colorDarkGrey);
        drawRect(x, y + tileSize - 1, tileSize, 1, colorDarkGrey);
        // vertical border
        drawRect(x, y, 1, tileSize, colorDarkGrey);
        drawRect(x + tileSize - 1, y, 1, tileSize, colorDarkGrey);
        break;
    case 1:
        // inner square
        drawRect(x + 1, y + 1, tileSize - 2, tileSize - 2, 2);
        // highligth
        putPixel(x + 1, y + 1, 255);
        putPixel(x + 2, y + 2, 255);
        putPixel(x + 2, y + 3, 255);
        putPixel(x + 3, y + 2, 255);
        // horizontal border
        drawRect(x, y, tileSize, 1, colorDarkGrey);
        drawRect(x, y + tileSize - 1, tileSize, 1, colorDarkGrey);
        // vertical border
        drawRect(x, y, 1, tileSize, colorDarkGrey);
        drawRect(x + tileSize - 1, y, 1, tileSize, colorDarkGrey);
        break;
    case 2:
        // inner square
        drawRect(x + 1, y + 1, tileSize - 2, tileSize - 2, 255);
        // inner edge
        drawRect(x + 1, y + 1, tileSize - 2, 1, 2);
        drawRect(x + 1, y + tileSize - 2, tileSize - 2, 1, 2);
        drawRect(x + 1, y + 1, 1, tileSize - 2, 2);
        drawRect(x + tileSize - 2, y + 1, 1, tileSize - 2, 2);
        // horizontal border
        drawRect(x, y, tileSize, 1, colorDarkGrey);
        drawRect(x, y + tileSize - 1, tileSize, 1, colorDarkGrey);
        // vertical border
        drawRect(x, y, 1, tileSize, colorDarkGrey);
        drawRect(x + tileSize - 1, y, 1, tileSize, colorDarkGrey);
        // highligth
        putPixel(x + 1, y + 1, 255);
        break;
    default:
        break;
    }
}

void clearTileOnGame(int horizontalTile, int verticalTile)
{
    int x = (horizontalTile * tileSize) + horizontalPadding;
    int y = (verticalTile * tileSize) + verticalPadding;
    drawRect(x, y, tileSize, tileSize, 0);
}

//fix color
void draw2dArray(int Array[20][10])
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            drawTileOnGame(i, j, color % 3);
        }
    }
}

void drawSprite(int x0, int y0, int sprite[4][4])
{
    // this does not check edgecollision yet
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (sprite[i][j] > 0)
            {
                drawTileOnGame(i + x0, j + y0, 1);
            }
        }
    }
}

void clearSprite(int x0, int y0, int sprite[4][4])
{
    // this does not check edgecollision yet
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (sprite[i][j] > 0)
            {
                clearTileOnGame(i + x0, j + y0);
            }
        }
    }
}

// take in the current bag and show index to show?
void drawQueue(int sprite[4][4], int yOffset)
{
    drawRect(horizontalPadding + borderLength + 10, screenHeigth / 2 - 20 + (yOffset * 240), 44, 2, colorWhite);
    drawRect(horizontalPadding + borderLength + 10, screenHeigth / 2 + 22 + (yOffset * 240), 44, 2, colorWhite);

    drawRect(horizontalPadding + borderLength + 10, screenHeigth / 2 - 20 + (yOffset * 240), 2, 44, colorWhite);
    drawRect(horizontalPadding + borderLength + 52, screenHeigth / 2 - 20 + (yOffset * 240), 2, 44, colorWhite);

    drawSprite(12, 8 + (yOffset * 30), sprite);
}

void drawHold()
{
    return;
}

// wrtie to the backbuffer control to swap the fram being shown.
void renderFrame()
{
    *(VGACTRl + 1) = (unsigned int)(VGA + (y_ofs * 240) * 320);
    *(VGACTRl + 0) = 0;
    if (y_ofs == 0)
    {
        y_ofs = 1;
    }
    else
    {
        y_ofs = 0;
    }
}
