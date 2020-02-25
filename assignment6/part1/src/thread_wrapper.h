#pragma once

#include <thread>
#include <atomic>

#include "object.h"


// Treat as struct essentially
class ThreadWrapper : public Object {
public:
    std::thread *thread;
    std::atomic<bool> finished;


    ThreadWrapper() : thread(nullptr), finished(false) {}

    ThreadWrapper(std::thread *t) : thread(t), finished(false) {}

    ~ThreadWrapper(){
        if(thread) {
            delete thread;
        }
    }

    void set_thread(std::thread *t) {
        thread = t;
    }

    bool is_finished() {
        return finished;
    }

    void joindelete() {
        if(thread){
            thread->join();
            delete thread;
            thread = nullptr;
        }
    }
};
