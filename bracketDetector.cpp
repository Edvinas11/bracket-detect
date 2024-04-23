#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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

    for (const auto& bracketInfo : bracketList) {
        std::cout << "Bracket " << bracketInfo.first << " found at line " << bracketInfo.second.first << ", column " << bracketInfo.second.second << std::endl;
    }

    file.close();

    return 0;
}