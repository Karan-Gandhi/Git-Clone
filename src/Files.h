//
// Created by Karan Gandhi on 25-12-2023.
//
#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <filesystem>

#include "../include/cwalk.h"

#ifndef GIT_CLONE_FILES_H
#define GIT_CLONE_FILES_H

namespace gitc {

    class Files {
    public:
        bool inRepo() {
            // check if a given file is in the repo
            return !rootPath(".").empty();
//            return true;
        }

        static std::vector<std::string> lsRecursive(const std::string &path) {
            // return a vector containing all the files in path
            std::vector<std::string> files;
            if (auto dir = opendir(path.c_str())) {
                while (auto f = readdir(dir)) {
                    if (!f->d_name || f->d_name[0] == '.')
                        continue;

                    if (f->d_type == DT_DIR) {
                        for (auto &file: lsRecursive(joinPath(path, f->d_name))) {
                            files.push_back(file);
                        }
                    }

                    if (f->d_type == DT_REG) {
                        files.push_back(joinPath(path, f->d_name));
                    }
                }
            }

            return files;
        }

        std::string rootPath(const std::string &path) {
            // return the location of the gitc directory wrt path
            // find the gitc directory
            if (path == "/" || path == ".") return "";
            if (auto dir = opendir(path.c_str())) {
                while (auto f = readdir(dir)) {
                    if (!f->d_name || f->d_name[0] == '.')
                        continue;
                    if (f->d_type == DT_DIR) {
                        std::cout << f->d_name << std::endl;
                        if (std::string(f->d_name) == ".gitc") {
                            return path;
                        }
                    }
                }
            }

            std::cout << path << std::endl;

            return rootPath(joinPath(path, "../"));
        }

    private:
        static std::string joinPath(const std::string &base_path, const std::string &other_path) {
            char new_path[FILENAME_MAX];

            cwk_path_join(base_path.c_str(), other_path.c_str(), new_path, sizeof new_path);
            return std::string(new_path);
        }
    };

} // gitc

#endif //GIT_CLONE_FILES_H
