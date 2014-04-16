#include <ESE/Text/Text.hpp>
namespace ESE{
	
Text::Text(){
	
}

Text::Text(std::string file, std::string language){
	load(file,language);
}

void Text::load(std::string file, std::string language){
	content.clear();
	currentLanguage = language;
	
	pugi::xml_document doc;
	
	if (!doc.load_file(file.c_str())){
		ESE_LOG_ERROR("A file could not be loaded.");
		return;
	}
	
	for (pugi::xml_node node = doc.first_child(); node; node = node.next_sibling()){
		if (strcmp(node.attribute("name").value(),language.c_str())==0){
			//Ya hemos encontrado el elemento que nos interesa, ahora recorremos las
			//distintas etiquetas y vamos guardando el contenido en un map.
			
			for (pugi::xml_node node_texto = node.first_child(); node_texto; node_texto = node_texto.next_sibling()){
				content[node_texto.attribute("name").value()] = node_texto.child_value();
			}
		}
		if (strcmp(node.attribute("name").value(),"DEFAULT")==0){
			//También nos interesa obtener los string DEFAULT porque serán valores globales
			//que servirán a todos los lenguajes. Eso sí, tenemos que asegurarnos de que ese valor por defecto
			//no sustituya a un elemento del otro idioma, porque los otros tienen prioridad.
			
			//Igualmente, recorremos los elementos...
			for (pugi::xml_node node_texto = node.first_child(); node_texto; node_texto = node_texto.next_sibling()){
				//Sólo que ahora nos aseguramos de que el string no esté añadido antes de añadirlo.
				if (content.find(node_texto.attribute("name").value())==content.end()){
					//No está, se añade.
					content[node_texto.attribute("name").value()] = node_texto.child_value();
				}
				
			}
		}
	}
}

std::string Text::getString(std::string name){
	return content[name];
}

std::string Text::getCurrentLanguage(){
	return currentLanguage;
}

}