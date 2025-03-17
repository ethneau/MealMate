/**
 * @file mealplan.h
 * @brief Header file for MealPlan class
 */

#ifndef MEALPLAN_H
#define MEALPLAN_H

#include <QList>
#include "daymeal.h"
#include "mealcomponent.h"

class MealPlan : public MealComponent
{
private:
    QList<DayMeal *> dayMeals; // list of day meals

public:
    void add(MealComponent *mealcomponent) override;
    void remove(MealComponent *mealcomponent) override;
    QList<DayMeal *> &getDayMeal();
    DayMeal *&getSpecificDayMeal(QDate date);
};

#endif // MEALPLAN_H
