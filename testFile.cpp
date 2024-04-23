#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main (int argc, char **argv){

    // process a file
    if (argc <= 1) {
        cout << "No file specified" << endl;
    }

    ifstream file(argv[1]);

    return 0;