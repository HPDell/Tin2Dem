#include "stdafx.h"
#include "Tin2DEM.h"
#include "Triangle3d.h"

#include <string>
#include <iostream>
#include <fstream>
#include <Eigen/Eigen>
using namespace std;
using namespace Eigen;

namespace DigitalPhotogrammetry
{
    /// <summary>
    /// 析构函数
    /// </summary>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    CTin2DEM::~CTin2DEM()
    {
        m_vTriangles.clear();
    }


    /// <summary>
    /// 读取TIN数据
    /// </summary>
    /// <param name="sTinPath">Tin数据文件路径</param>
    /// <returns></returns>
    /// <created>HuYG,2017/5/22</created>
    BOOL CTin2DEM::ReadTin(const char * m_sTinPath)
    {
        ifstream fin(m_sTinPath);
        
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
        //vector<Vector3d> v_points;
        vector<CPoint3d> v_points;
        size_t n_nodeRead = 0;
        while (n_nodeRead < n_nodeNum)
        {
            double lf_coordinates[3] = { 0.0 };
            fin >> lf_coordinates[0] >> lf_coordinates[1] >> lf_coordinates[2];
            UpdateAreaRange(lf_coordinates[0], lf_coordinates[1]);
            //v_points.push_back(Vector3d(lf_coordinates[0], lf_coordinates[1], lf_coordinates[2]));
            v_points.push_back(CPoint3d(lf_coordinates[0], lf_coordinates[1], lf_coordinates[2]));
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
        //Vector3d* p_points = v_points.data();
        CPoint3d* p_points = v_points.data();
        while (n_triangleRead < n_triangleNum)
        {
            size_t n_pointIndex[3] = { 0 };
            fin >> n_pointIndex[0] >> n_pointIndex[1] >> n_pointIndex[2];
            m_vTriangles.push_back(CTriangle3d(v_points[n_pointIndex[0]], v_points[n_pointIndex[1]], v_points[n_pointIndex[2]]));
            n_triangleRead++;
        }
        // 返回成功标号
        is_DemAreaSet = true;
        return 1;
    }

    /// <summary>
    /// 将TIN数据转换为DEM数据
    /// </summary>
    /// <created>HuYG,2017/5/23</created>
    void CTin2DEM::Convert2DEM()
    {
        if (!is_DemInit) return;
        CTriangle3d* pTriangles = m_vTriangles.data();
        size_t nTriangles = m_vTriangles.size();
        // 对每个三角形进行内插
        for (size_t iTriangle = 0; iTriangle < nTriangles; iTriangle++)
        {
            CTriangle3d* triangle = pTriangles + iTriangle;
            CPoint3d* triNodes = triangle->nodes;
            double tri_node_range[] = {
                min(triNodes[0].X, min(triNodes[1].X, triNodes[2].X)),
                min(triNodes[0].Y, min(triNodes[1].Y, triNodes[2].Y)),
                max(triNodes[0].X, max(triNodes[1].X, triNodes[2].X)),
                max(triNodes[0].Y, max(triNodes[1].Y, triNodes[2].Y))
            }; // 三角形区域坐标 X_MIN Y_MIN X_MAX Y_MAX
            int offset[] = {
                (int)(tri_node_range[0] - m_lfXmin) / m_lfDemResolution,
                (int)(tri_node_range[2] - m_lfXmin) / m_lfDemResolution + 1,
                (int)(tri_node_range[1] - m_lfYmin) / m_lfDemResolution,
                (int)(tri_node_range[3] - m_lfYmin) / m_lfDemResolution + 1
            }; // 偏移值的顺序为： Nx_min Nx_max Ny_min Ny_max
            double area_config[] = {
                m_lfXmin + m_lfDemResolution * offset[0],
                m_lfYmin + m_lfDemResolution * offset[2],
                offset[1] - offset[0] + 1,
                offset[3] - offset[2] + 1
            }; // 代表三角形所在区域最大范围的参数，前两个为最小X Y坐标，后两个为X Y方向包含的格网数

            // 拟合三角形三条边的方程
            // 生成三角形三个点的其次坐标
            Vector3d nodes_h[] = {
                Vector3d(triangle->nodes[0].X, triangle->nodes[0].Y, 1.0),
                Vector3d(triangle->nodes[1].X, triangle->nodes[1].Y, 1.0),
                Vector3d(triangle->nodes[2].X, triangle->nodes[2].Y, 1.0)
            };
            // 计算三条边的参数
            Vector3d arcs_h[3];
            for (size_t i = 0; i < 3; i++)
            {
                arcs_h[i] = nodes_h[(i + 1) % 3].cross(nodes_h[(i + 2) % 3]);
            }
            // 对三角形范围内每一个点进行判断
            for (size_t ix = 0; ix < area_config[2]; ix++)
            {
                for (size_t iy = 0; iy < area_config[3]; iy++)
                {
                    // 当前点的齐次坐标
                    Vector3d cur(area_config[0] + ix * m_lfDemResolution, area_config[1] + iy * m_lfDemResolution, 1.0);
                    //double cur_x = area_config[0] + ix * m_lfDemResolution;
                    //double cur_y = area_config[y] + iy * m_lfDemResolution;
                    // 判断当前点是否在三角形内
                    int flag = 0; // 当前点状态的变量。只有当 flag = 7 时，才代表当前点在三角形内
                    flag = (abs(cur.dot(arcs_h[0]) - nodes_h[0].dot(arcs_h[0])) < 1.0e-8) ? flag | 4 : flag;
                    flag = (abs(cur.dot(arcs_h[1]) - nodes_h[1].dot(arcs_h[1])) < 1.0e-8) ? flag | 2 : flag;
                    flag = (abs(cur.dot(arcs_h[2]) - nodes_h[2].dot(arcs_h[2])) < 1.0e-8) ? flag | 1 : flag;
                    // 如果点在三角形内，内插其高程值
                    if (flag == 7)
                    {
                        // 计算内插参数
                        Matrix3d matA = Matrix3d::Constant(1.0);
                        matA(0, 0) = triangle->nodes[0].X;
                        matA(0, 1) = triangle->nodes[1].X;
                        matA(0, 2) = triangle->nodes[2].X;
                        matA(1, 0) = triangle->nodes[0].Y;
                        matA(1, 1) = triangle->nodes[1].Y;
                        matA(1, 2) = triangle->nodes[2].Y;
                        Vector3d coefficient = matA.ldlt().solve(cur);
                        // 内插高程值
                        double elevation = coefficient.dot(Vector3d(triangle->nodes[0].Z, triangle->nodes[1].Z, triangle->nodes[2].Z));
                        // DEM 对象记录高程值
                        m_dem.SetElevation(offset[0] + ix, offset[2] + iy, elevation);
                    }
                }
            }
        }
    }

}
