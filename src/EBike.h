#ifndef EBIKE_H
#define EBIKE_H
#include <string>
#include <vector>
using namespace std;

class Ebike{

    public:
        Ebike(); // create a default Constructor

        Ebike(const string& brand, const string& model, const string& color, int engineSize_cc, int year, const string& plateNum); //Create a Constructor with all the information of 1 bike

        bool Listing(const string& start, const string& end, int dailyRate, int minRate, bool available); //Create information for listing with start and end day, CP daily, minimum rating of user, the bike is available or not

        

};

#endif // EBIKE_H