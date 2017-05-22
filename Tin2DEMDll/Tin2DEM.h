#pragma once
// Tin2DEM.h
#ifdef TIN2DEMDLL_EXPORTS
#define TIN2DEMDLL_API __declspec(dllexport)
#else
#define TIN2DEMDLL_API __declspec(dllimport)
#endif

#include <vector>

#include "Triangle3d.h"

using namespace std;

namespace DigitalPhotogeommetry
{
    /**
     * CTin2DEM类：
     * 将不规则三角网转换为规则格网
     * 
     */
    class CTin2DEM
    {
    private:
        vector<CTriangle3d> m_vTriangles;

    public:
        /*********
        ** 构造 **
        *********/
        CTin2DEM();
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
    };
}

