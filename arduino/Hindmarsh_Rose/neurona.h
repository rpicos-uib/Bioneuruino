//---------------------------------------------------------//
// HINDMARSH-ROSE NEURONAL MODEL                           //
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
    double x1,x2,x3;
    dades operator+(const dades& b) const{
      dades suma{b.x1+x1, b.x2+x2, b.x3+x3};
      return suma;
    }
    dades operator*(const dades& b) const{
      dades prod{b.x1*x1, b.x2*x2, b.x3*x3};
      return prod;
    }
    dades operator*(const double& b) const{
      dades prod{b*x1, b*x2, b*x3};
      return prod;
    }
    dades operator/(const dades& b) const{
      dades quoc{b.x1/x1, b.x2/x2, b.x3/x3};
      return quoc;
    }
  }x,x0,xaux,dx,k1,k2,k3,k4;

  double V; // Membrane potential
  double y; // Recovery constant
  double z; // Interior constant current

  double x1;

  double Iapp;
  double r;
  double s;

  double t;
  double dt;
  
  //Builder
  neurona();
  
  void setX(dades _x);
  dades getX(void);
  
  //Hindmarsh-Rose neuronal model
  dades HindRose(dades _x);
  //Runge Kutta 4 integrator
  void RK4(void);
  //Update
  void updt(void);
};
