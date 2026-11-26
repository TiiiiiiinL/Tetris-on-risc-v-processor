#include "vga.h"

void handle_interrupt(unsigned _irq)
{
}

int main()
{
    int x = 0;
    int lastX = -1;
    int y = 0;
    int currentFrame = 0;
    int sprite[4][4] = {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
    clearBuffer();
    drawBorder(0);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 5; j < 20; j++)
        {
            drawTileOnGame(i, j, i % 3);
        }
    }
    while (1)
    {
        if (currentFrame == 0)
        {
            clearSprite(lastX, y, sprite);
            x = x + 1;
            lastX = lastX + 1;
            drawSprite(x, y, sprite);
            drawBorder(0);
            renderFrame();
            currentFrame++;
            for (int i = 0; i < 10000000; i++)
            {
                asm volatile("nop");
            }
        }
        else
        {

            clearSprite(lastX, y + 27, sprite);
            x = x + 1;
            lastX = lastX + 1;
            drawSprite(x, y + 27, sprite);
            drawBorder(240);
            renderFrame();
            currentFrame--;
            for (int i = 0; i < 10000000; i++)
            {
                asm volatile("nop");
            }
        }
    }
}
