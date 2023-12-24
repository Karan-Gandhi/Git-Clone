//
// Created by Karan Gandhi on 25-12-2023.
//
#include "Files.h"

#ifndef GIT_CLONE_GITC_H
#define GIT_CLONE_GITC_H

namespace gitc {
    class gitc {
    public:
        gitc() {}

        void init() {
            if (gitc::files.inRepo()) return;


        }

        void add() {

        }

        void rm() {

        }

        void commit() {

        }

        void checkout() {

        }

        void help() {

        }

    private:
        Files files;
        std::string HEAD; // contains the current commit id of the head

    };

} // gitc

#endif //GIT_CLONE_GITC_H
