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
        }

        ~gitc() {
            delete index;
        }

        void init() {
            if (Files::in_repo()) {
                std::cout << "Already initialised git repository" << std::endl;
                return;
            }

            // else just create the directory
            // need the working tree
        }

        void add(const std::string &path) {
//            gitc::files::assert_files

            std::vector<std::string> added_files = Files::ls_recursive(path);

            if (added_files.empty()) {
                std::cout << path << " did not match any files" << std::endl;
                return;
            }

            for (std::string &files : added_files) {
                // update the files in the index
//                index.
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
