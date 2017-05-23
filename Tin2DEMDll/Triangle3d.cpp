#include "stdafx.h"
#include "Triangle3d.h"

namespace DigitalPhotogrammetry
{
    CTriangle3d::CTriangle3d()
    {
    }

    //CTriangle3d::CTriangle3d(Vector3d& node1, Vector3d& node2, Vector3d& node3)
    //{
    //    nodes[0] = node1;
    //    nodes[1] = node2;
    //    nodes[2] = node3;
    //}

    /// <summary>
    /// ��ֵ���캯��
    /// </summary>
    /// <param name="node1">��һ�����</param>
    /// <param name="node2">�ڶ������</param>
    /// <param name="node3">���������</param>
    /// <returns></returns>
    /// <created>HuYG,2017/5/22</created>
    CTriangle3d::CTriangle3d(CPoint3d & node1, CPoint3d & node2, CPoint3d & node3)
        : CTriangle3d()
    {
        nodes[0] = node1;
        nodes[1] = node2;
        nodes[2] = node3;
    }

    CTriangle3d::~CTriangle3d()
    {
    }

}
