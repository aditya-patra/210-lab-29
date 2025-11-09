#include <map>
#include <array>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
const int RAND_CHANCE_DEATH = 6;
const int RAND_CHANCE_ILLNESS = 20;
const int RAND_CHANCE_PLAGUE = 3;
const int TOTAL_PLOTS = 1110;
const int MAX_POP = 120;
const int BIRTH_RATE = 6;

// function converts input string to interger
int string_to_int(string val, map<char, int> counts) {
    int output = 0;
    for(int i = 0; i < val.size(); i++) {
        output *= 10;
        output += counts[val[i]];
    }
    return output;
}

// function converts input integer to string
string int_to_string(int val, map<int, string> counts_rev) {
    string output = "";
    if (val == 0) {
        output = "0";
    }
    while(val > 0) {
        output = counts_rev[val % 10] + output;
        val /= 10;
    }
    return output;
}

// simulation function, takes input of map of farmers as well as information on animal types
void simulation(map<string, array<list<string>, 3>>& farmers, map<char, int> counts, map<int, string> counts_rev, map<string, int> animal_val) {
    int open_plots = 0;
    for (const auto& pair : farmers){
        string curr_farmer = pair.first;
        string curr_animal;
        int curr_pop;
        int curr_land;
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
            // get number of natural deaths
            for(int e = 0; e < curr_pop; e++) {
                if ((int)(rand() % (RAND_CHANCE_DEATH / animal_value)) < 1) {
                    curr_pop -= 1;
                    e--;
                }
            }
            // get number of illness/sudden deaths
            for(int e = 0; e < curr_pop; e++) {
                if ((int)(rand() % RAND_CHANCE_ILLNESS) < 8) {
                    curr_pop -= 1; 
                    e--;
                }
            }
            // check for plague
            if ((int)(rand() % RAND_CHANCE_PLAGUE) < 1) {
                curr_pop *= (((double)(rand() % 11)+10)/100.0);
            }
            // get number of births
            curr_pop += curr_pop * BIRTH_RATE / animal_value;
            if (curr_pop > MAX_POP / animal_value) {
                curr_pop = MAX_POP / animal_value;
            }
            // save new population
            new_pops.push_back(curr_pop);
        }
        // update population
        int e = 0;
        for (auto it = farmers[curr_farmer][1].begin(); it != farmers[curr_farmer][1].end(); it++) {
            *it = int_to_string(new_pops.at(e), counts_rev);
            e++;
        }
        // update land
        for(int i = new_pops.size()-1; i >= 0; i--) {
            if (new_pops.at(i) < (int)(30/animal_value)) {
                int e = 0;
                for (auto it = farmers[curr_farmer][0].begin(); it != farmers[curr_farmer][0].end(); it++) {
                    if (e == i) {
                        farmers[curr_farmer][0].erase(it);
                        break;
                    }
                    e++;
                }
                e = 0;
                for (auto it = farmers[curr_farmer][1].begin(); it != farmers[curr_farmer][1].end(); it++) {
                    if (e == i) {
                        farmers[curr_farmer][1].erase(it);
                        break;
                    }
                    e++;
                }
                e = 0;
                for (auto it = farmers[curr_farmer][2].begin(); it != farmers[curr_farmer][2].end(); it++) {
                    if (e == i) {
                        open_plots += string_to_int(*it, counts);
                        farmers[curr_farmer][2].erase(it);
                        break;
                    }
                    e++;
                }
            }
        }
    }
    // update farmer list
    vector<string> farmers_to_delete;
    for (const auto& pair : farmers){
        if (pair.second[0].size() == 0) {
            farmers_to_delete.push_back(pair.first);
        }
    }
    for(string val: farmers_to_delete) {
        farmers.erase(val);
    }
    // update plot allocation
    for(int i = 0; i < open_plots; i++) {
        int add_to_farmer = (int)(rand() % farmers.size());
        int e = 0;
        string farmer_name;
        // find farmer to add to
        for (const auto& pair : farmers){
            if (e == add_to_farmer) {
                farmer_name = pair.first;
                break;
            }
            e++;
        }
        // find animal to add
        int rand_animal = (int)(rand() % 5);
        string animal;
        if (rand_animal == 0) 
            animal = "Sheep";
        if (rand_animal == 1) 
            animal = "Chicken";
        if (rand_animal == 2) 
            animal = "Horse";
        if (rand_animal == 3) 
            animal = "Pig";
        if (rand_animal == 4)
            animal = "Cow";
        // add to existing index if possible
        int index = -1;
        e = 0;
        for(auto it = farmers[farmer_name][0].begin(); it != farmers[farmer_name][0].end(); ++it) {
            if (*it == animal) {
                index = e;
                break;
            }
            e++;
        }
        if (index == -1) {
            farmers[farmer_name][0].push_back(animal);
            farmers[farmer_name][1].push_back(int_to_string((int)(rand() % 20), counts_rev));
            farmers[farmer_name][2].push_back(int_to_string(1, counts_rev));
        }
        else {
            for(auto it = farmers[farmer_name][2].begin(); it != farmers[farmer_name][2].end(); ++it) {
                if (index == 0) {
                    *it = int_to_string(string_to_int(*it, counts)+1, counts_rev);
                    break;
                }
                index--;
            }
        }
    }
}

void driver_function(map<string, array<list<string>, 3>>& farmers, map<char, int> counts, map<int, string> counts_rev, map<string, int> animal_val) {
    //stoi function test
    cout << (string_to_int("101", counts)) * 10 << endl;
    cout << (int_to_string(101, counts_rev)) << endl;
    // function to test simulation
    // print out original farmer 1 values
    for(int outer = 0; outer <= 300; outer += 5) {
        cout << "Time: " << outer << " years" << endl;
        cout << "Farmer List ------------------------------" << endl;
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
        // run simulation
        simulation(farmers, counts, counts_rev, animal_val);
    }
}

int main () {
    ifstream file("farmers.txt");
    map<string, array<list<string>, 3>> farmers;
    string reader;
    // 5 animal types
    map<char, int> counts = {{'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9}};
    map<int, string> counts_rev = {{0, "0"}, {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"}, {6, "6"}, {7, "7"}, {8, "8"}, {9, "9"}};
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
    // driver_function(farmers, counts, counts_rev, animal_val);

    // simulation run
    for(int i = 0; i <= 300; i += 5) {
        cout << "Farmer List --------------------------------------------------------------------------------------" << endl;
        for (const auto& pair : farmers){
            cout << pair.first << ": " << endl;
            for (int i = 0; i < 3; i++) {
                int e = 0;
                for (auto it = pair.second[0].begin(); it != pair.second[0].end(); ++it) {
                    if (e == i) {
                        cout << "Animal 1: " << *it << " ";
                        break;
                    }
                    e++;
                }
                e = 0;
                for (auto it = pair.second[1].begin(); it != pair.second[1].end(); ++it) {
                    if (e == i) {
                        cout << "; Count: " << *it << " ";
                        break;
                    }
                    e++;
                }
                e = 0;
                for (auto it = pair.second[2].begin(); it != pair.second[2].end(); ++it) {
                    if (e == i) {
                        cout << "; Land Allocated: " << *it << " " << endl;
                        break;
                    }
                    e++;
                }
            }
            cout << endl;
        }
        // run simulation
        simulation(farmers, counts, counts_rev, animal_val);
    }
    return 0;
}