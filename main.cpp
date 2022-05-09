#include <iostream>
#include "DataStream.h"
#include "ThreadTask.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto dataStream = new DataStream<int,int,int>;
    auto task = new ThreadTask;

    // 开启线程，此时线程被一直阻塞中....
    task->StartThread(&DataStream<int,int,int>::CalledFunction, dataStream);

    task->NotifyThread();
    // 11s 过后 进行休眠，然后设置新数据
    std::chrono::milliseconds milliseconds(11);
    std::this_thread::sleep_for(milliseconds);
    task->SuspendThread();
    dataStream->SetData("after 11s!");
    task->NotifyThread();
    std::this_thread::sleep_for(milliseconds);
    task->DestoryThread();

    return 0;
}
