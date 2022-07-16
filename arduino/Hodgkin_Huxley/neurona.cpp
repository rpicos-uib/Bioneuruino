//---------------------------------------------------------//
// HODGKIN-HUXLEY NEURONAL MODEL                           //
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
  V = -65.0;
  n = 0.1;
  m = 0.1;
  h = 0.9;
  Ps = 0.0;
  
  Iapp = 0.0;

  t = 0.0;
  dt = 0.05;

  //Conductances
  gl_o = 0.1;
  gk_o = 18.0;
  gna_o = 45.0;
  phi = 4.0;

  gl = 0;
  gk = 0;
  gna = 0;

  //Corrents interns
  iL = 0;
  iNa = 0;
  iK = 0;
  im = 0;
  
  //Equilibrium potentials
  EK = -80.0;
  ENa = 55.0;
  EL = -65.0;
  
  C = 1;
}

void neurona::setX(dades _x){
  x = _x;
}
neurona::dades neurona::getX(){
  return x;
}

//Hodgking-Huxley neuronal model
neurona::dades neurona::RHS(dades d)
{  
  alfa11 = 0.01*(d.x1+34.0)/(1-exp(-0.1*(d.x1+34.0)));
  beta11 = 0.125*exp(-(d.x1+44.0)/25.0);
  alfa21 = 0.1*(d.x1+33.0)/(1-exp(-0.1*(d.x1+33.0)));
  beta21 = 4.0*exp(-(d.x1+58.0)/12.0);
  alfa31 = 0.07*exp(-(d.x1+50.0)/10.0);
  beta31 = 1.0/(1+exp(-0.1*(d.x1+20.0)));
  
  dx.x1 = (Iapp - gl_o*(d.x1-EL) - gk_o*pow(d.x2,4)*(d.x1-EK) 
          - gna_o*pow(d.x3,3)*d.x4*(d.x1-ENa));
  dx.x2 = phi*(alfa11*(1-d.x2)-beta11*(d.x2));
  dx.x3 = phi*(alfa21*(1-d.x3)-beta21*(d.x3));
  dx.x4 = phi*(alfa31*(1-d.x4)-beta31*(d.x4));
  dx.x5 = (1/(1+exp((-d.x1+20)/2)))-(d.x5/10);

  gk = gk_o*pow(d.x2,4);
  gna = gna_o*pow(d.x3,3)*(d.x4);

  iL = (d.x1 - EL)*gl;
  iNa = (d.x1 - ENa)*gna;
  iK = (d.x1 - EK)*gk;

  im = iL + iNa + iK;
  
  return dx;
}

//Runge Kutta 4 Integrator
void neurona::RK4(void)
{ 
  k1 = RHS(getX())*dt;
  k2 = RHS(getX()+k1*(1/2))*dt;
  k3 = RHS(getX()+k2*(1/2))*dt;
  k4 = RHS(getX()+k3)*dt;

  x0 = x;

  xaux = ((k1+k4) + (k2+k3)*2)*0.166666666666666666667;

  x = x0 + xaux;
  
  t = t + dt;
}
void neurona::updt(void)
{
  RK4();
}

//----------I_SYN CLASS----------//
//Builder
i_syn::i_syn(){

  gsyn = 5.4;       //Valor per defecte: 5.4nS
  Iout = 0.0;
  
  v_membrana = -65; //Valor per defecte: -65mV
  v_thres = 0;      //Umbral per defecte: 0mV
}
//Synapsis condition
bool i_syn::syn(void){
  return (v_membrana >= v_thres);
}
//Synaptic current calculation
float i_syn::current_out(double Vmem, double Ps){
  return Iout = gsyn*Ps*(Vmem - v_thres);
}
