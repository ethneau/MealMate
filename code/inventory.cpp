#include "inventory.h"
#include <stdexcept>

Inventory *Inventory::instance = nullptr; // initialize the singleton instance

// add an ingredient to the inventory
void Inventory::addIngredient(Ingredient *ingredient)
{
    // check if the ingredient already exists in the inventory
    for (auto &existingIngredient : ingredients)
    {
        if (existingIngredient->getName() == ingredient->getName())
        {
            // if the ingredient is perishable and the expiry date is different, skip
            if (ingredient->getType() == "Perishable" && existingIngredient->getType() == "Perishable" &&
                dynamic_cast<Perishable *>(ingredient)->getExpiryDate() != dynamic_cast<Perishable *>(existingIngredient)->getExpiryDate())
            {
                continue;
            }
            // if the ingredient already exists, update the quantity
            if (ingredient->getType() == existingIngredient->getType())
            {
                existingIngredient->setQuantity(existingIngredient->getQuantity() + ingredient->getQuantity());
                return;
            }
        }
    }
    ingredients.append(const_cast<Ingredient *>(ingredient)); // add new ingredient if not found
}

// remove an ingredient from the inventory
void Inventory::removeIngredient(const Ingredient *ingredient)
{
    for (Ingredient *i : getInventory())
    {
        if (i == ingredient)
        {
            ingredients.removeAll(i);
            return;
        }
    }
}

// update the quantity of an ingredient in the inventory
void Inventory::updateQuantity(const Ingredient *ingredient, qint16 quantity)
{
    // find the ingredient in the inventory and update the quantity
    for (auto &existingIngredient : ingredients)
    {
        if (existingIngredient->getName() == ingredient->getName())
        {
            existingIngredient->setQuantity(quantity);
            return;
        }
    }
    throw std::runtime_error("Ingredient not found in inventory.");
}

// get the list of ingredients in the inventory
const QList<Ingredient *> &Inventory::getInventory() const
{
    return ingredients;
}
