/**
 * @file ingredient.h
 * @brief Header file for Ingredient class with Factory design pattern
 */

#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>
#include <QtTypes>
#include <QDate>
#include "mealcomponent.h"

class Ingredient : public MealComponent // Ingredient Abstract class
{
private:
    QString name;    // name of the ingredient
    qint16 quantity; // quantity of the ingredient

public:
    Ingredient(const QString &name, qint16 quantity);

    // compare two ingredient objects
    bool operator==(const Ingredient &other) const
    {
        return name == other.name && quantity == other.quantity;
    }

    QString getName() const;
    qint16 getQuantity() const;
    void setQuantity(qint16 q);

    void add(MealComponent *mealcomponent) {}
    void remove(MealComponent *mealcomponent) {}

    // abstract methods
    virtual QString getType() const = 0;
    virtual ~Ingredient() {}
};

class Perishable : public Ingredient // concrete class
{
public:
    Perishable(const QString &name, qint16 quantity, const QDate &expiryDate);
    QString getType() const override;
    QDate getExpiryDate() const;
    void setExpiryDate(QDate &date);

private:
    QDate expiryDate; // expiry date of the ingredient
};

class NonPerishable : public Ingredient // concrete class
{
public:
    NonPerishable(const QString &name, qint16 quantity);
    QString getType() const override;
};

class IngredientFactory // abstract factory class
{
public:
    virtual Ingredient *createIngredient(const QString &name, qint16 quantity) = 0;
    virtual ~IngredientFactory() {}
};

class PerishableIngredientFactory : public IngredientFactory // concrete factory class
{
public:
    Ingredient *createIngredient(const QString &name, qint16 quantity) override;
};

class NonPerishableIngredientFactory : public IngredientFactory // concrete factory class
{
public:
    Ingredient *createIngredient(const QString &name, qint16 quantity) override;
};

#endif
