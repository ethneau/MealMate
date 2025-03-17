/**
 * @file grocerylist.h
 * @brief Header file for GroceryList class
 */

#ifndef GROCERYLIST_H
#define GROCERYLIST_H

#include "ingredient.h"
#include "daymeal.h"
#include "inventory.h"

class GroceryList
{
private:
    QList<Ingredient*> requiredIngredients; // list of required ingredients

public:
    GroceryList(){}
    void addItem(const Ingredient* ingredient);
    void removeItem(const Ingredient* ingredient);
    void generateList(const QString &filename) const;
    void getRequiredIngredients(DayMeal &daymeal, Inventory &inv);
    ~GroceryList();
};

#endif // GROCERYLIST_H
