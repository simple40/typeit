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

void changeTextColor(short x, short y, WORD color, string &ch) {
    moveToPosition(x, y);
    setColor(color);
    cout << ch;
    setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void formatText(int nw, int ind, int l, char ch, vector<string>& text, COORD startPosition) {
    
    short pos = 0;
    for (int i = 0; i < nw; i++) {
        pos += text[i].size();
    }

    if (ind <= text[nw].size()) {
        string t = "";
        t += text[nw][ind];

        pos += ind;
        if (ch == text[nw][ind]) {
            changeTextColor(startPosition.X + l, startPosition.Y - 1, FOREGROUND_GREEN | FOREGROUND_INTENSITY, t);
        }
        else {
            changeTextColor(startPosition.X + l, startPosition.Y - 1, FOREGROUND_RED | FOREGROUND_INTENSITY, t);
        }
    }
    else {
        //pos += text[nw].size();
        changeTextColor(startPosition.X + pos, startPosition.Y - 1, FOREGROUND_RED | FOREGROUND_INTENSITY, text[nw]);
    }
}

chrono::time_point<chrono::high_resolution_clock> getInput(int nw, vector<string>& input, vector<string> &text,  COORD startPosition) {

    char ch;
    string word = "";
    //cout << nw << endl;

    int start = false;
    chrono::time_point<std::chrono::high_resolution_clock> startTime;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD inputStartPoint = csbi.dwCursorPosition;

    int l = 0;
   
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
                continue;
            }
        }

        else {
            word += ch;
            cout << ch;

            formatText(text.size() - nw, word.size()-1, l, ch, text, startPosition);
        }

        l++;
        moveToPosition(inputStartPoint.X + l, inputStartPoint.Y);
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

     //Save the starting cursor position
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    COORD startPosition = csbi.dwCursorPosition;

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
    auto startTime = getInput(noOfWords, input, textV, startPosition);

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
// () add some formatting in the text
      // [*] what I can do is that check each input character whethe it match with the text and give color to it
      // an error is occuring whe space is pressed.


