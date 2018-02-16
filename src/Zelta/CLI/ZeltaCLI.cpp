/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <map>
#include <regex>

#include <Zelta/Core/Arguments.hpp>
#include <Zelta/Core/Package.hpp>
#include <Zelta/Core/FileNotFoundException.hpp>
#include <Zelta/Core/ConsoleLog.hpp>

#ifdef __linux__
#include <sys/stat.h>
#endif

namespace zt {

    class Command {
    public:
        virtual void run(const zt::Arguments &args) = 0;
        virtual int requiredParameters() const = 0;
        virtual std::string shortDescription() const = 0;
    };

    class HelpCommand : public Command {
    public:
        HelpCommand(const std::map<std::string, Command*>& commands) {
            this->commands = &commands;
        }

        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;

            for (auto it = commands->cbegin(); it != commands->cend(); ++it) {
                log.info((*it).first + ": " + (*it).second->shortDescription());
            }
        }

        int requiredParameters() const {
            return 0;
        }

        std::string shortDescription() const {
            return "Prints all commands.";
        }

    private:
        const std::map<std::string, Command*>* commands;
    };

    class CreateProjectCommand : public Command {
    public:
        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;
            try {
                zt::Package package;

    #ifdef __linux__
                // Create project folder.
                const int dir_err = mkdir(args.get(2).toString().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (-1 == dir_err) {
                    log.error("Directory could not be created.");
                    return;
                }
                log.success("Project folder created");

                // Copy files to the project folder.

                // Set up the makefile.
                std::ifstream  mk("ZeltaLib/cli-files/Makefile");

                std::string mkStr((std::istreambuf_iterator<char>(mk)),
                     std::istreambuf_iterator<char>());

                // Replace <<PROJECT_NAME>> with project name defined by the user.
                std::regex e ("<<PROJECT_NAME>>");
                mkStr = std::regex_replace (mkStr,e,args.get(2).toString());

                std::ofstream  mkDst(args.get(2).toString() + "/Makefile");
                mkDst << mkStr;
                mk.close();
                mkDst.close();

                std::ifstream  mn("ZeltaLib/cli-files/main.cpp", std::ios::binary);
                std::ofstream  mnDst(args.get(2).toString() + "/main.cpp",   std::ios::binary);
                mnDst << mn.rdbuf();
                mn.close();
                mnDst.close();

                log.success("Files created.");
    #else
                log.warning("Command not implemented for your system.");
    #endif
            }
            catch (zt::FileNotFoundException ex) {
                log.error("File could not be created.");
            }
        }

        int requiredParameters() const {
            return 1;
        }

        std::string shortDescription() const {
            return "Creates a new ZeltaLib project. Params: <PROJECT_NAME>.";
        }
    };

    class CreatePackageCommand : public Command {
    public:
        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;
            try {
                zt::Package package;
                package.create(args.get(2).toString());

                log.success("File created.");
            }
            catch (zt::FileNotFoundException ex) {
                log.error("File could not be created.");
            }
        }

        int requiredParameters() const {
            return 1;
        }

        std::string shortDescription() const {
            return "Creates a new empty package. Params: <FILENAME>.";
        }
    };

    class AddFileToPackage : public Command {
    public:
        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;
            try {
                zt::Package package;
                package.open(args.get(2).toString());

                std::string target = args.size() > 4 ? args.get(4).toString() : args.get(3).toString();

                package.addFile(args.get(3).toString(), target);

                log.success("File added.");
            }
            catch (zt::FileNotFoundException ex) {
                log.error("File could not be added.");
            }
        }

        int requiredParameters() const {
            return 2;
        }

        std::string shortDescription() const {
            return "Adds a file to an existing package. Params: <PACKAGE> <FILENAME> [FILENAME_IN_PACKAGE].";
        }
    };

    class AddDirectoryToPackage : public Command {
    public:
        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;
            try {
                zt::Package package;
                package.open(args.get(2).toString());

                package.addDirectory(args.get(3).toString());

                log.success("Directory added.");
            }
            catch (zt::FileNotFoundException ex) {
                log.error("Directory could not be added.");
            }
        }

        int requiredParameters() const {
            return 1;
        }

        std::string shortDescription() const {
            return "Adds a directory to an existing package. Params: <PACKAGE> <DIRECTORY>.";
        }
    };

    class RemoveFileFromPackage : public Command {
    public:
        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;
            try {
                zt::Package package;
                package.open(args.get(2).toString());
                package.removeFile(args.get(3).toString());

                log.success("File removed.");
            }
            catch (zt::FileNotFoundException ex) {
                log.error("File could not be removed.");
            }
        }

        int requiredParameters() const {
            return 2;
        }

        std::string shortDescription() const {
            return "Removes a file from a package. Params: <PACKAGE> <FILENAME_IN_PACKAGE>.";
        }    
    };

    class ExtractFileFromPackage : public Command {
    public:
        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;
            try {
                zt::Package package;
                package.open(args.get(2).toString());

                std::string extractName = args.size() > 4 ? args.get(4).toString() : args.get(3).toString();

                std::vector<uint8_t> res = package.getFileData(args.get(3).toString());

                std::ofstream outputFile;
                outputFile.open(extractName, std::ios_base::trunc | std::ios_base::binary);
                if (!outputFile.is_open()) throw zt::FileNotFoundException();

                for (uint8_t& b : res) {
                    outputFile.write((const char*)&b, 1);
                }
                outputFile.close();

                log.success("File extracted.");
            }
            catch (zt::FileNotFoundException ex) {
                log.error("File could not be extracted.");
            }
        }

        int requiredParameters() const {
            return 2;
        }

        std::string shortDescription() const {
            return "Extracts a file from a package. Params: <PACKAGE> <FILENAME_IN_PACKAGE> [OUTPUT_FILE].";
        }      
    };

    class ListPackage : public Command {
    public:
        void run(const zt::Arguments &args) {
            zt::ConsoleLog log;
            try {
                zt::Package package;
                package.open(args.get(2).toString());

                std::vector<std::string> files = package.getNames();

                if (files.size() == 0) {
                    log.warning("Empty package.");
                }

                for (std::string& name : files) {
                    log.info(name);
                }
            }
            catch (zt::FileNotFoundException ex) {
                log.error("Package could not be listed.");
            }
        }

        int requiredParameters() const {
            return 1;
        }

        std::string shortDescription() const {
            return "List all files in a package. Params: <PACKAGE>.";
        }    
    };
}
int main(int argc, char** argv) {
    
    zt::Arguments args(argc, argv);
    zt::ConsoleLog log;
    std::map<std::string, Command*> commands;
    
    commands["package:create"] = new CreatePackageCommand;
    commands["package:add"] = new AddFileToPackage;
    commands["package:add-directory"] = new AddDirectoryToPackage;
    commands["package:remove"] = new RemoveFileFromPackage;
    commands["package:extract"] = new ExtractFileFromPackage;
    commands["package:list"] = new ListPackage;
    commands["project:create"] = new CreateProjectCommand;
    commands["help"] = new HelpCommand(commands);
    
    if (args.size() >= 2 && commands.count(args.get(1).toString()) > 0 && commands[args.get(1).toString()]->requiredParameters() <= args.size() - 2) {
        commands[args.get(1).toString()]->run(args);
    }
    else {
        log.error("Command not found.");
    }
    
    for (auto it = commands.begin(); it != commands.end(); ++it) {
        delete (*it).second;
    }
    
    return 0;
}