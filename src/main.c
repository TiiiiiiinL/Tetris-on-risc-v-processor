#include "vga.h"

void handle_interrupt(unsigned _irq)
{
}

int main()
{
    clearBuffer();
    drawBorder();
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            drawTileOnGame(i, j);
        }
    }

    // renderFrame();
}
