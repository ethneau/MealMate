#include "ingredient.h"
using namespace std;

// Ingredient Abstract class
// constructor
Ingredient::Ingredient(const QString &name, qint16 quantity) : name(name), quantity(quantity) {}

// get the name of the ingredient
QString Ingredient::getName() const { return name; }

// get the quantity of the ingredient
qint16 Ingredient::getQuantity() const { return quantity; }

// set the quantity of the ingredient
void Ingredient::setQuantity(qint16 q) { quantity = q; }

// Perishable class
// constructor
Perishable::Perishable(const QString &name, qint16 quantity, const QDate &expiryDate) : Ingredient(name, quantity), expiryDate(expiryDate) {}

// get the type of the ingredient
QString Perishable::getType() const
{
    return "Perishable";
}

// get the expiry date of the ingredient
QDate Perishable::getExpiryDate() const
{
    return expiryDate;
}

// set the expiry date of the ingredient
void Perishable::setExpiryDate(QDate &date)
{
    expiryDate = date;
}

// NonPerishable class

NonPerishable::NonPerishable(const QString &name, qint16 quantity) : Ingredient(name, quantity) {}

// get the type of the ingredient
QString NonPerishable::getType() const
{
    return "NonPerishable";
}

// Perishable Ingredient Factory
Ingredient *PerishableIngredientFactory::createIngredient(const QString &name, qint16 quantity)
{
    return new Perishable(name, quantity, QDate::currentDate());
}

// NonPerishable Ingredient Factory
Ingredient *NonPerishableIngredientFactory::createIngredient(const QString &name, qint16 quantity)
{
    return new NonPerishable(name, quantity);
}
