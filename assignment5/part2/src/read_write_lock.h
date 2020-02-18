#pragma once

#include <mutex>
#include <condition_variable>

#include "object.h"

class ReadWriteLock : public Object {
public:
    std::mutex _mutex;
    std::condition_variable _waiting_readers;
    std::condition_variable _waiting_writers;
    size_t _readers;
    size_t _queued_writers;

    void readLock(){}

    void readUnlock(){}

    bool readTryLock(){
        return false;
    }

    void writeLock(){}

    void writeUnlock(){}

    bool writeTryLock(){
        return false;
    }
};
