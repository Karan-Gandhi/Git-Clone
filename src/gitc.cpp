//
// Created by Karan Gandhi on 24-12-2023.
//
#include <iostream>
#include <string>

#include "gitc.h"
#include "Files.h"


int main(int argc, char *argv[]) {
//    gitc::gitc().add(".");


    if (argc == 1) {
        // display help info
    } else {
        std::string command = argv[1];

        if (command == "-h" || command == "--help") {
            // display help info
        }

        if (command == "init") {
            gitc::gitc::init();
            return 0;
        }

        if (command == "add") {
            for (int i = 2; i < argc; i++) {
                gitc::gitc().add(argv[i]);
            }
        } else if (command == "rm") {

        } else if (command == "commit") {

        } else if (command == "checkout") {

        } else {
            // no command matches
        }
    }

    return 0;
}