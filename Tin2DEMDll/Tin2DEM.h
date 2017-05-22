#pragma once
// Tin2DEM.h

#include <vector>

#include "ITin2DEM.h"
#include "Tin2DEMDll.h"

using namespace std;

namespace DigitalPhotogrammetry
{
    /**
     * CTin2DEM类：
     * 将不规则三角网转换为规则格网
     * 
     */
    class CTin2DEM : ITin2DEM
    {
    private:
        // 三角形数据
        vector<CTriangle3d> m_vTriangles;
        // DEM 参数
        double m_demSize;
        double m_Xmin;
        double m_Xmax;
        double m_Ymin;
        double m_Ymax;

    public:
        /*********
        ** 构造 **
        *********/
        CTin2DEM() : m_demSize(0.0), m_Xmin(DBL_MAX), m_Xmax(-DBL_MAX), m_Ymin(DBL_MAX), m_Ymax(-DBL_MAX) {}
        ~CTin2DEM();

        /*********
        ** 接口 **
        *********/
        /// <summary>
        /// 读取TIN数据
        /// </summary>
        /// <param name="sTinPath">Tin数据文件路径</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        BOOL ReadTin(const char* sTinPath);
        /// <summary>
        /// 更新测区范围
        /// </summary>
        /// <param name="lf_X"></param>
        /// <param name="lf_Y"></param>
        /// <created>HuYG,2017/5/22</created>
        void UpdateAreaRange(double lf_X, double lf_Y)
        {
            m_Xmin = (lf_X < m_Xmin) ? lf_X : m_Xmin;
            m_Ymin = (lf_Y < m_Ymin) ? lf_Y : m_Ymin;
            m_Xmax = (lf_X > m_Xmax) ? lf_X : m_Xmax;
            m_Ymax = (lf_Y > m_Ymax) ? lf_Y : m_Ymax;
        }
    };
}

