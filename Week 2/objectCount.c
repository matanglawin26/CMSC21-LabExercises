#include <stdio.h>

int countCells(int row,int col,int x, int y,int mat[row][col]);

int main(){
    
    int n,m,count = 0;

    scanf("%d %d",&n,&m);

    int mat[n][m];

    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            scanf(" %d",&mat[i][j]);
        }
    }

    for(int i=0;i<n;i++){
	for(int j=0;j<m;j++){
		if(mat[i][j] == 1)
                	count+=countCells(i,j,n,m,mat);            
        }
    }
    
    printf("%d\n",count);
    
    return 0;
}

int countCells(int x,int y,int n, int m,int mat[n][m]){   

    if(x<0 || y<0 || x>=n || y>=m)
		return 0;
    
    if(mat[x][y] == 0)
        return 0;

    mat[x][y] = 0;    

    for(int row = x-1;row<x+2;row++){
        for(int col = y-1;col<y+2;col++){
            if(row!=x || col!=y)
                countCells(row,col,n,m,mat);            
        }
    }
    
    return 1;
}
