/*
    Exercise #11: Student Information 2
    Date completed: 04/30/2021
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int number, yearLevel, age, grade, index;
    char firstN[15], lastN[15], course[15],sex[15];
} Record;

Record subSelection(int n, Record student,FILE *temp);
void displayAll(FILE *fp);
void menu();
void subMenu();
void drop();
void edit(FILE *fp);
void intFilter(FILE *fp, int n);
void strFilter(FILE *fp, int n);
void stringSort();
void intSort();
int enrol(FILE *fp);
int intCheck(Record student, int num,int n);
int stringCheck(Record student, char *str,int n);
int numRecords(FILE *fp);
int stringCompare(char s1[], char s2[]);
char toLower(char ch);
char toUpper(char ch);

int main(){
    int n, studentNum;
    FILE *fp = fopen("records.bin","rb+");

    if (!fp) {
        printf("Oh no, an error occurred!\n");
        return -1;
    }
    do{
        fseek(fp,0,SEEK_SET);
        menu();
        scanf("%d",&n);
        printf("\n");
        switch(n){
            case 1:
                printf("Enrol\n");
                studentNum = enrol(fp);
                printf("\n");
                printf("%d added!\n",studentNum);
                break;
            case 2:
                printf("Drop a student\n");
                drop();
                break;
            case 3:
                edit(fp);
                break;
            case 4:
                displayAll(fp);
                break;
            case 5:
                printf("Filter students by last name: ");
                strFilter(fp,1);
                break;
            case 6:
                printf("Filter students by student number: ");
                intFilter(fp,1);
                break;
            case 7:
                printf("Filter students by year level: ");
                intFilter(fp,2);
                break;
            case 8:
                printf("Filter students by course: ");
                strFilter(fp,2);
                break;
            case 9:
                printf("Filter students by sex: ");
                strFilter(fp,3);
                break;
            case 10:
                printf("Filter students by passing:\n");
                intFilter(fp,3);
                break;
            case 11:
                printf("Filter students by failing:\n");
                intFilter(fp,4);
                break;
            case 12:
                printf("Sort students by last name:\n\n");
                stringSort();
                displayAll(fp);
                break;
            case 13:
                printf("Sort students by student number:\n\n");
                intSort();
                displayAll(fp);
                break;
            case 14:
                break;    
            default:
                printf("Please enter a valid selection!\n");
                break;
        }        
    }while(n != 14);
    
    fclose(fp);
    return 0;
}

int enrol(FILE *fp){
    Record student;
    int temp,flag;

    while(1){
        while(1){
            fseek(fp,0,SEEK_SET);

            flag = 1;
            printf("Student number: ");
            scanf("%d",&temp);

            do{
                if (temp == student.number) {
                    printf("Student %d is already enrolled!\n", student.number);
                    flag = 0;
                    break;
                }
            }while(fread(&student, sizeof(Record), 1, fp) && !feof(fp));

            if(flag)
                break;
        }

        if(temp > 0 && temp <= 300){
            student.number = temp;
            printf("Last name: ");
            scanf("%s",student.lastN);
            printf("First name: ");
            scanf("%s",student.firstN);
            printf("Course: ");
            scanf("%s",student.course);
            printf("Year level: ");
            scanf("%d",&student.yearLevel);
            printf("Age: ");
            scanf("%d",&student.age);
            printf("Sex: ");
            scanf("%s",student.sex);
            printf("Final grade: ");
            scanf("%d",&student.grade);

            fseek(fp, sizeof(Record) * (student.number - 1),SEEK_SET);
            fwrite(&student, sizeof(Record), 1, fp);

            return student.number;
            
        }else{        
            printf("Invalid Student Number\n");
        }
    }
}

void edit(FILE *fp){
    Record student, wala;
    FILE *temp;
    int n,num,flag = 0;

    temp = fopen("temp.bin","wb");

    fseek(fp,0,SEEK_SET);    

    printf("Student number: ");
    scanf("%d",&num);

    while(fread(&student, sizeof(Record), 1, fp)){
        if(student.number == num){
            printf("\nEdit: %d\n",num);

            do{
                subMenu();
                scanf("%d",&n);
                printf("\n");
                student = subSelection(n,student,temp);
            }while(n != 9);   

            fwrite(&student, sizeof(Record),1,temp);
            flag = 1;
        }
        else{
            fwrite(&student, sizeof(Record),1,temp);
        }
    }

    fclose(temp);
    fseek(fp,0,SEEK_SET);  

    if(flag){
        temp = fopen("temp.bin","rb");

        while(fread(&student,sizeof(Record),1,temp))
            fwrite(&student,sizeof(Record),1,fp);        
        
        fclose(temp);
    }else{
        printf("\nThis student is not enrolled.\n");
    }
}

void drop(){
    Record student;
    FILE *fp, *temp;
    int num, flag = 0;

    fp = fopen("records.bin","rb");
    temp = fopen("temp.bin","wb");

    fseek(fp,0,SEEK_SET);    

    printf("Student number: ");
    scanf("%d",&num);

    while(fread(&student, sizeof(Record), 1, fp)){
        if(student.number == num)
            flag = 1;        
        else
            fwrite(&student, sizeof(Record),1,temp);
        
    }
    fclose(fp);
    fclose(temp);   

    if(flag){
        temp = fopen("temp.bin","rb");
        fp = fopen("records.bin","wb");

        while(fread(&student,sizeof(Record),1,temp))
            fwrite(&student,sizeof(Record),1,fp);
        
        fclose(fp);
        fclose(temp);
        
        printf("\nStudent Dropped.\n");
    }else{
        printf("\nThis student is not enrolled.\n");
    }
}

int intCheck(Record student, int num,int n){
    switch (n){
        case 1:        
            if(student.number == num )
                return 1;
            break;
        case 2:
            if(student.yearLevel == num)
                return 1;
            break;
        case 3:
            if(student.grade >= 60)
                return 1;
            break;
        case 4:
            if(student.grade < 60)
                return 1;
            break;
        default:
            break;
    }
    return 0;
}
int stringCheck(Record student, char *str,int n){
    switch(n){
        case 1:
            for(int i = 0; student.lastN[i] != '\0';i++)
                if(toLower(student.lastN[i]) != toLower(str[i]))
                    return 0;                            
            str[0] = toUpper(str[0]);
            break;
        case 2:
            for(int i = 0; student.course[i] != '\0';i++){           
                str[i] = toUpper(str[i]);                   
                if(toUpper(student.course[i]) != str[i])
                    return 0;  
            }
            break;
        case 3:
            for(int i = 0; student.sex[i] != '\0';i++){         
                if(toLower(student.sex[i]) != toLower(str[i]))
                    return 0;  
            }
            str[0] = toUpper(str[0]);
            break;
        default:
            break;
    }
    return 1;
}

void intFilter(FILE *fp, int n){
    fseek(fp,0,SEEK_SET);
    Record student;
    int count = 0, num;

    fflush(stdin);
    if(n == 1 || n == 2)
        scanf("%d",&num);

    printf("\n");

    do{
        if (student.number > 0 && student.number <= 300){
            if(intCheck(student,num,n)){
                printf("Student number: %d\n",student.number);
                printf("Last name: %s\n",student.lastN);
                printf("First name: %s\n",student.firstN);
                printf("Course: %s\n",student.course);
                printf("Year level: %d\n",student.yearLevel);      
                printf("Age: %d\n",student.age);      
                printf("Sex: %s\n",student.sex);  
                printf("Final grade: %d\n",student.grade);       
                printf("\n");
                count++;
            }
        }
    }while(fread(&student, sizeof(Record), 1, fp) && !feof(fp));

    if(count)
        printf("Displaying %d of %d student(s)\n",count,numRecords(fp));
    else
        printf("No student(s) found.\n");
}

void strFilter(FILE *fp, int n){
    fseek(fp,0,SEEK_SET);
    Record student;
    int count = 0;
    char str[15];

    fflush(stdin);
    scanf("%s",str);

    printf("\n");

    do{
        if (student.number > 0 && student.number <= 300){
            if(stringCheck(student,str,n)){
                printf("Student number: %d\n",student.number);
                printf("Last name: %s\n",student.lastN);
                printf("First name: %s\n",student.firstN);
                printf("Course: %s\n",student.course);
                printf("Year level: %d\n",student.yearLevel);      
                printf("Age: %d\n",student.age);      
                printf("Sex: %s\n",student.sex);  
                printf("Final grade: %d\n",student.grade);       
                printf("\n");
                count++;
            }
        }
    }while(fread(&student, sizeof(Record), 1, fp) && !feof(fp));

    if(count)
        printf("Displaying %d of %d student(s)\n",count,numRecords(fp));
    else
        printf("No student(s) found.\n");
}

void displayAll(FILE *fp){
    int count = 0;
    Record student;
    fseek(fp,0,SEEK_SET);

    while(fread(&student, sizeof(Record), 1, fp) && !feof(fp)) {
        if (student.number != 0) {
            printf("Student number: %d\n",student.number);
            printf("Last name: %s\n",student.lastN);
            printf("First name: %s\n",student.firstN);
            printf("Course: %s\n",student.course);
            printf("Year level: %d\n",student.yearLevel);      
            printf("Age: %d\n",student.age);      
            printf("Sex: %s\n",student.sex);  
            printf("Final grade: %d\n",student.grade);       
            printf("\n");
            count++;
        }
    }
    printf("Displaying %d of %d student(s)\n",count,count);
}

void menu(){
    printf("\n");
    printf("1. Enrol a student\n");
    printf("2. Drop a student\n");
    printf("3. Edit a student\n");
    printf("4. Display all students\n");
    printf("5. Filter students by last name\n");
    printf("6. Filter students by student number\n");
    printf("7. Filter students by year level\n");
    printf("8. Filter students by course\n");
    printf("9. Filter students by sex\n");
    printf("10. Filter students by passing\n");
    printf("11. Filter students by failing\n");
    printf("12. Sort students by last name\n");
    printf("13. Sort students by student number\n");
    printf("14. Exit\n");
    printf("\n");
    printf("? ");
}

void subMenu(){
    printf("1. Student number\n");
    printf("2. Last name\n");
    printf("3. First name\n");
    printf("4. Course\n");
    printf("5. Year level\n");
    printf("6. Age\n");
    printf("7. Sex\n");
    printf("8. Final grade\n");
    printf("9. Back\n");
    printf("\n");
    printf("? ");
}

Record subSelection(int n, Record student,FILE *temp){
    switch(n){
        case 1:            
            printf("Student number: ");
            scanf("%d",&student.number);
            printf("\nStudent number updated!\n");
            break;
        case 2:
            printf("Last name: ");
            scanf("%s",student.lastN);
            printf("\nLast name updated!\n");
            break;
        case 3:
            printf("First name: ");
            scanf("%s",student.firstN);
            printf("\nFirst name updated!\n");
            break;
        case 4:
            printf("Course: ");
            scanf("%s",student.course);
            printf("\nCourse updated!\n");
            break;
        case 5:           
            printf("Year level: ");
            scanf("%d",&student.yearLevel);
            printf("\nYear level updated!\n");
            break;
        case 6:
            printf("Age: ");
            scanf("%d",&student.age);
            printf("\nAge updated!\n");
            break;
        case 7:
            printf("Sex: ");
            scanf("%s",student.sex);
            printf("\nSex updated!\n");
            break;
        case 8:
            printf("Final grade (%d): ",student.grade);
            scanf("%d",&student.grade);
            printf("\nFinal grade updated!\n");
            break;
        case 9:
            break;
        default:
            printf("Please enter a valid selection!\n");
            break;
    }
    printf("\n");
    return student;
}

char toLower(char ch){
    if(ch>=65 && ch<=90)
        return (int)ch+32;
    return ch;
}

char toUpper(char ch){
    if(ch>=97 && ch<=122)
        return (int)ch-32;
    return ch;
}

int numRecords(FILE *fp){
    int count = 0;
    Record student;
    fseek(fp,0,SEEK_SET);

    while(fread(&student, sizeof(Record), 1, fp) && !feof(fp)) {    
        if(student.number != 0)   
            count++;        
    }
    return count;
}

int stringCompare(char s1[], char s2[]){    
    for(int i=0;i<15;i++){
        if(toLower(s1[i])>toLower(s2[i]))
            return 1;        
        else if(toLower(s1[i])<toLower(s2[i]))            
            return 0;
        else
            continue;
    }
}

void stringSort(){
    FILE *fp, *temp;
    int i = 0,size;

    fp = fopen("records.bin","rb");
    temp = fopen("temp.bin","wb");
    size = numRecords(fp);

    fseek(fp,0,SEEK_SET);

    Record student, sArr[size], buffer, *tempArr;

    while(fread(&student, sizeof(Record), 1, fp)){
        if(student.number > 0 && student.number <= 300)
            sArr[i++] = student;           
    }

    for(int i=0;i<size;i++){        
        for(int j = i+1; j<size;j++){            
            if(stringCompare(sArr[i].lastN,sArr[j].lastN)){
                student = sArr[i];
                sArr[i] = sArr[j];
                sArr[j] = student;          
            }
        }
    }

    for(int idx = 0; idx < size;idx++){
        if (student.number > 0 && student.number <= 300)
            fwrite(&sArr[idx], sizeof(Record),1,temp);        
    }

    fclose(fp);
    fclose(temp); 

    temp = fopen("temp.bin","rb");
    fp = fopen("records.bin","wb");

    while(fread(&student,sizeof(Record),1,temp))
        fwrite(&student,sizeof(Record),1,fp);        
        
    fclose(fp);
    fclose(temp);
}
void intSort(){
    FILE *fp, *temp;
    int i = 0,size;

    fp = fopen("records.bin","rb");
    temp = fopen("temp.bin","wb");

    size = numRecords(fp);

    fseek(fp,0,SEEK_SET);

    Record student, sArr[size], buffer, *tempArr;

    while(fread(&student, sizeof(Record), 1, fp)){
        if(student.number > 0 && student.number <= 300)
            sArr[i++] = student;              
    }

    for(int i=0;i<size;i++){        
        for(int j = i+1; j<size;j++){            
            if(sArr[i].number > sArr[j].number){
                student = sArr[i];
                sArr[i] = sArr[j];
                sArr[j] = student;          
            }
        }
    }

    for(int idx = 0; idx < size;idx++){
        if (student.number > 0 && student.number <= 300)
            fwrite(&sArr[idx], sizeof(Record),1,temp);        
    }

    fclose(fp);
    fclose(temp); 

    temp = fopen("temp.bin","rb");
    fp = fopen("records.bin","wb");

    while(fread(&student,sizeof(Record),1,temp))
        fwrite(&student,sizeof(Record),1,fp);        
        
    fclose(fp);
    fclose(temp);
}
