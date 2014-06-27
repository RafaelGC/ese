#ifndef LOG_HPP
#define LOG_HPP

#include <fstream>
#include <iostream>

#ifdef ESE_DEBUG
	#define ESE_LOG_OPEN(MODE) ESE::Log::open(MODE);
	#define ESE_LOG_WARNING(MESSAGE) ESE::Log::warning(MESSAGE);
	#define ESE_LOG_INFORMATION(MESSAGE) ESE::Log::information(MESSAGE);
	#define ESE_LOG_ERROR(MESSAGE) ESE::Log::error(MESSAGE);
	#define ESE_LOG_CLOSE()
	#define ESE_PRINT(MESSAGE) std::cout << MESSAGE << std::endl;
#else
	#define ESE_LOG_OPEN(MODE)
	#define ESE_LOG_WARNING(MESSAGE)
	#define ESE_LOG_INFORMATION(MESSAGE)
	#define ESE_LOG_ERROR(MESSAGE)
	#define ESE_LOG_CLOSE()
	#define ESE_PRINT(MESSAGE)
#endif
/*Con el script anterior se consigue optimizar el programa. Si el usuario establece el
 * modo de depuración definiendo la constante ESE_DEBUG y hace uso de algunos de esos
 * métodos, efectivamente, llamará a los métodos correspondientes. Sin embargo, si no
 * está definida la constante ESE_DEBUG, las llamadas a los métodos LOG_XXX serán
 * ignoradas. La ventaja de esto es que se hace al momento de compilar y no en tiempo
 * de ejecución.
*/

namespace ESE{
class Log
{
	static std::ofstream outputFile;
	//outputFile nos permite escribir en el archivo de log.
public:
	enum {KEEP_PREVIOUS_LOG, REMOVE_PREVIOUS_LOG};
	//A la hora de crear un nuevo log, podemos eliminar el anterior o mantenerlo y
	//escribir después de éste, con estas dos constantes especificamos el modo. Son
	//el argumento que recibe el método open()
	
	/**
	 * @brief Abre el archivo de log para ser escrito.
	 * @param MODE Modo de apertura. Si es KEEP_PREVIOUS_LOG no se perderá
	 * el log anterior. Si es REMOVE_PREVIOUS_LOG se sobreescribirá.
	 * @return TRUE si el archivo está abierto y se puede escribir, si no, FALSE.
	 * */
	static bool open(int mode = KEEP_PREVIOUS_LOG);

	/**
	 * @brief Cierra el archivo, no se podrá escribir en él después de liberarlo.
	 * */
	static void close();

	/**
	 * @brief Escribe una entrada en el archivo de log.
	 * @param tag La etiqueta que tendrá el mensaje.
	 * @param message El mensaje que queremos escribir después de la etiqueta.
	 * Cuando llamamos a esta función, escribiremos una línea en el archivo de así:<br>
	 * <em>TAG		MENSAJE</em><br>
	 * Entre ambos hay una tabulación.
	 * */
	static void post(std::string tag, std::string message);
	
	/**
	 * @brief Escribe una entrada con el tag ERR (error).
	 * @param message Mensaje de error.
	 * Este método hace uso de post() al que envía como etiqueta "ERR".
	 * */
	static void error(std::string message);
	/**
	 * @brief Escribe una entrada con el tag WAR (warning).
	 * @param message Mensaje de warning.
	 * Este método hace uso de post() al que envía como etiqueta "WAR".
	 * */
	static void warning(std::string message);
	/**
	 * @brief Escribe una entrada con el tag INF (información).
	 * @param message Mensaje informativo.
	 * Este método hace uso de post() al que envía como etiqueta "INF".
	 * */
	static void information(std::string message);
};

}
#endif // LOG_HPP
