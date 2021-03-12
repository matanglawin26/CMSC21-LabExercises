/*
    Exercise #6: Snakes and Ladders
    Date completed: 03/13/2021
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 31
#define M 51
#define SIZE 10

typedef struct{
    int id,x,y,win,fall,climb;
} data;

typedef struct{
    int startX,startY,endX,endY,startPos,endPos;
    int i,j;
} data2;


void printBoard(char **bPtr);
void updateBoard(char **bPtr, int *posX, int *posY,data2 *snakeMain,data2 *ladderMain);
void printTurn(int turn);
void who(int turn,int die,data *player);
void snakeLoc(data2 *snakeMain, int *spHPtr,int *spTPtr);
void ladderLoc(data2 *ladderMain,int *spHPtr,int *spTPtr);
int rollDie();
int movePlayer(int turn,int index);
data playerLoc(int *position, int turn, int move, data player, data2 *snake,data2 *ladder);

int main(){
    srand((unsigned int)time(NULL));  
    
    data2 *snakePtr,*ladderPtr; // pointers to the data2 struct

    char board[N][M]={
        "+----+----+----+----+----+----+----+----+----+----+",
        "|#   |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+",
        "|    |    |    |    |    |    |    |    |    |    |", 
        "|    |    |    |    |    |    |    |    |    |    |", 
        "+----+----+----+----+----+----+----+----+----+----+"
    };    

    // Memory Allocation part (idk if acceptable kay lesson ni for next week, pero g lang)
    char **bPtr = (char **)malloc(N*sizeof(char*));
    *bPtr = (char *)malloc(sizeof(char)*N*M);

    for (int i = 0; i < N; i++)
        *(bPtr+i) = (*bPtr + M*i);
    
    for(int i=0;i<N;i++)
        for(int j =0;j<M;j++)
            *(*(bPtr+i)+j) = *(*(board+i)+j);    

    data player;
    data2 S1,S2,S3,L1,L2,L3;

    data2 snakeMain[3] = {S1,S2,S3};
    data2 ladderMain[3] = {L1,L2,L3};

    // Pointer 
    snakePtr = snakeMain;
    ladderPtr = ladderMain;

    // Arrays for tracking purposes (e.g. player pos, snakes and ladders' pos)
    int posX[10] = {29,26,23,20,17,14,11,8,5,2};
    int spotsH[6] = {0,0,0,0,0,0};
    int spotsT[6] = {0,0,0,0,0,0};
    int currX[4] = {29,29,29,29};
    int currY[4] = {1,2,3,4};
    int track[4] = {1,1,1,1};

    int *tPtr, *spHPtr,*spTPtr,*moveX,*moveY,die,turn=0;

    tPtr = track;
    spHPtr = spotsH;
    spTPtr = spotsT;
    moveX = currX;
    moveY = currY;
    
    snakeLoc(snakePtr,spHPtr,spTPtr); // modifies and stores the values of the randomized position of the snakes
    ladderLoc(ladderPtr,spHPtr,spTPtr); // modifies and stores the values of the randomized position of the ladders
    
    updateBoard(bPtr,moveX,moveY,snakePtr,ladderPtr); // initializes the board
    printBoard(bPtr); // prints the board once

    while(1){  
            die = rollDie(); 

            printTurn(turn);

            // getting the player's x and y position
            player = playerLoc(tPtr,turn,die,player,snakePtr,ladderPtr); 
            *(moveX+turn) = *(posX+player.x);        
            *(moveY+turn) = movePlayer(turn,player.y);    
            
            fflush(stdin); // clears the input buffer      
            scanf("%[^\n]"); // accepts enter as input
            
            // updates and prints the board with the new position of the player
            updateBoard(bPtr,moveX,moveY,snakePtr,ladderPtr); 
            printBoard(bPtr); 

            who(turn,die,&player); // displays the current player

            // condition to terminate the loop and end the game
            if(player.win){
                printf("Player '%c' won the game!\n",(char)player.id+97);
                break;
            }

            turn++;

            if(turn>3) // if turn surpasses the total number of players (4), it will reset the counter to 0
                turn = 0;
    }

    return 0;
}

void configure(char **bPtr){
    
}

void printBoard(char **bPtr){    
    // prints the board
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){            
            printf("%c",*(*(bPtr + i)+j));
        }
        printf("\n");
    }
}

void updateBoard(char **bPtr, int *posX, int *posY, data2 *snakeMain,data2 *ladderMain){
    int x[20]={1,2,4,5,7,8,10,11,13,14,16,17,19,20,22,23,25,26,28,29}; // the board's x positions (rows) where it is legible for modification
    int y[40]={
        1,2,3,4,6,7,8,9,11,12,
        13,14,16,17,18,19,21,22,23,24,
        26,27,28,29,31,32,33,34,36,37,
        38,39,41,42,43,44,46,47,48,49
    }; // the board's y positions (columns) where it is legible for modification

    for(int i=19;i>=0;i--){ // loop for the rows
        for(int j=0;j<40;j++){ // loop for the columns
            
             *(*(bPtr + *(x+i))+*(y+j)) = ' '; // erases the previous positions of the players before placing the new position (remove this line to see the effect)

            for(int k=0;k<4;k++){ // loop for the four players
                switch(k){ // switch case for identifying which player's position will be changed
                    case 0:     
                        if(*(x+i) ==*(posX+k) && *(y+j) ==*(posY+k))
                             *(*(bPtr + *(x+i))+*(y+j)) = 'a';
                        break;
                    case 1:            
                        if(*(x+i) == *(posX+k) && *(y+j )==*(posY+k))
                             *(*(bPtr + *(x+i))+*(y+j)) = 'b';               
                        break;
                    case 2:            
                        if(*(x+i) == *(posX+k) && *(y+j )==*(posY+k))
                             *(*(bPtr + *(x+i))+*(y+j)) = 'c';         
                        break;
                    case 3:     
                        if(*(x+i) == *(posX+k) && *(y+j )==*(posY+k))
                             *(*(bPtr + *(x+i))+*(y+j)) = 'd';        
                        break;
                    default:
                        break;
                }
            }
            for(int s=0;s<3;s++){ // loop for placing the (3) snakes and ladders' head and tails
                if(*(x+i) == (*(snakeMain+s)).startX && *(y+j)==(*(snakeMain+s)).startY)
                     *(*(bPtr + *(x+i))+*(y+j)) = 'S';
                if(*(x+i) == (*(snakeMain+s)).endX && *(y+j)==(*(snakeMain+s)).endY)
                     *(*(bPtr + *(x+i))+*(y+j)) = 's';
                    
                if(*(x+i) == (*(ladderMain+s)).startX && *(y+j)==(*(ladderMain+s)).startY)
                     *(*(bPtr + *(x+i))+*(y+j)) = 'L';
                if(*(x+i) == (*(ladderMain+s)).endX && *(y+j)==(*(ladderMain+s)).endY)
                     *(*(bPtr + *(x+i))+*(y+j)) = 'l';
            }
            
        }
    }

    *(*(bPtr + 1)+1) = '#'; // placing # for the finish line
}

int rollDie(){
    return rand() % 6 + 1; 
}

void who(int turn,int die,data *player){
    printf("%c rolls a %d!\n",(char)97+turn,die);

    if((*player).fall){
        printf("%c lands on a snake and falls down!\n",(char)97+turn);
        (*player).fall = 0;
    }

    if((*player).climb){
        printf("%c lands on a ladder and goes up!\n",(char)97+turn);
        (*player).climb = 0;
    }
}

void printTurn(int turn){

    printf("%c's turn.\n",(char)97+turn);
    printf("%c, press <Enter> to roll.\n",(char)97+turn);

}

data playerLoc(int *position,int turn, int move, data player, data2 *snake,data2 *ladder){
    int arr[SIZE][SIZE]; // initializing array for the quasi s&b
    int reverse = 1;

    *(position+turn)+=move; // tracks the position of the player

    if(*(position+turn)>=100){ // if statement when the current player reached or passed the 100th position
        player.win = 1;
        player.id = turn;
        player.x = 9;
        player.y = 0;
        return player; // returns the player to signify that the game has ended
    }else{ // otherwise the game continues
        player.win = 0;
        player.fall = 0;
        player.climb = 0;
    }

    for(int i=9;i>=0;i--){
        for(int j=0;j<10;j++){
            if(reverse) // since the direction of each row of the board is alternating, we initialize each row separately
                *(*(arr+i)+j) = ((i*10)+(10-j-1)+1); // (e.q in the 2nd row from the start, the counting is 20 19 18 17 16 15 14 13 12 11)        
            else         
                *(*(arr+i)+j) = ((i*10)+j+1); // (e.g in the 1st row (the final row), the counting is 1 2 3 4 5 6 7 8 9 10) 
            
            if(*(position+turn) == *(*(arr+i)+j)){ // if statement when the player's current position is equal with the cell position of the quasi board
                player.x = i; // i will the player's x pos
                player.y = j; // j will the player's y pos
                for(int s = 0;s<3;s++){ // for loop if the cell that the player has landed on contains a snake or a ladder
                    if(*(position+turn) == (*(snake+s)).startPos){ // if a player lands on a snake, the player's position will now be tail position of the snake
                        player.fall = 1;
                        player.x = (*(snake+s)).i;
                        player.y = (*(snake+s)).j;
                        *(position+turn) = (*(snake+s)).endPos;
                    }
                    if(*(position+turn) == (*(ladder+s)).startPos){ // if a player lands on a ladder, the player's position will now be end position of the ladder
                        player.climb = 1;
                        player.x = (*(ladder+s)).i;
                        player.y = (*(ladder+s)).j;
                        *(position+turn) = (*(ladder+s)).endPos;
                    }
                }
            }
        }
        reverse = !reverse;
    }
    return player;
}
void randomGenerator(int id, int *headPtr,int *tailPtr,int *spHPtr,int *spTPtr){
    // this function is for generating the random placements of the snakes and ladders at every start of the game
    // this function also makes sure that there will be no duplicate positions since it will impact the flow of the game

    int rngH,rngT,flag;
    
    if(id){ // code block for the snake
        for(int i=0;i<3;i++){ // loops until all the snakes' head and tail have their respective position
            while(1){
                flag = 1;
                rngH = rand() % 99 + 1; // random number from 1 to 99
                rngT = rand() % 99 + 1;
                for(int j=0;j<6;j++){ // iterates through the spotsH and spotsT array to check for duplicate numbers
                    if((rngH-7 <= rngT) || (rngH == *(spHPtr+j) || rngT == *(spTPtr+j))) // if the head's pos of the snake is less than the tail it creates a flag and if there are no duplicates 
                        flag=0;
                                            
                }

                if(flag) // the while loop will only terminate if the head's pos is greater than the tail's pos AND if the generated number has no duplicate in the spotsH and spotsT
                    break;
                
            }
            *(headPtr+i) = rngH; // generated random position of the snake's head
            *(tailPtr+i) = rngT; // generated random position of the snake's tail
            *(spHPtr+i) = rngH; // updates the spotsH array 
            *(spTPtr+i) = rngT; // updates the spotsT array      
        }
    }else{ // code block for the ladder
        for(int i=0;i<3;i++){ // loops until all the ladders' start and end have their respective position
            while(1){
                flag = 1;
                rngH = rand() % 98 + 2; // random number from 2 to 99 (since the 1st pos should have no ladder)
                rngT = rand() % 98 + 2;
                for(int j=0;j<6;j++){
                    if((rngH+7 >= rngT) || (rngH == *(spHPtr+j) || rngT == *(spTPtr+j))) // same principle as the snakes             
                        flag=0;                    
                }

                if(flag)
                    break;
                
            }
            // same principle
            *(headPtr+i) = rngH;
            *(tailPtr+i) = rngT;      
            *(spHPtr+i+3) = rngH;
            *(spTPtr+i+3) = rngT;               
        }
    }
}
void snakeLoc(data2 *snakeMain, int *spHPtr,int *spTPtr){
    int arr[SIZE][SIZE];
    int reverse = 1;
    int sH[3],sT[3]; // 2 arrays for storing the positions of the 3 heads and tails of the snake

    randomGenerator(1,sH,sT,spHPtr,spTPtr); // invoking the randgenerator function

    int snakes[3][2] = {
        {sH[0],sT[0]},
        {sH[1],sT[1]},
        {sH[2],sT[2]}
    }; // the 2d array which contains the start and end position of each snakes

    int posX[10] = {28,25,22,19,16,13,10,7,4,1}; // the legible rows in which the snakes can be put
    int posY[10] = {4,9,14,19,24,29,34,39,44,49}; // the legible columns in which the snakes can be put

    // looping through the array snakes and the pointer snakeMain
    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            switch(j){
                case 0: // all first columns of each row are the start (head) position of each snake
                    (*(snakeMain+i)).startPos = *(*(snakes+i)); // updates the data2 structs inside the struct array 'snakeMain' with the start position of the snake     
                    break;
                case 1: // all second columns of each row are the start (head) position of each snake
                    (*(snakeMain+i)).endPos = *(*(snakes+i)+1); // updates the data2 structs inside the struct array 'snakeMain' with the end position of the snake     
                    break;            
                default:
                    break;
            }
        }
    }

    // creating and looping through the quasi board (same procedure in the playerLoc function)
    for(int i=9;i>=0;i--){
        for(int j=0;j<10;j++){
            for(int k=0;k<3;k++){
                if(reverse)
                    *(*(arr+i)+j) = ((i*10)+(10-j-1)+1);           
                else         
                    *(*(arr+i)+j) = ((i*10)+j+1);
                
                if((*(snakeMain+k)).startPos == *(*(arr+i)+j)){ // if statement when the current cell position of the quasi board is equal to the start pos (head) of the snake
                    (*(snakeMain+k)).startX = *(posX+i); // retrieves the x pos of the board
                    (*(snakeMain+k)).startY = *(posY+j); // retrieves the y pos of the board
                }
                if((*(snakeMain+k)).endPos == *(*(arr+i)+j)){ // if statement when the current cell position of the quasi board is equal to the end pos (tail) of the snake
                    (*(snakeMain+k)).endX = *(posX+i); // retrieves the x pos of the board
                    (*(snakeMain+k)).endY = *(posY+j); // retrieves the y pos of the board
                    (*(snakeMain+k)).i = i; // gets the ith index of the board (for the player's updated position)
                    (*(snakeMain+k)).j = j; // gets the jth index of the board (for the player's updated position)
                }
            }
        }
        reverse = !reverse;
    }
}
void ladderLoc(data2 *ladderMain, int *spHPtr,int *spTPtr){ 
    // same procedure with the snakeLoc function
    int arr[SIZE][SIZE];
    int reverse = 1;

    int lH[3],lT[3];

    randomGenerator(0,lH,lT,spHPtr,spTPtr);

    int ladders[3][2] = {
        {lH[0],lT[0]},
        {lH[1],lT[1]},
        {lH[2],lT[2]}
    };

    int posX[10] = {28,25,22,19,16,13,10,7,4,1};
    int posY[10] = {4,9,14,19,24,29,34,39,44,49};

    for(int i=0;i<3;i++){
        for(int j=0;j<2;j++){
            switch(j){
                case 0:
                    (*(ladderMain+i)).startPos = *(*(ladders+i));                 
                    break;
                case 1:
                    (*(ladderMain+i)).endPos = *(*(ladders+i)+1); 
                    break;            
                default:
                    break;
            }
        }
    }

    for(int i=9;i>=0;i--){
        for(int j=0;j<10;j++){
            for(int k=0;k<3;k++){
                if(reverse)
                    *(*(arr+i)+j) = ((i*10)+(10-j-1)+1);            
                else         
                    *(*(arr+i)+j) = ((i*10)+j+1);
                
                if((*(ladderMain+k)).startPos == *(*(arr+i)+j)){
                    (*(ladderMain+k)).startX = *(posX+i);
                    (*(ladderMain+k)).startY = *(posY+j);
                }
                if((*(ladderMain+k)).endPos == *(*(arr+i)+j)){
                    (*(ladderMain+k)).endX = *(posX+i);
                    (*(ladderMain+k)).endY = *(posY+j);
                    (*(ladderMain+k)).i = i;
                    (*(ladderMain+k)).j = j;
                }
            }
        }
        reverse = !reverse;
    }
}
int movePlayer(int turn,int index){
    // function to return the player's new y pos (column)
    
    int posYA[SIZE] = {1,6,11,16,21,26,31,36,41,46};
    int posYB[SIZE] = {2,7,12,17,22,27,32,37,42,47};
    int posYC[SIZE] = {3,8,13,18,23,28,33,38,43,48};
    int posYD[SIZE] = {4,9,14,19,24,29,34,39,44,49};

    switch(turn){
        case 0:
            return *(posYA+index);
        case 1:
            return *(posYB+index);
        case 2:
            return *(posYC+index);
        case 3:
            return *(posYD+index);
        default:
            break;
    }
}
