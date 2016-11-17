#include "MainWindow.h"

// The Constructor calls the subfunctions for creation of the sample application

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent)
{
    createGuiControlComponents();
    createSubSlidingWidgets();
    createSlidingStackedWidget();
    createMainLayout();
    createConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createGuiControlComponents()
{
    buttonNext = new QPushButton(tr("Next"));
    buttonNext->setEnabled(false);
    buttonCancel = new QPushButton(tr("Cancel"));
}

void MainWindow::createMainLayout()
{
    //centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout();
    //centralWidget->setLayout(mainLayout);
    this->setLayout(mainLayout);
    controlPaneLayout = new QGridLayout();
    mainLayout->addWidget(slidingStacked);
    mainLayout->addLayout(controlPaneLayout);

    controlPaneLayout->addWidget(buttonCancel, 1, 1, 1, 1);
    controlPaneLayout->addWidget(buttonNext, 1, 2, 1, 1);

    process = new QProcessViewer(this);
    mainLayout->addWidget(process);

}

void MainWindow::createSubSlidingWidgets()
{
    slideWidget1 = new Loading();
    slideWidget2 = new Filtering();
    slideWidget3 = new QWidget();

    QVBoxLayout* slideWidget3layout = new QVBoxLayout();
    slideWidget3->setLayout(slideWidget3layout);

    QPushButton* b31 = new QPushButton("Isn't");
    slideWidget3layout->addWidget(b31);
    QPushButton* b32 = new QPushButton("Qt cool ?");
    slideWidget3layout->addWidget(b32);
}

void MainWindow::createSlidingStackedWidget()
{
    slidingStacked = new SlidingStackedWidget(this);
    slidingStacked->addWidget(slideWidget1);
    slidingStacked->addWidget(slideWidget2);
    slidingStacked->addWidget(slideWidget3);
}

void MainWindow::createConnections()
{
    QObject::connect(slideWidget1, SIGNAL(ready(File, File)), this, SLOT(readyToNext1(File, File)));
    QObject::connect(slideWidget1, SIGNAL(readyNext(File)), slideWidget2, SLOT(getInfo(File)));
    QObject::connect(slideWidget2, SIGNAL(ready(double, int)), this, SLOT(readyToNext2(double, int)));
    QObject::connect(buttonNext, SIGNAL(clicked()), slidingStacked, SLOT(slideInNext()));
    QObject::connect(buttonNext, SIGNAL(clicked()), this, SLOT(putNone()));
    QObject::connect(buttonCancel, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void MainWindow::putNone()
{
    buttonNext->setEnabled(false);
}

void MainWindow::readyToNext1(File file1, File file2)
{
    File fileTrack = file1;
    File fileGrid = file2;
    QString fileT = fileTrack.filePath.at(0) + fileTrack.fileName.at(0) + "." + fileTrack.fileExtension.at(0);
    QString fileG = fileGrid.filePath.at(0) + fileGrid.fileName.at(0) + "." + fileGrid.fileExtension.at(0);

    trace.readFromCSV(fileT);
    grille.setBoundingBox(trace.m_xMin, trace.m_xMax, trace.m_yMin, trace.m_yMax);
    grille.readFromCSV(fileG);

    if (!grille.trackInGrid()) {
        QMessageBox::warning(this, "Erreur de fichiers", "Attention, l'emprise des données de correspond pas !");
    } else {
        buttonNext->setEnabled(true);
    }
}

void MainWindow::readyToNext2(double fSpat,int fTemp)
{
    if (fSpat != 0)
    {
        trace.spaceFilter(double(fSpat));
    }
    if (fTemp != 0)
    {
        trace.temporalFilter(fTemp);
    }
    buttonNext->setEnabled(true);
}
