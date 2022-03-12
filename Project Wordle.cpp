#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <time.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool wordle(string word_of_the_day, string user_guess) {

    int results[5];
    // 1 for black, 2 for yellow, 3 for green
    for (int i = 0; i < 5; i++) {
        results[i] = 0;
    }
    // initialized the array with 0

    unordered_map<char, int> freq;   // stores frequency of characters in the word_of_the_day

    for(int i = 0; i < 5; i++) {
        freq[word_of_the_day[i]]++;
    }
    // frequency of each character stored

    for(int i = 0; i < 5; i++) {
        if(word_of_the_day[i] == user_guess[i]) {
            //count++;
            results[i] = 3;
            freq[user_guess[i]]--;              // decrease frequency so that no. of yellows = no. of chars left
        }
    }

    for(int i = 0; i < 5; i++) {
        if(results[i] == 3) {
            continue;                 // we won't do anything with letters already in the correct place
        }
        if(freq.count(user_guess[i]) > 0 && freq[user_guess[i]] > 0) {
            results[i] = 2;           // if the character is present in the map, make it yellow
            freq[user_guess[i]]--;    // no. of yellows = no. of frequency of characters left
        }
        else {
            results[i] = 1;           // if the character is not present in the map, make it black i.e. 0 frequency
        }
    }

    int count = 0;      // will count no. of characters which are at their correct place

    for(int i = 0; i < 5; i++) {
        if(results[i] == 1) {
            cout << user_guess[i] << ": " << "Black" << endl;
        }
        if(results[i] == 2) {
            cout << user_guess[i] << ": " << "Yellow" << endl;
        }
        if(results[i] == 3) {
            count++;
            cout << user_guess[i] << ": " << "Green" << endl;
        }
    }

    if(count == 5) {
        return true;                 // returning true would mean the game is won and thus end the game
    }
    return false;
}

template <typename T>
bool contains(vector<T> vec, const T & elem)
{
    bool result = false;
    if( find(vec.begin(), vec.end(), elem) != vec.end() )
    {
        result = true;
    }
    return result;
}

int main() {

    string line;
    vector<string> lines;
    srand(time(0));

    ifstream file("Words.txt");

    int total_lines = 0;
    while(getline(file,line)) {
        total_lines++;
        lines.push_back(line);
    }
 
    int random_number = rand() % total_lines;
    
    cout << "Welcome to Wordle" << endl;

    string word_of_the_day = lines[random_number];

    int i;
    bool a = false;

    for(i = 0; i < 6; i++) {
        cout << "User Guess " << i + 1 << ": " << endl;
        string user_guess;
        cin >> user_guess;

        while(user_guess.size() != 5 || !contains(lines, user_guess)) {
            if(user_guess.size() != 5) {
                cout << "Word should be of 5 letters, try again!" << endl;
            }
            else if(!contains(lines, user_guess)) {
                cout << "Word not in the list!" << endl;
            }
            cin >> user_guess;
        }
        
        a = wordle(word_of_the_day, user_guess);
        if(a) {
            break;
        }
    }
    if(!a) {
        cout << "Defeat!" << endl;
        cout << "The word of the day was: " << word_of_the_day << endl;
    }
    else {
        cout << "Victory!" << endl;
    }

    
}

/*
Had problems in test cases where word of the day
1) "today": On guess taboo, it should have G Y B Y B, but it was giving G Y B Y Y
2) "three": Had problems with guesses ellee (gave Y B B G G instead of B B B G G)
*/