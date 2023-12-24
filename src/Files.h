//
// Created by Karan Gandhi on 25-12-2023.
//
#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>

#ifndef GIT_CLONE_FILES_H
#define GIT_CLONE_FILES_H

namespace gitc {

    class Files {
    public:
        bool inRepo() {
            // check if a given file is in the repo
            return true;
        }

        static std::vector<std::string> lsRecursive(const std::string &path) {
            // return a vector containing all the files in path
            std::vector<std::string> files;
            if (auto dir = opendir(path.c_str())) {
                while (auto f = readdir(dir)) {
                    if (!f->d_name || f->d_name[0] == '.')
                        continue;
                    if (f->d_type == DT_DIR)
                        for (auto &file: lsRecursive(path + f->d_name + "/")) {
                            files.push_back(file);
                        }

                    if (f->d_type == DT_REG) {
                        files.push_back(path + f->d_name);
                    }
                }
            }

            return files;
        }
    };

} // gitc

#endif //GIT_CLONE_FILES_H
