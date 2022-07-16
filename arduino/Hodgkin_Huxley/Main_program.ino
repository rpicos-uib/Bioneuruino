//---------------------------------------------------------//
// HODGKIN-HUXLEY NEURONAL MODEL                           //
// AUTHOR: Marc Bauza Armero                               //
// DEGREE: Electric, Industrial and Automation Engineering //
//---------------------------------------------------------//

#include <stdlib.h>
#include <math.h>
#include "neurona.h"

using namespace std;

//------NEURONS AND SYNAPTIC CHANNELS STATEMENTS-----------//
//i_syn channel0 activated by initial pulse
neurona neurona1;
i_syn channel1;
neurona neurona2;
i_syn channel2;
neurona neurona3;
i_syn channel3;
neurona neurona4;
i_syn channel4;
neurona neurona5;
i_syn channel5;
neurona neurona6;
i_syn channel6;
neurona neurona7;
i_syn channel7;
neurona neurona8;
i_syn channel8;
neurona neurona9;
i_syn channel9;
neurona neurona10;
i_syn channel10;

//--------Pulse shot parameters----------------------------//
double Iin = 10;     //Initial current pulse DC Value

int to1 = 0;         //Start time pols1
int tf1 = 3;         //End time pols1
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
      pulse[numpulse] = true;
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
  Serial.println("V_1 V_2 V_3 V_4 V_5 V_6 V_7 V_8 V_9 V_10");
  Serial.println("  ");
  
//------NEURONS INITIALIZATION-----------------------------// 
  neurona::dades init = {neurona1.V,neurona1.n,neurona1.m,neurona1.h,neurona1.Ps};
  neurona1.setX(init);
  neurona2.setX(init);
  neurona3.setX(init);
  neurona4.setX(init);
  neurona5.setX(init);
  neurona6.setX(init);
  neurona7.setX(init);
  neurona8.setX(init);
  neurona9.setX(init);
  neurona10.setX(init);

//------SYNAPTIC CHANNEL PINS CONFIGURATION----------------//
  //Synaptic channel 0
  pinMode(18, OUTPUT);
  digitalWrite(18,LOW);
  pinMode(19, INPUT);
  //Synaptic channel 1
  pinMode(20, OUTPUT);
  digitalWrite(20,LOW);
  pinMode(21, INPUT);
  //Synaptic channel 2
  pinMode(22, OUTPUT);
  digitalWrite(22,LOW);
  pinMode(23, INPUT);
  //Synaptic channel 3
  pinMode(24, OUTPUT);
  digitalWrite(24,LOW);
  pinMode(25, INPUT);
  
  //Synaptic channel 4
  pinMode(36, OUTPUT);
  digitalWrite(36,LOW);
  pinMode(37, INPUT);
  //Synaptic channel 5
  pinMode(38, OUTPUT);
  digitalWrite(38,LOW);
  pinMode(39, INPUT);
  //Synaptic channel 6
  pinMode(40, OUTPUT);
  digitalWrite(40,LOW);
  pinMode(41, INPUT);
  //Synaptic channel 7
  pinMode(42, OUTPUT);
  digitalWrite(42,LOW);
  pinMode(43, INPUT);
  
  //Synaptic channel 8
  pinMode(A15, OUTPUT);
  digitalWrite(A15,LOW);
  pinMode(A14, INPUT);
  //Synaptic channel 9
  pinMode(A13, OUTPUT);
  digitalWrite(A13,LOW);
  pinMode(A12, INPUT);
}

void loop(){
//-------NEURONAL NETWORK STRUCTURE------------------------//
  generatePulse(18,to1,tf1,0);
  //generatePulse(18,to2,tf2,1);

//Actualització variables de cada neurona
  neurona1.updt();
  neurona2.updt();
  neurona3.updt();
  neurona4.updt();
  neurona5.updt();
  neurona6.updt();
  neurona7.updt();
  neurona8.updt();
  neurona9.updt();
  neurona10.updt();
  
  //(Pols --> Neurona1) ò (Neurona10 --> Channel10 --> Neurona1)
  channel10.v_membrana = neurona10.x.x1;
  if(!pulse[0] && !pulse[1]){   //Condició per a evitar anul·lar els polsos
    digitalWrite(18,channel10.syn());
    if(digitalRead(19)){
      neurona1.Iapp=channel10.current_out(neurona10.x.x1, neurona10.x.x5);
    }
    else{
      neurona1.Iapp = 0;
    }
  }
  //Neurona1 --> Channel1 --> Neurona2
  channel1.v_membrana = neurona1.x.x1; //Agafa V_mem de la neurona presinàptica
  digitalWrite(20,channel1.syn());     //Compara aquest valor amb v_thres
  if(digitalRead(21)){
    //Dona corrent a la neurona postsinàptica
    neurona2.Iapp=channel1.current_out(neurona1.x.x1, neurona1.x.x5);
  }
  else{
    neurona2.Iapp = 0;
  }
  //Neurona2 --> Channel2 --> Neurona3
  channel2.v_membrana = neurona2.x.x1;
  digitalWrite(22,channel2.syn());
  if(digitalRead(23)){
    neurona3.Iapp=channel2.current_out(neurona2.x.x1, neurona2.x.x5);
  }
  else{
    neurona3.Iapp = 0;
  }
  //Neurona3 --> Channel3 --> Neurona4
  channel3.v_membrana = neurona3.x.x1;
  digitalWrite(24,channel3.syn());
  if(digitalRead(25)){
    neurona4.Iapp=channel3.current_out(neurona3.x.x1, neurona3.x.x5);
  }
  else{
    neurona4.Iapp = 0;
  }
  //Neurona4 --> Channel4 --> Neurona5
  channel4.v_membrana = neurona4.x.x1;
  digitalWrite(36,channel4.syn());
  if(digitalRead(37)){
    neurona5.Iapp=channel4.current_out(neurona4.x.x1, neurona4.x.x5);
  }
  else{
    neurona5.Iapp = 0;
  }
  //Neurona5 --> Channel5 --> Neurona6
  channel5.v_membrana = neurona5.x.x1;
  digitalWrite(38,channel5.syn());
  if(digitalRead(39)){
    neurona6.Iapp=channel5.current_out(neurona5.x.x1, neurona5.x.x5);
  }
  else{
    neurona6.Iapp = 0;
  }
  //Neurona6 --> Channel6 --> Neurona7
  channel6.v_membrana = neurona6.x.x1;
  digitalWrite(40,channel6.syn());
  if(digitalRead(41)){
    neurona7.Iapp=channel6.current_out(neurona6.x.x1, neurona6.x.x5);
  }
  else{
    neurona7.Iapp = 0;
  }
  //Neurona7 --> Channel7 --> Neurona8
  channel7.v_membrana = neurona7.x.x1;
  digitalWrite(42,channel7.syn());
  if(digitalRead(43)){
    neurona8.Iapp=channel7.current_out(neurona7.x.x1, neurona7.x.x5);
  }
  else{
    neurona8.Iapp = 0;
  }
  //Neurona8 --> Channel8 --> Neurona9
  channel8.v_membrana = neurona8.x.x1;
  digitalWrite(A15,channel8.syn());
  if(digitalRead(A14)){
    neurona9.Iapp=channel8.current_out(neurona8.x.x1, neurona8.x.x5);
  }
  else{
    neurona9.Iapp = 0;
  }
  //Neurona9 --> Channel9 --> Neurona10
  channel9.v_membrana = neurona9.x.x1;
  digitalWrite(A13,channel9.syn());
  if(digitalRead(A12)){
    neurona10.Iapp=channel9.current_out(neurona9.x.x1, neurona9.x.x5);
  }
  else{
    neurona10.Iapp = 0;
  }
//---------------------------------------------------------//

//--------RESULTS PRINTING---------------------------------//
  Serial.print(neurona1.x.x1);
  
  Serial.print(", ");
  Serial.print(neurona2.x.x1);
  Serial.print(", ");
  Serial.print(neurona3.x.x1);
  Serial.print(", ");
  Serial.print(neurona4.x.x1);
  Serial.print(", ");
  Serial.print(neurona5.x.x1);
  Serial.print(", ");
  Serial.print(neurona6.x.x1);
  Serial.print(", ");
  Serial.print(neurona7.x.x1);
  Serial.print(", ");
  Serial.print(neurona8.x.x1);
  Serial.print(", ");
  Serial.print(neurona9.x.x1);
  Serial.print(", ");
  Serial.print(neurona10.x.x1);
  
  Serial.println(" ");

  i++;

  //Serial.println(millis());
//---------------------------------------------------------//
}
