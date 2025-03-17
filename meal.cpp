#include "meal.h"

// constructor
Meal::Meal(QString &mealName, QList<Ingredient *> ingredientList) : name(mealName), ingredients(ingredientList) {}

// add an ingredient to the meal
void Meal::add(MealComponent *mealcomponent)
{
    Ingredient *ingredient = (Ingredient *)mealcomponent;
    // check if the ingredient already exists in the meal
    if (!checkIfExists(ingredient))
    {
        ingredients.append(const_cast<Ingredient *>(ingredient));
    }
}

// remove an ingredient from the meal
void Meal::remove(MealComponent *mealcomponent)
{
    Ingredient *ingredient = (Ingredient *)mealcomponent;
    ingredients.removeAll(ingredient);
}

// get the list of ingredients in the meal
const QList<Ingredient *> &Meal::getIngredients() const
{
    return ingredients;
}

// get the name of the meal
const QString Meal::getName() const
{
    return name;
}

// change the name of the meal
void Meal::changeName(const QString &newName)
{
    name = newName;
}

// check if an ingredient already exists in the meal
bool Meal::checkIfExists(const Ingredient *ingredient)
{
    for (Ingredient *i : ingredients)
    {
        if (i->getName() == ingredient->getName())
        {
            i->setQuantity(ingredient->getQuantity()); // update the quantity
            return true;
        }
    }
    return false;
}
