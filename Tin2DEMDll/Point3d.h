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
        ** ���� **
        *********/
        /// <summary>
        /// Ĭ�Ϲ��캯��
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CPoint3d() : X(0.0) , Y(0.0) , Z(0.0) {}
        /// <summary>
        /// ȫ��ֵ���캯��
        /// </summary>
        /// <param name="lf_X">X����ֵ</param>
        /// <param name="lf_Y">Y����ֵ</param>
        /// <param name="lf_Z">Z����ֵ</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        CPoint3d(double lf_X, double lf_Y, double lf_Z) : X(lf_X) , Y(lf_Y) , Z(lf_Z) {}
        ~CPoint3d();

        /*********
        ** �ӿ� **
        *********/
        /// <summary>
        /// ���õ������ֵ
        /// </summary>
        /// <param name="lf_X">X����ֵ</param>
        /// <param name="lf_Y">Y����ֵ</param>
        /// <param name="lf_Z">Z����ֵ</param>
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

