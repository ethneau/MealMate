/**
 * @file meal.h
 * @brief Header file for Meal class
 */

#ifndef MEAL_H
#define MEAL_H

#include <QString>
#include <QList>
#include "ingredient.h"
#include "mealcomponent.h"

class Meal : public MealComponent
{
private:
    QString name;
    QList<Ingredient *> ingredients;

public:
    Meal(QString &mealName, QList<Ingredient *> ingredientList);

    // compare two meal objects
    bool operator==(const Meal &other) const
    {
        return name == other.name && ingredients == other.ingredients;
    }

    void add(MealComponent * mealcomponent) override;
    void remove(MealComponent * mealcomponent) override;
    const QList<Ingredient *> &getIngredients() const;
    const QString getName() const;
    void changeName(const QString &name);
    bool checkIfExists(const Ingredient *ingredient);
};

#endif // MEAL_H
