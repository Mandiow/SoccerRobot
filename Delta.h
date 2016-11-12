#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "ConjuntoFuzzy.h"
#endif

class Delta:public ConjuntoFuzzy
{
    protected:
    float alpha;
    float beta;
    public:
    Delta(float alpha, float beta);
    float pertinencia(float u);
};

