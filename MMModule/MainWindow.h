#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QCheckBox>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QtGui/QMainWindow>
#include <QtGui>

#include "SlidingStackedWidget.h"
#include "filtering.h"
#include "loading.h"

#include "track.h"
#include "grid.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void readyToNext1(File file1, File file2);

protected:
    void createGuiControlComponents();
    void createMainLayout();
    void createSubSlidingWidgets();
    void createConnections();
    void createSlidingStackedWidget();
    QPushButton* buttonNext;
    QPushButton* buttonCancel;

    SlidingStackedWidget* slidingStacked;
    QVBoxLayout* mainLayout;
    QGridLayout* controlPaneLayout;
    QWidget* centralWidget;
    Loading* slideWidget1;
    Filtering* slideWidget2;
    QWidget* slideWidget3;

    /**
     * @brief Value of the first Slide
     */
    Track trace;
    Grid grille;

};

#endif // MAINWINDOW_H
