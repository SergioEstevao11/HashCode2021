#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <unistd.h>
#include <map>

int time = 0;
int PointsForBonus;


using namespace std;
class Street{
public:
    int start; //ou int
    int finish; //ou int
    string name;
    int duration;
    Street(){};

    Street(int s, int f, string n, int d){
        start = s;
        finish = f;
        name = n;
        duration = d;
    }
};
class Intersection{
public:
    vector <Street> streetsIn;
    vector <Street> streetsOut;
    int TimeStop;

    Intersection(){};


};


class Car{
public:
    int StreetAmount;
    vector<string> streetnames;
    int pathCounter = 0;
    Car(){};

};


int main()
{
    map<string, Street> AllStreets;
    map<int,Intersection> AllIntersections;
    vector<Car> AllCars;

    int time,numInt,numStreets,numCars;
    int points;
    ifstream file("C:\\Users\\35191\\Desktop\\hashcode\\cmake-build-debug\\f.txt");
    file>>time>>numInt>>numStreets>>numCars>>points;
    for (int i=0;i<numStreets;i++) {
        int i1, i2;
        string streetname;
        int timePer;
        file >> i1 >> i2 >> streetname >> timePer;
        Street s(i1, i2, streetname, timePer);
        AllStreets[streetname] = s;
        AllIntersections[i1].streetsOut.push_back(s);
        AllIntersections[i2].streetsIn.push_back(s);
    }
    for(int c = 0; c < numCars; c++){
        int carStreetsNum;
        Car car;
        file>>carStreetsNum;
        car.StreetAmount = carStreetsNum;
        string aux;
        for (int i=0;i<carStreetsNum;i++){
            file>>aux;
            car.streetnames.push_back(aux);
        }
        AllCars.push_back(car);
    }
    file.close();

    for(auto it = AllIntersections.begin(); it != AllIntersections.end(); it++){
        int media = 0;

        for(int c = 0; c < it->second.streetsOut.size(); c++){
            media+= it->second.streetsOut[c].duration;
        }
        it->second.TimeStop = media/it->second.streetsOut.size();
    }

    ofstream filename;
    string myLine;

    filename.open("answerf.txt");

    if(filename.is_open())
    {

        filename << numInt << endl;

        for(int c=0; c < numInt; c++){
            filename << c << endl;
            filename << AllIntersections[c].streetsIn.size() << endl;
            for (int w = 0; w < AllIntersections[c].streetsIn.size(); w++){
                filename << AllIntersections[c].streetsIn[w].name << " " << AllIntersections[c].TimeStop << endl;
            }
        }
    }
    filename.close();
    return 0;
}
