// Tin2Dem.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <iostream>
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
        cout << "没有DEM的尺寸" << endl;
    }
    else if (argc < 4)
    {
        cout << "没有DEM数据路径！" << endl;
        return -1;
    }
    // 创建对象
    cout << "创建对象...";
    cout << "分辨率" << atof(argv[2]) << endl;
    ITin2DEM* tin2dem = ITin2DEM::create(atof(argv[2]));
    cout << "完成" << endl;
    // 读取TIN文件
    cout << "读取文件...";
    tin2dem->ReadTin(argv[1]);
    cout << "完成" << endl;
    cout << "初始化DEM...";
    tin2dem->InitDEM();
    cout << "完成" << endl;
    cout << "转换TIN为DEM...";
    tin2dem->Convert2DEM();
    //tin2dem->Convert2DEM_Backward();
    cout << "完成" << endl;
    //tin2dem->PrintDem("Result.ddem");
    IDem* dem = tin2dem->GetDem();
    cout << "输出DEM...";
    dem->Print(argv[3]);
    cout << "完成" << endl;

    ITin2DEM::del(tin2dem);
    
    system("pause");
}

