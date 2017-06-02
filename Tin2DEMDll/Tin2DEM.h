#pragma once
// Tin2DEM.h

#include <vector>

//#include "ITin2DEM.h"
#include "DataTypes.h"
#include "Dem.h"
#include "ITin2DEM.h"
#include "Triangle3d.h"


using namespace std;

namespace DigitalPhotogrammetry
{
    /**
     * CTin2DEM类：
     * 将不规则三角网转换为规则格网
     * 
     */
    class CTin2DEM : public ITin2DEM
    {
    private:
        // 三角形数据
        vector<CTriangle3d> m_vTriangles;
        // DEM 数据及参数
        double m_lfDemResolution;
        double m_lfXmin;
        double m_lfXmax;
        double m_lfYmin;
        double m_lfYmax;
        double m_lfZmin;
        double m_lfZmax;
        bool m_isSetOrigin;
        bool m_isDemAreaSet;
        CDem m_dem;
        bool m_isDemInit;

    public:
        /*********
        ** 构造 **
        *********/
        /// <summary>
        /// 默认构造函数
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        CTin2DEM() 
            : m_lfDemResolution(-1.0)
            , m_lfXmin(DBL_MAX), m_lfXmax(-DBL_MAX), m_lfYmin(DBL_MAX), m_lfYmax(-DBL_MAX), m_lfZmin(DBL_MAX), m_lfZmax(-DBL_MAX)
            , m_isDemAreaSet(false), m_isDemInit(false), m_isSetOrigin(false) {}
        /// <summary>
        /// 赋值构造函数
        /// </summary>
        /// <param name="lf_demResolution">DEM数据的分辨率</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        CTin2DEM(double lf_demResolution) 
            : m_lfDemResolution(lf_demResolution)
            , m_lfXmin(DBL_MAX), m_lfXmax(-DBL_MAX), m_lfYmin(DBL_MAX), m_lfYmax(-DBL_MAX), m_lfZmin(DBL_MAX), m_lfZmax(-DBL_MAX)
            , m_isDemAreaSet(false), m_isDemInit(false), m_isSetOrigin(false) {}
        CTin2DEM(double lf_demResolution, double lf_originX, double lf_originY)
            : m_lfDemResolution(lf_demResolution)
            , m_lfXmin(lf_originX), m_lfXmax(-DBL_MAX), m_lfYmin(lf_originY), m_lfYmax(-DBL_MAX)
            , m_isDemAreaSet(false), m_isDemInit(false), m_isSetOrigin(true)
        {
        }
        /// <summary>
        /// 析构函数
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
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
        virtual BOOL ReadTin(const char* sTinPath);
        /// <summary>
        /// 更改DEM分辨率
        /// </summary>
        /// <param name="lf_demSize">DEM分辨率</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void SetDemSize(double lf_demResolution)
        {
            m_lfDemResolution = lf_demResolution;
        }
        /// <summary>
        /// 初始化DEM对象
        /// </summary>
        /// <created>HuYG,2017/5/23</created>
        virtual void InitDEM()
        {
            if (!m_isDemAreaSet) return;
            size_t rows = (size_t)(m_lfYmax - m_lfYmin) / m_lfDemResolution + 1, cols = (size_t)(m_lfXmax - m_lfXmin) / m_lfDemResolution + 1;
            m_dem.SetConfig(m_lfDemResolution, m_lfXmin, m_lfYmin, rows, cols);
            m_dem.SetElevationRange(m_lfZmin, m_lfZmax);
            m_isDemInit = true;
        }
        /// <summary>
        /// 将TIN数据转换为DEM数据
        /// </summary>
        /// <created>HuYG,2017/5/23</created>
        virtual void Convert2DEM();
        /// <summary>
        /// 获取DEM对象
        /// </summary>
        /// <returns>DEM对象</returns>
        /// <created>HuYG,2017/5/23</created>
        virtual IDem* GetDem()
        {
            return &m_dem;
        }
        /// <summary>
        /// 以文件的形式保存DEM
        /// </summary>
        /// <param name="filepath">文件路径</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void PrintDem(const char* filepath)
        {
            m_dem.Print(filepath);
        }

    private:
        /// <summary>
        /// 更新测区范围
        /// </summary>
        /// <param name="lf_X"></param>
        /// <param name="lf_Y"></param>
        /// <created>HuYG,2017/5/22</created>
        void UpdateAreaRange(double lf_X, double lf_Y, double lf_Z)
        {
            if (!m_isSetOrigin) {
                m_lfXmin = (lf_X < m_lfXmin) ? lf_X : m_lfXmin;
                m_lfYmin = (lf_Y < m_lfYmin) ? lf_Y : m_lfYmin;
            }
            m_lfXmax = (lf_X > m_lfXmax) ? lf_X : m_lfXmax;
            m_lfYmax = (lf_Y > m_lfYmax) ? lf_Y : m_lfYmax;
            m_lfZmin = (lf_Z < m_lfZmin) ? lf_Z : m_lfZmin;
            m_lfZmax = (lf_Z > m_lfZmax) ? lf_Z : m_lfZmax;
        }
    };
}

