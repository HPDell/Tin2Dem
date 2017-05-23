#pragma once
#ifdef TIN2DEMDLL_EXPORTS
#define TIN2DEMDLL_API __declspec(dllexport)
#else
#define TIN2DEMDLL_API __declspec(dllimport)
#endif

namespace DigitalPhotogrammetry
{
    class CPoint3d
    {
    public:
        double X;
        double Y;
        double Z;

    public:
        /*********
        ** 构析 **
        *********/
        /// <summary>
        /// 默认构造函数
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CPoint3d() : X(0.0) , Y(0.0) , Z(0.0) {}
        /// <summary>
        /// 全赋值构造函数
        /// </summary>
        /// <param name="lf_X">X坐标值</param>
        /// <param name="lf_Y">Y坐标值</param>
        /// <param name="lf_Z">Z坐标值</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CPoint3d(double lf_X, double lf_Y, double lf_Z) : X(lf_X) , Y(lf_Y) , Z(lf_Z) {}
        ~CPoint3d();

        /*********
        ** 接口 **
        *********/
        /// <summary>
        /// 设置点的坐标值
        /// </summary>
        /// <param name="lf_X">X坐标值</param>
        /// <param name="lf_Y">Y坐标值</param>
        /// <param name="lf_Z">Z坐标值</param>
        /// <created>HuYG,2017/5/22</created>
        void SetCoordinate(double lf_X, double lf_Y, double lf_Z)
        {
            this->X = lf_X; this->Y = lf_Y; this->Z = lf_Z;
        }

        void operator=(CPoint3d& source)
        {
            X = source.X;
            Y = source.Y;
            Z = source.Z;
        }
    };

}

