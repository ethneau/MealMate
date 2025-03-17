#include "daymeal.h"

// constructor
DayMeal::DayMeal(QList<Meal *> mealList, QDate date) : meals(mealList), date(date) {}

// add a meal to the day meal
void DayMeal::add(MealComponent * mealcomponent)
{
    Meal* meal = (Meal*) mealcomponent;
    meals.append(meal);
}

// remove a meal from the day meal
void DayMeal::remove(MealComponent * mealcomponent)
{
    Meal* meal = (Meal*) mealcomponent;
    meals.removeAll(meal);
}

// set the list of meals
void DayMeal::setMeals(QList<Meal *> &newMeals)
{
    meals = newMeals;
}

// get the list of meals
QList<Meal *> &DayMeal::getMeals()
{
    return meals;
}

// set the date of the day meal
void DayMeal::setDate(QDate &newDate)
{
    date = newDate;
}

// get the date of the day meal
QDate DayMeal::getDate() const
{
    return date;
}
