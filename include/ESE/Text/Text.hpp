#ifndef TEXT_HPP
#define TEXT_HPP

#include <cstring>
#include <map>

#include <ESE/External/pugixml.hpp>
#include <ESE/Core/Log.hpp>
namespace ESE{
	
class Text{
protected:
	std::map<std::string,std::string>content;
	std::string currentLanguage;
public:
	Text();
	Text(std::string file, std::string language);
	void load(std::string file, std::string language);
	std::string getString(std::string name);
	std::string getCurrentLanguage();
};

}

#endif