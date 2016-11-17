#include "solver.h"
#define DEBUG_SOLVER false

void Solver::start()
{
    track.readFromCSV(m_trackFilename);
    m_trackPoints= track.getPointsAsPointer();
    emit signalMessage(QString::fromStdString(track.infos()));
    emit signalDimension(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    emit signalAllPoints(m_trackPoints);

    grid.readFromCSV(m_gridFilename);
    emit signalMessage(QString::fromStdString(grid.infos()));
    emit signalAllRoads(&grid.m_mapOfAllRoads, &(grid.m_vectorOfPoints));
    grid.buildMarkovMatrix();
    emit signalMessage("Markov Matrix built");
}

void Solver::setDistance(PointGPS* p, Road& r)
{
    if (DEBUG_SOLVER) {
        std::cout << p->infos() << std::endl;
        r.outputInfos();
    }
    const std::vector<int>& listOfPointId = r.vectorOfPointsId();
    double d, bestDistance = std::numeric_limits<double>::max();
    for (uint i = 1; i < listOfPointId.size(); i++) {
        //int j=listOfPointId[i-1];
        //Point p1= m_roadPoints->at(j);
        d = p->distanceToSegment(m_roadPoints->at(listOfPointId[i - 1]), m_roadPoints->at(listOfPointId[i]));
        if (d < bestDistance)
            bestDistance = d;
    }
    if (bestDistance < DISTANCE_THRESHOLD)
        p->addEmissionProbability(r.edgeId(), bestDistance);

    if (DEBUG_SOLVER) {
        std::cout << p->infos() << std::endl;
    }
}

void Solver::onSignalSetGrid(QString s)
{
    m_gridFilename = s;
}

void Solver::onSignalSetTrack(QString s)
{
    m_trackFilename = s;
}

void Solver::onSignalStart()
{
    emit signalMessage("Solver started");
    start();
}
