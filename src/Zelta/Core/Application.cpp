#include <Zelta/Core/Application.hpp>

namespace zt {

    Application::Application() {
    }
    
    Application::Application(int argc, char** argv) : Application() {
        arguments.initialize(argc, argv);
    }

    Application::~Application() {

    }
    
    const Arguments& Application::getArguments() const {
        return arguments;
    }

}

