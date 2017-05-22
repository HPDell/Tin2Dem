#pragma once

#include <Eigen/Eigen>

#include "Tin2DEMDll.h"

using namespace Eigen;

namespace DigitalPhotogrammetry
{
    class TIN2DEMDLL_API CTriangle3d
    {
    public:
        Vector3d Nodes[3];  // 三角形的三个结点

    public:
        /// <summary>
        /// 默认构造函数
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CTriangle3d();
        /// <summary>
        /// 赋值构造函数
        /// </summary>
        /// <param name="node1">第一个结点</param>
        /// <param name="node2">第二个结点</param>
        /// <param name="node3">第三个结点</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CTriangle3d(Vector3d& node1, Vector3d& node2, Vector3d& node3);
        ~CTriangle3d();
    };

}

