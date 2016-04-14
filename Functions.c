// FOR A RLY GOOD DISCLAIMER, I RLY NEED TO COMMENT MORE ON MY CODES, I KNOW THAT...



//MACROS ARE AWWWWWWWWWWWWWWWWWWWWWSOOOOOOOOOOOOOOOOOMMMMEEEEEE
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


    /*Portuguese shit, translate later
    * What this does?
    * This make the inference chart for the acc of the mi
    */
float triangulo (int x,int alfa, int beta,int gama)
{
    float mi;
    if ((x <= alfa) || (x >= gama)) mi = 0;
    else if ((x >= alfa) && (x <= beta)) mi =(float) ((x - alfa)/ (float)(beta - alfa));
    else if ((x > beta) && (x < gama)) mi = (float)(gama - x)/(float)(gama - beta);
    return mi;
}

// shitty way to get the MIN of the rules to make the MAX and the centroid.
float* rulesActive(float _rleft,float _rcenter,float _rright,float _tleft,float _tcenter,float _tright)
{
    float rules[9];
    static float max[3];
    //Center
	rules[0] = MIN(_rleft,_tleft);
    rules[4] = MIN(_rcenter,_tcenter);
    rules[8] = MIN(_rright,_tright);
    max[1] = MAX(rules[0],rules[4]);
    max[1] = MAX(max[1],rules[8]);
    //Right
    rules[1] = MIN(_rleft,_tcenter);
    rules[2] = MIN(_rleft,_tright);
    rules[5] = MIN(_rcenter,_tright);
    max[2] = MAX(rules[1],rules[2]);
    max[2] = MAX(max[2],rules[5]);
    //Left
    rules[3] = MIN(_rcenter,_tleft);
    rules[6] = MIN(_rright,_tleft);
    rules[7] = MIN(_rright,_tcenter);
    max[0] = MAX(rules[3],rules[6]);
    max[0] = MAX(max[0],rules[7]);
    return max;

}

//OMFG U CAN PUT THJE CENTROID HERE AND DON"T MAKE ONE FOR!!!!!! LET IT TO NEXT STEP!!
float cutAndCentroid(float *rules, float left[], float center[], float right[], float out[])
{
    int i;
    float miSum,angleSum;
    miSum = 0;
    angleSum = 0;
    for(i=0;i<361;i++)
    {
        out[i] = 0;
        if(rules[0]>=left[i])
            out[i] = left[i];
        else out[i] = rules[0];
        if((out[i] < center[i]) && (center[i] < rules[1]))
            out[i] = center[i];
        if((out[i] < center[i]) && (center[i] > rules[1]))
            out[i] = rules[1];
        if((out[i] < right[i]) && (right[i] < rules[2]))
            out[i] = right[i];
        if((out[i] < right[i]) && (right[i] > rules[2]))
            out[i] = rules[2];

        miSum += out[i];
        angleSum += ((i-180) * out[i]);

    }
    return angleSum/miSum;

}
