//
// Created by Karan Gandhi on 25-12-2023.
//
#include "Files.h"
#include "Index.h"
#include "Head.h"
#include "Commit.h"

#ifndef GIT_CLONE_GITC_H
#define GIT_CLONE_GITC_H

namespace gitc {
    class gitc {
    public:
        gitc() {
            index = new Index();
            head = new Head();

            if (!Files::in_repo()) {
                std::cout << "fatal: not a gitc repository (or any of the parent directories): .gitc" << std::endl;
                std::exit(1);
            }
        }

        ~gitc() {
            delete index;
            delete head;
        }

        static void init() {
            if (Files::in_repo()) {
                std::cout << "Already a gitc repository in " << Files::get_cwd() << "/.gitc" << std::endl;
                return;
            }

            // create the .gitc directory
            Files::create_gitc_dir(Files::get_cwd());
            Files::create_file(Files::join_path(Files::get_cwd(), ".gitc/HEAD"));
            Head::init();
            std::cout << "Initialized empty gitc repository in " << Files::get_cwd() << "/.gitc" << std::endl;
        }

        void add(const std::string &path) {
            std::vector<std::string> added_files = Files::ls_recursive(path);

            if (added_files.empty()) {
                std::cout << path << " did not match any files" << std::endl;
                return;
            }

            for (std::string &file: added_files) {
                // update the file in the index
                index->update(file, ADD);
            }
        }

        void rm(const std::string &path) {
            std::vector<std::string> removed_files = Files::ls_recursive(path);

            if (removed_files.empty()) {
                std::cout << path << " did not match any files" << std::endl;
                return;
            }

            for (std::string &file: removed_files) {
                // update the file in the index
                index->update(file, REMOVE);
            }
        }

        void status() {

        }

        void commit(const std::string &message) {
            // make a commit object, object tree (which is the snapshot of index), and update the head
            Commit *new_commit = Commit::create_commit_from_index(*index, head->get_last_commit_hash(), message);
            head->update_last_commit_hash(new_commit->get_commit_hash());
            delete new_commit;
        }

        void checkout() {

        }

        void log() {
            if (head->get_last_commit_hash().empty()) {
                std::cout << "No commits to display" << std::endl;
                return;
            }

            Commit *current_commit = new Commit(head->get_last_commit_hash());
            current_commit->print_commit(true);

            while (!current_commit->get_parent_commit_hash().empty()) {
                std::string next_commit_hash = current_commit->get_parent_commit_hash();
                delete current_commit;
                current_commit = new Commit(next_commit_hash);
                current_commit->print_commit(false);
            }
        }

        static void help() {

        }

    private:
        Files files;
        Head *head;
        Index *index;

    };

} // gitc

#endif //GIT_CLONE_GITC_H
