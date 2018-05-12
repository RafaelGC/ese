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

#include <Zelta/Export.hpp>
#include <Zelta/Concurrency/Task.hpp>

#include <mutex>
#include <condition_variable>
#include <thread>

namespace zt {
    /**
     * @brief Represents a thread. A Worker can have one task assigned at a time.
     * It communicates with the TaskPool through a condition_variable to send
     * notifications when the task is done.
     */
    class Worker {
    public:
        EXPORT Worker(std::condition_variable& poolCv);
        EXPORT virtual ~Worker();

        /**
         * Tries to set the task of the Worker. If it already has a Task the
         * request will be ignored and it will return false.
         * @param task
         * @return 
         */
        EXPORT bool setTask(Task& task);
        
        /**
         * @return False if the worker has an assigned task.
         */
        EXPORT bool isFree() const;
        EXPORT void work();
        EXPORT void join();
        EXPORT void stop();

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

