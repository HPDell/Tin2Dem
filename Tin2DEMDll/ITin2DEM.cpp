#include "stdafx.h"
#include "ITin2DEM.h"
#include "Tin2DEM.h"

namespace DigitalPhotogrammetry
{
    /// <summary>
    /// 默认构造函数
    /// </summary>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    ITin2DEM * ITin2DEM::create()
    {
        return new CTin2DEM();
    }
    /// <summary>
    /// 赋值构造函数
    /// </summary>
    /// <param name="lf_demResolution">DEM数据的分辨率</param>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    ITin2DEM * ITin2DEM::create(double lf_demResolution)
    {
        return new CTin2DEM(lf_demResolution);
    }
    /// <summary>
    /// 析构函数
    /// </summary>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    void ITin2DEM::del(ITin2DEM * pInstance)
    {
        delete (CTin2DEM*)pInstance;
    }
}