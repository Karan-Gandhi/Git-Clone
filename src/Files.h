//
// Created by Karan Gandhi on 25-12-2023.
//
#include <string>
#include <vector>
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <random>

#include "../include/cwalk.h"

#ifndef GIT_CLONE_FILES_H
#define GIT_CLONE_FILES_H

namespace gitc {
    const int HASH_LENGTH = 12;

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
                    if ((std::string) f->d_name == "." || (std::string) f->d_name == ".." ||
                        (std::string) f->d_name == ".gitc" || (std::string) f->d_name == ".git")
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

        static std::string root_path(const std::string &path = get_cwd()) {
            if (path == "/") return "";
            if (auto dir = opendir(path.c_str())) {
                while (auto f = readdir(dir)) {
                    if (std::string(f->d_name) == "." || std::string(f->d_name) == "..")
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

        static std::string relative_root_path() {
            return get_relative_path(get_cwd(), root_path());
        }

        static std::string get_cwd() {
            char buffer[PATH_MAX];
            getcwd(buffer, sizeof buffer);

            return (std::string) buffer;
        }

        static std::string join_path(const std::string &base_path, const std::string &other_path) {
            char new_path[FILENAME_MAX];

            cwk_path_join(base_path.c_str(), other_path.c_str(), new_path, sizeof new_path);
            return (std::string) new_path;
        }

        static bool check_for_changes(const std::string &file1, const std::string &file2) {
            std::ifstream f1(file1);
            std::ifstream f2(file2);

            if (!f1.good() || !f2.good()) {
                return true;
            }

            std::string line1, line2;

            while (std::getline(f1, line1) && std::getline(f2, line2)) {
                if (line1 != line2) {
                    return true;
                }
            }

            return false;
        }

        static void copy_file_contents(const std::string &file1, const std::string &file2) {
            std::ifstream f1(file1);
            std::ofstream f2(file2);

            std::string line;

            while (std::getline(f1, line)) {
                f2 << line << std::endl;
            }

            f1.close();
            f2.close();
        }

        static void create_gitc_dir(const std::string &path) {
            const std::string gitc_dir_path = join_path(path, ".gitc");
            mkdir(gitc_dir_path.c_str(), 0777);
        }

        static std::string create_hash(const int len) {
            std::string alphanum = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            std::string tmp_s(len, ' ');

            for (int i = 0; i < len; ++i) {
                tmp_s[i] = alphanum[get_random_number(0, (int) alphanum.size() - 1)];
            }

            return tmp_s;
        }

        static void delete_file(const std::string &path) {
            remove(path.c_str());
        }

        static std::string get_relative_path(const std::string &base, const std::string &path) {
            char buffer[FILENAME_MAX];
            cwk_path_get_relative(base.c_str(), path.c_str(), buffer, sizeof(buffer));
            return (std::string) buffer;
        }

        static void create_file(const std::string &path) {
            std::ofstream file(path);
            file.close();
        }

    private:
        static bool file_exists(const std::string &path) {
            std::ifstream f(path.c_str());
            return f.good();
        }

        static unsigned long get_random_number(const int min, const int max) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> distribution(min, max);
            return distribution(rng);
        }
    };

} // gitc

#endif //GIT_CLONE_FILES_H
