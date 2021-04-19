/*
    Exercise #10: Zodiac Signs
    Date completed: 04/18/2021
*/

#include <stdio.h>
#include <stdlib.h>
#define N 200

typedef struct{
    int year, month, day, index;
} Birthday;

int duplicate(int n,int idx, int trackArr[]);

int main(){    
    Birthday date;

    FILE* fpData;
    FILE* fpIn = fopen("data.in", "r");

    int i,idx = 0,size = 5;
    char strF[N];

    int *trackArr = (int*)malloc(sizeof(int)*size);

    if (!fpData && !fpIn) {
        printf("Oh no, an error occurred!\n");
        return -1;
    }

    // The dates will be based on the 2021 zodiac sign dates by http://bit.ly/3hEANZs

    while(fscanf(fpIn,"%d-%d-%d",&date.year,&date.month,&date.day) != EOF){ 
        fpData = fopen("data.for", "r");
        i = 0;
        switch(date.month){
            case 1:
                if(date.day<=19){            
                    printf("Capricorn: ");
                    date.index = 11;
                }else{            
                    printf("Aquarius: ");
                    date.index = 0;
                }
                break;
            case 2:
                if(date.day<=18){
                    printf("Aquarius: ");
                    date.index = 0;
                }else{
                    printf("Pisces: ");
                    date.index = 1;
                }
                break;
            case 3:
                if(date.day<=20){
                    printf("Pisces: ");
                    date.index = 1;
                }else{
                    printf("Aries: ");
                    date.index = 2;
                }
                break;
            case 4:
                if(date.day<=19){
                    printf("Aries: ");
                    date.index = 2;
                }else{
                    printf("Taurus: ");
                    date.index = 3;
                }
                break;
            case 5:
                if(date.day<=20){
                    printf("Taurus: ");
                    date.index = 3;
                }else{
                    printf("Gemini: ");
                    date.index = 4;
                }
                break;
            case 6:
                if(date.day<=20){
                    printf("Gemini: ");
                    date.index = 4;
                }else{
                    printf("Cancer: ");
                    date.index = 5;
                }
                break;
            case 7:
                if(date.day<=22){
                    printf("Cancer: ");
                    date.index = 5;
                }else{
                    printf("Leo: ");
                    date.index = 6;
                }
                break;
            case 8:
                if(date.day<=22){
                    printf("Leo: ");
                    date.index = 6;
                }else{
                    printf("Virgo: ");
                    date.index = 7;
                }
                break;
            case 9:
                if(date.day<=22){
                    printf("Virgo: ");
                    date.index = 7;
                }else{
                    printf("Libra: ");
                    date.index = 8;
                }
                break;
            case 10:
                if(date.day<=23){
                    printf("Libra: ");
                    date.index = 8;
                }else{
                    printf("Scorpio: ");
                    date.index = 9;
                }
                break;
            case 11:
                if(date.day<=21){
                    printf("Scorpio: ");
                    date.index = 9;
                }else{
                    printf("Sagittarius: ");
                    date.index = 10;
                }
                break;
            case 12:    
                if(date.day<=21){
                    printf("Sagittarius: ");
                    date.index = 10;
                }else{
                    printf("Capricorn: ");
                    date.index = 11;
                }
                break;        
            default:
                printf("Please enter a valid month!\n");
                break;
        }       
        
        while (fgets(strF, N, fpData) != NULL){

            if(i % 12 == date.index){        
                if(duplicate(i,idx,trackArr)){
                    i++;
                    continue;
                }    

                printf("%s",strF);
                trackArr[idx++] = i;
                break;
            }            
            i++;
        }                 

        if(idx == size){
            size += idx;
            trackArr = realloc(trackArr,sizeof(int)*size);
        }   
    }
    
    fclose(fpData);
    fclose(fpIn);

    free(trackArr);
    return 0;
}

int duplicate(int n,int idx, int trackArr[]){
    for(int i = 0; i<idx;i++){
        if(n==trackArr[i])
            return 1; 
    }
    return 0;
}
