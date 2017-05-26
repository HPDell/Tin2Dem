#pragma once

#include <float.h>

#include "IDem.h"
#include "DataTypes.h"

namespace DigitalPhotogrammetry
{
    class CDem : public IDem
    {
    private:
        double* m_pDem;

    public:
        double x_min;
        double y_min;
        double resolution;
        size_t cols;
        size_t rows;
        double rotation;
        
    public:
        CDem() : m_pDem(nullptr), x_min(DBL_MAX), y_min(DBL_MAX), resolution(0.0), cols(0), rows(0), rotation(0.0) {}
        /// <summary>
        /// �������캯��
        /// </summary>
        /// <param name="source">����Դ</param>
        /// <returns></returns>
        /// <created>HuYG,2017/5/23</created>
        CDem(const CDem& source);
        ~CDem();

        /// <summary>
        /// ��������
        /// </summary>
        /// <param name="source">����Դ</param>
        /// <created>HuYG,2017/5/23</created>
        void operator=(CDem& source);

        /// <summary>
        /// ����DEM����
        /// </summary>
        /// <param name="lf_demResolution">�ֱ���</param>
        /// <param name="lf_Xmin">��ʼ��X����</param>
        /// <param name="lf_Ymin">��ʼ��Y����</param>
        /// <param name="n_rows">DEM����</param>
        /// <param name="n_cols">DEM����</param>
        /// <created>HuYG,2017/5/23</created>
        void SetConfig(double lf_demResolution, double lf_Xmin, double lf_Ymin, size_t n_rows, size_t n_cols);
        /// <summary>
        /// ���ø߳�ֵ
        /// </summary>
        /// <param name="lf_X">�̵߳��X����</param>
        /// <param name="lf_Y">�̵߳��Y����</param>
        /// <param name="lf_Elevation">�߳�ֵ</param>
        /// <created>HuYG,2017/5/23</created>
        void SetElevation(double lf_X, double lf_Y, double lf_Elevation);
        /// <summary>
        /// ���ø߳�ֵ
        /// </summary>
        /// <param name="off_X">�̵߳��X����</param>
        /// <param name="off_Y">�̵߳��Y����</param>
        /// <param name="lf_Elevation">�߳�ֵ</param>
        /// <created>HuYG,2017/5/23</created>
        void SetElevation(size_t off_X, size_t off_Y, double lf_Elevation)
        {
            if (off_X < cols && off_Y < rows)
            {
                *(m_pDem + off_Y * cols + off_X) = lf_Elevation;
            }
        }
        /// <summary>
        /// ���ļ�����ʽ����DEM
        /// </summary>
        /// <param name="filepath">�ļ�·��</param>
        /// <created>HuYG,2017/5/23</created>
        virtual void Print(const char* filepath);
    };
}

