/**
 * @file mainwindow.h
 * @brief Header file for MainWindow class
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QCalendarWidget>
#include "mealplan.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToEditScreen();
    void switchToMainScreen();
    void switchToInventoryScreen();
    void switchToStartScreen();

    void displayMealInfoForSelectedDate();
    void getMealInfo();

    void generateList();

    void populateIngredientList();
    void addIngredient();
    void removeIngredient();

private:
    Ui::MainWindow *ui;
    QCalendarWidget *calendarWidget;
    QListWidget *ingredientsListWidget;
    MealPlan *mealPlan;
};
#endif // MAINWINDOW_H
