#include "stdafx.h"
#include "ITin2DEM.h"
#include "Tin2DEM.h"

namespace DigitalPhotogrammetry
{
    /// <summary>
    /// Ĭ�Ϲ��캯��
    /// </summary>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    ITin2DEM * ITin2DEM::create()
    {
        return new CTin2DEM();
    }
    /// <summary>
    /// ��ֵ���캯��
    /// </summary>
    /// <param name="lf_demResolution">DEM���ݵķֱ���</param>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    ITin2DEM * ITin2DEM::create(double lf_demResolution)
    {
        return new CTin2DEM(lf_demResolution);
    }
    /// <summary>
    /// ��������
    /// </summary>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    void ITin2DEM::del(ITin2DEM * pInstance)
    {
        delete (CTin2DEM*)pInstance;
    }
}