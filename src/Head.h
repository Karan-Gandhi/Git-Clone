//
// Created by karan on 25-12-2023.
//

#include <string>
#include "Files.h"

#ifndef GIT_CLONE_HEAD_H
#define GIT_CLONE_HEAD_H

namespace gitc {

    class Head {
    public:
        Head() { // no support for branches yet
            read_from_file();
        }

        ~Head() {
            write_to_file();
        }

        void update_last_commit_hash(const std::string &hash) {
            last_commit_hash = hash;
        }

        static void init() {
            std::ofstream head_file(Files::join_path(Files::root_path(), ".gitc/HEAD"));
            head_file << "refs/heads/master";
            head_file.close();

            mkdir(Files::join_path(Files::root_path(), ".gitc/refs/heads").c_str(), 0777);

            std::ofstream master(Files::join_path(Files::root_path(), ".gitc/refs/heads/master"));
            master << "";
            master.close();
        }

        std::string get_last_commit_hash() {
            return last_commit_hash;
        }

    private:
        std::string head_ref;
        std::string last_commit_hash;

        void write_to_file() {
            std::ofstream head_file(Files::join_path(Files::root_path(), ".gitc/HEAD"));
            head_file << head_ref;
            head_file.close();

            mkdir(Files::join_path(Files::root_path(), ".gitc/refs/heads").c_str(), 0777);

            std::ofstream master(Files::join_path(Files::root_path(), ".gitc/refs/heads/master"));
            master << last_commit_hash;
            master.close();
        }

        void read_from_file() {
            std::ifstream head_file(Files::join_path(Files::root_path(), ".gitc/HEAD"));
            std::getline(head_file, head_ref);
            head_file.close();

            std::ifstream master(Files::join_path(Files::root_path(), ".gitc/" + head_ref));
            std::getline(master, last_commit_hash);
            master.close();
        }
    };

} // gitc

#endif //GIT_CLONE_HEAD_H
