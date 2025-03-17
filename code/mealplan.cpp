#include "mealplan.h"

/**
 * @brief add a day meal to the meal plan
 * @param dayMeal
 */
void MealPlan::add(MealComponent * mealcomponent)
{
    DayMeal * dayMeal = (DayMeal*) mealcomponent;
    dayMeals.push_back(dayMeal);
}
/**
 * @brief remove a day meal from the meal plan
 * @param dayMeal
 */
void MealPlan::remove(MealComponent * mealcomponent)
{
    DayMeal * dayMeal = (DayMeal*) mealcomponent;
    dayMeals.removeAll(dayMeal);
}
/**
 * @brief get the list of day meals
 * @return list of day meals
 */
QList<DayMeal *> &MealPlan::getDayMeal()
{
    return dayMeals;
}
/**
 * @brief get the day meal for a specific date
 * @param date
 */
DayMeal *&MealPlan::getSpecificDayMeal(QDate date)
{
    // find day meal for the date
    for (auto &daymeal : dayMeals)
    {
        if (daymeal->getDate() == date)
        {
            return daymeal;
        }
    }
    // return new day meal if not found
    DayMeal *newDayMeal = new DayMeal(QList<Meal *>(), date);
    add(newDayMeal);
    return dayMeals.back();
}
