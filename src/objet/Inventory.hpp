#pragma once
#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <vector>
#include <iostream>
#include "Item.hpp"

template <typename T>
class Inventory {
public:
    void addItem(const Item<T>& item) {
        items.push_back(item);
        std::cout << item.getName() << " add to inventory\n";
    }

    void removeItem(const std::string& itemName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getName() == itemName) {
                std::cout << it->getName() << " remove from inventory\n";
                items.erase(it);
                return;
            }
        }
        std::cout << "Objet " << itemName << " introuvable !\n";
    }

    bool hasItem(const std::string& itemName) const {
        for (const auto& item : items) {
            if (item.getName() == itemName) {
                return true;
            }
        }
        return false;
    }

    void displayInventory() const {
        if (items.empty()) {
            std::cout << "Inventaire vide.\n";
            return;
        }
        std::cout << "Inventaire :\n";
        for (const auto& item : items) {
            std::cout << "- " << item.getName() << " (Valeur: " << item.getValue() << ")\n";
        }
    }

    const std::vector<Item<T>>& getItems() const { return items; }

private:
    std::vector<Item<T>> items;
};

#endif // INVENTORY_HPP