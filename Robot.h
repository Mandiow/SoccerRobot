#ifndef FUZZYGROUP_ADD
#define FUZZYGROUP_ADD
#include "ConjuntoFuzzy.h"
#endif

#ifndef FUZZYFUNCTIONS
#define FUZZYFUNCTIONS
#include "Triangulo.h"
#include "Delta.h"
#include "Gamma.h"
#endif // FUZZYFUNCTIONS


// Static Class that calculates the whole Fuzzy Logic system
class Robot
{
    private:
    static float ballAngle;
    static float targetAngle;
    static float ballDistance;
    static ConjuntoFuzzy* distanceRule;


    public:
    static void setBallAngle(float value);
    static void setTargetAngle(float value);
    static void setBallDistance(float value);
    static void setDistanceRule(ConjuntoFuzzy* rule);
    static Delta* E;
    static Triangulo* EF;
    static Triangulo* F;
    static Triangulo* FD;
    static Gamma* D;
    static float setMin(float first, float second);
    static float setMax(float first, float second);
    static float setMinimum(float firstSet, float secondSet, float thirdSet);
    static void fuzzyCalculations(float fuzzySet[]);
    static void centroidDeffuzification(float far__[], float middle[], float near__[],float* sum, float* weightedSum);
    };

