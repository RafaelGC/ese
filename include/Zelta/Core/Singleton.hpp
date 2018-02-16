/* 
 * File:   Singleton.hpp
 * Author: Rafa
 *
 * Created on 22 de enero de 2016, 6:50
 */

#ifndef SINGLETON_HPP
#define	SINGLETON_HPP

namespace zt {

    template <class T>
    /**
     * @brief Base class for other singleton classes.
     * 
     * To use this class: 
     * 1. Inherit from this class and use your child class as template parament.
     * 2. Child class must declare this class as friend (friend class Singleton<YOUR CHILD CLASS>).
     * 3. Make your child class constructor private.
     */
    class Singleton {

        private:
        protected:        
        Singleton() {}
        public:
        static T& instance() {
            static T t;
            return t;
        }


    };

}

#endif	/* SINGLETON_HPP */

