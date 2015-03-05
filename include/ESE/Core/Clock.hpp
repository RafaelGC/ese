/* 
 * File:   Clock.hpp
 * Author: Rafa
 *
 * Created on February 1, 2015, 10:33 PM
 */

#ifndef CLOCK_HPP
#define	CLOCK_HPP

#include <ESE/Core/Animatable.hpp>

namespace ESE{
    /**
     * @brief Esta clase es una alternativa a la clase Clock de SFML. Implementa
     * la interfaz Animatable por lo que será necesario llamar a su método
     * advanceTime(float dt) para que actualice su contador interno. Permite pausar
     * y continuar.
     */
    class Clock : public Animatable
    {
        private:
            float elapsedTime;
            bool paused;
        public:
            Clock();
            /**
             * @return Devuelve los segundos transcurridos.
             */
            float getElapsedTime() const;
            /**
             * @param deltaTime Actualiza el contador interno del reloj. Imprescindible
             * llamar a este método desde el gameloop.
             */
            void advanceTime(float deltaTime);
            /**
             * @brief Pausa el reloj.
             */
            void pause();
            /**
             * @brief Reinicia el contador interno de segundos transcurridos.
             */
            void reset();
            /**
             * @brief Continua con el contador interno.
             */
            void resume();
            /**
             * @return Devuelve true si el reloj está pausado.
             */
            bool isPaused() const;

    };
}
#endif	/* CLOCK_HPP */

