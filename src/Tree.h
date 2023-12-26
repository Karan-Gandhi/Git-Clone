//
// Created by Karan Gandhi on 25-12-2023.
//

#include <string>
#include <vector>
#include <sstream>
#include "Files.h"

#ifndef GIT_CLONE_TREE_H
#define GIT_CLONE_TREE_H

namespace gitc {

    class Tree {
    public:
        Tree(std::string _hash) : hash(_hash) {
//            read_from_file();
        }

        ~Tree() {
            write_to_file();
        }

        void add_entry(std::string path, std::string hash, std::string type) {
            Tree_entry *new_entry = new Tree_entry();
            new_entry->path = path;
            new_entry->hash = hash;
            new_entry->type = type;

            entries.push_back(new_entry);
        }
    private:
        std::string hash;

        struct Tree_entry {
            std::string path;
            std::string hash;
            std::string type;
        };

        std::vector<Tree_entry *> entries;

        void read_from_file() {
            std::string file_path = Files::join_path(Files::root_path(), ".gitc/objects/" + hash);
            std::ifstream file(file_path);

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                Tree_entry *new_entry = new Tree_entry();

                iss >> new_entry->type >> new_entry->hash;
                std::getline(iss, new_entry->path);
                entries.push_back(new_entry);
            }

            file.close();
        }

        void write_to_file() {
            std::string file_path = Files::join_path(Files::root_path(), ".gitc/objects/" + hash);
            std::ofstream file(file_path);

            for (Tree_entry *entry: entries) {
                file << entry->type << " " << entry->hash << " " << entry->path << std::endl;
            }

            file.close();
        }
    };

} // gitc

#endif //GIT_CLONE_TREE_H
