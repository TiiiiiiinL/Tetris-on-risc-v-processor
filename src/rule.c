#include <stdio.h>
#include <stdlib.h>
/*
TODO:
Blocks //
Rotation
CanPlace //kolla om den inuti board / på botten / träffa nåt
Lock
CheckFuLLRows
ClearLines
ShuffleBag
...

*/


int board[20][10];
//startpunkt för piece centrum börjar i (0,5)    
//(y,x)
int blockType; 
int blockRotation;


int canPlace(){

int tetrisShapes[7] = {1,2,3,4,5,6,7}; //se nedan för nummer motsvarar


void fisherYates(int tetrisShapes[]) {
    for (int i = 6; i > 0; i--) {
        int min = 0;
        int max = i;
        int x = rand() % (max - min + 1) + min;

        int temp = tetrisShapes[i];
        tetrisShapes[i] = tetrisShapes[x];
        tetrisShapes[x] = temp;
    }
}



};


int forms[7][4][4][2]{ //blockType, blockrotation, blocktile, block coordinate
    { // O
        { {0,0}, {1,0}, {0,1}, {1,1} },
        { {0,0}, {1,0}, {0,1}, {1,1} },
        { {0,0}, {1,0}, {0,1}, {1,1} },
        { {0,0}, {1,0}, {0,1}, {1,1} }
    },
    { // I
        { {0,1}, {1,1}, {2,1}, {3,1} },
        { {2,0}, {2,1}, {2,2}, {2,3} },
        { {0,2}, {1,2}, {2,2}, {3,2} },
        { {1,0}, {1,1}, {1,2}, {1,3} }
    },
    { // S
        { {1,0}, {2,0}, {0,1}, {1,1} },
        { {1,0}, {1,1}, {2,1}, {2,2} },
        { {1,1}, {2,1}, {0,2}, {1,2} },
        { {0,0}, {0,1}, {1,1}, {1,2} }
    },
    { // Z
        { {0,0}, {1,0}, {1,1}, {2,1} },
        { {2,0}, {1,1}, {2,1}, {1,2} },
        { {0,1}, {1,1}, {1,2}, {2,2} },
        { {1,0}, {0,1}, {1,1}, {0,2} }
    },
    { // L
        { {2,0}, {0,1}, {1,1}, {2,1} },
        { {1,0}, {1,1}, {1,2}, {2,2} },
        { {0,1}, {1,1}, {2,1}, {0,2} },
        { {0,0}, {1,0}, {1,1}, {1,2} }
    }    
    { // J
        { {0,0}, {0,1}, {1,1}, {2,1} },
        { {1,0}, {2,0}, {1,1}, {1,2} },
        { {0,1}, {1,1}, {2,1}, {2,2} },
        { {1,0}, {1,1}, {0,2}, {1,2} }
    },
    { // T
        { {1,0}, {0,1}, {1,1}, {2,1} },
        { {1,0}, {1,1}, {2,1}, {1,2} },
        { {0,1}, {1,1}, {2,1}, {1,2} },
        { {1,0}, {0,1}, {1,1}, {1,2} }
    },};


