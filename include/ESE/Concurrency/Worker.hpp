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

#ifndef ESE_WORKER_HPP
#define ESE_WORKER_HPP

#include <mutex>
#include <condition_variable>
#include <thread>
#include <ESE/Concurrency/Task.hpp>

namespace ESE {

    class Worker {
    public:
        Worker(std::condition_variable& poolCv);
        virtual ~Worker();

        bool setTask(Task& task);
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

