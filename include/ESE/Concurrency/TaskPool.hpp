/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TaskPool.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 3:00 AM
 */

#ifndef ESE_TASKPOOL_HPP
#define ESE_TASKPOOL_HPP

#include <ESE/Concurrency/Task.hpp>
#include <ESE/Concurrency/Worker.hpp>

#include <thread>
#include <condition_variable>
#include <vector>
#include <mutex>
#include <queue>

namespace ESE {

    class TaskPool {
    public:
        TaskPool();
        virtual ~TaskPool();

        void addTask(Task& task);

        void work();
        void join();
        void stop();
    protected:
    private:
        std::queue<Task*> pendantTasks;

        std::thread threadManager;
        std::vector<Worker*> workers;
        int maxThreads;
        std::mutex mtx;

        std::condition_variable cv;
        std::unique_lock<std::mutex> uniqueLock;

        bool stopped;
    };

}

#endif /* TASKPOOL_HPP */

