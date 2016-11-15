#include "loading.h"

Loading::Loading() : QWidget()
{
    country();
    track();
    grid();
    boutonXY();

    // Création d'un widget qui servira de fenêtre
    setFixedSize(500, 400);



     QVBoxLayout *mainLayout = new QVBoxLayout;
     mainLayout->addWidget(m_country);
     mainLayout->addWidget(m_track);
     mainLayout->addWidget(m_grid);
     mainLayout->addWidget(m_boutonXY);
     setLayout(mainLayout);
     setWindowTitle("Launch");

}

Loading::~Loading()
{
}

void Loading::boutonXY()
{
    m_boutonXY = new QGroupBox("");

    m_cancel = new QPushButton("Cancel");
    m_launch = new QPushButton("Launch");
    QObject::connect(m_cancel, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(m_launch, SIGNAL(clicked()), this, SLOT(launchFiles()));

    QHBoxLayout *vbox = new QHBoxLayout;
    vbox->addWidget(m_cancel);
    vbox->addWidget(m_launch);
    vbox->addStretch(1);
    m_boutonXY->setLayout(vbox);

}

void Loading::country()
{
    m_country = new QGroupBox("Country");

    m_fr = new QRadioButton("France");
    m_usa = new QRadioButton("USA");
    //radio1->setChecked(true);

    QObject::connect(m_fr, SIGNAL(clicked()), this, SLOT(getCountry()));
    QObject::connect(m_usa, SIGNAL(clicked()), this, SLOT(getCountry()));

    QHBoxLayout *vbox = new QHBoxLayout;
    vbox->addWidget(m_fr);
    vbox->addWidget(m_usa);
    vbox->addStretch(1);
    m_country->setLayout(vbox);
}

void Loading::grid()
{
    m_grid = new QGroupBox("Grid");
    m_fileGrid = new QLabel(this);

    m_csvGrid = new QPushButton("SHP");
    m_csvGrid->setGeometry(0, 2, 0, 3);

    QObject::connect(m_csvGrid, SIGNAL(clicked()), this, SLOT(loadFileGrid()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_csvGrid);
    vbox->addWidget(m_fileGrid);
    vbox->addStretch(1);
    m_grid->setLayout(vbox);
}

void Loading::track()
{
    m_track = new QGroupBox("GPS Track");

    m_csvTrack = new QPushButton("CSV");
    m_shpTrack = new QPushButton("SHP");
    m_fileGPS = new QLabel(this);

    QObject::connect(m_csvTrack, SIGNAL(clicked()), this, SLOT(loadFileCSVTrack()));
    QObject::connect(m_shpTrack, SIGNAL(clicked()), this, SLOT(loadFileSHPTrack()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(m_csvTrack);
    vbox->addWidget(m_shpTrack);
    vbox->addWidget(m_fileGPS);
    vbox->addStretch(1);
    m_track->setLayout(vbox);
}

void Loading::loadFileCSVTrack()
{
    m_fileGPS->setText("1 file loaded");
    m_csvTrack->setEnabled(false);
    m_shpTrack->setEnabled(false);
    File fileCSV;
    fileCSV.selectFilesToOpen("csv");
}

void Loading::loadFileSHPTrack()
{
    m_fileGPS->setText("1 file loaded");
    m_csvTrack->setEnabled(false);
    m_shpTrack->setEnabled(false);
    File fileSHP;
    fileSHP.selectFilesToOpen("shp");
    //fileSHP.shp2csv("Point");
}

void Loading::loadFileGrid()
{
    m_fileGrid->setText("1 file loaded");
    m_csvGrid->setEnabled(false);
    File fileSHP;
    fileSHP.selectFilesToOpen("shp");
    //fileSHP.shp2csv("Polyline");
}

void Loading::getCountry()
{
    //m_country->setEnabled(false);
    if( m_fr->isChecked())
        cout << "fr";
    else
        cout << "usa";
}

void Loading::launchFiles()
{
    //if (m_fileGrid->)
}
