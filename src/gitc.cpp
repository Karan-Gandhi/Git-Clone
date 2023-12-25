//
// Created by Karan Gandhi on 24-12-2023.
//
#include <iostream>
#include <string>

#include "gitc.h"
#include "Files.h"


int main(int argc, char *argv[]) {
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
            if (argc == 2) {
                std::cout << "Nothing specified, nothing added." << std::endl;
                return 0;
            }

            for (int i = 2; i < argc; i++) {
                gitc::gitc().add(argv[i]);
            }
        } else if (command == "rm") {
            if (argc == 2) {
                std::cout << "Nothing specified, nothing removed." << std::endl;
                return 0;
            }

            for (int i = 2; i < argc; i++) {
                gitc::gitc().rm(argv[i]);
            }

        } else if (command == "commit") {

        } else if (command == "checkout") {

        } else {
            // no command matches
        }
    }

    return 0;
}