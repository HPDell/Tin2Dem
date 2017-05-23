#pragma once

#include "stdafx.h"

#include "DataTypes.h"
//#include "Tin2DEM.h"

namespace DigitalPhotogrammetry
{
    class TIN2DEMDLL_API ITin2DEM
    {
    public:
        /*********
        ** 构造 **
        *********/
        /// <summary>
        /// 默认构造函数
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        static ITin2DEM* create();
        /// <summary>
        /// 赋值构造函数
        /// </summary>
        /// <param name="lf_demResolution">DEM数据的分辨率</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        static ITin2DEM* create(double lf_demResolution);
        /// <summary>
        /// 析构函数
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        static void del(ITin2DEM* pInstance);

        /// <summary>
        /// 读取TIN数据
        /// </summary>
        /// <param name="sTinPath">Tin数据文件路径</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        virtual BOOL ReadTin(const char* sTinPath) = 0;
        /// <summary>
        /// 更改DEM分辨率
        /// </summary>
        /// <param name="lf_demSize">DEM分辨率</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void SetDemSize(double lf_demResolution) = 0;
        /// <summary>
        /// 初始化DEM对象
        /// </summary>
        /// <created>HuYG,2017/5/23</created>
        virtual BOOL InitDEM() = 0;
        /// <summary>
        /// 将TIN数据转换为DEM数据
        /// </summary>
        /// <created>HuYG,2017/5/23</created>
        virtual void Convert2DEM() = 0;
        /// <summary>
        /// 获取DEM对象
        /// </summary>
        /// <returns>DEM对象</returns>
        /// <created>HuYG,2017/5/23</created>
        virtual IDem* GetDem() = 0;
        /// <summary>
        /// 以文件的形式保存DEM
        /// </summary>
        /// <param name="filepath">文件路径</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void PrintDem(const char* filepath) = 0;

    };

}