/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <Zelta/Core/Arguments.hpp>

namespace zt {
    Arguments::Arguments() {}

    Arguments::Arguments(int argc, char** argv) {
        initialize(argc, argv);
    }

    void Arguments::initialize(int argc, char** argv) {
        args.clear();
        for (int i = 0; i < argc; i++) {
            args.push_back(Argument(argv[i]));
        }
    }

    int Arguments::size() const {
        return args.size();
    }

    const Argument& Arguments::get(int i) const {
        return args[i];
    }
}