/**
 * @file ProDaq.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <Arduino.h>
#include "Json/Json.hpp"

#define attachObject(x) attachItem(#x, x);

class ProDaq
{
private:
    int _interval;
    unsigned long _timer = 0;

protected:
    Json _json;

    bool timerTick()
    {
        if (millis() > _timer)
        {
            _timer += _interval;
            return true;
        }
        return false;
    }

    virtual void dataLogTask() = 0;

public:
    ProDaq(int interval, uint8_t itemsCount, size_t bufSize) : _json(itemsCount, bufSize)
    {
        _interval = interval;
    }

    ~ProDaq() {}

    void setInterval(int interval)
    {
        _interval = interval;
    }

    void task()
    {
        if (timerTick())
        {
            dataLogTask();
        }
    }

    template <typename T>
    void attachItem(String name, T &obj) {
        _json.addItem(name, obj);
    }
};