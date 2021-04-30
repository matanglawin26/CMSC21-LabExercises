#include <iostream>
#include <stdlib.h>

using namespace std; 

struct Frac{
    int numerator, denominator, whole;
};
typedef struct Frac Frac;

Frac toFrac();
int gcd(Frac f);
int abs(int x);

class Fraction{
    public:
        Frac fraction;

        Frac add(Frac f2){
            Frac out,*ptr1,*ptr2;
            
            ptr1 = &this->fraction;
            ptr2 = &f2;

            getLCD(ptr1,ptr2);     

            this->fraction.numerator = this->fraction.numerator+f2.numerator;
            this->fraction.denominator = f2.denominator;

            out = this->simplify();

            return out;
        }

        Frac subtract(Frac f2){
            Frac *ptr1,*ptr2, out;
            
            ptr1 = &this->fraction;
            ptr2 = &f2;
            
            getLCD(ptr1,ptr2);

            this->fraction.numerator = this->fraction.numerator-f2.numerator;
            this->fraction.denominator = f2.denominator;    
            
            out = this->simplify();

            return out;
        }

        Frac multiply(Frac f2){
            Frac out;
            
            this->fraction.numerator = this->fraction.numerator*f2.numerator;
            this->fraction.denominator = this->fraction.denominator*f2.denominator;

            out = this->simplify();

            return out;
        }

        Frac divide(Frac f2){
            Frac out;
            
            this->fraction.numerator = this->fraction.numerator*f2.denominator;
            this->fraction.denominator = this->fraction.denominator*f2.numerator;
            
            out = this->simplify();

            return out;
        }

        Frac simplify(){
            Frac out;
            int div;

            out.whole = 0;

            div = gcd(this->fraction);
            
            if(this->fraction.numerator<0 && this->fraction.denominator<0){
                this->fraction.numerator = abs(this->fraction.numerator);
                this->fraction.denominator = abs(this->fraction.denominator);
            }else if(this->fraction.denominator<0){
                this->fraction.numerator*=-1;
                this->fraction.denominator*=-1;
            }else if(this->fraction.numerator == 0){
                this->fraction.numerator = 0;
                this->fraction.whole = 1; 
                return this->fraction;
            }

            if(div>1){
                out.numerator = this->fraction.numerator/div;
                out.denominator = this->fraction.denominator/div;

                if(out.numerator==out.denominator){
                    out.whole = 1;
                    out.numerator = 1;
                }
                if(out.denominator==1)
                    out.whole = 1; 
                    
                return out;
            }else{        
                if(this->fraction.denominator==1)
                    this->fraction.whole = 1; 
                else 
                    this->fraction.whole = 0;
            }

            return this->fraction;
        }
        void getLCD(Frac *f1,Frac *f2){
            int newDenom;
            newDenom = (*(f1)).denominator * (*(f2)).denominator;

            (*(f1)).numerator *= (newDenom/(*(f1)).denominator);
            (*(f2)).numerator *= (newDenom/(*(f2)).denominator);
            (*(f1)).denominator = newDenom;
            (*(f2)).denominator = newDenom;            
        }
};

int main(){
    int n;
    Frac out;
    Fraction f1,f2;

    do{
        cout << "Input: ";

        cin >> n;
        
        f1.fraction = toFrac();

        if(n!=5)
            f2.fraction = toFrac();
    }while(n<1||n>5);

    switch(n){
        case 1: // Addition            
            out = f1.add(f2.fraction);
            break;
        case 2: // Subtraction
            out = f1.subtract(f2.fraction);
            break; 
        case 3: // Multiplication
            out = f1.multiply(f2.fraction);
            break;
        case 4: // Division
            out = f1.divide(f2.fraction);
            break;
        case 5: // Simplification
            out = f1.simplify();
            break;
        default:
            break;
    }

    if(out.whole)
        cout << out.numerator << endl;
    else
        cout << out.numerator << "/" << out.denominator << endl;
        
    return 0;
}

Frac toFrac(){
    Frac result;
    string st, tempStr;
    int size, countN = 0,countD = 0,flag = 1, i; 
    
    cin >> st;
     
    tempStr = "";

    for(i = 0; i < st.length();i++){
        if(st[i] == '/'){
            flag = 0;
            break;
        }
        tempStr += st[i];
        countN++;        
    }    

    if(flag){
        result.numerator = atoi(st.c_str());
        result.denominator = 1;

        return result;
    }

    result.numerator = atoi(tempStr.c_str());

    tempStr = "";
    for(i = countN+1; i<st.length();i++)      
        tempStr += st[i];          

    result.denominator = atoi(tempStr.c_str());

    return result;
}

int gcd(Frac f){
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
        return -x;
    return x;
}