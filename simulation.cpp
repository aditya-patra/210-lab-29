#include <map>
#include <array>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main () {
    ifstream file("farmers.txt");
    map<string, array<list<string>, 3>> farmers;
    string reader;
    while(getline(file, reader)) {
        array<list<string>, 3> temp;
        string name = reader;
        for(int i = 0; i < 3; i++) {
            getline(file, reader);
            string animal1 = reader;
            getline(file, reader);
            string count1 = reader;
            getline(file, reader);
            string plot1 = reader;
            temp[i].push_back(animal1);
            temp[i].push_back(count1);
            temp[i].push_back(plot1);
        }
        farmers.insert(make_pair(name, temp));
    }
    return 0;
}