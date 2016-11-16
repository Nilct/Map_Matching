#include "pointroad.h"

#include <iomanip>

long PointRoad::counter = 0;

void PointRoad::updateBelongToRoad(long roadId)
{
    m_vectorOfRoadId.push_back(roadId);
}

void PointRoad::outputInfos()
{
    std::cout << std::setprecision(10);
    std::cout << (m_isNode ? "EXT" : "   ") << " (" << m_x << ", " << m_y << ") [" << m_id << "]" << std::endl;
    std::cout << "belong to " << m_vectorOfRoadId.size() << " roads\n\t";
    for (const auto r : m_vectorOfRoadId)
        std::cout << r << ' ';
    std::cout << std::endl;
}
