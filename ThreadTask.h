//
// Created by Mr Ding on 2022/5/9.
//

#ifndef TEST_DATA_STREAM_THREADTASK_H
#define TEST_DATA_STREAM_THREADTASK_H

#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>
#include <condition_variable>

class ThreadTask {
public:
    bool NotifyThread();
    bool SuspendThread();
    void DestoryThread();

    template<typename F, typename O>
    void StartThread(F f, O obj) {
        std::thread thread(&ThreadTask::SetThread<F, O>, this, std::forward<F>(f), std::forward<O>(obj));
        mThread = std::move(thread);
    };

    template<typename F, typename O>
    void SetThread(F f, O obj){
        while (!isQuit.load()) {
            // 等待直至 main() 发送数据 默认阻塞状态
            std::unique_lock<std::mutex> lk(m);
            cv.wait(lk, [=] { return ready.load(); });

            // 嵌入的函数
            (std::forward<O>(obj)->*f)();

            // 通知前完成手动解锁，以避免等待线程才被唤醒就阻塞
            lk.unlock();
            cv.notify_all();
        }
        std::cout << "end thread" << std::endl;
    };
private:
    std::mutex m;
    std::condition_variable cv;
    std::thread mThread;
    std::atomic_bool ready{false};
    std::atomic_bool isQuit{false};
};

#endif //TEST_DATA_STREAM_THREADTASK_H
