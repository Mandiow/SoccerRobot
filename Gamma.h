#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "ConjuntoFuzzy.h"
#endif
class Gamma: public ConjuntoFuzzy
{
    protected:
    float alpha;
    float beta;

    public:
    Gamma(float alpha, float beta);
    float pertinencia(float u);
};

