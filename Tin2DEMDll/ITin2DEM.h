#pragma once

#include "stdafx.h"

#include "Tin2DEMDll.h"

namespace DigitalPhotogrammetry
{
    class TIN2DEMDLL_API ITin2DEM
    {
        virtual BOOL ReadTin() = 0;
        virtual void UpdateAreaRange(double lf_X, double lf_Y) = 0;
    };

    extern "C" TIN2DEMDLL_API ITin2DEM* CreateTin2DEM()
    {
        return new CTin2DEM();
    }
}