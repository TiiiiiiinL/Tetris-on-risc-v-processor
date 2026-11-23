/*
putPixel() / getPixel(): routines used to write a pixel to the VGA or retrieve a pixel from the VGA buffer.
scroll(): a routine that changes from which line in the buffer the VGA starts drawing
(check lecture 6 for more details)
clearScreen(): a routine that sets the screen to black (=0)
drawSprite(): a routine that draws a sprite to the screen at some location
(what is a sprite? Check hereLinks to an external site.)
*/

#include <stdint.h>

const int screenWidth = 320;
const int screenHeigth = 240;

volatile char *VGA = (volatile char *)0x08000000;

// need a color maker
// 8 bits of color gives 256 colors including black and white
// https://en.wikipedia.org/wiki/List_of_monochrome_and_RGB_color_formats
// According to wikipedia a popular 8 bit way is 3 red 3 green 2 blue
// and is used for VGA built-in output of the Digilent Inc. NEXYS 2, NEXYS 3 and BASYS2 FPGA boards

uint8_t colorMapper(int r, int g, int b)
{
    uint8_t color = 0b00000000;
    if (r >= 0 && r <= 7 && g >= 0 && g <= 7 && b > 0 && b <= 3)
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
    if (x <= screenWidth && y <= screenHeigth)
    {
        VGA[y * screenWidth + x] = color;
    }
}

// kolla return typ
int getPixel(int x, int y, )
{
    return VGA[y * screenWidth + x];
}

void scroll()
{
    return;
}

void clearScreen()
{
    for (int i = 0; i < screenWidth * screenHeigth; i++)
        VGA[i] = 0;
}

void drawSprite()
{
    return;
}
