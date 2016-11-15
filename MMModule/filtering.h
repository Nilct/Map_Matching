#ifndef FILTERING_H
#define FILTERING_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QObject>
#include <QSlider>
#include <QLCDNumber>

#include "track.h"

class Filtering : public QWidget
{
    Q_OBJECT
public:
    Filtering();
    ~Filtering();


public slots:


signals:


private:

    void nbPtTrack();
    void spatial();
    void temporal();
    void boutonXY();

    QGroupBox *m_spat;
    QGroupBox *m_temp;
    QGroupBox *m_boutonXY;

    QSlider *m_slidTemp;
    QLCDNumber *m_valueTemp;
    QSlider *m_slidSpat;
    QLCDNumber *m_valueSpat;
    QLabel *m_nbPtTrack;

    QPushButton *m_cancel;
    QPushButton *m_launch;
};

#endif // FILTERING_H
