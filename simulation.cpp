#include <map>
#include <array>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int RAND_CHANCE = 5;

// function converts input string to interger
int string_to_int(string val, map<char, int> counts) {
    int output = 0;
    for(int i = 0; i < val.size(); i++) {
        output *= 10;
        output += counts[val[i]];
    }
    return output;
}

// simulation function, takes input of map of farmers as well as information on animal types
void simulation(map<string, array<list<string>, 3>>& farmers, map<char, int> counts, map<string, int> animal_val) {
    for (const auto& pair : farmers){
        string curr_animal;
        int curr_pop;
        int curr_land;
        int max_pop;
        int animal_value;
        vector<int> new_pops;
        // extract each set of animals, land, and population
        for(int i = 0; i < pair.second[0].size(); i++) {
            int e = 0;
            for (auto it = pair.second[0].begin(); it != pair.second[0].end(); ++it) {
                if (e == i) {
                    curr_animal = *it;
                    break;
                }
                e++;
            }
            e = 0;
            for (auto it = pair.second[1].begin(); it != pair.second[1].end(); ++it) {
                if (e == i) {
                    curr_pop = string_to_int(*it, counts);
                    break;
                }
                e++;
            }
            e = 0;
            for (auto it = pair.second[2].begin(); it != pair.second[2].end(); ++it) {
                if (e == i) {
                    curr_land = string_to_int(*it, counts);
                    break;
                }
                e++;
            }
            //get animal value
            animal_value = animal_val[curr_animal];
            //cout << curr_animal << " " << curr_land << " " << curr_pop << endl;
            // get number of natural deaths
            for(int e = 0; e < curr_pop; e++) {
                if ((int)(rand() % RAND_CHANCE) < 1) {
                    curr_pop -= 1; 
                }
            }
            //cout << curr_animal << " " << curr_land << " " << curr_pop << endl;
            // get number of illness/sudden deaths
            for(int e = 0; e < curr_pop; e++) {
                if ((int)(rand() % RAND_CHANCE) < 1) {
                    curr_pop -= 1; 
                }
            }
            //cout << curr_animal << " " << curr_land << " " << curr_pop << endl;
            // check for plague
            if ((int)(rand() % RAND_CHANCE) < 1) {
                curr_pop *= 0.2; 
            }
            //cout << curr_animal << " " << curr_land << " " << curr_pop << endl;
            // get number of births
            curr_pop += curr_pop * 10 / animal_value;
            //cout << curr_animal << " " << curr_land << " " << curr_pop << endl;
            // save new population
            new_pops.push_back(curr_pop);
        }
        // update population
        int e = 0;
        for (auto& it = farmers[curr_animal][1].begin(); it != farmers[curr_animal][1].end(); ++it) {
            *it = new_pops.at(e);
            e++;
        }
        break;
    }
}

void driver_function(map<string, array<list<string>, 3>>& farmers, map<char, int> counts, map<string, int> animal_val) {
    //stoi function test
    cout << (string_to_int("101", counts)) * 10 << endl;
    // function to test simulation
    // print out original farmer 1 values
    
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
        }
        cout << endl;
        break;
    }
    // run simulation
    simulation(farmers, counts, animal_val);
    // print new values
    
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
        }
        cout << endl;
        break;
    }
}

int main () {
    ifstream file("farmers.txt");
    map<string, array<list<string>, 3>> farmers;
    string reader;
    // 5 animal types
    map<char, int> counts = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};
    map<string, int> animal_val = {{"Cow", 5}, {"Horse", 6}, {"Sheep", 4}, {"Chicken", 1}, {"Pig", 3}};
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
    driver_function(farmers, counts, animal_val);
    /*
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
        }
        cout << endl;
    }
    */
    return 0;
}