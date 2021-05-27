#include <iostream>
#include <iomanip>

using namespace std;

class Package{
    public:
        double weight, cost;

        Package(double weight, double cost){
            this->weight = weight;
            this->cost = cost;
        }

        double calculateCost(){
            return this->weight*this->cost;
        }
};

class TwoDayPackage : public Package{
    private:
        double flatFee;

    public:
        TwoDayPackage(double weight, double cost,double flatFee) : Package(weight,cost){
            this->flatFee = flatFee;
        }
        
        double calculateCost(){
            return Package::calculateCost() + this->flatFee;
        }
};

class OvernightPackage : public Package{
    private:
        double overnightFee;

    public:
        OvernightPackage(double weight, double cost,double overnightFee) : Package(weight,cost){
            this->overnightFee = overnightFee;
        }

        double calculateCost(){
            return Package::calculateCost()+(this->overnightFee*this->weight);
        }
};

int main(){
    double weight, cost, flatFee, overnightFee;
    cin >> weight >> cost >> flatFee >> overnightFee;
    
    Package stdPkg(weight,cost);
    TwoDayPackage twoDayPkg(weight,cost,flatFee);
    OvernightPackage oNPkg(weight,cost,overnightFee);

    cout << fixed << setprecision(2);
    cout << stdPkg.calculateCost() << ' ' << twoDayPkg.calculateCost() << ' ' << oNPkg.calculateCost() << endl;

    return 0;
}