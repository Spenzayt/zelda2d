#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

template <typename T>
class Item {
public:
    Item(std::string name, T value) : name(name), value(value) {}

    std::string getName() const { return name; }
    T getValue() const { return value; }

private:
    std::string name;
    T value;
};

#endif // ITEM_HPP

