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
int blockX;
int blockY;
int tetrisOrder = 0;



int tetrisShapes[7] = {1,2,3,4,5,6,7}; //se nedan för nummer motsvarar


void fisherYates(int tetrisShapes[]) {
    //bestämmer vilken ordning block landa
    //landa alla en gång och sen igen när vi är klar
    for (int i = 6; i > 0; i--) {
        int min = 0;
        int max = i;
        int x = rand() % (max - min + 1) + min;

        int temp = tetrisShapes[i];
        tetrisShapes[i] = tetrisShapes[x];
        tetrisShapes[x] = temp;
    }
};


void spawn(){
    //anropas efter vi starta spelet och efter den tidigare block har landats
    //kolla vilken form, beroende på form kolla i forms och ta den med rotation 0
    if (tetrisOrder < 7) {
        blockType = tetrisShapes[tetrisOrder];
        blockRotation = 0;
        blockX = 4;
        blockY = 0;
        tetrisOrder++;
        //om den lika med 0, något lika med form[0][0][k][] och för k går genom alla 4 och plussa på (0,4)på x och y lägga de???
    }

    if (tetrisOrder == 7 ){
        fisherYates(tetrisShapes);
        tetrisOrder = 0;
    }
}


void boolen canPlace(){
    /*om 0 <= y <= 20, 0 <= x <= 10, eller block har ngt under, alltså (y,x) + (1,0)*/
    if(blockX <= 10 && blockX >= 0 && blockY <= 20 && blockY >= 0 /*hur ska man skriva att det finns inget som är placerad där*/) {
        return true;
    }
    return false;
}

void moveLeft() {
    //d där grejen som triggrar igig
}

void moveRight() {

}

void dashDown() {

}

void boolen gameOverCheck() {
    if (/*(0,x) är inte lika med 0*/){
        return true; //gameOver
    }
    return false; //inte game over än
}

int forms[7][4][4][2]{ //blockType, blockrotation(moturs), blocktile, block coordinate
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
    { // J
        { {2,0}, {0,1}, {1,1}, {2,1} },
        { {1,0}, {1,1}, {1,2}, {2,2} },
        { {0,1}, {1,1}, {2,1}, {0,2} },
        { {0,0}, {1,0}, {1,1}, {1,2} }
    }    
    { // L
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


