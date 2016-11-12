#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "ConjuntoFuzzy.h"
#endif

class Trapezio:public ConjuntoFuzzy
{
    protected:
    float alpha;
    float beta;
    float gamma;
    float delta;
    public:
    Trapezio(float alpha, float beta, float gamma, float delta);
    float pertinencia(float u);
};

