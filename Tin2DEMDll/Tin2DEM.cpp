#include "stdafx.h"
#include "Tin2DEM.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

namespace DigitalPhotogeommetry
{
    CTin2DEM::CTin2DEM()
    {
    }


    CTin2DEM::~CTin2DEM()
    {
    }


    BOOL CTin2DEM::ReadTin(const char * m_sTinPath)
    {
        ifstream fin(m_sTinPath);
        //string s_curline;
        //getline(fin, s_curline);
        //if (s_curline == "xyztri")
        //{
        //    cout << "�ļ���ʽ����" << endl;
        //    return -1;
        //}
        //getline(fin, s_curline);
        
        string s_datatype;
        fin >> s_datatype;
        if (s_datatype != "xyztri")
        {
            cout << "�ļ���ʽ����" << endl;
            return -1;
        }
        // ��ȡ���ǵ�
        size_t n_nodeNum = 0;
        fin >> n_nodeNum;
        if (n_nodeNum < 3)
        {
            cout << "��������û�нǵ�" << endl;
            return -2;
        }
        vector<Vector3d> v_points;
        size_t n_nodeRead = 0;
        while (n_nodeRead < n_nodeNum)
        {
            double lf_coordinates[3] = { 0.0 };
            fin >> lf_coordinates[0] >> lf_coordinates[1] >> lf_coordinates[2];
            v_points.push_back(Vector3d(lf_coordinates[0], lf_coordinates[1], lf_coordinates[2]));
            n_nodeRead++;
        }
        // ��ȡ������
        size_t n_triangleNum = 0;
        fin >> n_triangleNum;
        if (n_triangleNum < 1)
        {
            cout << "��������ȱ��������" << endl;
            return -3;
        }
        size_t n_triangleRead = 0;
        Vector3d* p_points = v_points.data();
        while (n_triangleRead < n_triangleNum)
        {
            size_t n_pointIndex[3] = { 0 };
            fin >> n_pointIndex[0] >> n_pointIndex[1] >> n_pointIndex[2];
            m_vTriangles.push_back(CTriangle3d(v_points[n_pointIndex[0]], v_points[n_pointIndex[1]], v_points[n_pointIndex[2]]));
            n_triangleRead++;
        }
        // ���سɹ����
        return 1;
    }
}
