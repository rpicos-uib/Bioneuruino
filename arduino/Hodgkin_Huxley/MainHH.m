close all
%Initial conditions
V = -65;
h = 0.9;
n = 0.1;
m = 0.1;

ti = 0;
tf = 1000;
dt = 0.05;

N = (tf - ti)/dt;
ic = [V; n; m; h];

%Applied current
Iapp=20;

% Resolve dif.eq
tic
[x, t] = solveEDOrk45('HH',ti,ic,tf,N,Iapp);
toc

function [dx] = HH(~,x, Iapp)
% nS/mm^2:
gl=0.1;
gk=18.0;
gna=45.0; 
phi=4.0;
% (mV):
EK = -80;
ENa = 55;
EL = -65;
E = [EK ENa EL];
C=1; %nF

%Differential equations to resolve:
alfa(1,1) = 0.01*(x(1)+34)/(1-exp(-0.1*(x(1)+34)));
beta(1,1) = 0.125*exp(-(x(1)+44)/25);

alfa(2,1) = 0.1*(x(1)+33)/(1-exp(-0.1*(x(1)+33)));
beta(2,1) = 4*exp(-(x(1)+58)/12);

alfa(3,1) = 0.07*exp(-(x(1)+50)/10);
beta(3,1) = 1/(1+exp(-0.1*(x(1)+20)));

%Membrane potential
dx(1,1) = (1/C)*(Iapp - gl*(x(1)-E(3)) - gk*(x(2)^4)*(x(1)-E(1)) - gna*(x(3)^3)*x(4)*(x(1)-E(2)));
%m, n, h
dx(2:4,1) = phi*(alfa(:,1).*(1-x(2:4))-beta(:,1).*(x(2:4)));
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
    
    x0 = x0 + (k1 + 2*k2 + 2*k3 + k4)/6;
    t0 = t0 + h;
    t(i) = t0;
    dx(1:neqn, i) = x0';
	i = i + 1;
    
end
end