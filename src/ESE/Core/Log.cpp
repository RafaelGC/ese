#include <ESE/Core/Log.hpp>

std::ofstream ESE::Log::outputFile;
//Hay que definir el objeto.

bool ESE::Log::open(int mode){
	if (mode==Log::KEEP_PREVIOUS_LOG){
		Log::outputFile.open("log.txt",std::ofstream::out | std::ofstream::app);
		//std::ofstream::app, app = APPEND
	}
	else{
		Log::outputFile.open("log.txt",std::ofstream::out | std::ofstream::trunc);
		//std::ofstream::app, trunc = TRUNCATE
	}
	
	return Log::outputFile.is_open();
}

void ESE::Log::close(){
	Log::outputFile.close();
}

void ESE::Log::post(std::string tag, std::string message){
	Log::outputFile << tag << "\t" << message << std::endl;
}

void ESE::Log::error(std::string message){
	Log::post("ERR",message);
}

void ESE::Log::warning(std::string message){
	Log::post("WAR",message);
}

void ESE::Log::information(std::string message){
	Log::post("INF",message);
}