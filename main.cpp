//------------------------------------------------------------------------------
// Inclusão da biblioteca que implementa a interface com o SoccerMatch.

#include "../../client_implementation/environm.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Functions.h"
#include <iostream>
#include <fstream>
using namespace std;

int main( int argc, char* argv[] ) {

    float   ballAngle, targetAngle, ballDistance, adjustment, rightMotor, leftMotor;
    float   inBallLeft[361], inBallRight[361], inBallCenter[361];
    float   inTargetLeft[361], inTargetRight[361], inTargetCenter[361];
    float   outLEFT[361], outRIGHT[361], outCENTER[361];
    float   adjustmentT;
    float   *RULES,z[361],output;
    int i;

    ofstream myfile;
    myfile.open ("example.txt");

    // Declaração do objeto que representa o ambiente.
    environm::soccer::clientEnvironm environment;

    if ( argc != 3 ) {
        printf( "\nInvalid parameters. Expecting:" );
        printf( "\nSoccerPlayer SERVER_ADDRESS_STRING SERVER_PORT_NUMBER\n" );
        printf( "\nSoccerPlayer localhost 1024\n" );
        return 0;
    }

    for (i = 0; i <= 360; ++i)
    {
        inBallRight[i] = triangulo(i-180,0,180, 190);
        inBallCenter[i] = triangulo(i-180,-90,0,90);
        inBallLeft[i] = triangulo(i-180,-190, -180, 0);
        inTargetRight[i] = triangulo(i-180,0,180, 190);
        inTargetCenter[i] = triangulo(i-180,-90,0,90);
        inTargetLeft[i] = triangulo(i-180,-190, -180, 0);
        outRIGHT[i] = triangulo(i-180,0,180, 190);
        outCENTER[i] = triangulo(i-180,-180,0,180);
        outLEFT[i] = triangulo(i-180,-190, -180, 0);
        //myfile << "outleft"<< outLEFT[i] << '\n';



    }
    myfile.close();

    // Conecta-se ao SoccerMatch. Supõe que SoccerMatch está rodando na máquina
    // local e que um dos robôs esteja na porta 1024. Porta e local podem mudar.
    if ( ! environment.connect( argv[1], atoi( argv[2] ) ) ) {
        printf( "\nFail connecting to the SoccerMatch.\n" );
        return 0;  // Cancela operação se não conseguiu conectar-se.
    }




    // Laço de execução de ações.
    printf( "\nRunning..." );
    int x = 0;
    while ( 1 ) {

        // Deve obter os dados desejados do ambiente. Métodos do clientEnvironm.
        // Exemplos de métodos que podem ser utilizados.
        ballAngle = environment.getBallAngle();
        targetAngle = environment.getTargetAngle( environment.getOwnGoal() );
        ballDistance = environment.getDistance();
        adjustment = ballAngle * 180.0 / M_PI;
        adjustment += 180.0f;
        adjustmentT = targetAngle  * 180.0 / M_PI;
        adjustmentT += 180.0f;
        RULES = rulesActive(inBallLeft[(int) (adjustment)]
                            ,inBallCenter[(int)(adjustment)]
                            ,inBallRight[(int) (adjustment)]
                            ,inTargetLeft[(int) (adjustmentT)]
                            ,inTargetCenter[(int) (adjustmentT)]
                            ,inTargetRight[(int)(adjustmentT)]);
        output = cutAndCentroid(RULES, outLEFT, outCENTER, outRIGHT, z);
        output = output * M_PI/180.0;
        output = -output;





        // A partir dos dados obtidos, deve inferir que ações executar. Neste
        // exemplo as forcas destinadas a cada robo sao guardadas em leftMotor e
        // rightMotor. Esta etapa deve ser substituida pelo controlador fuzzy.
        printf("output %f\n",output);

        for(i = 0; i <361; i++)
        {
            //printf("Z[%d] = %f\n",i,z[i]);
        }
        x = 0;
        while (x < 10000)
        {
            x++;
        }
        /*for(i = 0; i < 3; i++)
        {
            printf("\nRULE[%d] = %f\n",i,RULES[i]);
        }


/*

        ballAngle = ballAngle - targetAngle;
        if ( ballAngle < -M_PI ) {
            ballAngle += 2 * M_PI;
        }
        if ( ballAngle > M_PI ) {
            ballAngle -= 2 * M_PI;
        }
        if ( ballAngle < ( -M_PI / 2 ) ) {
            ballAngle = -M_PI / 2;
        }
        if ( ballAngle > ( M_PI / 2 ) ) {
            ballAngle = M_PI / 2;
        }
*/
        leftMotor =  cos( output ) - sin( output );
        rightMotor = cos( output ) + sin( output );
        leftMotor = leftMotor * 0.5;
        rightMotor = rightMotor * 0.5;


        // Transmite ação do robô ao ambiente. Fica bloqueado até que todos os
        // robôs joguem. Se erro, retorna false (neste exemplo, sai do laco).
        if ( ! environment.act( leftMotor, rightMotor ) ) {
            break; // Termina a execução se falha ao agir.
        }

    }

    return 0;
}
//------------------------------------------------------------------------------
