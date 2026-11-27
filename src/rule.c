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
        //på nåt sätt vill vi koppla det här med forms[][][][]
        //ksk ba liksom basera på block X och Y och sedan plasera alla andra beroende på det
        //om den lika med 0, något lika med forms[0][0][k][] och för k går genom alla 4 och plussa på (0,4)på x och y lägga de???
    }

    if (tetrisOrder == 7 ){
        fisherYates(tetrisShapes);
        tetrisOrder = 0;
    }
}


void bool canPlace(int type, int rot, int px, int py){ 
    // ta in vilka värde för att kolla canPlace innan vi kör in riktiga värde
    bool check = true;

    for (int i = 0; i < 4; i++){
        int x = forms[type-1][rot][i][0] + px;
        int y = forms[type-1][rot][i][1] + py;

        if(x > 9 || x < 0 || y > 19 || y < 0 || board[y][x] != 0) {
            check = false; //om ngn av de e false så e det false
            return check;
        }
    } 
    return check;
}

void land() {
    bool canLand = false;

    for (int i = 0, i < 4; i++){
        blockY = forms[blockType-1][blockRotation][i][0];
        blockX = forms[blockType-1][blockRotation][i][1];
        
        if (board[blockY+1][blockX] != 0){ //den kan inte placeras i luften
            canLand = true;
        }
    } 

    return canLand;
}

void moveLeft() {
    if (canPlace(blockType, blockRotation, blockX-1, blockY)) {
        blockX--;
    }
}

void moveRight() {
    if (canPlace(blockType, blockRotation, blockX+1, blockY)) {
        blockX++;
    }
}

void rotation() {
    int rot = blockRotation;
    if (rot == 3) {
        rot = 0;
    }
    else {
        rot++;
    }

    if(canPlace(blockType, rot, blockX, blockY)) {
        blockRotation = rot;
    }
}

void hardDrop() {
    //för alla 4 blockpart
    //hmmmmmmmmmm
    while (board[blockY+1][blockX]==0) {
        //och canPlace
        blockY++;
    }
}

void lock() {

}

void clearLines() {
    //vi bechöver bara checka största Y värde blockY uppåt till mindre.

}


void bool gameOverCheck() {
    bool gameCheck = true;
    for (int i = 0; i < 10; i++) {
        if (board[0][i] != 0){
            gameCheck = false; //gameOver
        }
    }
    return gamecheck;
}

int forms[7][4][4][2]{ //blockType, blockrotation(moturs), blocktile, block coordinate
    { // 0, O 
        { {0,0}, {1,0}, {0,1}, {1,1} },
        { {0,0}, {1,0}, {0,1}, {1,1} },
        { {0,0}, {1,0}, {0,1}, {1,1} },
        { {0,0}, {1,0}, {0,1}, {1,1} }
    },
    { // 1, I
        { {0,1}, {1,1}, {2,1}, {3,1} },
        { {2,0}, {2,1}, {2,2}, {2,3} },
        { {0,2}, {1,2}, {2,2}, {3,2} },
        { {1,0}, {1,1}, {1,2}, {1,3} }
    },
    { // 2, S
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
    { // 7, T
        { {1,0}, {0,1}, {1,1}, {2,1} },
        { {1,0}, {1,1}, {2,1}, {1,2} },
        { {0,1}, {1,1}, {2,1}, {1,2} },
        { {1,0}, {0,1}, {1,1}, {1,2} }
    },};


