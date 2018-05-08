/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ResourceLoader.hpp
 * Author: rafa
 *
 * Created on January 16, 2018, 6:02 AM
 */

#ifndef ZELTALIB_RESOURCEPROVIDER_HPP
#define ZELTALIB_RESOURCEPROVIDER_HPP

#include <Zelta/Core/LoadingTarget.hpp>
#include <Zelta/Core/Package.hpp>
#include <Zelta/Core/FileNotFoundException.hpp>
#include <Zelta/Core/ResourceNotFoundException.hpp>
#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <sstream>

namespace zt {
    /**
     * @brief This class allows you to load resources from the filesystem
     * or a package.
     * 
     * The set of resources that will be loaded is determined by
     * a resource file that you set through the load(file) method. (Note: that
     * file must not be in a package.) Then you can specify with fromFilesystem()
     * or fromPackage() where you want to load the resources from. Then you can
     * call the onDemand() method, that way the resources will be loaded only
     * when they are requested. Finally, is important to call the into() method
     * to set to which resource managers you will be loading into.
     * 
     * @warning If you are using the on-demand loading you must be sure that
     * the ResourceProvider is not destroyed because it will be used by the
     * ResourceManager to load the requested file.
     */
    class ResourceProvider {
    public:
        
        ResourceProvider() {
            mFromFileSystem = true;
            mOnDemand = false;
            readResourcesFileFromPackage = true;
        }
        
        ResourceProvider& load(const std::string& file) {
            this->resourceFile = file;
            
            return *this;
        }
        
        ResourceProvider& fromFileSystem() {
            mFromFileSystem = true;
            return *this;
        }
        
        ResourceProvider& fromPackage(const std::string& path, bool readResourcesFileFromPackage = true) {
            pkg.open(path);
            mFromFileSystem = false;
            this->readResourcesFileFromPackage = readResourcesFileFromPackage;
            return *this;
        }
        
        ResourceProvider& now() {
            mOnDemand = false;
            return *this;
        }
        
        ResourceProvider& onDemand() {
            mOnDemand = true;
            return *this;
        }
        
        void into() {
            parse(this->resourceFile);
            
            for (auto& file : files) {
                if (mOnDemand) {
                    // The file is marked as pendant. When the file is requested,
                    // its resource manager will ask the ResourceLoader to load it.
                    resourceManagers[file.type]->pendant(file.name, *this);
                }
                else {
                    load(file.type, file.name, file.path);
                }
            }
        }
        
        /**
         * Sets the ResourceManagers where the resources will be loaded.
         * @param t
         * @param ts
         */
        template<class... TS>
        void into(LoadingTarget& t, TS&... ts) {
            resourceManagers[t.getName()] = &t;
            into(ts...);
        }
        
        void require() {}
        
        /**
         * @brief This method makes sure that the given resource names are
         * loaded. If they are not, they will be.
         * @param t Resource name.
         * @param ts Other resource name.
         */
        template<class S, class... SS>
        void require(S& t, SS& ...ts) {
            bool found = false;
            for (File& file : files) {
                // Note that if two resources (in different
                // managers) have the same name, both are loaded.
                if (file.name == t) {
                    found = true;
                    if (!isLoaded(file.type, file.name)) {
                        load(file.type, file.name, file.path);
                    }
                }
            }
            
            if (!found) { throw ResourceNotFoundException(t); }
            
            require(ts...);
        }
        
        /**
         * @brief Given the resource manager name and the name of the
         * resource, the resource is loaded. If the resource
         * does not exists a zt::ResourceNotFoundException() is returned.
         * @param file
         * @return 
         */
        void request(const std::string& type, const std::string& name) {
            for (File& file : files) {
                if (file.name == name && file.type == type) {
                    load(file.type, file.name, file.path);
                    return;
                }
            }
            
            throw ResourceNotFoundException(name);
        }
        
    protected:
        void load(const std::string& type, const std::string& name, const std::string& path) {
            if (mFromFileSystem) {
                resourceManagers[type]
                    ->loadFromFile(name, path);
            }
            else {
                std::vector<uint8_t> data = pkg.getFileData(path);
                resourceManagers[type]
                    ->loadFromMemory(name, data.data(), data.size());
            }
        }
        
        /**
         * @brief This method tells if one resource of certain type is loaded.
         * @param type Type of the resource (the name of the container).
         * @param name Name of the resource.
         * @return True if it is loaded.
         */
        bool isLoaded(const std::string& type, const std::string& name) {
            for (File& file : files) {
                if (file.name == name && file.type == type) {
                    if (this->resourceManagers[file.type]->isLoaded(name)) {
                        return true;
                    }
                }
            }
            return false;
        }
        
        // Parses de resource file.
        void parse(const std::string& file) {
            
            std::istream* input;
            
            // If we're loading files from the package we will also
            // read the resources file from there unless the user
            // specifies anything else.
            if (!mFromFileSystem && readResourcesFileFromPackage) {
                std::string textFile = pkg.getFileDataAsString(file);
                input = new std::istringstream(textFile);
            }
            else {
                input = new std::ifstream(file);
            }
            
            std::string name, type, path;
            int rangeFrom, rangeTo;
            State state = FIRST_TOKEN;
            while (!input->eof()) {
                std::string line;
                
                (*input) >> line;
                
                if (state == FIRST_TOKEN) {
                    if (line == "load") {
                        state = TYPE;
                    }
                    else if (line == "load_range") {
                        state = RANGE_FROM;
                    }
                }
                else if (state == TYPE) {
                    type = line;
                    state = NAME;
                }
                else if (state == NAME) {
                    name = line;
                    state = PATH;
                }
                else if (state == PATH) {
                    path = line;
                    
                    state = FIRST_TOKEN;
                    files.push_back(File(type, name, path));
                }
                else if (state == RANGE_FROM) {
                    rangeFrom = std::stoi(line);
                    
                    state = RANGE_TO;
                }
                else if (state == RANGE_TO) {
                    rangeTo = std::stoi(line);
                    
                    state = RANGE_TYPE;
                }
                else if (state == RANGE_TYPE) {
                    type = line;
                    state = RANGE_NAME;
                }
                else if (state == RANGE_NAME) {
                    name = line;
                    state = RANGE_PATH;
                }
                else if (state == RANGE_PATH) {
                    path = line;
                    state = FIRST_TOKEN;
                    if (rangeFrom <= rangeTo) {
                        for (int i = rangeFrom; i <= rangeTo; i++) {
                            
                            std::string cname = name;
                            std::string cpath = path;
                            
                            std::size_t p = cname.find("%");
                            cname.replace(p, 1, std::to_string(i));
                            
                            std::size_t p2 = cpath.find("%");
                            cpath.replace(p2, 1, std::to_string(i));
                            
                            files.push_back(File(type, cname, cpath));
                        }
                    }
                }
                
                if (input->eof()) break;
            }
            
            if (mFromFileSystem) {
                ((std::ifstream*)input)->close(); // :(
            }
            delete input;
        }
    private:
        enum State {
            FIRST_TOKEN,
            LOAD,
            NAME,
            TYPE,
            PATH,
            
            RANGE_FROM,
            RANGE_TO,
            RANGE_NAME,
            RANGE_TYPE,
            RANGE_PATH
        };
        std::map <std::string, LoadingTarget*> resourceManagers;
        
        struct File {
            std::string name, type, path;
            File(const std::string& type, const std::string& name, const std::string& path) :
            name(name), type(type), path(path) {}
        };
        
        std::string resourceFile;
        
        // Files that are about to be loaded.
        // (name, type, path)
        std::vector<File> files;
        
        // This package will be used if the user loads fromPackage().
        Package pkg;
        // If the user loads from a package he can decide if the
        // resource file is also in the package or outside. By default,
        // we'll assume it's inside.
        bool readResourcesFileFromPackage;
        
        
        bool mFromFileSystem, mOnDemand;
        

    };
}

#endif /* RESOURCELOADER_HPP */

