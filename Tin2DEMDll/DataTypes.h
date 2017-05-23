#pragma once
#ifdef TIN2DEMDLL_EXPORTS
#define TIN2DEMDLL_API __declspec(dllexport)
#else
#define TIN2DEMDLL_API __declspec(dllimport)
#endif

namespace DigitalPhotogrammetry
{
    class IDem;
    class ITin2DEM;
    class CPoint3d;
    class CTriangle3d;
    class CDem;
    class CTin2DEM;
}