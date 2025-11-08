#include <map>
#include <array>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
    ifstream file("farmers.txt");
    map<string, array<list<string>, 3>>;
    string reader;
    while(getline(file, reader)) {
        string name = reader;
        getline(file, reader);
        string animal1 = reader;
        getline(file, reader);
        string count1 = reader;
        getline(file, reader);
        string plot1 = reader;
        array<list<string>, 3> temp1;
        temp1[0].push_back(animal1);
        temp1[0].push_back(count1);
        temp1[0].push_back(plot1);
    }
    return 0;
}