//---------------------------------------------------------//
// HODGKIN-HUXLEY NEURONAL MODEL                           //
// AUTHOR: Marc Bauza Armero                               //
// DEGREE: Electric, Industrial and Automation Engineering //
//---------------------------------------------------------//

#include <stdlib.h>
#include <math.h>  

//----------NEURON CLASS----------//
class neurona
{
  public:
  
  struct dades
  {
    //x.x1 = Vm, x.x2 = n, x.x3 = m, x.x4 = h, x.x5 = Ps
    double x1,x2,x3,x4,x5; 
    dades operator+(const dades& b) const{
      dades suma{b.x1+x1, b.x2+x2, b.x3+x3, b.x4+x4, b.x5+x5};
      return suma;
    }
    dades operator*(const double& b) const{
      dades prod{b*x1, b*x2, b*x3, b*x4, b*x5};
      return prod;
    }
    dades operator*(const dades& b) const{
      dades prod{b.x1*x1, b.x2*x2, b.x3*x3, b.x4*x4, b.x5*x5};
      return prod;
    }
    dades operator/(const dades& b) const{
      dades quoc{b.x1/x1, b.x2/x2, b.x3/x3, b.x4/x4, b.x5/x5};
      return quoc;
    }
  } k1,k2,k3,k4,x,x0,dx,xaux; //variables which use 'dades' structure

  double V;
  double n;
  double m;
  double h;
  double Ps;

  double Iapp;

  double t;
  double dt;

  //Conductances
  double gl_o;
  double gk_o;
  double gna_o;
  double phi;

  double gl;
  double gk;
  double gna;

  //Interior currents
  double iL;
  double iNa;
  double iK;
  double im;

  //Equilibrium potentials
  double EK;
  double ENa;
  double EL;
  
  int C;

  double expa11;
  double alfa11;
  double expb11;
  double beta11;

  double expa21;
  double alfa21;
  double expb21;
  double beta21;

  double expa31;
  double alfa31;
  double expb31;
  double beta31;
  
  //Builder
  neurona();
  //Modificador de 'x'
  void setX(dades _x);
  dades getX(void);
  
  //Hodgking-Huxley neuronal model
  dades RHS(dades _x);
  //Runge Kutta 4 integrator
  void RK4(void);
  //Update
  void updt(void);
};

class i_syn
{
  public:

  double gsyn;
  float Iout;

  double v_membrana;
  double v_thres;
  
  //Builder
  i_syn();
  //Get actual membrane potential value from presynpatic neuron
  void get_V(void);
  //Synapsis condition
  bool syn(void);
  //Synaptic current calculation
  float current_out(double Vmem, double Ps);
};
