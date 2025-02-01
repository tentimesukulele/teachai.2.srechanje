#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ncurses.h>

using namespace std;

// Function to display file contents
void displayFile(const vector<string>& lines, int startRow, int maxRows) {
    clear();
    for (int i = startRow; i < lines.size() && i < startRow + maxRows; ++i) {
        mvprintw(i - startRow, 0, lines[i].c_str());
    }
    refresh();
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    
    string filename = argv[1];
    vector<string> lines;

    // Read file
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while(getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cerr << "Error: Could not open file " << filename << endl;
    }
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);
    int currentLine = 0;
    int startRow = 0;

    displayFile(lines, startRow, maxRows - 1);
    
    int ch;
    while((ch = getch()) != 27) { // ESC key to exit
        switch (ch) {
            case KEY_UP:
                if (currentLine > 0) {
                    currentLine--;
                    if (currentLine < startRow) {
                        startRow--;
                    }
                }
                break;
            case KEY_DOWN:
                if (currentLine < lines.size() - 1) {
                    currentLine++;
                    if(currentLine >= startRow + maxRows - 1)
                    {
                         startRow++;
                    }
                }
                break;
            case KEY_LEFT:
                break;
            case KEY_RIGHT:
                break;
            case KEY_ENTER:
            case 10:
                lines.insert(lines.begin() + currentLine + 1, "");
                 currentLine++;
                if(currentLine >= startRow + maxRows - 1)
                    {
                         startRow++;
                    }
                break;
            case KEY_BACKSPACE:
            case 127:
            {
               if(lines[currentLine].size() > 0){
                   lines[currentLine].pop_back();
               } else if (lines.size() > 1){
                   lines.erase(lines.begin() + currentLine);
                    if (currentLine > 0) {
                        currentLine--;
                        if(currentLine < startRow)
                            startRow--;
                    }
               }
                break;
            }
            default:
            {
               if(ch >= 32 && ch <= 126){
                   lines[currentLine] += (char)ch;
               }
               break;
            }
            
        }
         displayFile(lines, startRow, maxRows - 1);
        move(currentLine - startRow, lines[currentLine].size());
    }


    // Save file
     ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const string& line : lines) {
            outputFile << line << endl;
        }
        outputFile.close();
        cout << "File saved successfully!" << endl;
    } else {
        cerr << "Error: Could not save file!" << endl;
    }

    endwin();
    return 0;
}
