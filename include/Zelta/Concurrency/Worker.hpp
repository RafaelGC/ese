/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Worker.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 3:42 PM
 */

#ifndef ZELTALIB_WORKER_HPP
#define ZELTALIB_WORKER_HPP

#include <mutex>
#include <condition_variable>
#include <thread>
#include <Zelta/Concurrency/Task.hpp>

namespace zt {
    /**
     * @brief Represents a thread. A Worker can have one task assigned at a time.
     * It communicates with the TaskPool through a condition_variable to send
     * notifications when the task is done.
     */
    class Worker {
    public:
        Worker(std::condition_variable& poolCv);
        virtual ~Worker();

        /**
         * Tries to set the task of the Worker. If it already has a Task the
         * request will be ignored and it will return false.
         * @param task
         * @return 
         */
        bool setTask(Task& task);
        
        /**
         * @return False if the worker has an assigned task.
         */
        bool isFree() const;
        void work();
        void join();
        void stop();

    private:
        std::thread thread;
        Task* task;
        std::mutex mtx;

        std::condition_variable cv;
        std::condition_variable *poolCv;
        std::unique_lock<std::mutex> uniqueLock;

        bool stopped;
    };

}

#endif /* WORKER_HPP */

