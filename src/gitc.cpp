//
// Created by Karan Gandhi on 24-12-2023.
//
#include <iostream>
#include <string>

#include "gitc.h"
#include "Files.h"
using namespace std;

int main(int argc, char *argv[]) {
    for (auto a : gitc::Files::lsRecursive("./")) {
        cout << a << endl;
    }


    if (argc == 1) {
        // display help info
    } else {
        std::string command = argv[1];

        if (command == "-h" || command == "--help") {
            // display help info
        }
        if (command == "init") {

        } else if (command == "add") {

        } else if (command == "rm") {

        } else if (command == "commit") {

        } else if (command == "checkout") {

        } else {
            // no command matches
        }
    }

    return 0;
}