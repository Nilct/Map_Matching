#ifndef POINTROAD_H
#define POINTROAD_H

#include "point.h"
#include <iostream>
#include <vector>

#define NO_ID -1

class PointRoad : public Point {
public:
    PointRoad() {} // should never be used !!

    /**
     * @brief Constructor for Road points
     * @param x
     * @param y
     * @param isNode
     */
    PointRoad(double x, double y, bool isNode)
        : Point(x, y)
        , m_isNode(isNode)
        , m_id(NO_ID)
    {
    }

    void updateBelongToRoad(long roadId);

    std::string infos() const { return Point::infos(); }
    void outputInfos();

    // accessors
    int id() const { return m_id; }
    void setid(int id) { m_id = id; }
    long isNode() const { return m_isNode; }
    const std::vector<long>& vectorOfRoadId() const { return m_vectorOfRoadId; }
protected:
    static long counter; // counter used to generate unique m_id (not used for Seattle data)
    bool m_isNode; // true if this point is an extremity of a road
    int m_id; // unique id of the point
    std::vector<long> m_vectorOfRoadId; // list of roads sharing the point
};

#endif // POINTROAD_H
