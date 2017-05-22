#pragma once

#include "stdafx.h"

#include "Tin2DEMDll.h"

namespace DigitalPhotogrammetry
{
    class TIN2DEMDLL_API ITin2DEM
    {
    public:
        virtual BOOL ReadTin(const char* sTinPath) = 0;
        //virtual void UpdateAreaRange(double lf_X, double lf_Y) = 0;
        
        static ITin2DEM* create()
        {
            return new CTin2DEM();
        }
    };

}