#pragma once
#ifndef task_h__
#define task_h__

#include <atomic>

#include "boost/core/noncopyable.hpp"

class ITask: public boost::noncopyable
{
    friend class TaskManager;

public:
    explicit ITask() { _is_run.store(true); };
    virtual ~ITask() {};

    void stop() { _is_run.store(false); disconnect(); };
    void start() { _is_run.store(true); run(); }

protected:
    virtual void disconnect() = 0;
    virtual void run() = 0;

private:
    void operator=(const ITask&) = delete;

protected:
    std::atomic<bool> _is_run;
};

#endif // !task_h__