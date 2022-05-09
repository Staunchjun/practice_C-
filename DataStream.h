//
// Created by Mr Ding on 2022/5/9.
//

#ifndef TEST_DATA_STREAM_DATASTREAM_H
#define TEST_DATA_STREAM_DATASTREAM_H

#include <iostream>
#include <thread>

template<typename T, typename T1, typename T2>
class DataStream {
public:
    void SetData(const std::string &basicString);
    void CalledFunction();
private:
    std::string data{"default string"};
};

template<typename T, typename T1, typename T2>
void DataStream<T, T1, T2>::SetData(const std::string &basicString) {
    this->data = basicString;
}

template<typename T, typename T1, typename T2>
void DataStream<T, T1, T2>::CalledFunction() {
    std::cout << "Function Called!" << std::endl;
    std::cout << "Print data:" << data << std::endl;

    // 模拟执行耗时函数，此处需要花费5ms
    std::chrono::milliseconds milliseconds(5);
    std::this_thread::sleep_for(milliseconds);
}

#endif //TEST_DATA_STREAM_DATASTREAM_H
