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
        ** ���� **
        *********/
        /// <summary>
        /// Ĭ�Ϲ��캯��
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        static ITin2DEM* create();
        /// <summary>
        /// ��ֵ���캯��
        /// </summary>
        /// <param name="lf_demResolution">DEM���ݵķֱ���</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        static ITin2DEM* create(double lf_demResolution);
        /// <summary>
        /// ��������
        /// </summary>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        static void del(ITin2DEM* pInstance);

        /// <summary>
        /// ��ȡTIN����
        /// </summary>
        /// <param name="sTinPath">Tin�����ļ�·��</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/22</created>
        virtual BOOL ReadTin(const char* sTinPath) = 0;
        /// <summary>
        /// ����DEM�ֱ���
        /// </summary>
        /// <param name="lf_demSize">DEM�ֱ���</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void SetDemSize(double lf_demResolution) = 0;
        /// <summary>
        /// ��ʼ��DEM����
        /// </summary>
        /// <created>HuYG,2017/5/23</created>
        virtual BOOL InitDEM() = 0;
        /// <summary>
        /// ��TIN����ת��ΪDEM����
        /// </summary>
        /// <created>HuYG,2017/5/23</created>
        virtual void Convert2DEM() = 0;
        /// <summary>
        /// ��ȡDEM����
        /// </summary>
        /// <returns>DEM����</returns>
        /// <created>HuYG,2017/5/23</created>
        virtual IDem* GetDem() = 0;
        /// <summary>
        /// ���ļ�����ʽ����DEM
        /// </summary>
        /// <param name="filepath">�ļ�·��</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void PrintDem(const char* filepath) = 0;

    };

}