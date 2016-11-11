#ifndef POINTGPS_H
#define POINTGPS_H

#include "point.h"

#define ALT_DEFAULT 0.0
class PointGPS : public Point {
public:
    /**
     * @brief PointGPS constructor
     * Create a new Point GPS with default altitude
     */
    PointGPS(double x, double y, unsigned int timestamp)
        : Point(x, y)
        , m_altitude(ALT_DEFAULT)
        , m_timeStamp(timestamp)
    {
    }

    /**
     * @brief PointGPS constructor
     * Create a new Point GPS
     */
    PointGPS(double x, double y, float altitude, unsigned int timestamp)
        : Point(x, y)
        , m_altitude(altitude)
        , m_timeStamp(timestamp)
    {
    }

    unsigned int timeStamp() const { return m_timeStamp;}
    float altitude() const { return m_altitude;}
protected:
    float m_altitude;   // TO keep ?
    unsigned int m_timeStamp; // WARNING in second
};
#endif // POINTGPS_H
