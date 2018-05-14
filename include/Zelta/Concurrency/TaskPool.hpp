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

#ifndef ZELTALIB_TASKPOOL_HPP
#define ZELTALIB_TASKPOOL_HPP

#include <Zelta/Export.hpp>
#include <Zelta/Concurrency/Task.hpp>
#include <Zelta/Concurrency/Worker.hpp>

#include <thread>
#include <condition_variable>
#include <vector>
#include <mutex>
#include <queue>

namespace zt {

    /**
     * @brief A TaskPool keeps a set of workers (threads represented by the Worker class). You
     * can enqueue tasks in the TaskPool and they will be executed when a worker
     * is free.
     * 
     * To create a task just inherit from Task and implement in the work() method 
     * the code you want to execute in a different thread. The work() method must
     * return true if it has finished the task so that the worker gets released.
     * Then, instance the Task and add it to a TaskPool with addTask(). 
     * The task will be executed as soon as a Worker is free.
     * 
     */
    class TaskPool {
    public:
        /**
         * Creates a TaskPool with a certain amount of threads.
         * @param threads 
         */
        EXPORT TaskPool(unsigned int threads = 2);
        EXPORT virtual ~TaskPool();

        /**
         * Adds a new task to the queue.
         * @param task
         */
        EXPORT void addTask(Task& task);

        /**
         * Waits until the manager thread and the Worker threads are done.
         */
        EXPORT void join();
        EXPORT void stop();
    protected:
        /**
         * Manages the queue. This method is executed in a different thread and
         * keeps running until you call stop(). Workers notificates this thread
         * when they are free so that it can send them new tasks.
         */
        EXPORT void work();
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

