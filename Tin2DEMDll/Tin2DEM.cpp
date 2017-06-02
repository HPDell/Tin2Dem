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
    /// ��������
    /// </summary>
    /// <returns></returns>
    /// <created>HuYG,2017/5/23</created>
    CTin2DEM::~CTin2DEM()
    {
        m_vTriangles.clear();
    }


    /// <summary>
    /// ��ȡTIN����
    /// </summary>
    /// <param name="sTinPath">Tin�����ļ�·��</param>
    /// <returns></returns>
    /// <created>HuYG,2017/5/22</created>
    BOOL CTin2DEM::ReadTin(const char * m_sTinPath)
    {
        ifstream fin(m_sTinPath);
        
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
        vector<CPoint3d> v_points;
        for (size_t i = 0; i < n_nodeNum; i++)
        {
            double lf_coordinates[3] = { 0.0 };
            fin >> lf_coordinates[0] >> lf_coordinates[1] >> lf_coordinates[2];
            UpdateAreaRange(lf_coordinates[0], lf_coordinates[1], lf_coordinates[2]);
            v_points.push_back(CPoint3d(lf_coordinates[0], lf_coordinates[1], lf_coordinates[2]));
        }
        // ��ȡ������
        size_t n_triangleNum = 0;
        fin >> n_triangleNum;
        if (n_triangleNum < 1)
        {
            cout << "��������ȱ��������" << endl;
            return -3;
        }
        CPoint3d* p_points = v_points.data();
        for (size_t i = 0; i < n_triangleNum; i++)
        {
            size_t n_pointIndex[3] = { 0 };
            fin >> n_pointIndex[0] >> n_pointIndex[1] >> n_pointIndex[2];
            m_vTriangles.push_back(CTriangle3d(v_points[n_pointIndex[0]], v_points[n_pointIndex[1]], v_points[n_pointIndex[2]]));
        }
        // ���سɹ����
        m_isDemAreaSet = true;
        return 1;
    }

    /// <summary>
    /// ��TIN����ת��ΪDEM����
    /// </summary>
    /// <created>HuYG,2017/5/23</created>
    void CTin2DEM::Convert2DEM()
    {
        if (!m_isDemInit) return;
        CTriangle3d* pTriangles = m_vTriangles.data();
        size_t nTriangles = m_vTriangles.size();
        // ��ÿ�������ν����ڲ�
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
            // �������������ڵ��������
            // ************************
            CTriangle3d* triangle = pTriangles + iTriangle;
            CPoint3d* triNodes = triangle->nodes;
            double tri_node_range[] = {
                min(triNodes[0].X, min(triNodes[1].X, triNodes[2].X)),
                min(triNodes[0].Y, min(triNodes[1].Y, triNodes[2].Y)),
                max(triNodes[0].X, max(triNodes[1].X, triNodes[2].X)),
                max(triNodes[0].Y, max(triNodes[1].Y, triNodes[2].Y))
            }; // �������������� X_MIN Y_MIN X_MAX Y_MAX
            int offset[] = {
                int((tri_node_range[0] - m_lfXmin) / m_lfDemResolution),
                int((tri_node_range[2] - m_lfXmin) / m_lfDemResolution) + 1,
                int((tri_node_range[1] - m_lfYmin) / m_lfDemResolution),
                int((tri_node_range[3] - m_lfYmin) / m_lfDemResolution) + 1
            }; // ƫ��ֵ��˳��Ϊ�� Nx_min Nx_max Ny_min Ny_max
            double area_start[] = {
                m_lfXmin + m_lfDemResolution * offset[0],
                m_lfYmin + m_lfDemResolution * offset[2]
            }; // ���������������������Χ�Ĳ�����ǰ����Ϊ��СX Y����
            size_t area_size[] = {
                offset[1] - offset[0] + 1,
                offset[3] - offset[2] + 1
            };

            // **************************
            // ��������������ߵķ���
            // ������������������������
            // **************************
            Vector3d nodes_h[] = {
                Vector3d(triNodes[0].X, triNodes[0].Y, 1.0),
                Vector3d(triNodes[1].X, triNodes[1].Y, 1.0),
                Vector3d(triNodes[2].X, triNodes[2].Y, 1.0)
            };
            // ���������ߵĲ���
            Vector3d arcs_h[] = {
                nodes_h[1].cross(nodes_h[2]),
                nodes_h[2].cross(nodes_h[0]),
                nodes_h[0].cross(nodes_h[1])
            };
            // ******************************
            // �������η�Χ��ÿһ��������ж�
            // ******************************
            bool isHasDem = false;
            for (size_t iy = 0; iy < area_size[1]; iy++)
            {
                for (size_t ix = 0; ix < area_size[0]; ix++)
                {
#ifdef _DEBUG
                    dem_test_times++;
#endif // _DEBUG
                    // ��ǰ����������
                    Vector3d cur(area_start[0] + ix * m_lfDemResolution, area_start[1] + iy * m_lfDemResolution, 1.0);
                    // �жϵ�ǰ���Ƿ�����������
                    int flag = 0; // ��ǰ��״̬�ı�����ֻ�е� flag = 7 ʱ���Ŵ���ǰ������������
                    flag = ((cur.dot(arcs_h[0]) < 0) == (nodes_h[0].dot(arcs_h[0]) <= 0)) ? flag | 4 : flag;
                    flag = ((cur.dot(arcs_h[1]) < 0) == (nodes_h[1].dot(arcs_h[1]) <= 0)) ? flag | 2 : flag;
                    flag = ((cur.dot(arcs_h[2]) < 0) == (nodes_h[2].dot(arcs_h[2]) <= 0)) ? flag | 1 : flag;
                    // ��������������ڣ��ڲ���߳�ֵ
                    switch (flag)
                    {
                        case 7:
                        {
                            isHasDem = true;
                            // �����ڲ����
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
                                // �ڲ�߳�ֵ
                                double elevation = coefficient.dot(Vector3d(triangle->nodes[0].Z, triangle->nodes[1].Z, triangle->nodes[2].Z));
                                // DEM �����¼�߳�ֵ
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
                cout << "������" << iTriangle << "��û��DEM��" << endl;
            }
#endif // _DEBUG
        }
#ifdef _DEBUG
        cout << "���Ե���������Ŀ��     " << triangle_test_times << endl;
        cout << "����DEM�����������Ŀ��" << triangle_hit_times << endl;
        cout << "�ܵ�DEM�����Ŀ��      " << m_dem.rows * m_dem.cols << endl;
        cout << "���Ե�DEM�����Ŀ��    " << dem_test_times << endl;
        cout << "���е�DEM�����Ŀ��    " << dem_hit_times << endl;
#endif // _DEBUG
    }

}
