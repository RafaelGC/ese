/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TaskPool.cpp
 * Author: rafa
 * 
 * Created on January 14, 2018, 3:00 AM
 */

#include <Zelta/Concurrency/TaskPool.hpp>

namespace zt {

    TaskPool::TaskPool(unsigned int threads) : uniqueLock(mtx) {
        maxThreads = threads;
        stopped = false;

        threadManager = std::thread(&TaskPool::work, this);

        for (int i = 0; i < maxThreads; i++) {
            workers.push_back(new Worker(cv));
        }

    }

    TaskPool::~TaskPool() {
        for (auto t : workers) {
            delete t;
        }
    }

    void TaskPool::addTask(Task& task) {
        this->pendantTasks.push(&task);
        cv.notify_all();
    }

    void TaskPool::work() {
        while (!stopped) {
            // While there are pendant tasks we assign them to the workers
            // until all are busy.
            while (pendantTasks.size() > 0) {
                Task* t = pendantTasks.front();
                bool success = false;
                // We look for a worker to do the task.
                for (auto it = workers.begin(); it != workers.end(); ++it) {
                    // We call setTask() to assign the task to the worker.
                    // If it returns true means that the worker accepted the task.
                    if ((*it)->setTask(*t)) {
                        pendantTasks.pop();
                        success = true;
                        break;
                    }


                }

                // If there is no success assigning a task, the pool will
                // wail until one of them is free.
                if (!success) { break; }


            }

            cv.wait(uniqueLock);
        }
    }

    void TaskPool::join() {
        threadManager.join();
        for (auto t : workers) {
            t->join();
        }
    }

    void TaskPool::stop() {
        stopped = true;

        for (auto it = workers.begin(); it != workers.end(); ++it) {
            (*it)->stop();
        }

        cv.notify_all();
    }

}