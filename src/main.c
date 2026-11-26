#include "vga.h"

void handle_interrupt(unsigned _irq)
{
}

// TODO
// fix y offset for frame 1 and 2
// add edge collision
// add draw 2darray (placed blocks)
// add row clear animation

int main()
{
    int tileFrameOffset = 30;
    int currentSpriteX = 0;
    int currentSpriteLastX = -1;
    int currentSpriteY = 0;
    int currentFrame = 0;
    int sprite[4][4] = {{0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0}};
    clearBuffer();
    drawBorder(0);
    drawQueue(sprite);
    for (int i = 0; i < 10; i++)
    {
        for (int j = 5; j < 20; j++)
        {
            drawTileOnGame(i, j, i % 3);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        for (int j = 5; j < 20; j++)
        {
            drawTileOnGame(i, j + tileFrameOffset, i % 3);
        }
    }

    while (1)
    {
        if (currentFrame == 0)
        {
            clearSprite(currentSpriteLastX, currentSpriteY, sprite);
            currentSpriteX = currentSpriteX + 1;
            currentSpriteLastX = currentSpriteLastX + 1;
            drawSprite(currentSpriteX, currentSpriteY, sprite);
            drawBorder(0);
            drawQueue(sprite, 0);
            renderFrame();
            currentFrame++;
            for (int i = 0; i < 10000000; i++)
            {
                asm volatile("nop");
            }
        }
        // else
        {

            clearSprite(currentSpriteLastX, currentSpriteY + tileFrameOffset, sprite);
            currentSpriteX = currentSpriteX + 1;
            currentSpriteLastX = currentSpriteLastX + 1;
            drawSprite(currentSpriteX, currentSpriteY + tileFrameOffset, sprite);
            drawBorder(240);
            drawQueue(sprite, 1);
            renderFrame();
            currentFrame--;
            for (int i = 0; i < 10000000; i++)
            {
                asm volatile("nop");
            }
        }
    }
}
