#ifndef VGA_H
#define VGA_H

int colorMapper(int r, int g, int b);
void putPixel(int x, int y, int color);
int getPixel(int x, int y);
void scroll(void);
void clearBuffer(void);
void drawRect(int x0, int y0, int width, int heigth, int color);
void drawBorder(int yOffset);
void drawTileOnGame(int horizontalTile, int verticaltile, int tileColor);
void drawQueue(int sprite[4][4], int yOffset);
void drawSprite(int x0, int y0, int sprite[4][4]);
void clearSprite(int x0, int y0, int sprite[4][4]);
void renderFrame(void);

#endif