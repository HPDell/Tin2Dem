// Tin2Dem.cpp : 定义控制台应用程序的入口点。
//

#pragma comment(lib, "../x64/Debug/Tin2DEMDll.lib")

#include "stdafx.h"

// 引用Tin2DemDll
#include "ITin2DEM.h"
//#include "Tin2DEM.h"

//#include "Tin2DEM.h"
using namespace DigitalPhotogrammetry;

int main()
{
    ITin2DEM* tin2dem = ITin2DEM::create();

}

