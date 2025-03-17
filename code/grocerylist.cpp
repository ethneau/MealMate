#include "grocerylist.h"
#include "inventory.h"
#include <iostream>
#include <fstream>

// add an item to the grocery list
void GroceryList::addItem(const Ingredient *ingredient)
{
    requiredIngredients.append(const_cast<Ingredient *>(ingredient));
}

// remove an item from the grocery list
void GroceryList::removeItem(const Ingredient *ingredient)
{
    requiredIngredients.removeAll(ingredient);
}

// generate the grocery list, output to file
void GroceryList::generateList(const QString &filename) const
{
    // open the file
    std::ofstream outFile(filename.toStdString());
    if (outFile.is_open())
    {
        for (const auto &item : requiredIngredients)
        {
            // write the item to the file
            outFile << item->getName().toStdString() << " "
                    << item->getQuantity()
                    << std::endl;
        }
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filename.toStdString() << std::endl; // error message
    }
}

// get the list of items
void GroceryList::getRequiredIngredients(DayMeal &daymeal, Inventory &inv)
{
    QList<Ingredient *> req;                                       // list of required ingredients
    QList<Ingredient *> inventoryIngredients = inv.getInventory(); // list of inventory ingredients
    QList<Meal *> meals = daymeal.getMeals();                      // list of meals

    IngredientFactory *factory = new NonPerishableIngredientFactory(); // factory for creating ingredients

    // iterate through the meals
    for (const Meal *meal : meals)
    {
        QList<Ingredient *> mealIngredients = meal->getIngredients(); // list of meal ingredients

        for (Ingredient *ingredient : mealIngredients)
        {
            bool found = false;

            for (Ingredient *invIngredient : inventoryIngredients)
            {
                if (ingredient->getName() == invIngredient->getName())
                {
                    found = true;
                    if (ingredient->getQuantity() >= invIngredient->getQuantity())
                    {
                        // create a new ingredient for the required quantity
                        Ingredient *neededIngredient;
                        if (invIngredient->getType() == "Perishable" && dynamic_cast<Perishable *>(invIngredient)->getExpiryDate() < QDate::currentDate())
                        {
                            neededIngredient = factory->createIngredient(ingredient->getName(), ingredient->getQuantity()); // create a new ingredient
                        }
                        else
                        {
                            neededIngredient = factory->createIngredient(ingredient->getName(), ingredient->getQuantity() - invIngredient->getQuantity()); // create a new ingredient
                        }
                        inv.removeIngredient(invIngredient); // remove the ingredient from the inventory

                        // add the ingredient to the required list
                        if (neededIngredient->getQuantity() != 0)
                        {
                            req.append(neededIngredient);
                        }
                    }
                    break;
                }
            }

            if (!found)
            {
                // Add ingredient directly to the required list
                Ingredient *neededIngredient = factory->createIngredient(ingredient->getName(), ingredient->getQuantity());
                req.append(neededIngredient);
            }
        }
    }

    // Clean up the existing requiredIngredients
    qDeleteAll(requiredIngredients);
    requiredIngredients.clear();

    // Transfer the newly calculated ingredients
    requiredIngredients = req;
}
// Destructor
GroceryList::~GroceryList()
{
    qDeleteAll(requiredIngredients);
    requiredIngredients.clear();
}
