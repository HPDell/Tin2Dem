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
        // ��ȡ������
        size_t n_triangleNum = 0;
        fin >> n_triangleNum;
        if (n_triangleNum < 1)
        {
            cout << "��������ȱ��������" << endl;
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
        // ���سɹ����
        is_DemAreaSet = true;
        return 1;
    }

    /// <summary>
    /// ��TIN����ת��ΪDEM����
    /// </summary>
    /// <created>HuYG,2017/5/23</created>
    void CTin2DEM::Convert2DEM()
    {
        if (!is_DemInit) return;
        CTriangle3d* pTriangles = m_vTriangles.data();
        size_t nTriangles = m_vTriangles.size();
        // ��ÿ�������ν����ڲ�
        for (size_t iTriangle = 0; iTriangle < nTriangles; iTriangle++)
        {
            CTriangle3d* triangle = pTriangles + iTriangle;
            CPoint3d* triNodes = triangle->nodes;
            double tri_node_range[] = {
                min(triNodes[0].X, min(triNodes[1].X, triNodes[2].X)),
                min(triNodes[0].Y, min(triNodes[1].Y, triNodes[2].Y)),
                max(triNodes[0].X, max(triNodes[1].X, triNodes[2].X)),
                max(triNodes[0].Y, max(triNodes[1].Y, triNodes[2].Y))
            }; // �������������� X_MIN Y_MIN X_MAX Y_MAX
            int offset[] = {
                (int)(tri_node_range[0] - m_lfXmin) / m_lfDemResolution,
                (int)(tri_node_range[2] - m_lfXmin) / m_lfDemResolution + 1,
                (int)(tri_node_range[1] - m_lfYmin) / m_lfDemResolution,
                (int)(tri_node_range[3] - m_lfYmin) / m_lfDemResolution + 1
            }; // ƫ��ֵ��˳��Ϊ�� Nx_min Nx_max Ny_min Ny_max
            double area_config[] = {
                m_lfXmin + m_lfDemResolution * offset[0],
                m_lfYmin + m_lfDemResolution * offset[2],
                offset[1] - offset[0] + 1,
                offset[3] - offset[2] + 1
            }; // ���������������������Χ�Ĳ�����ǰ����Ϊ��СX Y���꣬������ΪX Y��������ĸ�����

            // ��������������ߵķ���
            // ������������������������
            Vector3d nodes_h[] = {
                Vector3d(triangle->nodes[0].X, triangle->nodes[0].Y, 1.0),
                Vector3d(triangle->nodes[1].X, triangle->nodes[1].Y, 1.0),
                Vector3d(triangle->nodes[2].X, triangle->nodes[2].Y, 1.0)
            };
            // ���������ߵĲ���
            Vector3d arcs_h[3];
            for (size_t i = 0; i < 3; i++)
            {
                arcs_h[i] = nodes_h[(i + 1) % 3].cross(nodes_h[(i + 2) % 3]);
            }
            // �������η�Χ��ÿһ��������ж�
            for (size_t ix = 0; ix < area_config[2]; ix++)
            {
                for (size_t iy = 0; iy < area_config[3]; iy++)
                {
                    // ��ǰ����������
                    Vector3d cur(area_config[0] + ix * m_lfDemResolution, area_config[1] + iy * m_lfDemResolution, 1.0);
                    //double cur_x = area_config[0] + ix * m_lfDemResolution;
                    //double cur_y = area_config[y] + iy * m_lfDemResolution;
                    // �жϵ�ǰ���Ƿ�����������
                    int flag = 0; // ��ǰ��״̬�ı�����ֻ�е� flag = 7 ʱ���Ŵ���ǰ������������
                    flag = (abs(cur.dot(arcs_h[0]) - nodes_h[0].dot(arcs_h[0])) < 1.0e-8) ? flag | 4 : flag;
                    flag = (abs(cur.dot(arcs_h[1]) - nodes_h[1].dot(arcs_h[1])) < 1.0e-8) ? flag | 2 : flag;
                    flag = (abs(cur.dot(arcs_h[2]) - nodes_h[2].dot(arcs_h[2])) < 1.0e-8) ? flag | 1 : flag;
                    // ��������������ڣ��ڲ���߳�ֵ
                    if (flag == 7)
                    {
                        // �����ڲ����
                        Matrix3d matA = Matrix3d::Constant(1.0);
                        matA(0, 0) = triangle->nodes[0].X;
                        matA(0, 1) = triangle->nodes[1].X;
                        matA(0, 2) = triangle->nodes[2].X;
                        matA(1, 0) = triangle->nodes[0].Y;
                        matA(1, 1) = triangle->nodes[1].Y;
                        matA(1, 2) = triangle->nodes[2].Y;
                        Vector3d coefficient = matA.ldlt().solve(cur);
                        // �ڲ�߳�ֵ
                        double elevation = coefficient.dot(Vector3d(triangle->nodes[0].Z, triangle->nodes[1].Z, triangle->nodes[2].Z));
                        // DEM �����¼�߳�ֵ
                        m_dem.SetElevation(offset[0] + ix, offset[2] + iy, elevation);
                    }
                }
            }
        }
    }

}
