/**
 * @file daymeal.h
 * @brief Header file for DayMeal class
 */

#ifndef DAYMEAL_H
#define DAYMEAL_H

#include "meal.h"
#include "mealcomponent.h"
#include <QDate>
#include <QList>

class DayMeal : public MealComponent
{
private:
    QList<Meal *> meals; // list of meals
    QDate date;          // date of the meal

public:
    DayMeal(QList<Meal *> mealList, QDate date);
    bool operator==(const DayMeal &other) const
    {
        return date == other.date;
    }
    void add(MealComponent * mealcomponent) override;
    void remove(MealComponent * mealcomponent) override;
    void setMeals(QList<Meal *> &newMeals);
    QList<Meal *> &getMeals();
    void setDate(QDate &newDate);
    QDate getDate() const;
};

#endif // DAYMEAL_H
