#include "stdafx.h"
#include "Triangle3d.h"

namespace DigitalPhotogrammetry
{
    CTriangle3d::CTriangle3d()
    {
    }

    CTriangle3d::CTriangle3d(Vector3d& node1, Vector3d& node2, Vector3d& node3)
    {
        Nodes[0] = node1;
        Nodes[1] = node2;
        Nodes[2] = node3;
    }


    CTriangle3d::~CTriangle3d()
    {
    }

}
