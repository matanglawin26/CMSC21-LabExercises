/*
    Exercise #13: Rectangle Plot
    Date completed: 05/01/2021
*/

#include <iostream>
#include <iomanip>

using namespace std;

class Point{
    public:
        int x,y;
        float cX, cY;
};

class Rectangle{
    public:
        int x, y, length, width;

        void display(Point pt){
            for(int i = 0;i <= this->y;i++){
                for(int j = 0;j <= this->x;j++){
                    if(i>= pt.y && j>= pt.x){
                        if(i==pt.y || i==this->y)
                            cout << "# ";
                        else{
                            if(j==pt.x||j==this->x)
                                cout << "# ";
                            else
                                cout << "  ";
                        }
                    }else
                        cout << "  ";
                }
                cout << endl;
            }
        }

        int area(Point pt){    
            int area;
            this->length = this->x-pt.x;
            this->width = this->y-pt.y;
            area = this->length*this->width;

            return area;
        }

        int perimeter(Point pt){
            int perim;      
            this->length = this->x-pt.x;
            this->width = this->y-pt.y;
            perim = (2*this->length)+(2*this->width);
            return perim;
        }
        Point centerPoint(Point pt){
            Point center;
            center.cX = ((float)pt.x+(float)this->x)/2;
            center.cY = ((float)pt.y+(float)this->y)/2;    
            return center;
        }
        bool square(Point pt){    
            this->length = this->x-pt.x;
            this->width = this->y-pt.y;

            if(this->length==this->width)
                return true;
            else
                return false;
        }
};

int main(){
    Point pt;
    Rectangle rect;
    cout << "Input: ";

    cin >> pt.x >> pt.y >> rect.x >> rect.y;

    cout << endl;
    cout << "area: " << rect.area(pt) << endl;
    cout << "perimeter: " << rect.perimeter(pt) << endl;
    cout << "center: (" << setprecision(2) << fixed;
    cout << rect.centerPoint(pt).cX << ", " << rect.centerPoint(pt).cY << ')' << endl;
    cout << "square: " << (rect.square(pt)? "yes" : "no") << endl;
    rect.display(pt);
    return 0;
}
