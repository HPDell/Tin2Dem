// Tin2Dem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <iostream>

#include "stdafx.h"

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
        cout << "û��DEM����·����" << endl;
        return -1;
    }
    // ��������
    ITin2DEM* tin2dem = ITin2DEM::create();
    // ��ȡTIN�ļ�
    tin2dem->ReadTin(argv[1]);
    tin2dem->InitDEM();
    tin2dem->Convert2DEM();
    //tin2dem->PrintDem("Result.ddem");
    IDem* dem = tin2dem->GetDem();
    dem->Print(argv[2]);

}

