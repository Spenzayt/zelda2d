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
        std::cout << item.getName() << " ajout� � l'inventaire.\n";
    }

    void removeItem(const std::string& itemName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getName() == itemName) {
                std::cout << it->getName() << " retir� de l'inventaire.\n";
                items.erase(it);
                return;
            }
        }
        std::cout << "Objet " << itemName << " introuvable !\n";
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

