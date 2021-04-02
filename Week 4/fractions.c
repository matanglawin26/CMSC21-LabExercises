#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int numerator, denominator,whole;
} frac;

frac toFrac();
void getLCD(frac *f1,frac *f2);
int gcd(frac f);
frac add(frac f1,frac f2);
frac subtract(frac f1,frac f2);
frac multiply(frac f1,frac f2);
frac divide(frac f1,frac f2);
frac simplify(frac f);

int main(){
    int n;
    frac f1, f2, out;

    do{
        scanf("%d",&n);
    }while(n<1||n>5);
    
    f1 = toFrac();

    if(n>=1 && n<5){
        f2 = toFrac();
    }

    switch(n){
        case 1:
            out = add(f1,f2);
            break;
        case 2:
            out = subtract(f1,f2);
            break;
        case 3:
            out = multiply(f1,f2);
            break;
        case 4:
            out = divide(f1,f2);
            break;
        case 5:
            out = simplify(f1);
            break;    
        default:
            break;
    }

    switch (out.whole){
        case 1:
            printf("1\n");
            break;
        case 2:
            printf("%d\n",out.numerator);
            break;
        default:
            printf("%d/%d\n",out.numerator,out.denominator);
            break;
    }
    
    return 0;
}

frac add(frac f1,frac f2){
    frac *ptr1,*ptr2, out;

    ptr1 = &f1;
    ptr2 = &f2;
    
    getLCD(ptr1,ptr2);

    out.numerator = f1.numerator+f2.numerator;
    out.denominator = f1.denominator;

    out = simplify(out);

    return out;
}
frac subtract(frac f1,frac f2){
    frac *ptr1,*ptr2, out;
    
    ptr1 = &f1;
    ptr2 = &f2;
    
    getLCD(ptr1,ptr2);

    out.numerator = f1.numerator-f2.numerator;
    out.denominator = f1.denominator;    

    out = simplify(out);

    return out;
}
frac multiply(frac f1,frac f2){
    frac out;
    
    out.numerator = f1.numerator*f2.numerator;
    out.denominator = f1.denominator*f2.denominator;

    out = simplify(out);

    return out;
}
frac divide(frac f1,frac f2){
    frac out;
    
    out.numerator = f1.numerator*f2.denominator;
    out.denominator = f1.denominator*f2.numerator;

    out = simplify(out);

    return out;
}

frac simplify(frac f){
    frac out;
    int div;

    out.whole = 0;

    div = gcd(f);
    
    if(f.numerator<0 && f.denominator<0){
        f.numerator = abs(f.numerator);
        f.denominator = abs(f.denominator);
    }else if(f.denominator<0){
        f.numerator*=-1;
        f.denominator*=-1;
    }else if(f.numerator == 0){
        f.numerator = 0;
        f.whole = 2;
        return f;
    }

    if(div>1){
        out.numerator = f.numerator/div;
        out.denominator = f.denominator/div;

        if(out.numerator==out.denominator)
            out.whole = 1;
        if(out.denominator==1)
            out.whole = 2;
            
        return out;
    }else{        
        if(f.denominator==1)
            f.whole = 2;
        else 
            f.whole = 0;
    }

    return f;
}

void getLCD(frac *f1,frac *f2){
    int newDenom;
    newDenom = (*(f1)).denominator * (*(f2)).denominator;

    (*(f1)).numerator *= (newDenom/(*(f1)).denominator);
    (*(f2)).numerator *= (newDenom/(*(f2)).denominator);
    (*(f1)).denominator = newDenom;
    (*(f2)).denominator = newDenom;
    
}

frac toFrac(){
    frac result;
    char st[16],tempStr[16];
    int size, countN = 0,countD = 0,flag = 1, i; 

    scanf("%s",&st);

    size = strlen(st);    

    for(i = 0;i<size;i++){
        if(st[i] == '/'){
            flag = 0;
            break;
        }
        tempStr[i] = st[i];
        countN++;        
    }    

    if(flag){
        result.numerator = atoi(st);
        result.denominator = 1;

        return result;
    }

    tempStr[i] = '\0';
    result.numerator = atoi(tempStr);

    for(i = countN+1; i<size;i++){        
        tempStr[countD] = st[i];
        countD++;
    }    

    tempStr[countD] = '\0';
    result.denominator = atoi(tempStr);

    return result;
}

int gcd(frac f){

    int x, y, r;

    x = abs(f.numerator);
    y = abs(f.denominator);

    while(y>0){
        r = x%y;
        x = y;
        y = r;
    }
    return x;
}
int abs(int x){
    if(x<0)
        return -1*x;
    return x;
}