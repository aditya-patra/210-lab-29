#include <map>
#include <array>
#include <list>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// simulation function, takes input of map of farmers as well as information on animal types
void simulation(map<string, array<list<string>, 3>>* farmers) {
    
}

int main () {
    ifstream file("farmers.txt");
    map<string, array<list<string>, 3>> farmers;
    string reader;
    // file input
    while(getline(file, reader)) {
        // getting each farmer at once(each list in the array will contain one set of values, farmer animals, animal counts, or allocated fields)
        array<list<string>, 3> temp;
        string name = reader;
        getline(file, reader);
        string animal1 = reader;
        getline(file, reader);
        string count1 = reader;
        getline(file, reader);
        string plot1 = reader;
        getline(file, reader);
        string animal2 = reader;
        getline(file, reader);
        string count2 = reader;
        getline(file, reader);
        string plot2 = reader;
        getline(file, reader);
        string animal3 = reader;
        getline(file, reader);
        string count3 = reader;
        getline(file, reader);
        string plot3 = reader;
        //push inputted values into temporary array
        temp[0].push_back(animal1);
        temp[0].push_back(animal2);
        temp[0].push_back(animal3);
        temp[1].push_back(count1);
        temp[1].push_back(count2);
        temp[1].push_back(count3);
        temp[2].push_back(plot1);
        temp[2].push_back(plot2);
        temp[2].push_back(plot3);
        // create new index in farmer map
        farmers.insert(make_pair(name, temp));
    }
    for (const auto& pair : farmers){
        cout << pair.first << ": ";
        for (int i = 0; i < 3; i++) {
            int e = 0;
            for (auto it = pair.second[0].begin(); it != pair.second[0].end(); ++it) {
                if (e == i) {
                    cout << *it << " ";
                    break;
                }
                e++;
            }
            e = 0;
            for (auto it = pair.second[1].begin(); it != pair.second[1].end(); ++it) {
                if (e == i) {
                    cout << *it << " ";
                    break;
                }
                e++;
            }
            e = 0;
            for (auto it = pair.second[2].begin(); it != pair.second[2].end(); ++it) {
                if (e == i) {
                    cout << *it << " ";
                    break;
                }
                e++;
            }
            cout << endl;
        }
    }
    return 0;
}