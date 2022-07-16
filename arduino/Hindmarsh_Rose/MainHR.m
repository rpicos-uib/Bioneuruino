close all
%Initial conditions
ti = 0;
tf = 500;
dt = 0.05;

x1 = -1.5; %Initial position
y = 0;
z = 0;

N = (tf - ti)/dt;
ic = [x1; y; z];

%Applied current
Iapp=11;

% Resolve dif.eq
[x, t] = solveEDOrk45('HH',ti,ic,tf,N,Iapp);

function [dx] = HH(~,x, Iapp)
x1 = -1.5;
r = 0.001;
s = 4;

%Differential equations to resolve:
%Membrane potential
dx(1,1) = x(2) - x(1)^3 + 3*x(1)^2 + Iapp - x(3);
%Recovery variable
dx(2,1) = 1 - 5*x(1)^2 - x(2);
%Interior current
dx(3,1) = r*s*(x(1) - x1 - x(3));
end

function [dx, t] = solveEDOrk45 (RHS, t0, x0, tf, N , param)

neqn = length(x0);
t(1) = t0;
dx(1:neqn, 1) = x0';
i = 2;

if(N <= 0)
    disp( 'N must be positive and different to 0' );
    return;
else
    h = (tf - t0)/N;
end
while(t0 < tf)
   
    k1 = h * feval(RHS, t0, x0, param);
    k2 = h * feval(RHS, t0 + h/2, x0 + k1/2, param);
    k3 = h * feval(RHS, t0 + h/2, x0 + k2/2, param);
    k4 = h * feval(RHS, t0 + h, x0 + k3, param);
    
    fv=k1(1)/h;
%     fprintf(fdesti,'%d \t %d \n' ,t0,fv);
    
    x0 = x0 + (k1 + 2*k2 + 2*k3 + k4)/6;
    t0 = t0 + h;
    t(i) = t0;
    dx(1:neqn, i) = x0';
	i = i + 1;
    
end
end