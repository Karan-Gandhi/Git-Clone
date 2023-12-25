//
// Created by Karan Gandhi on 25-12-2023.
//
#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <unistd.h>

#include "../include/cwalk.h"

#ifndef GIT_CLONE_FILES_H
#define GIT_CLONE_FILES_H

namespace gitc {

    class Files {
    public:
        static bool in_repo() {
            // check if a given file is in the repo
            return !root_path(get_cwd()).empty();
        }

        static std::vector<std::string> ls_recursive(const std::string &path) {
            // return a vector containing all the files in path
            std::vector<std::string> files;

            if (auto dir = opendir(path.c_str())) {
                while (auto f = readdir(dir)) {
                    if (!f->d_name || std::string(f->d_name) == "." || std::string(f->d_name) == ".." ||
                        std::string(f->d_name) == ".gitc")
                        continue;

                    if (f->d_type == DT_DIR) {
                        for (auto &file: ls_recursive(join_path(path, f->d_name))) {
                            files.push_back(file);
                        }
                    }

                    if (f->d_type == DT_REG) {
                        files.push_back(join_path(path, f->d_name));
                    }
                }
            } else if (file_exists(path)) {
                files.push_back(join_path(path, "."));
            }

            return files;
        }

        static std::string root_path(const std::string &path) {
            // return the location of the gitc directory wrt path
            // find the gitc directory
            if (path == "/") return "";
            if (auto dir = opendir(path.c_str())) {
                while (auto f = readdir(dir)) {
                    if (!f->d_name || std::string(f->d_name) == "." || std::string(f->d_name) == "..")
                        continue;
                    if (f->d_type == DT_DIR) {
                        if (std::string(f->d_name) == ".gitc") {
                            return path;
                        }
                    }
                }
            }


            return root_path(join_path(path, "../"));
        }

        static std::string get_cwd() {
            char buffer[PATH_MAX];
            getcwd(buffer, sizeof buffer);

            return std::string(buffer);
        }

        static std::string join_path(const std::string &base_path, const std::string &other_path) {
            char new_path[FILENAME_MAX];

            cwk_path_join(base_path.c_str(), other_path.c_str(), new_path, sizeof new_path);
            return std::string(new_path);
        }

    private:


        static bool file_exists(const std::string &path) {
            std::ifstream f(path.c_str());
            return f.good();
        }

    };

} // gitc

#endif //GIT_CLONE_FILES_H
