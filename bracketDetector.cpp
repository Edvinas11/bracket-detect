#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

void printErrorMessage(char bracket, int line, int column, string fileName) {
    cout << "Invalid bracket " << bracket << " found at " << fileName << ":" << line << ":" << column << endl;
}

void areBracketsBalanced(vector<pair<char, pair<int, int>>> brackets, string fileName) {
    stack<pair<char, pair<int, int>>> stack;

    for (const auto& info : brackets) {
        char bracket = info.first;
        int line = info.second.first;
        int column = info.second.second;

        if (bracket == '[' || bracket == '{' || bracket == '(') {
            stack.push({bracket, {line, column}});
        } 
        else {
            if (stack.empty()) {
                // empty stack means that there are no matching opening bracket
                printErrorMessage(bracket, line, column, fileName);
                return;
            }

            char topValue = stack.top().first;
            int topLine = stack.top().second.first;
            int topColumn = stack.top().second.second;
            stack.pop();
            if ((bracket == ']' && topValue != '[') || (bracket == '}' && topValue != '{') || (bracket == ')' && topValue != '(')) {
                printErrorMessage(topValue, topLine, topColumn, fileName);
                return;
            }
        }
    }

    if (!stack.empty()) {
        char topValue = stack.top().first;
        int topLine = stack.top().second.first;
        int topColumn = stack.top().second.second;

        printErrorMessage(topValue, topLine, topColumn, fileName);
        return;
    }

    cout << "Brackets are balanced in " << fileName << endl;
}

int main(int argc, char **argv){
    if (argc <= 1) {
        cout << "No file specified" << endl;
        return 1;
    }

    ifstream file(argv[1]);

    if (!file.is_open()) {
        cout << "Cannot open specified file" << endl;
        return 1;
    }

    vector<pair<char, pair<int, int>>> bracketList;
    char bracket;
    int line = 1;
    int column = 0;

    // Read all brackets and store them in vector
    while (file.get(bracket)) {
        column++;

        if (bracket == '[' || bracket == ']' || bracket == '{' || bracket == '}' || bracket == '(' || bracket == ')') {
            bracketList.push_back({bracket, {line, column}});
        }

        if (bracket == '\n') {
            line++;
            column = 0;
        }
    }

    areBracketsBalanced(bracketList, argv[1]);

    file.close();

    return 0;
}