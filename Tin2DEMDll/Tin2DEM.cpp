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
        //    cout << "文件格式错误！" << endl;
        //    return -1;
        //}
        //getline(fin, s_curline);
        
        string s_datatype;
        fin >> s_datatype;
        if (s_datatype != "xyztri")
        {
            cout << "文件格式错误！" << endl;
            return -1;
        }
        // 读取三角点
        size_t n_nodeNum = 0;
        fin >> n_nodeNum;
        if (n_nodeNum < 3)
        {
            cout << "数据有误！没有角点" << endl;
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
        // 读取三角形
        size_t n_triangleNum = 0;
        fin >> n_triangleNum;
        if (n_triangleNum < 1)
        {
            cout << "数据有误！缺少三角形" << endl;
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
        // 返回成功标号
        return 1;
    }
}
