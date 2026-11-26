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

const int screenWidth = 320;
const int screenHeigth = 240;
const int bufferHeigth = 480;

volatile char *VGA = (volatile char *)0x08000000;
volatile int *VGACTRl = (volatile int *)0x04000100;

int color1;

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
    if (x < screenWidth && y < screenHeigth)
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

void drawBorder()
{
    drawRect(115, 25, 90, 5, 255);
    drawRect(115, 210, 90, 5, 255);

    drawRect(110, 25, 5, 190, 255);
    drawRect(205, 25, 5, 190, 255);
}

void drawTileOnGame(int horizontalTile, int verticalTile)
{
    int x = (horizontalTile * 9) + 115;
    int y = (verticalTile * 9) + 30;
    int tileColor = (horizontalTile + verticalTile) % 3;

    switch (tileColor)
    {
    case 0:
        drawRect(x + 1, y + 1, 8, 8, 63);
        putPixel(x + 1, y + 1, 255);
        putPixel(x + 2, y + 2, 255);
        putPixel(x + 2, y + 3, 255);
        putPixel(x + 3, y + 2, 255);
        drawRect(x, y, 9, 1, colorMapper(1, 1, 0));
        drawRect(x, y + 8, 8, 1, colorMapper(1, 1, 0));
        drawRect(x, y, 1, 9, colorMapper(1, 1, 0));
        drawRect(x + 8, y, 1, 9, colorMapper(1, 1, 0));
        break;
    case 1:
        drawRect(x + 1, y + 1, 8, 8, 2);
        putPixel(x + 1, y + 1, 255);
        putPixel(x + 2, y + 2, 255);
        putPixel(x + 2, y + 3, 255);
        putPixel(x + 3, y + 2, 255);
        drawRect(x, y, 9, 1, colorMapper(1, 1, 0));
        drawRect(x, y + 8, 8, 1, colorMapper(1, 1, 0));
        drawRect(x, y, 1, 9, colorMapper(1, 1, 0));
        drawRect(x + 8, y, 1, 9, colorMapper(1, 1, 0));
        break;
    case 2:
        drawRect(x + 1, y + 1, 8, 8, 255);
        drawRect(x, y, 9, 1, 2);
        drawRect(x, y + 8, 8, 1, 2);
        drawRect(x, y, 1, 9, 2);
        drawRect(x + 8, y, 1, 9, 2);
        break;
    default:
        break;
    }
}

void draw2dArray()
{
    return;
}

void drawQueue()
{
    return;
}

void drawHold()
{
    return;
}

void drawSprite()
{
    return;
}

// wrtie to the backbuffer control to swap the fram being shown.
void renderFrame()
{
    *(VGACTRl + 1) = (unsigned int)(VGA + y_ofs * 320);
    *(VGACTRl + 0) = 0;
    y_ofs = (y_ofs + 1) % 240;
}
