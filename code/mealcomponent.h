/**
 * @file mealcomponent.h
 * @brief component class for composite design pattern
 *
 */
#ifndef MEALCOMPONENT_H
#define MEALCOMPONENT_H

class MealComponent
{
public:
    virtual ~MealComponent() = default; // virtual destructor

    virtual void add(MealComponent *component) = 0;    // add a component
    virtual void remove(MealComponent *component) = 0; // remove a component
};

#endif // MEALCOMPONENT_H