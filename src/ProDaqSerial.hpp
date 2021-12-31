/**
 * @file ProDaqSerial.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <Stream.h>
#include "ProDaq.hpp"

class ProDaqSerial : public ProDaq
{
private:
    Stream *_port;

protected:
    void dataLogTask() override
    {
        Serial.println(_json.toString());
    }

public:
    ProDaqSerial(int interval, uint8_t itemsCount, size_t bufSize) : ProDaq(interval, itemsCount, bufSize) {}
    ~ProDaqSerial() {}

    void setPort(Stream &port)
    {
        _port = &port;
    }
};