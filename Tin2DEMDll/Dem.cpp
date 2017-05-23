#include "stdafx.h"
#include "Dem.h"

#include <fstream>

using namespace std;

namespace DigitalPhotogrammetry
{
    CDem::CDem(const CDem & source)
    {
        x_min = source.x_min;
        y_min = source.y_min;
        cols = source.cols;
        rows = source.rows;
        resolution = source.resolution;
        m_pDem = new double[rows*cols];
        memcpy_s(m_pDem, rows*cols * sizeof(double), source.m_pDem, rows*cols * sizeof(double));
    }

    CDem::~CDem()
    {
        delete[] m_pDem;
        m_pDem = nullptr;
    }

    /// <summary>
    /// ��������
    /// </summary>
    /// <param name="source">����Դ</param>
    /// <created>HuYG,2017/5/23</created>
    void CDem::operator=(CDem & source)
    {
        x_min = source.x_min;
        y_min = source.y_min;
        cols = source.cols;
        rows = source.rows;
        resolution = source.resolution;
        if (!m_pDem) delete[] m_pDem;
        m_pDem = new double[rows*cols];
        memcpy_s(m_pDem, rows*cols * sizeof(double), source.m_pDem, rows*cols * sizeof(double));
    }

    /// <summary>
    /// ����DEM����
    /// </summary>
    /// <param name="lf_demResolution">�ֱ���</param>
    /// <param name="lf_Xmin">��ʼ��X����</param>
    /// <param name="lf_Ymin">��ʼ��Y����</param>
    /// <param name="rows">DEM����</param>
    /// <param name="cols">DEM����</param>
    /// <created>HuYG,2017/5/23</created>
    void CDem::SetConfig(double lf_demResolution, double lf_Xmin, double lf_Ymin, size_t n_rows, size_t n_cols)
    {
        // ����DEM����
        this->x_min = lf_Xmin;
        this->y_min = lf_Ymin;
        this->rows = n_rows;
        this->cols = n_cols;
        this->resolution = lf_demResolution;
        // ����DEM����
        this->m_pDem = new double[rows*cols];
        for (size_t i = 0; i < rows*cols; i++)
        {
            *(m_pDem + i) = -99999.0;
        }
        //memset(m_pDem, INFINITE, rows*cols * sizeof(double));
    }

    /// <summary>
    /// ���ø߳�ֵ
    /// </summary>
    /// <param name="lf_X">�̵߳��X����</param>
    /// <param name="lf_Y">�̵߳��Y����</param>
    /// <param name="lf_Elevation">�߳�ֵ</param>
    /// <created>HuYG,2017/5/23</created>
    void CDem::SetElevation(double lf_X, double lf_Y, double lf_Elevation)
    {
    }

    /// <summary>
    /// ���ļ�����ʽ����DEM
    /// </summary>
    /// <param name="filepath">�ļ�·��</param>
    /// <created>HuYG,2017/5/23</created>
    void CDem::Print(const char * filepath)
    {
        ofstream fout(filepath);
        fout.precision(6);
        // ��ʼд����
        // �ļ�ͷ
        fout << x_min << " " << y_min << " ";
        fout.width(9);
        fout.setf(fout.right);
        fout << 0.0 << " " << resolution << " " << resolution << " " << cols << " " << rows << endl;
        // ������
        fout.precision(3);
        fout.width(12);
        for (size_t i = 0; i < rows; i++)
        {
            for (size_t j = 0; j < cols; j++)
            {
                fout << *(m_pDem + i * cols + j);
            }
            fout << endl;
        }
        fout.close();
    }

}
