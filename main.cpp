#include <iostream>
#include "DataStream.h"
#include "ThreadTask.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto dataStream = new DataStream<int,int,int>;
    auto task = new ThreadTask;

    // 开启线程，此时线程被一直阻塞中....
    task->StartThread(&DataStream<int,int,int>::CalledFunction, dataStream);
    // 通知线程，解除阻塞
    task->NotifyThread();
    // 11ms 过后 进行休眠，然后设置新数据
    std::chrono::milliseconds milliseconds(11);
    std::this_thread::sleep_for(milliseconds);
    task->SuspendThread();
    dataStream->SetData("after 11s!");

    // 设置完新数据后，通知线程进行打印，主线程休眠11ms
    task->NotifyThread();
    std::this_thread::sleep_for(milliseconds);

    // 过完11ms后手动销毁线程
    task->DestoryThread();
    return 0;
}
