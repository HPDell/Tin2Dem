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
        vector<CPoint3d> v_points;
        for (size_t i = 0; i < n_nodeNum; i++)
        {
            double lf_coordinates[3] = { 0.0 };
            fin >> lf_coordinates[0] >> lf_coordinates[1] >> lf_coordinates[2];
            UpdateAreaRange(lf_coordinates[0], lf_coordinates[1], lf_coordinates[2]);
            v_points.push_back(CPoint3d(lf_coordinates[0], lf_coordinates[1], lf_coordinates[2]));
        }
        // 读取三角形
        size_t n_triangleNum = 0;
        fin >> n_triangleNum;
        if (n_triangleNum < 1)
        {
            cout << "数据有误！缺少三角形" << endl;
            return -3;
        }
        CPoint3d* p_points = v_points.data();
        for (size_t i = 0; i < n_triangleNum; i++)
        {
            size_t n_pointIndex[3] = { 0 };
            fin >> n_pointIndex[0] >> n_pointIndex[1] >> n_pointIndex[2];
            m_vTriangles.push_back(CTriangle3d(v_points[n_pointIndex[0]], v_points[n_pointIndex[1]], v_points[n_pointIndex[2]]));
        }
        // 返回成功标号
        m_isDemAreaSet = true;
        return 1;
    }

    /// <summary>
    /// 将TIN数据转换为DEM数据
    /// </summary>
    /// <created>HuYG,2017/5/23</created>
    void CTin2DEM::Convert2DEM()
    {
        if (!m_isDemInit) return;
        CTriangle3d* pTriangles = m_vTriangles.data();
        size_t nTriangles = m_vTriangles.size();
        // 对每个三角形进行内插
#ifdef _DEBUG
        size_t dem_hit_times = 0;
        size_t dem_test_times = 0;
        size_t triangle_test_times = 0;
        size_t triangle_hit_times = 0;
#endif // _DEBUG
        for (size_t iTriangle = 0; iTriangle < nTriangles; iTriangle++)
        {
#ifdef _DEBUG
            triangle_test_times++;
#endif // _DEBUG
            // ************************
            // 计算三角形所在的区域参数
            // ************************
            CTriangle3d* triangle = pTriangles + iTriangle;
            CPoint3d* triNodes = triangle->nodes;
            double tri_node_range[] = {
                min(triNodes[0].X, min(triNodes[1].X, triNodes[2].X)),
                min(triNodes[0].Y, min(triNodes[1].Y, triNodes[2].Y)),
                max(triNodes[0].X, max(triNodes[1].X, triNodes[2].X)),
                max(triNodes[0].Y, max(triNodes[1].Y, triNodes[2].Y))
            }; // 三角形区域坐标 X_MIN Y_MIN X_MAX Y_MAX
            int offset[] = {
                int((tri_node_range[0] - m_lfXmin) / m_lfDemResolution),
                int((tri_node_range[2] - m_lfXmin) / m_lfDemResolution) + 1,
                int((tri_node_range[1] - m_lfYmin) / m_lfDemResolution),
                int((tri_node_range[3] - m_lfYmin) / m_lfDemResolution) + 1
            }; // 偏移值的顺序为： Nx_min Nx_max Ny_min Ny_max
            double area_start[] = {
                m_lfXmin + m_lfDemResolution * offset[0],
                m_lfYmin + m_lfDemResolution * offset[2]
            }; // 代表三角形所在区域最大范围的参数，前两个为最小X Y坐标
            size_t area_size[] = {
                offset[1] - offset[0] + 1,
                offset[3] - offset[2] + 1
            };

            // **************************
            // 拟合三角形三条边的方程
            // 生成三角形三个点的其次坐标
            // **************************
            Vector3d nodes_h[] = {
                Vector3d(triNodes[0].X, triNodes[0].Y, 1.0),
                Vector3d(triNodes[1].X, triNodes[1].Y, 1.0),
                Vector3d(triNodes[2].X, triNodes[2].Y, 1.0)
            };
            // 计算三条边的参数
            Vector3d arcs_h[] = {
                nodes_h[1].cross(nodes_h[2]),
                nodes_h[2].cross(nodes_h[0]),
                nodes_h[0].cross(nodes_h[1])
            };
            // ******************************
            // 对三角形范围内每一个点进行判断
            // ******************************
            bool isHasDem = false;
            for (size_t iy = 0; iy < area_size[1]; iy++)
            {
                for (size_t ix = 0; ix < area_size[0]; ix++)
                {
#ifdef _DEBUG
                    dem_test_times++;
#endif // _DEBUG
                    // 当前点的齐次坐标
                    Vector3d cur(area_start[0] + ix * m_lfDemResolution, area_start[1] + iy * m_lfDemResolution, 1.0);
                    // 判断当前点是否在三角形内
                    int flag = 0; // 当前点状态的变量。只有当 flag = 7 时，才代表当前点在三角形内
                    flag = ((cur.dot(arcs_h[0]) < 0) == (nodes_h[0].dot(arcs_h[0]) <= 0)) ? flag | 4 : flag;
                    flag = ((cur.dot(arcs_h[1]) < 0) == (nodes_h[1].dot(arcs_h[1]) <= 0)) ? flag | 2 : flag;
                    flag = ((cur.dot(arcs_h[2]) < 0) == (nodes_h[2].dot(arcs_h[2]) <= 0)) ? flag | 1 : flag;
                    // 如果点在三角形内，内插其高程值
                    switch (flag)
                    {
                        case 7:
                        {
                            isHasDem = true;
                            // 计算内插参数
                            Matrix3d matA = Matrix3d::Constant(1.0);
                            matA(0, 0) = triangle->nodes[0].X;
                            matA(0, 1) = triangle->nodes[1].X;
                            matA(0, 2) = triangle->nodes[2].X;
                            matA(1, 0) = triangle->nodes[0].Y;
                            matA(1, 1) = triangle->nodes[1].Y;
                            matA(1, 2) = triangle->nodes[2].Y;
                            Vector3d coefficient = matA.lu().solve(cur);
                            if ((coefficient.array() > 0).all()) 
                            {
#ifdef _DEBUG
                                dem_hit_times++;
#endif // _DEBUG
                                // 内插高程值
                                double elevation = coefficient.dot(Vector3d(triangle->nodes[0].Z, triangle->nodes[1].Z, triangle->nodes[2].Z));
                                // DEM 对象记录高程值
                                m_dem.SetElevation(offset[0] + ix, offset[2] + iy, elevation);
                                break;
                            }
                        }
                        default:
                            break;
                    }
                }
            }
#ifdef _DEBUG
            if (isHasDem) triangle_hit_times++;
            else
            {
                cout << "三角形" << iTriangle << "中没有DEM点" << endl;
            }
#endif // _DEBUG
        }
#ifdef _DEBUG
        cout << "测试的三角形数目：     " << triangle_test_times << endl;
        cout << "含有DEM点的三角行数目：" << triangle_hit_times << endl;
        cout << "总的DEM点的数目：      " << m_dem.rows * m_dem.cols << endl;
        cout << "测试的DEM点的数目：    " << dem_test_times << endl;
        cout << "命中的DEM点的数目：    " << dem_hit_times << endl;
#endif // _DEBUG
    }

}
