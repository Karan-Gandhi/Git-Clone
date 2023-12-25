//
// Created by Karan Gandhi on 25-12-2023.
//

#include <string>
#include <algorithm>
#include "Index.h"
#include "Files.h"
#include "Tree.h"

#ifndef GIT_CLONE_COMMIT_H
#define GIT_CLONE_COMMIT_H

namespace gitc {

    class Commit {
    public:
        Commit(std::string _commit_hash) : commit_hash(_commit_hash) {
            read_from_file();
        }

        Commit() {}

        ~Commit() {
            write_to_file();
        }

        std::string get_commit_hash() {
            return commit_hash;
        }

        static Commit *create_commit_from_index(Index &index, std::string previous_commit_hash, std::string message) {
            Commit *new_commit = new Commit();

            new_commit->commit_hash = Files::create_hash(HASH_LENGTH);
            new_commit->tree_hash = Files::create_hash(HASH_LENGTH);
            new_commit->parent_hash = previous_commit_hash;
            new_commit->commit_message = message;
            new_commit->timestamp = time(nullptr);

            create_tree_recursively(index.get_entries(), new_commit->tree_hash);

            return new_commit;
        }

        static void create_tree_recursively(std::vector<Index_entry *> entries, const std::string &current_tree_hash) {
            std::vector<std::string> directories;
            std::vector<std::string> files;

            for (Index_entry *entry: entries) {
                if (entry->stage_number == UNTRACKED)
                    continue;

                if (entry->path.find('/') != std::string::npos) {
                    directories.push_back(entry->path.substr(0, entry->path.find('/')));
                } else {
                    files.push_back(entry->path);
                }
            }

            directories.erase(std::unique(directories.begin(), directories.end()), directories.end());
            files.erase(std::unique(files.begin(), files.end()), files.end());

            Tree *new_tree = new Tree(current_tree_hash);

            for (auto &directory: directories) {
                std::vector<Index_entry *> directory_entries;
                for (Index_entry *entry: entries) {
                    if (entry->path.find(directory) == 0) {
                        Index_entry *new_entry = new Index_entry();

                        new_entry->path = entry->path.substr(entry->path.find('/') + 1);
                        new_entry->hash = entry->hash;
                        new_entry->stage_number = entry->stage_number;

                        directory_entries.push_back(new_entry);
                    }
                }

                std::string next_tree_hash = Files::create_hash(HASH_LENGTH);
                create_tree_recursively(directory_entries, next_tree_hash);
                new_tree->add_entry(directory, next_tree_hash, "tree");
            }

            for (auto &file: files) {
                for (Index_entry *entry: entries) {
                    if (entry->path == file) {
                        new_tree->add_entry(file, entry->hash, "blob");
                    }
                }
            }

            delete new_tree;
        }

    private:
        std::string commit_hash;
        std::string tree_hash;
        std::string parent_hash;
        std::string commit_message;
        unsigned long timestamp;

        void read_from_file() {
            std::string file_path = Files::join_path(Files::root_path(), ".gitc/objects/" + commit_hash);
            std::ifstream file(file_path);

            std::string line;
            std::getline(file, line);
            std::istringstream iss(line);

            std::string type;
            iss >> type >> tree_hash;

            std::getline(file, line);
            iss = std::istringstream(line);
            iss >> type >> parent_hash;

            std::getline(file, line);
            iss = std::istringstream(line);
            iss >> type >> timestamp;

            std::getline(file, commit_message);

            file.close();
        }

        void write_to_file() {
            std::string file_path = Files::join_path(Files::root_path(), ".gitc/objects/" + commit_hash);
            std::ofstream file(file_path);

            file << "tree " << tree_hash << std::endl;
            file << "parent " << parent_hash << std::endl;
            file << "time " << timestamp << std::endl;
            file << commit_message << std::endl;
        }
    };

} // gitc

#endif //GIT_CLONE_COMMIT_H
