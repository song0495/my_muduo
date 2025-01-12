#pragma once

#include <functional>
#include <thread>
#include <memory>
#include <unistd.h>
#include <string>
#include <atomic>

#include "noncopyable.h"

class Thread: noncopyable
{
public:
    using ThreadFunc = std::function<void()>;

    explicit Thread(ThreadFunc, const std::string& name = std::string());
    ~Thread();

    void Start();
    void Join();

    bool Started() const { return started_; }
    pid_t Tid() const { return tid_; }

    const std::string& name() const { return name_; }

    static int NumCreated() { return NumCreated_; }

private:
    void SetDefaultName();

    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    static std::atomic_int NumCreated_;
};