//
// Created by Karan Gandhi on 25-12-2023.
//
#include "Files.h"
#include "Index.h"

#ifndef GIT_CLONE_GITC_H
#define GIT_CLONE_GITC_H

namespace gitc {
    class gitc {
    public:
        gitc() {
            index = new Index();

            if (!Files::in_repo()) {
                std::cout << "fatal: not a gitc repository (or any of the parent directories): .gitc" << std::endl;
                std::exit(1);
            }

        }

        ~gitc() {
            delete index;
        }

        static void init() {
            if (Files::in_repo()) {
                std::cout << "Already a gitc repository in " << Files::get_cwd() << "/.gitc" << std::endl;
                return;
            }

            // create the .gitc directory
            Files::create_gitc_dir(Files::get_cwd());
            std::cout << "Initialized empty gitc repository in " << Files::get_cwd() << "/.gitc" << std::endl;
        }

        void add(const std::string &path) {
            std::vector<std::string> added_files = Files::ls_recursive(path);

            if (added_files.empty()) {
                std::cout << path << " did not match any files" << std::endl;
                return;
            }

            for (std::string &file : added_files) {
                // update the file in the index
                std::cout << file << std::endl;
                index->update(file, ADD);
            }
        }

        void rm() {

        }

        void commit() {

        }

        void checkout() {

        }

        static void help() {

        }

    private:
        Files files;
        std::string HEAD; // contains the current commit id of the head
        Index *index;

    };

} // gitc

#endif //GIT_CLONE_GITC_H
