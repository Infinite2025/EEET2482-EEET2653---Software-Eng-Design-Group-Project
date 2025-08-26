#ifndef EBIKE_H
#define EBIKE_H
#include <string>
#include <vector>
using namespace std;

class Ebike{

    public:
        Ebike(); // create a default Constructor

        Ebike(const string& brand, const string& model, const string& color, int engineSize_cc, int year, const string& plateNum); //Create a Constructor with all the information of 1 bike
        

}