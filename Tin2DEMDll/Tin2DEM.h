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
     * CTin2DEM�ࣺ
     * ��������������ת��Ϊ�������
     * 
     */
    class CTin2DEM : public ITin2DEM
    {
    private:
        // ����������
        vector<CTriangle3d> m_vTriangles;
        // DEM ���ݼ�����
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
        ** ���� **
        *********/
        /// <summary>
        /// Ĭ�Ϲ��캯��
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        CTin2DEM() 
            : m_lfDemResolution(-1.0)
            , m_lfXmin(DBL_MAX), m_lfXmax(-DBL_MAX), m_lfYmin(DBL_MAX), m_lfYmax(-DBL_MAX), m_lfZmin(DBL_MAX), m_lfZmax(-DBL_MAX)
            , m_isDemAreaSet(false), m_isDemInit(false), m_isSetOrigin(false) {}
        /// <summary>
        /// ��ֵ���캯��
        /// </summary>
        /// <param name="lf_demResolution">DEM���ݵķֱ���</param>
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
        /// ��������
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
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
        virtual BOOL ReadTin(const char* sTinPath);
        /// <summary>
        /// ����DEM�ֱ���
        /// </summary>
        /// <param name="lf_demSize">DEM�ֱ���</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void SetDemSize(double lf_demResolution)
        {
            m_lfDemResolution = lf_demResolution;
        }
        /// <summary>
        /// ��ʼ��DEM����
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
        /// ��TIN����ת��ΪDEM����
        /// </summary>
        /// <created>HuYG,2017/5/23</created>
        virtual void Convert2DEM();
        /// <summary>
        /// ��ȡDEM����
        /// </summary>
        /// <returns>DEM����</returns>
        /// <created>HuYG,2017/5/23</created>
        virtual IDem* GetDem()
        {
            return &m_dem;
        }
        /// <summary>
        /// ���ļ�����ʽ����DEM
        /// </summary>
        /// <param name="filepath">�ļ�·��</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void PrintDem(const char* filepath)
        {
            m_dem.Print(filepath);
        }

    private:
        /// <summary>
        /// ���²�����Χ
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

