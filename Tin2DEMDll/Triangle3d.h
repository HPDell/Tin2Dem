#pragma once

#include <Eigen/Eigen>

#include "Tin2DEMDll.h"

using namespace Eigen;

namespace DigitalPhotogrammetry
{
    class TIN2DEMDLL_API CTriangle3d
    {
    public:
        Vector3d Nodes[3];  // �����ε��������

    public:
        /// <summary>
        /// Ĭ�Ϲ��캯��
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CTriangle3d();
        /// <summary>
        /// ��ֵ���캯��
        /// </summary>
        /// <param name="node1">��һ�����</param>
        /// <param name="node2">�ڶ������</param>
        /// <param name="node3">���������</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CTriangle3d(Vector3d& node1, Vector3d& node2, Vector3d& node3);
        ~CTriangle3d();
    };

}

