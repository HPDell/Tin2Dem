#pragma once
#include "DataTypes.h"
//#include "Dem.h"
namespace DigitalPhotogrammetry
{
    class TIN2DEMDLL_API IDem
    {
    public:
        virtual void Print(const char* filepath) = 0;

        static IDem* create();
        

        static IDem* create(IDem* source);
        

        static void del(IDem* pInstance);
        
    };

}