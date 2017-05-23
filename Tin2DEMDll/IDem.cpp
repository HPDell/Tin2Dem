#include "stdafx.h"
#include "IDem.h"
#include "Dem.h"

namespace DigitalPhotogrammetry
{
    IDem * IDem::create()
    {
        return new CDem();
    }
    IDem * IDem::create(IDem * source)
    {
        return new CDem(*((CDem*)source));
    }
    void IDem::del(IDem * pInstance)
    {
        delete (CDem*)pInstance;
    }
}