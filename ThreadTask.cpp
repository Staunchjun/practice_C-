//
// Created by Mr Ding on 2022/5/9.
//

#include "ThreadTask.h"

void ThreadTask::DestoryThread() {
    // 结束线程
    isQuit.store(true);

    // 最后join一下
    if (mThread.joinable()) {
        mThread.join();
        std::cout << "join thread!";
    }
}

bool ThreadTask::SuspendThread() {
    ready.store(false);
    cv.notify_all();
    return true;
}

bool ThreadTask::NotifyThread() {
    ready.store(true);
    cv.notify_all();
    return true;
}