#pragma once

namespace DigitalPhotogrammetry
{
    class CDem
    {
    private:
        double* m_lfDem;

    public:
        double x_min;
        double y_min;
        double size;
        size_t cols;
        size_t rows;
        
    public:
        CDem() : m_lfDem(nullptr), x_min(0.0), y_min(0.0), size(0.0), cols(0), rows(0) {}
        ~CDem();
    };
}

