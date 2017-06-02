#pragma once

#include <float.h>

#include "IDem.h"
#include "DataTypes.h"

namespace DigitalPhotogrammetry
{
    class CDem : public IDem
    {
    private:
        double* m_pDem;
        //size_t* m_pChangeTime;
        double m_lfZmin;
        double m_lfZmax;

    public:
        double x_min;
        double y_min;
        double resolution;
        size_t cols;
        size_t rows;
        double rotation;
        
    public:
        CDem() : m_pDem(nullptr), x_min(DBL_MAX), y_min(DBL_MAX), resolution(0.0), cols(0), rows(0), rotation(0.0) {}
        /// <summary>
        /// 拷贝构造函数
        /// </summary>
        /// <param name="source">拷贝源</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        CDem(const CDem& source);
        ~CDem();

        /// <summary>
        /// 拷贝函数
        /// </summary>
        /// <param name="source">拷贝源</param>
        /// <created>HuYG,2017/5/23</created>
        void operator=(CDem& source);

        /// <summary>
        /// 设置DEM参数
        /// </summary>
        /// <param name="lf_demResolution">分辨率</param>
        /// <param name="lf_Xmin">起始点X坐标</param>
        /// <param name="lf_Ymin">起始点Y坐标</param>
        /// <param name="n_rows">DEM行数</param>
        /// <param name="n_cols">DEM列数</param>
        /// <created>HuYG,2017/5/23</created>
        void SetConfig(double lf_demResolution, double lf_Xmin, double lf_Ymin, size_t n_rows, size_t n_cols);
        /// <summary>
        /// 设定高程范围
        /// </summary>
        /// <param name="lf_min">最小值</param>
        /// <param name="lf_max">最大值</param>
        /// <created>HuYG,2017/5/26</created>
        void SetElevationRange(double lf_min, double lf_max)
        {
            m_lfZmin = lf_min;
            m_lfZmax = lf_max;
        }
        /// <summary>
        /// 设置高程值
        /// </summary>
        /// <param name="lf_X">高程点的X坐标</param>
        /// <param name="lf_Y">高程点的Y坐标</param>
        /// <param name="lf_Elevation">高程值</param>
        /// <created>HuYG,2017/5/23</created>
        void SetElevation(double lf_X, double lf_Y, double lf_Elevation);
        /// <summary>
        /// 设置高程值
        /// </summary>
        /// <param name="off_X">高程点的列号</param>
        /// <param name="off_Y">高程点的行号</param>
        /// <param name="lf_Elevation">高程值</param>
        /// <created>HuYG,2017/5/23</created>
        void SetElevation(size_t off_X, size_t off_Y, double lf_Elevation)
        {
            if (off_X < cols && off_Y < rows)
            {
                double* pCur = m_pDem + off_Y * cols + off_X;
                //*pCur = (lf_Elevation < m_lfZmin || lf_Elevation > m_lfZmax) ? -99999.0 : lf_Elevation;
                *pCur = lf_Elevation;
            }
        }
        /// <summary>
        /// 以文件的形式保存DEM
        /// </summary>
        /// <param name="filepath">文件路径</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void Print(const char* filepath);
    };
}

