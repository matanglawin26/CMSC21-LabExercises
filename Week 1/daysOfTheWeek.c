/*
    Exercise #3: Day of the Week
    Date completed: 03/02/2021
*/
#include <stdio.h>

int isLeapYear(int y);
int date(int l,int month,int day);
int gauss(int y,int m);
int firstDay(int y);
int operation(int d);
int suffix(int n);

typedef struct{
    int year,month,day;
} cal;

int main(){
    int feb,result,weekDay,first;
    cal time;

    char days[7][10] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};

    do{
        // printf("Enter Valid Date: ");
        scanf("%d %d %d",&time.year,&time.month,&time.day);
    }while(time.year < 0 || (time.month < 0 || time.month > 12) || (time.day < 0 || time.day > 31));

    if(isLeapYear(time.year))
        feb = 29;
    else
        feb = 28;
    
    result = date(feb,time.month,time.day);
    weekDay = (firstDay(time.year)+operation(result)-1)%7;

    printf("%s, ",days[weekDay]);

    switch(suffix(result)){
        case 1:
            printf("%dst day of the year\n",result);
            break;
        case 2:
            printf("%dnd day of the year\n",result);
            break;
        case 3:
            printf("%drd day of the year\n",result);
            break;
        default:
            printf("%dth day of the year\n",result);
            break;
    }

        
    return 0;
}
int isLeapYear(int y){
    if(y%4==0){
        if(y%100!=0 || (y%100==0 && y%400==0))
            return 1;        
    }else{
        return 0;
    }
}
int date(int l,int month,int day){
    int list[] = {31,l,31,30,31,30,31,31,30,31,30,31};

    for(int i = 0; i<month-1;i++)
        day += list[i];
    
    return day;
}
int gauss(int y,int m){
    return y%m;
}
int firstDay(int y){
    return gauss(1+5*gauss(y-1,4)+4*gauss(y-1,100)+6*gauss(y-1,400),7);
}
int operation(int d){
    while(d>=8){
        d-=7;
    }
    return d;
}
int suffix(int n){
    switch(n%10){
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        default:
            return 0;
    }
}
