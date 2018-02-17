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

#ifndef ZELTALIB_RESOURCELOADER_HPP
#define ZELTALIB_RESOURCELOADER_HPP

#include <Zelta/Core/LoadingTarget.hpp>
#include <Zelta/Core/Package.hpp>
#include <fstream>
#include <map>
#include <iostream>
#include <vector>

namespace zt {
    class ResourceLoader {
    public:
        
        ResourceLoader() {
            mFromFileSystem = true;
        }
        
        ResourceLoader& load(const std::string& file) {
            std::ifstream input(file);
            std::string name, type, path;
            int rangeFrom, rangeTo;
            State state = FIRST_TOKEN;
            while (!input.eof()) {
                std::string line;
                
                input >> line;
                
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
                    pendantFiles.push_back(std::make_tuple(type, name, path));
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
                            
                            pendantFiles.push_back(std::make_tuple(type, cname, cpath));
                        }
                    }
                }
                
                if (input.eof()) break;
            }
            
            return *this;
        }
        
        ResourceLoader& fromFileSystem() {
            mFromFileSystem = true;
            return *this;
        }
        
        ResourceLoader& fromPackage(const std::string& path) {
            pkg.open(path);
            mFromFileSystem = false;
            return *this;
        }
        
        void into() {
            for (auto& file : pendantFiles) {
                if (mFromFileSystem) {
                    resourceManagers[std::get<0>(file)]
                        ->loadFromFile(std::get<1>(file), std::get<2>(file));
                }
                else {
                    std::vector<uint8_t> data = pkg.getFileData(std::get<2>(file));
                    resourceManagers[std::get<0>(file)]
                        ->loadFromMemory(std::get<1>(file), data.data(), data.size());
                }
            }
        }
        
        template<class T, class... TS>
        void into(T& t, TS&... ts) {
            resourceManagers[t.getName()] = &t;
            into(ts...);
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
        std::vector<std::tuple<std::string, std::string, std::string>> pendantFiles;
        Package pkg;
        bool mFromFileSystem;

    };
}

#endif /* RESOURCELOADER_HPP */

