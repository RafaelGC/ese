#include <Zelta/Core/Argument.hpp>

namespace zt {

    Argument::Argument(const std::string& argument) {
        arg = argument;
    }

    const std::string& Argument::toString() const {
        return arg;
    }

    int Argument::toInt() const {
        return std::stoi(arg);
    }

    float Argument::toFloat() const {
        return std::stof(arg);
    }

    double Argument::toDouble() const {
        return std::stod(arg);
    }

}