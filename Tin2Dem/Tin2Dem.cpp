// Tin2Dem.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>

#include "stdafx.h"

// 引用Tin2DemDll
#include "Tin2DEMDll.h"

using namespace std;
using namespace DigitalPhotogrammetry;

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        cout << "没有TIN数据路径！" << endl;
        return -1;
    }
    else if (argc < 3)
    {
        cout << "没有DEM数据路径！" << endl;
        return -1;
    }
    // 创建对象
    ITin2DEM* tin2dem = ITin2DEM::create();
    // 读取TIN文件
    tin2dem->ReadTin(argv[1]);
    tin2dem->InitDEM();
    tin2dem->Convert2DEM();
    //tin2dem->PrintDem("Result.ddem");
    IDem* dem = tin2dem->GetDem();
    dem->Print(argv[2]);

}

