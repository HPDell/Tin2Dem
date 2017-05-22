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
     * CTin2DEM�ࣺ
     * ��������������ת��Ϊ�������
     * 
     */
    class CTin2DEM
    {
    private:
        vector<CTriangle3d> m_vTriangles;

    public:
        /*********
        ** ���� **
        *********/
        CTin2DEM();
        ~CTin2DEM();

        /*********
        ** �ӿ� **
        *********/

        /// <summary>
        /// ��ȡTIN����
        /// </summary>
        /// <param name="sTinPath">Tin�����ļ�·��</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        BOOL ReadTin(const char* sTinPath);
    };
}

