/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Task.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 3:01 AM
 */

#ifndef ZELTALIB_TASK_HPP
#define ZELTALIB_TASK_HPP

namespace zt {

    /**
     * @brief A Task is a unit of work.
     * 
     * If you need something to be executed in a different thread you can use
     * Task and TaskPool classes.
     * 
     * @see TaskPool
     */
    class Task {
    public:
        Task();
        virtual ~Task();

        /**
         * 
         * @return True if the task is finished.
         */
        virtual bool work() = 0;
    private:

    };

}

#endif /* TASK_HPP */

