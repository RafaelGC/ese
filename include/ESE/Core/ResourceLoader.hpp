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

#ifndef ESE_RESOURCELOADER_HPP
#define ESE_RESOURCELOADER_HPP

#include <ESE/Core/Loadable.hpp>
#include <fstream>
#include <map>
#include <iostream>
#include <vector>

namespace ESE {
    class ResourceLoader {
    public:
        static void load(const std::string& file) {
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
                    ResourceLoader::resourceManagers[type]
                    ->loadFromFile(name, path);
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
                            
                            ResourceLoader::resourceManagers[type]
                                ->loadFromFile(cname, cpath);
                        }
                    }
                }
                
                if (input.eof()) break;
            }
        }
        
        static void registerResourceManager(const std::string& name, Loadable& loadable) {
            ResourceLoader::resourceManagers[name] = &loadable;
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
        static std::map <std::string, Loadable*> resourceManagers;
        
        class PendantLoad {
        public:
            std::string type, name, path;
        };
    };
}

#endif /* RESOURCELOADER_HPP */

