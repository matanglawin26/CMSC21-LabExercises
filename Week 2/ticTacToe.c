#include <stdio.h>

int score(char a[5][11],int posX[],int posY[]);
int move(int flag, int turn,int m,int n);
int blackout(char a[5][11],int posX[],int posY[]);

int main(){
    int flag = 0, turn = 1,m=0,n=0, out, draw;
    int posX[3] = {0,2,4};
    int posY[3] = {1,5,9};

    char grid[5][11] = {
        "   |   |   ",
        "---+---+---",
        "   |   |   ",     
        "---+---+---",
        "   |   |   "  
    };

    while(1){      
        for(int i = 0; i<5;i++){
            for(int j = 0;j<11;j++){
                if(i==posX[m-1] && j==posY[n-1]){
                    if(grid[i][j]=='X' || grid[i][j]=='O')
                        flag = 1;                    
                    else if(grid[i][j]==' '){
                        if(turn)
                            grid[i][j] = 'O';
                        else
                            grid[i][j] = 'X';
                        flag = 0;
                    }
                }
                printf("%c",grid[i][j]);
            }
            printf("\n");
        }

        out = score(grid,posX,posY);
        draw = blackout(grid,posX,posY);

        if(out || draw)
            break;        

        turn = move(flag,turn,m,n);

        printf("\n");

        do{
            // printf("Enter Valid Row (1-3): ");
            printf("Row: ");
            scanf("%d",&m);
        }while(m<1||m>3);
        
        do{
            // printf("Enter Valid Column (1-3): ");
            printf("Column: ");
            scanf("%d",&n);
        }while(n<1||n>3);

        printf("\n");
    }
    
    if(draw)
        printf("\nDraw!\n");
    else if(turn)
        printf("\nO is the winner!\n");
    else
        printf("\nX is the winner!\n");
    
    return 0;
}

int score(char a[5][11],int x[],int y[]){
    for(int i = 0;i<3;i++){
        if(a[x[i]][y[0]] != ' '){
            if(a[x[i]][y[0]] == a[x[i]][y[1]] && a[x[i]][y[1]] == a[x[i]][y[2]] && a[x[i]][y[0]] == a[x[i]][y[2]])
                return 1;            
        }
    }
    for(int j = 0;j<3;j++){
        if(a[x[0]][y[j]] != ' '){
            if(a[x[0]][y[j]] == a[x[1]][y[j]] && a[x[1]][y[j]] == a[x[2]][y[j]] && a[x[0]][y[j]] == a[x[2]][y[j]])
                return 1;            
        }
    }
    if(a[x[1]][y[1]] != ' '){
        if(a[x[0]][y[0]] == a[x[1]][y[1]] && a[x[1]][y[1]] == a[x[2]][y[2]] && a[x[0]][y[0]] == a[x[2]][y[2]])
            return 1;        
    }
    if(a[x[1]][y[1]] != ' '){
        if(a[x[0]][y[2]] == a[x[1]][y[1]] && a[x[1]][y[1]] == a[x[2]][y[0]] && a[x[0]][y[2]] == a[x[2]][y[0]])
            return 1;        
    }

    return 0;
}

int move(int flag, int turn,int m,int n){

    if(flag){
        printf("(%d, %d) Occupied!\n",m,n);
        if(turn){
            printf("O's turn\n");
            return 1;
        }
        else{
            printf("X's turn\n");
            return 0;
        }
    }

    if(turn){
        printf("X's turn\n");
        return 0;
    }else{
        printf("O's turn\n");
        return 1;
    }
}
int blackout(char a[5][11],int posX[],int posY[]){
    for(int i = 0;i<3;i++){
        for(int j=0;j<3;j++){
            if(a[posX[i]][posY[j]] == ' ')
                return 0;            
        }
    }
    return 1;
}