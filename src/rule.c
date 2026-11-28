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

void lock() { 
    //det här ska kopplas med canPlace på nåt sätt
    //en block ska lock om block inte kan flyttas ner mer
    if(!canPlace(blockType, blockRotation, blockX, blockY+1)) {
        bool canLand = false;

        for (int i = 0; i < 4; i++){
            int y = forms[blockType-1][blockRotation][i][1] + blockY;
            int x = forms[blockType-1][blockRotation][i][0] + blockX;
            
            if (board[y+1][x] != 0){ //den kan inte placeras i luften
                canLand = true;
            }
        } 

        for (int i = 0; i < 4; i++){
            int y = forms[blockType-1][blockRotation][i][1] + blockY;
            int x = forms[blockType-1][blockRotation][i][0] + blockX;
            
            if (canLand){ //den kan inte placeras i luften
                board[y][x] = 1;    //behöver vi olika siffror? fråga jonas
            }
        } 
    }
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
    //om y+1 canPlace så flytta ner en steg tills den inte canPlace och placera på den förra
    //hmmmmmmmmmm
    if (canPlace(blockType, blockRotation, blockX, blockY+1)) {
        blockY++;
        hardDrop();
    }
    else {
        lock();
        break;
    }
}


void clearLine(int y) { //inputta lägsta randen som ha landat typ
    //vi bechöver bara checka största Y värde blockY uppåt till mindre.
    //om en rad full ( inte finns board[a][b] =0)
    //då... flytta hela board[y-1][] till y. 
    //gör så med alla rader och sätt rad[0][x] till alla nollor

    //kallas varje gång efter placerat en ruta
    bool fullLine = true;
    for(int x = 0; x < 10; x++) {
        if(board[y][x] == 0) { //om det nån gång finns en värde som är 0, då inte full
            fullLine = false;
        }
    }

    if(fullLine) {
        for (int i = y; i > 0; i--) {
            board[i] = board[i-1];
        }
        board[0] = [0,0,0,0,0,0,0,0,0,0];
    }
    else{
        break;
    }

    clearLine(y);
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


