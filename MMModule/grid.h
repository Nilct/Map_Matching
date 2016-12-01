#ifndef GRID_H
#define GRID_H

#include "road.h"
#include "track.h"

#include <QObject>

#include <QString>
#include <unordered_map>
#include <vector>

struct hashFunc {
    size_t operator()(const PointRoad& p) const
    {
        size_t h1 = std::hash<double>()(p.x());
        size_t h2 = std::hash<double>()(p.y());
        return h1 ^ (h2 << 1);
    }
};

struct equalsFunc {
    bool operator()(const PointRoad& p1, const PointRoad& p2) const
    {
        return p1.samePointAs(p2);
    }
};

typedef std::unordered_map<PointRoad, int, hashFunc, equalsFunc> ExtremityPointMap; // for all node points
typedef std::unordered_map<long, Road> AllRoadMap;
//typedef std::unordered_map<long, Road&> AllRoadMap;   // for all roads (& do not recreate object)

/**
 * @brief Grid embedded roads. This describes the network.
 */
class Grid : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Constructor
     */
    Grid();
    /**
     * @brief Destructor
     */
    virtual ~Grid();

    /**
     * @brief Save data about our area of roads
     * @param xMin Coordinate xMin of a track
     * @param xMax Coordinate xMax of a track
     * @param yMin Coordinate yMin of a track
     * @param yMax Coordinate yMax of a track
     */
    void setTrackBoundingBox(double xMin, double xMax, double yMin, double yMax);

    /**
     * @brief Reads a csv file and inserts info into the corresponding attributs
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);

    /**
     * @brief Creates a new road and inserts it in m_road
     */
    void addRoad(const std::vector<std::vector<double> >& listOfCoordinates, long edgeId);

    /**
     * @brief Test if a point is in the defined area of a track
     * @param x Coordinate x of a point
     * @param y Coordinate x of a point
     * @return true or false
     */
    bool inFootPrint(double x, double y);

    /**
     * @brief Find max and min of the grid
     * @param x Coordinate x
     * @param y Coordinate y
     */
    void updateGrid(double x, double y);

    /**
     * @brief Check if track is in grid
     * @return true if track is in grid
     */
    bool trackInGrid();

    /**
     * @brief Compute the distance of a point to a road
     * @param p the Point GPS
     * @param r the Road
     */
    void setDistance(PointGPS& p, Road& r);

    /**
     * @brief buildMarkovMatrix
     */
    void buildMarkovMatrix();

    double computeDistanceFraction(PointGPS *prevPoint, PointGPS *curPoint, long prevRoadId, long curRoadId);
    std::vector<double> getProjectedPointAndDistance(PointGPS *p, Road *r);

    double getDistanceBetweenProjections(Point *projR1, Point *projR2, Road *r1);
    double getDistanceToExtremity(Point *projR1, int node, Road *r1);
    int getSegmentCounter(Point *p, Road *r);

    // test functions
    void outputInfos();
    std::string infos();
    AllRoadMap::iterator getRoadEntry(long id); // used to update neighbors (for markovmatrix)
    AllRoadMap* getRoads() { return &m_mapOfAllRoads; } // TODO const ?
    std::vector<PointRoad>* getPoints() { return &m_vectorOfPoints; }

    /**
     * @brief Getters
     */
    int getNoOfRoads() const { return m_mapOfAllRoads.size(); }
    int getNoOfPoints() const { return m_vectorOfPoints.size(); }
    double xMin() const { return m_xMin; }
    double xMax() const { return m_xMax; }
    double yMin() const { return m_yMin; }
    double yMax() const { return m_yMax; }
    double xMinGrid() const { return m_xMinGrid; }
    double xMaxGrid() const { return m_xMaxGrid; }
    double yMinGrid() const { return m_yMinGrid; }
    double yMaxGrid() const { return m_yMaxGrid; }

    AllRoadMap m_mapOfAllRoads;
    std::vector<PointRoad> m_vectorOfPoints;

signals:
    void signalMessage(QString);

protected:
    std::string m_gridFullName;
    ExtremityPointMap m_mapOfExtPoints; // temporary container during csv loading
    static long counter; // counter used to generate unique m_id (not used for Seattle data)

    /**
     * @brief The coordinates of the track
     */
    //@{
    double m_xMin; /**< The x min value*/
    double m_xMax; /**< The x max value*/
    double m_yMin; /**< The y min value*/
    double m_yMax; /**< The y max value*/
    //@}

    /**
     * @name The coordinates of the grid.
     */
    //@{
    double m_xMinGrid; /**< The x min value*/
    double m_xMaxGrid; /**< The x max value*/
    double m_yMinGrid; /**< The y min value*/
    double m_yMaxGrid; /**< The y max value*/
    //@}
};

#endif // GRID_H
