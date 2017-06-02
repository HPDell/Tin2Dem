// Tin2Dem.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"

#include <iostream>
// ����Tin2DemDll
#include "Tin2DEMDll.h"

using namespace std;
using namespace DigitalPhotogrammetry;

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        cout << "û��TIN����·����" << endl;
        return -1;
    }
    else if (argc < 3)
    {
        cout << "û��DEM�ĳߴ�" << endl;
    }
    else if (argc < 4)
    {
        cout << "û��DEM����·����" << endl;
        return -1;
    }
    // ��������
    cout << "��������...";
    cout << "�ֱ���" << atof(argv[2]) << endl;
    ITin2DEM* tin2dem = ITin2DEM::create(atof(argv[2]));
    cout << "���" << endl;
    // ��ȡTIN�ļ�
    cout << "��ȡ�ļ�...";
    tin2dem->ReadTin(argv[1]);
    cout << "���" << endl;
    cout << "��ʼ��DEM...";
    tin2dem->InitDEM();
    cout << "���" << endl;
    cout << "ת��TINΪDEM...";
    tin2dem->Convert2DEM();
    //tin2dem->Convert2DEM_Backward();
    cout << "���" << endl;
    //tin2dem->PrintDem("Result.ddem");
    IDem* dem = tin2dem->GetDem();
    cout << "���DEM...";
    dem->Print(argv[3]);
    cout << "���" << endl;

    ITin2DEM::del(tin2dem);
    
    system("pause");
}

