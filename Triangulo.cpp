#include "Triangulo.h"
Triangulo::Triangulo(float alpha, float beta, float gamma)
{
    this->alpha = alpha;
    this->beta = beta;
    this->gamma = gamma;
    this->spike = beta;
}

float Triangulo::pertinencia(float u)
{
    float mi = 0.0;
    if ((u < alpha) || (u > gamma)) mi = 0.0;
    if ((u >= alpha) && (u <= beta)) mi = (u - alpha)/(beta - alpha);
    if ((u > beta) && (u <= gamma)) mi = (gamma - u)/(gamma - beta);

    return mi;
}
