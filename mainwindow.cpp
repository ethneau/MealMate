#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inventory.h"
#include "grocerylist.h"

#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QInputDialog>
#include <QDialog>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), mealPlan(new MealPlan())
{
    ui->setupUi(this);

    // start screen buttons
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::switchToMainScreen);
    connect(ui->startExitButton, &QPushButton::clicked, this, QCoreApplication::quit);

    // inventory screen buttons
    connect(ui->invBackButton, &QPushButton::clicked, this, &MainWindow::switchToMainScreen);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::addIngredient);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeIngredient);

    // edit screen buttons
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &MainWindow::getMealInfo);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &MainWindow::switchToMainScreen);

    // main screen buttons
    // generate list
    connect(ui->generateButton, &QPushButton::clicked, this, &MainWindow::generateList);

    // change to inventory screen
    connect(ui->invButton, &QPushButton::clicked, this, &MainWindow::switchToInventoryScreen);

    // change to edit screen
    connect(ui->editButton, &QPushButton::clicked, this, &MainWindow::switchToEditScreen);

    // change to start screen
    connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::switchToStartScreen);

    // calendar select
    calendarWidget = ui->calendarWidget;
    connect(calendarWidget, &QCalendarWidget::selectionChanged, this, &MainWindow::displayMealInfoForSelectedDate);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mealPlan;
}

// display meal info to the ui
void MainWindow::displayMealInfoForSelectedDate()
{
    try
    {
        QDate selectedDate = calendarWidget->selectedDate();                          // get selected date
        QList<Meal *> meals = mealPlan->getSpecificDayMeal(selectedDate)->getMeals(); // get list of meals from selected date
        // set meal titles
        if (meals.isEmpty())
        { // no meal info added
            ui->meal1_2->setText("");
            ui->meal2_2->setText("");
            ui->meal3_2->setText("");
            ui->ingredientsList->setText("No meals added");
        }
        else
        {
            // set meal titles
            if (meals.at(0)->getName() == "")
            {
                ui->meal1_2->setText("");
            }
            else
            {
                ui->meal1_2->setText(meals.at(0)->getName());
            }
            if (meals.at(1)->getName() == "")
            {
                ui->meal2_2->setText("");
            }
            else
            {
                ui->meal2_2->setText(meals.at(1)->getName());
            }
            if (meals.at(2)->getName() == "")
            {
                ui->meal3_2->setText("");
            }
            else
            {
                ui->meal3_2->setText(meals.at(2)->getName());
            }

            ui->ingredientsList->clear();
            QStringList ingredientList;

            // get ingredients list
            for (const Meal *meal : meals)
            {
                for (const Ingredient *ingredient : meal->getIngredients())
                {
                    QString ingredientStr = QString("%1 %2").arg(ingredient->getName()).arg(ingredient->getQuantity());
                    ingredientList.append(ingredientStr);
                }
            }

            // Set ingredients list to QLabel
            if (ingredientList.isEmpty())
            {
                ui->ingredientsList->setText("No ingredients added");
            }
            else
            {
                ui->ingredientsList->setText(ingredientList.join("\n"));
            }
        }
    }
    catch (std::runtime_error &e)
    {
    }
}
// restore ingredient list from history
void restoreIngList(Meal *m, QTextEdit *ingList)
{
    QStringList ingredientList;
    for (const Ingredient *ingredient : m->getIngredients())
    {
        QString ingredientStr = QString("%1 %2").arg(ingredient->getName()).arg(ingredient->getQuantity());
        ingredientList.append(ingredientStr);
    }

    // set ingredients list to QLabel
    if (!ingredientList.isEmpty())
    {
        ingList->setText(ingredientList.join(", "));
    }
}

// add new ingredients to meal object
void addIngredientsToMeal(const QString &ingStr, Meal *meal)
{
    QStringList items = ingStr.split(",", Qt::SkipEmptyParts); // split ingredients by comma

    // trim whitespace from each item
    for (QString &item : items)
    {
        item = item.trimmed();
    }
    items.removeDuplicates(); // remove duplicate ingredients

    // create ingredient factory
    IngredientFactory *factory = new NonPerishableIngredientFactory();

    for (const QString &item : items)
    {
        QStringList parts = item.split(" ", Qt::SkipEmptyParts); // split ingredient name and quantity

        // check if ingredient has name and quantity
        if (parts.size() != 2)
        {
            continue;
        }

        QString name = parts[0];
        bool ok = false;
        qint16 quantity = parts[1].toShort(&ok); // extract quantity as integer

        // check if quantity is valid
        if (!ok)
        {
            std::cerr << "Invalid quantity for ingredient: " << item.toStdString() << std::endl;
            continue;
        }

        // create ingredient object and add to meal
        Ingredient *ing = factory->createIngredient(name, quantity);
        meal->add(ing);
    }
    delete factory;
}

// get meal info from user
void MainWindow::getMealInfo()
{
    // get meal titles and ingredients
    QString name1 = ui->mealtitle1->toPlainText();
    QString name2 = ui->mealtitle2->toPlainText();
    QString name3 = ui->mealtitle3->toPlainText();

    QString ing1 = ui->inglist1->toPlainText();
    QString ing2 = ui->inglist2->toPlainText();
    QString ing3 = ui->inglist3->toPlainText();

    // clear edits
    ui->mealtitle1->clear();
    ui->mealtitle2->clear();
    ui->mealtitle3->clear();

    ui->inglist1->clear();
    ui->inglist2->clear();
    ui->inglist3->clear();

    QDate selectedDate = calendarWidget->selectedDate();           // get selected date
    DayMeal *dayMeal = mealPlan->getSpecificDayMeal(selectedDate); // get meals for the selected date
    dayMeal->setDate(selectedDate);

    if (dayMeal->getMeals().isEmpty())
    {
        // add new meals to the list
        Meal *m1 = new Meal(name1, QList<Ingredient *>());
        dayMeal->add(m1);
        addIngredientsToMeal(ing1, m1);
        Meal *m2 = new Meal(name2, QList<Ingredient *>());
        dayMeal->add(m2);
        addIngredientsToMeal(ing2, m2);
        Meal *m3 = new Meal(name3, QList<Ingredient *>());
        dayMeal->add(m3);
        addIngredientsToMeal(ing3, m3);
        mealPlan->add(dayMeal);
    }
    else
    {
        // change existing meal titles and ingredients
        dayMeal->getMeals()[0]->changeName(name1);
        dayMeal->getMeals()[1]->changeName(name2);
        dayMeal->getMeals()[2]->changeName(name3);

        addIngredientsToMeal(ing1, dayMeal->getMeals()[0]);
        addIngredientsToMeal(ing2, dayMeal->getMeals()[1]);
        addIngredientsToMeal(ing3, dayMeal->getMeals()[2]);
    }
    switchToMainScreen();
}

// generate grocery list
void MainWindow::generateList()
{
    Inventory *inv = Inventory::getInstance();
    QString fileName = QFileDialog::getSaveFileName(this, "Save Grocery List", "", "Text Files (*.txt);;All Files (*)"); // get file name

    // user canceled the dialog
    if (fileName.isEmpty())
    {
        return;
    }

    QDate selectedDate = calendarWidget->selectedDate(); // get selected date
    DayMeal *dayMeal = mealPlan->getSpecificDayMeal(selectedDate);

    // generate grocery list
    GroceryList *groceryList = new GroceryList();
    groceryList->getRequiredIngredients(*dayMeal, *inv);
    groceryList->generateList(fileName);

    QMessageBox::information(nullptr, "Grocery List Generated", "The grocery list was successfully generated");
}

// populate ingredient list
void MainWindow::populateIngredientList()
{
    // get the inventory instance and its ingredients
    const QList<Ingredient *> &ingredients = Inventory::getInstance()->getInventory();

    // clear the list before repopulating
    ui->invList->clear();

    // add each ingredient to the list
    for (const Ingredient *ingredient : ingredients)
    {
        QString ingredientInfo = QString("%1 - %2").arg(ingredient->getName()).arg(ingredient->getQuantity());

        // check if the ingredient is a perishable and add expiry date
        if (ingredient->getType() == "Perishable")
        {
            const Perishable *perishable = dynamic_cast<const Perishable *>(ingredient);
            if (perishable)
            {
                ingredientInfo += QString(" (Expiry: %1)").arg(perishable->getExpiryDate().toString("yyyy-MM-dd"));
            }
        }

        ui->invList->addItem(ingredientInfo); // add the ingredient to the list widget
    }
}

// get a date from the user for perishable ingredients
QDate getDateFromUser(QWidget *parent = nullptr)
{
    // create a dialog to get the expiry date
    QDialog dialog(parent);
    dialog.setWindowTitle("Enter Expiry Date");

    QVBoxLayout layout(&dialog);

    QDateEdit dateEdit;
    dateEdit.setCalendarPopup(true);
    dateEdit.setDate(QDate::currentDate()); // default to today's date
    layout.addWidget(&dateEdit);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addWidget(&buttonBox);

    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted)
    {
        return dateEdit.date();
    }
    else
    {
        return QDate(); // return an invalid date if canceled
    }
}

// add a new ingredient to the inventory
void MainWindow::addIngredient()
{
    // get ingredient details (name, quantity, type, etc.)
    bool ok;
    QString name = QInputDialog::getText(this, "Add Ingredient", "Ingredient Name:", QLineEdit::Normal, "", &ok);
    qint16 quantity = QInputDialog::getInt(this, "Add Ingredient", "Quantity:", 1, 1, 1000, 1, &ok);

    // add the new ingredient to the inventory
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Ingredient Type", "Is this ingredient perishable?", QMessageBox::Yes | QMessageBox::No);

    bool isPerishable = (reply == QMessageBox::Yes);

    Ingredient *newIngredient = nullptr;
    IngredientFactory *factory = nullptr;
    if (isPerishable)
    {
        QDate expiryDate = getDateFromUser(this); // get the expiry date from the user
        if (!expiryDate.isValid())
        {
            QMessageBox::information(this, "Input Canceled", "No date was selected.");
            populateIngredientList(); // re-populate the list to reflect the new addition
            return;
        }
        else
        {
            QMessageBox::information(this, "Date Selected", "You selected: " + expiryDate.toString());
        }

        // create a perishable ingredient
        factory = new PerishableIngredientFactory();
        newIngredient = factory->createIngredient(name, quantity);
        dynamic_cast<Perishable *>(newIngredient)->setExpiryDate(expiryDate);
    }
    else
    {
        // create a non-perishable ingredient
        factory = new NonPerishableIngredientFactory();
        newIngredient = factory->createIngredient(name, quantity);
    }

    Inventory::getInstance()->addIngredient(newIngredient);
    populateIngredientList(); // re-populate the list to reflect the new addition
}

// remove an ingredient from the inventory
void MainWindow::removeIngredient()
{
    QListWidgetItem *selectedItem = ui->invList->currentItem(); // get the selected item from the list

    if (selectedItem)
    {
        QString ingredientInfo = selectedItem->text();
        QString ingredientName = ingredientInfo.split(" - ").first();

        // find the ingredient in the inventory
        QList<Ingredient *> ingredients = Inventory::getInstance()->getInventory();
        for (Ingredient *ingredient : ingredients)
        {
            if (ingredient->getName() == ingredientName)
            {
                Inventory::getInstance()->removeIngredient(ingredient);
                break;
            }
        }

        // re-populate the list to reflect the removal
        populateIngredientList();
    }
}

// switch to inventory screen
void MainWindow::switchToInventoryScreen()
{
    ui->stackedWidget->setCurrentIndex(3);
    populateIngredientList();
}

// switch to edit screen and restore history
void MainWindow::switchToEditScreen()
{
    ui->stackedWidget->setCurrentIndex(2);                                        // switch to edit screen
    QDate selectedDate = calendarWidget->selectedDate();                          // get selected date
    QList<Meal *> meals = mealPlan->getSpecificDayMeal(selectedDate)->getMeals(); // get meal list for selected date

    // restore meal title history
    if (!meals.isEmpty())
    {
        ui->mealtitle1->setText(meals[0]->getName());
        ui->mealtitle2->setText(meals[1]->getName());
        ui->mealtitle3->setText(meals[2]->getName());

        restoreIngList(meals.at(0), ui->inglist1);
        restoreIngList(meals.at(1), ui->inglist2);
        restoreIngList(meals.at(2), ui->inglist3);
    }
}

// switch to main screen
void MainWindow::switchToMainScreen()
{
    ui->stackedWidget->setCurrentIndex(1);
    displayMealInfoForSelectedDate();
}

// switch to start screen
void MainWindow::switchToStartScreen()
{
    ui->stackedWidget->setCurrentIndex(0);
}
