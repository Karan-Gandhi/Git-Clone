//
// Created by Karan Gandhi on 25-12-2023.
//
#include <string>
#include <sstream>

#ifndef GIT_CLONE_INDEX_H
#define GIT_CLONE_INDEX_H

namespace gitc {
    const int HASH_LENGTH = 12;

    enum Index_updates {
        REMOVE, ADD
    };

    enum Stage_number {
        UNMODIFIED, STAGED, UNTRACKED
    };

    class Index {
    public:
        Index() {
            readFromFiles();

            std::vector<std::string> files = Files::ls_recursive(Files::get_cwd());
            for (std::string &file: files) {
                if (!has_entry(file)) {
                    Index_entry *new_entry = new Index_entry();

                    new_entry->path = file;
                    new_entry->stage_number = UNMODIFIED;
                    new_entry->hash = Files::create_hash(HASH_LENGTH); // now come up with a hash function

                    entries.push_back(new_entry);
                }
            }
        }

        ~Index() {
            writeToFile();
            std::cout << entries.size() << std::endl;
            for (Index_entry *entry: entries)
                delete entry;

            entries.clear();
        }

        void update(const std::string &path, Index_updates updates) {
            if (updates == ADD) {
                // add the file

                for (Index_entry *entry: entries) {
                    if (entry->path == path) {
                        if (entry->stage_number == UNMODIFIED) {
                            entry->stage_number = STAGED;

                            const std::string object_path = Files::join_path(Files::root_path(Files::get_cwd()), ".gitc/objects/" + entry->hash);
                            Files::copy_file_contents(path, object_path);
                        } else {
                            const std::string current_object_path = Files::join_path(Files::root_path(Files::get_cwd()), ".gitc/objects/" + entry->hash);

                            if (Files::check_for_changes(path, current_object_path)) {
                                entry->hash = Files::create_hash(HASH_LENGTH);
                                Files::copy_file_contents(path, current_object_path);
                            }
                        }
                    }
                }

                Index_entry *new_entry = new Index_entry();
                new_entry->path = path;
                new_entry->stage_number = STAGED;
                new_entry->hash = Files::create_hash(HASH_LENGTH); // now come up with a hash function

                entries.push_back(new_entry);
            } else if (updates == REMOVE) {
                // make the file un
            }
        }

        bool has_entry(const std::string &path) {
            for (Index_entry *entry: entries) {
                if (entry->path == path) {
                    return true;
                }
            }

            return false;
        }

    private:
        struct Index_entry {
            std::string path;
            std::string hash;
            Stage_number stage_number = UNMODIFIED;
        };

        std::vector<Index_entry *> entries;

        void writeToFile() {
            // filepath stage_number hash
            const std::string index_file_path = Files::join_path(Files::root_path(Files::get_cwd()), ".gitc/index");
            std::ofstream index_file(index_file_path);

            index_file << entries.size() << " gitc_version_1.0" << std::endl;
            for (Index_entry *entry: entries) {
                index_file << entry->path << " " << entry->stage_number << " " << entry->hash << std::endl;
            }

            index_file.close();
        }

        void readFromFiles() {
            // read from the index file
            const std::string index_file_path = Files::join_path(Files::root_path(Files::get_cwd()), ".gitc/index");
            std::ifstream index_file(index_file_path);

            int size;
            std::string version;

            std::string line;
            std::getline(index_file, line);
            std::istringstream iss(line);
            iss >> size >> version;

            for (int i = 0; i < size; i++) {
                Index_entry *entry = new Index_entry();
                int stage_number;

                std::getline(index_file, line);
                std::istringstream current_iss(line);
                current_iss >> entry->path >> stage_number >> entry->hash;

                entry->stage_number = static_cast<Stage_number>(stage_number);
                entries.push_back(entry);
            }
        }
    };

} // gitc

#endif //GIT_CLONE_INDEX_H
