#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

float triangulo (int x,int alfa, int beta,int gama);
float* rulesActive(float _rleft,float _rcenter,float _rright,float _tleft,float _tcenter,float _tright);
float cutAndCentroid(float *rules, float left[], float center[], float right[], float out[]);
#ifdef __cplusplus
}
#endif

#endif
