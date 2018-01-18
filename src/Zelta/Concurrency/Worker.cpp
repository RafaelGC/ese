/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Worker.cpp
 * Author: rafa
 * 
 * Created on January 14, 2018, 3:42 PM
 */

#include <thread>

#include <Zelta/Concurrency/Worker.hpp>
#include <Zelta/Concurrency/Task.hpp>

namespace zt {

    Worker::Worker(std::condition_variable& poolCv) : uniqueLock(mtx) {
        task = nullptr;
        this->poolCv = &poolCv;
        thread = std::thread(&Worker::work, this);
        stopped = false;
    }

    Worker::~Worker() {
    }

    bool Worker::setTask(Task& task) {
        if (isFree()) {
            this->task = &task;
            cv.notify_all();
            return true;
        }

        return false;
    }

    bool Worker::isFree() const {
        return !task;
    }

    void Worker::work() {
        while (!stopped) {

            if (!isFree()) {
                if (this->task->work()) {
                    task = nullptr;
                    // Cuando la tarea ha terminado de ejecutarse (ha devuelto true)
                    // se notifica al pool para que sepa que puede mener aquí una
                    // nueva tarea.
                    if (poolCv) {
                        poolCv->notify_all();

                        cv.wait(uniqueLock);
                    }
                }
            }

        }
    }

    void Worker::join() {
        thread.join();
    }

    void Worker::stop() {
        stopped = true;
    }

}