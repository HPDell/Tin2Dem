#include "stdafx.h"
#include "ITin2DEM.h"
#include "Tin2DEM.h"

namespace DigitalPhotogrammetry
{
    ITin2DEM * ITin2DEM::create()
    {
        return new CTin2DEM();
    }
    ITin2DEM * ITin2DEM::create(double lf_demResolution)
    {
        return new CTin2DEM(lf_demResolution);
    }
    void ITin2DEM::del(ITin2DEM * pInstance)
    {
        delete (CTin2DEM*)pInstance;
    }
}