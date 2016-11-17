#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>

#include "grid.h"
#include "pointGPS.h"
#include "pointroad.h"
#include "road.h"
#include "track.h"
#include "file.h"

#include <unordered_map>
#include <vector>

typedef std::unordered_map<long, Road> AllRoadMap;
typedef std::vector<PointGPS*> AllPointVector;

class Solver : public QObject {
    Q_OBJECT
public:
    explicit Solver(QObject *parent=0) ;
    /*
    explicit Solver(AllRoadMap* gridRoad, std::vector<PointRoad>* roadPoints, AllPointVector* trackPoint)
        : m_roads(gridRoad)
        , m_roadPoints(roadPoints)
        , m_trackPoints(trackPoint)
    {
    }
    */
    void start();
    void setDistance(PointGPS* p, Road& r);
    void readFiles(File file1, File file2);

    QString m_gridFilename; // to move in protected once signals are in use
    QString m_trackFilename;
//protected:
    Track track;
    Grid grid;
    AllRoadMap* m_roads;
    std::vector<PointRoad>* m_roadPoints;
    AllPointVector* m_trackPoints;

signals:
    void signalMessage(QString);
    void signalDimension(double xMin, double xMax, double yMin, double yMax);
    void signalAllPoints(std::vector<PointGPS*> *);
    void signalAllRoads(std::unordered_map<long,Road>*, std::vector<PointRoad>*);

public slots:
    void onSignalSetGrid(QString s);
    void onSignalSetTrack(QString s);
    void onSignalStart();


};

#endif // SOLVER_H
