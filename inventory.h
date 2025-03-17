/**
 * @file inventory.h
 * @brief Header file for Inventory class
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include <QList>
#include "ingredient.h"

class Inventory
{
private:
    QList<Ingredient *> ingredients; // list of ingredients
    static Inventory *instance;      // singleton instance
    Inventory() {}                   // private constructor
    Inventory(const Inventory &) = delete;
    Inventory &operator=(const Inventory &) = delete;

public:
    // get the singleton instance of the inventory
    static Inventory *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new Inventory();
        }
        return instance;
    }

    void addIngredient(Ingredient *ingredient);
    void removeIngredient(const Ingredient *ingredient);
    void updateQuantity(const Ingredient *ingredient, qint16 quantity);
    const QList<Ingredient *> &getInventory() const;
};

#endif // INVENTORY_H
