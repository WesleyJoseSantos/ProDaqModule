/**
 * @file Json.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "JsonItem.hpp"

#define addObject(x) addItem(#x, x);

class Json
{
private:
    JsonItem *_items;
    uint8_t _itCount;
    size_t _size;

    void assignType(String &obj) {
        _items[_itCount].setType(ObjectType::t_string);
    }

    void assignType(int &obj) {
        _items[_itCount].setType(ObjectType::t_int);
    }

    void assignType(unsigned long &obj) {
        _items[_itCount].setType(ObjectType::t_ulong);
    }

    void assignType(long &obj) {
        _items[_itCount].setType(ObjectType::t_long);
    }

    void assignType(float &obj) {
        _items[_itCount].setType(ObjectType::t_float);
    }

    void assignType(double &obj) {
        _items[_itCount].setType(ObjectType::t_double);
    }

    void assignType(bool &obj) {
        _items[_itCount].setType(ObjectType::t_bool);
    }

    String getKeyValue(String &key, String &jsonStr){
        jsonStr.replace(": ",":");
        key = "\"" + key + "\":";
        int idx1 = jsonStr.indexOf(key);
        String subs = jsonStr.substring(idx1 + key.length());
        int idx2 = subs.indexOf(",");
        String val = subs.substring(0, idx2);
        val.replace("\"","");
        val.replace("}","");
        return val;
    }

public:
    Json(uint8_t count, size_t size) {
        _items = new JsonItem[count];
        _size = size;
    }

    ~Json() {
        delete [] _items;
    }

    JsonItem getItem(uint8_t id){
        return _items[id];
    }

    JsonItem getItem(String &name){
        for (int i = 0; i < _itCount; i++)
        {
            if(_items[i].getName() == name)
                return _items[i];
        }
    }

    String toString(){
        char jsonStr[_size];
        int idx = sprintf(jsonStr,"{");
        for (int i = 0; i < _itCount; i++)
        {
            idx += sprintf(&jsonStr[idx], "%s", _items[i].toString().c_str());
            if(i < _itCount - 1) idx += sprintf(&jsonStr[idx], ",");
        }
        idx += sprintf(&jsonStr[idx], "}");
        return String(jsonStr);
    }

    void fromString(String &jsonStr){
        for (size_t i = 0; i < _itCount; i++)
        {
            String name = _items[i].getName();
            String val = getKeyValue(name, jsonStr);
            _items[i].fromString(val);
        }
    }

    template <typename T>
    void addItem(String name, T &obj) {
        _items[_itCount] = JsonItem(name, &obj, sizeof(obj));
        assignType(obj);
        _itCount++;
    }
};