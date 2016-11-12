#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "ConjuntoFuzzy.h"
#endif

class Triangulo:public ConjuntoFuzzy
{
    protected:
    float alpha;
    float beta;
    float gamma;
    public:
    Triangulo(float alpha, float beta, float gamma);
    float pertinencia(float u);
};
