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
    for (const auto& pair : farmers){
        cout << pair.first << ": "  << endl;
        for (int i = 0; i < 3; i++) {
            int e = 0;
            for (auto it = pair.second[0].begin(); it != pair.second[0].end(); ++it) {
                if (e == i) {
                    cout << *it << " ";
                }
                e++;
            }
            e = 0;
            for (auto it = pair.second[1].begin(); it != pair.second[1].end(); ++it) {
                if (e == i) {
                    cout << *it << " ";
                }
                e++;
            }
            e = 0;
            for (auto it = pair.second[2].begin(); it != pair.second[2].end(); ++it) {
                if (e == i) {
                    cout << *it << " ";
                }
                e++;
            }
        }
    }
    return 0;
}