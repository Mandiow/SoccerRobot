#include "Robot.h"
#include <math.h>
#include <stdio.h>
#include <windows.h>
//Macros aren't very pretty? ;3
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

float Robot::ballAngle = 0.0;
float Robot::targetAngle = 0.0;
float Robot::ballDistance = 0.0;
Delta* Robot::E = 0;
Triangulo* Robot::EF = 0;
Triangulo* Robot::F = 0;
Triangulo* Robot::FD = 0;
Gamma* Robot::D = 0;

ConjuntoFuzzy* Robot::distanceRule = 0;

float Robot::setMin(float first, float second)
{
    if (first < second)
    {
        return first;
    }
    return second;
}

float Robot::setMax(float first, float second)
{
    if (first > second)
    {
        return first;
    }
    return second;
}

float Robot::setMinimum(float firstSet, float secondSet, float thirdSet)
{
    if (firstSet == 0.0 || secondSet == 0.0 || thirdSet == 0.0)
    {
        return 0.0;
    }
    float result = 1.0;
    result = MIN(result,firstSet);
    result = MIN(result,secondSet);
    result = MIN(result,thirdSet);

    return result;
}

void Robot::setBallAngle(float value)
{
    ballAngle = value;
}
void Robot::setTargetAngle(float value)
{
    targetAngle = value;
}
void Robot::setBallDistance(float value)
{
    ballDistance = value;
}

void Robot::fuzzyCalculations(float fuzzySet[])
{

    fuzzySet[0] = Robot::setMinimum(E->pertinencia(ballAngle), E->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[1] = Robot::setMinimum(E->pertinencia(ballAngle), EF->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[2] = Robot::setMinimum(E->pertinencia(ballAngle), F->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[3] = Robot::setMinimum(E->pertinencia(ballAngle), FD->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[4] = Robot::setMinimum(E->pertinencia(ballAngle), D->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[5] = Robot::setMinimum(EF->pertinencia(ballAngle), E->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[6] = Robot::setMinimum(EF->pertinencia(ballAngle), EF->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[7] = Robot::setMinimum(EF->pertinencia(ballAngle), F->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[8] = Robot::setMinimum(EF->pertinencia(ballAngle), FD->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[9] = Robot::setMinimum(EF->pertinencia(ballAngle), D->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[10] = Robot::setMinimum(F->pertinencia(ballAngle), E->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[11] = Robot::setMinimum(F->pertinencia(ballAngle), EF->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[12] = Robot::setMinimum(F->pertinencia(ballAngle), F->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[13] = Robot::setMinimum(F->pertinencia(ballAngle), FD->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[14] = Robot::setMinimum(F->pertinencia(ballAngle), D->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[15] = Robot::setMinimum(FD->pertinencia(ballAngle), E->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[16] = Robot::setMinimum(FD->pertinencia(ballAngle), EF->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[17] = Robot::setMinimum(FD->pertinencia(ballAngle), F->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[18] = Robot::setMinimum(FD->pertinencia(ballAngle), FD->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[19] = Robot::setMinimum(FD->pertinencia(ballAngle), D->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[20] = Robot::setMinimum(D->pertinencia(ballAngle), E->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[21] = Robot::setMinimum(D->pertinencia(ballAngle), EF->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[22] = Robot::setMinimum(D->pertinencia(ballAngle), F->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[23] = Robot::setMinimum(D->pertinencia(ballAngle), FD->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
    fuzzySet[24] = Robot::setMinimum(D->pertinencia(ballAngle), D->pertinencia(targetAngle), distanceRule->pertinencia(ballDistance));
}

void Robot::setDistanceRule(ConjuntoFuzzy *rule)
{
    distanceRule = rule;
}

/*
    Método de defuzificação do centróide ( de Mamdani )
*/

void Robot::centroidDeffuzification(float far__[], float middle[], float near__[],float* sum, float* weightedSum)
{
    float outValue = 0.0;
    int i;
    // For para cálculo de -180 até 180
    for (i = 0; i <= 100; i++)
    {
        float z = i*(M_PI/50) - M_PI; // z varia entre -180 até 180 em graus ou -pi até pi
        outValue = 0.0;
        outValue = MAX(MIN(far__[0], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[1], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[2], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[3], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[4], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[5], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[6], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[7], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[8], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[9], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[10], F->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[11], F->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[12], F->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[13], F->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[14], F->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[15], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[16], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[17], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[18], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[19], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[20], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[21], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[22], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[23], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(far__[24], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[0], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[1], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[2], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[3], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[4], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[5], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[6], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[7], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[8], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[9], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[10], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[11], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[12], F->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[13], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[14], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[15], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[16], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[17], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[18], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[19], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[20], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[21], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[22], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[23], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(middle[24], D->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[0], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[1], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[2], E->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[3], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[4], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[5], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[6], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[7], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[8], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[9], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[10], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[11], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[12], F ->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[13], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[14], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[15], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[16], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[17], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[18], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[19], FD->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[20], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[21], EF->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[22], D ->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[23], D ->pertinencia(z)), outValue);
        outValue = MAX(MIN(near__[24], D ->pertinencia(z)), outValue);

        *sum += outValue;
        *weightedSum += z*outValue;
    }
}
