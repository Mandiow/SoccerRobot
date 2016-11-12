//------------------------------------------------------------------------------
// Inclus�o da biblioteca que implementa a interface com o SoccerMatch.

#include "environm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Functions.h"
#include "Robot.h"
#ifndef FUZZYFUNCTIONS
#define FUZZYFUNCTIONS
#include "Triangulo.h"
#include "Delta.h"
#include "Gamma.h"

#endif // FUZZYFUNCTIONS
#include "Trapezio.h"
#include <iostream>
#include <fstream>
using namespace std;

int main( int argc, char* argv[] ) {

    float   ballAngle, targetAngle, ballDistance, rightMotor, leftMotor;
    double output;

    int i;


    // Declara��o do objeto que representa o ambiente.
    environm::soccer::clientEnvironm environment;

    if ( argc != 3 ) {
        printf( "\nInvalid parameters. Expecting:" );
        printf( "\nSoccerPlayer SERVER_ADDRESS_STRING SERVER_PORT_NUMBER\n" );
        printf( "\nSoccerPlayer localhost 1024\n" );
        return 0;
    }

    // Conecta-se ao SoccerMatch. Sup�e que SoccerMatch est� rodando na m�quina
    // local e que um dos rob�s esteja na porta 1024. Porta e local podem mudar.
    if ( ! environment.connect( argv[1], atoi( argv[2] ) ) ) {
        printf( "\nFail connecting to the SoccerMatch.\n" );
        return 0;  // Cancela opera��o se n�o conseguiu conectar-se.
    }


    Robot::E = new Delta(-M_PI,-M_PI/2);
    Robot::EF = new Triangulo(-M_PI, -M_PI/2, 0.0);
    Robot::F = new Triangulo(-M_PI/2, 0.0, M_PI/2);
    Robot::FD = new Triangulo(0.0, M_PI/2, M_PI);
    Robot::D = new Gamma(M_PI/2, M_PI);

    Gamma* far_ = new Gamma(300.0, 400.0);
    Trapezio* near_ = new Trapezio(25.0, 75.0, 300.0, 400.0);
    Delta* close_ = new Delta(25.0, 75.0);

    // La�o de execu��o de a��es.
    printf( "\nRunning..." );
    int x = 0;
    while ( 1 ) {

        // Deve obter os dados desejados do ambiente. M�todos do clientEnvironm.
        // Exemplos de m�todos que podem ser utilizados.
        ballAngle = environment.getBallAngle();
        targetAngle = environment.getTargetAngle( environment.getOwnGoal() );
        ballDistance = environment.getDistance();

        //FUZZIFICA��O
		float longMatrix[25];
		float mediumMatrix[25];
        float nearMatrix[25];
        float weightedSum = 0.0;
        float sum = 0.0;
        Robot::setBallAngle(ballAngle);
        Robot::setBallDistance(ballDistance);
        Robot::setTargetAngle(targetAngle);
        Robot::setDistanceRule(far_);
        Robot::fuzzyCalculations(longMatrix);
        Robot::setDistanceRule(near_);
        Robot::fuzzyCalculations(mediumMatrix);
        Robot::setDistanceRule(close_);
        Robot::fuzzyCalculations(nearMatrix);
        Robot::centroidDeffuzification(longMatrix,mediumMatrix,nearMatrix, &sum, &weightedSum);
        output = weightedSum/sum;
        // A partir dos dados obtidos, deve inferir que a��es executar. Neste
        // exemplo as forcas destinadas a cada robo sao guardadas em leftMotor e
        // rightMotor. Esta etapa deve ser substituida pelo controlador fuzzy.
        leftMotor =  cos( output ) - sin( output );
        rightMotor = cos( output ) + sin( output );
        leftMotor = leftMotor * 0.5;
        rightMotor = rightMotor * 0.5;
        // Transmite a��o do rob� ao ambiente. Fica bloqueado at� que todos os
        // rob�s joguem. Se erro, retorna false (neste exemplo, sai do laco).
        if ( ! environment.act( leftMotor, rightMotor ) ) {
            break; // Termina a execu��o se falha ao agir.
        }

    }

    return 0;
}
//------------------------------------------------------------------------------
