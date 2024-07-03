// typeit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <vector>
#include <chrono>

using namespace std;

// Function to set the console text color
void setColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Function to move the cursor to a specific position
void moveToPosition(short x, short y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { x, y };
    SetConsoleCursorPosition(hConsole, pos);
}

void convertTextToVector(string text, vector<string>& arr) {
    char ch;
    string word = "";
    for (int i = 0; i < text.size(); i++) {
        ch = text[i];
        if (ch == ' ') {
            arr.push_back(word);
            word = "";
        }
        else {
            word += ch;
        }
    }
    arr.push_back(word);
}

chrono::time_point<chrono::high_resolution_clock> getInput(int nw, vector<string>& input) {

    char ch;
    string word = "";
    cout << nw << endl;

    int start = false;
    chrono::time_point<std::chrono::high_resolution_clock> startTime;
   
    while (true) {
        
        ch = _getch();

        if (!start) {
            startTime = std::chrono::high_resolution_clock::now();
            start = true;
        }

        if (ch == ' ') {
            nw--;
            
            //cout << nw;

            input.push_back(word);
            word = "";
            
            cout << " ";
            if (nw == 0) return startTime;
        }

        else if (ch == 8) { // Backspace key
            if (!word.empty()) {
                word.pop_back();
                // Move the cursor back, overwrite the character with space, and move the cursor back again
                cout << "\b \b";
            }
        }

        else {
            word += ch;
            cout << ch;
        }
    }
}

int main() {
    // Initial text
    std::string text = "The quick brown fox jumps over the lazy dog";
    //std::string text = "A B";
    vector<string> textV;
    convertTextToVector(text, textV);






    
    // Print the text
    std::cout << text << std::endl;

    // Save the starting cursor position
    //CONSOLE_SCREEN_BUFFER_INFO csbi;
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //GetConsoleScreenBufferInfo(hConsole, &csbi);
    //COORD startPosition = csbi.dwCursorPosition;

    //// Modify part of the text (for demonstration, change "quick" to green)
    //std::string partToChange = "quick";
    //size_t pos = text.find(partToChange);
    //if (pos != std::string::npos) {
    //    moveToPosition(startPosition.X + pos, startPosition.Y - 1); // Move cursor to the part to change
    //    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Set color to green
    //    std::cout << partToChange; // Print the part with new color
    //    setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default color
    //}


    int noOfWords = textV.size();
    vector<string> input;
    auto startTime = getInput(noOfWords, input);

    int correctWords = 0;

    for (int i = 0; i < noOfWords; i++) {
        if (textV[i] == input[i])
            correctWords++;
        else
            cout << endl << input[i];
    }
    cout << endl << "Accuracy : " << (correctWords * 100 / noOfWords);
    
    auto endTime = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
    int speed = (double)correctWords / ((double)duration / 60.0);

    cout << endl << "Speed : " << speed << "WPM" << endl;

    return 0;
}


// (*) first make a simple version and then iterate to make it better.
// (*) add time 
//  -  added backspace


