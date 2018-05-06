#include <Zelta/Internationalization/Text.hpp>
#include <iostream>

int main() {
	zt::Text text;
	
	text.load("text.lxml");
	
	text.in(L"es");
	
	std::wcout << text.get(L"greeting") << std::endl;
	std::wcout << text.get(L"bye") << std::endl;
	std::wcout << text.get(L"hour", L"Hora") << std::endl;
	
	text.in(L"en");
	
	std::wcout << text.get(L"greeting") << std::endl;
	std::wcout << text.get(L"bye") << std::endl;

	
	return 0;
}
