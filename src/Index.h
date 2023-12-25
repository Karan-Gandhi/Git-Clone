//
// Created by Karan Gandhi on 25-12-2023.
//
#include <string>
#include <sstream>


#ifndef GIT_CLONE_INDEX_H
#define GIT_CLONE_INDEX_H

namespace gitc {
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
        }

        ~Index() {
            writeToFile();
            for (Index_entry *entry: entries)
                delete entry;

            entries.clear();
        }

        void update(const std::string &path, Index_updates updates) {
            if (updates == ADD) {
                // add the file

            } else if (updates == REMOVE) {
                // make the file un
            }
        }

    private:
        struct Index_entry {
            std::string path;
            std::string hash;
            Stage_number stage_number;
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
                auto *entry = new Index_entry();
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
