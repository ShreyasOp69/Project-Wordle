#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

void wordle(string word_of_the_day, string user_guess) {
    for(int i = 0; i < 5; i++) {
        if(word_of_the_day[i] == user_guess[i]) {
            cout << user_guess[i] << ": " << "G" << endl;
        }
        else if(word_of_the_day.find(user_guess[i]) != std::string::npos) {
            cout << user_guess[i] << ": " << "Y" << endl;
        }
        else {
            cout << user_guess[i] << ": " << "B" << endl;
        }
    }
}

int main() {

    string line;
    vector<string> lines;
    cout << "Check 1" << endl;
    srand(time(0));

    ifstream file("Words.txt");
    cout << "Check 2" << endl;

    int total_lines = 0;
    while(getline(file,line)) {
        total_lines++;
        lines.push_back(line);
    }
 
    int random_number = rand() % total_lines;
    
    cout << "Check" << endl;

    string word_of_the_day = lines[random_number];
    
    for(int i = 0; i < 6; i++) {
        cout << "User Guess 1:" << endl;
        string user_guess;
        cin >> user_guess;
        wordle(word_of_the_day, user_guess);
    }
    
}