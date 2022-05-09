//
// Created by Mr Ding on 2022/5/9.
//

#include "ThreadTask.h"

void ThreadTask::DestoryThread() {
    isQuit = true;
    if (mThread.joinable()) {
        mThread.join();
    }
}

bool ThreadTask::SuspendThread() {
    std::lock_guard<std::mutex> lockGuard(m);
    ready = false;
    cv.notify_one();
    return true;
}

bool ThreadTask::NotifyThread() {
    std::lock_guard<std::mutex> lockGuard(m);
    ready = true;
    cv.notify_one();
    return true;
}