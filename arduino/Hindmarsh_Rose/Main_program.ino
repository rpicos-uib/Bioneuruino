//---------------------------------------------------------//
// HINDMARSH-ROSE NEURONAL MODEL                           //
// AUTHOR: Marc Bauza Armero                               //
// DEGREE: Electric, Industrial and Automation Engineering //
//---------------------------------------------------------//

#include <stdlib.h>
#include <math.h>
#include "neurona.h"

using namespace std;
neurona neurona1;

//--------Pulse shot parameters----------------------------//
double Iin = 1;     //Initial current pulse DC Value

//int to1 = 0;         //Start time pols1
//int tf1 = 0;         //End time pols1
//int to2 = 200;       //Start time pols2
//int tf2 = 205;       //End time pols2

bool pulse[3] = {false,false,false};

int i = 0;           //Execution recount

//--------First neuron excitation--------------------------//
//Input parameters: PIN to write in, Start time pulse (ms), End time pulse (ms)
void generatePulse(int PINin, int to, int tf, int numpulse){
    if(i == to/neurona1.dt){
      digitalWrite(PINin,HIGH);
      neurona1.Iapp = Iin;
    }
    if(i == tf/neurona1.dt){  // i*dt = t (ms)
      neurona1.Iapp = 0;
      digitalWrite(PINin,LOW);
      pulse[numpulse] = false;
    }
  }
//---------------------------------------------------------//

void setup(){
  delay(50);
  Serial.begin(2000000);
  delay(50);
  Serial.println("x y z");
  Serial.println("  ");

//------NEURONS INITIALIZATION-----------------------------//
  neurona::dades init = {neurona1.V,neurona1.y,neurona1.z};
  neurona1.setX(init);

}

void loop(){
//-------NEURON OPERATION----------------------------------//
  neurona1.Iapp = Iin;
  neurona1.updt();
//---------------------------------------------------------//

//--------RESULTS PRINTING---------------------------------//
  Serial.print(neurona1.x.x1);
  Serial.println("");
  i++;
//---------------------------------------------------------//
}
