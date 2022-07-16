//---------------------------------------------------------//
// HINDMARSH-ROSE NEURONAL MODEL                           //
// AUTHOR: Marc Bauza Armero                               //
// DEGREE: Electric, Industrial and Automation Engineering //
//---------------------------------------------------------//

#include <stdlib.h>
#include <math.h>
#include "neurona.h" 

using namespace std;
//----------NEURON CLASS----------//
//Builder
neurona::neurona()
{ 
  x1 = -1.5;
  y = 0;
  z = 0;
  
  Iapp = 0;
  r = 0.001;
  s = 4;

  t = 0.0;
  dt = 0.05;
}

void neurona::setX(dades _x){
  x = _x;
}
neurona::dades neurona::getX(){
  return x;
}

//Hindmarsh-Rose neuronal model
neurona::dades neurona::HindRose(dades d)
{  
  /*
  dx.x1 = dx, 
  dx.x2 = dy,
  dx.x3 = dz,
  */
  dx.x1 = d.x2 - pow(d.x1,3) + 3*pow(d.x1,2) + Iapp - d.x3;
  dx.x2 = 1 - 5*pow(d.x1,2) - d.x2;
  dx.x3 = r*s*(d.x1 - x1 - d.x3);
  
  return dx;
}

////Runge Kutta 4 integrator
void neurona::RK4(void)
{ 
  k1 = HindRose(getX())*dt;
  k2 = HindRose(getX()+k1*(1/2))*dt;
  k3 = HindRose(getX()+k2*(1/2))*dt;
  k4 = HindRose(getX()+k3)*dt; 

  x0 = x;
  
  xaux = ((k1+k4) + (k2+k3)*2)*0.166666666666666666667;

  x = x0 + xaux;
  
  t = t + dt;
}
void neurona::updt(void)
{
  RK4();
}
