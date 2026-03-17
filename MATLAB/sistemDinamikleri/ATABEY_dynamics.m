function XDOT = ATABEY_dynamics(X, U)
%-------------------SABITLER VE GIRISLER-----------------------
m = 2.5;
g = 9.81;
S = 0.39;
cbar = 0.30;
b = 1.30;
Xcg = 0.216; Ycg = 0; Zcg = 0.04;
Xapt1 = 0; Yapt1 = 0; Zapt1 = 0;
Xapt2 = 0; Yapt2 = 0; Zapt2 = 0;
u1 = U(1); u2 = U(2); u3 = U(3); u4 = U(4);
u5 = 0;

%-------------------DURUM DEGISKENLERI-------------------------
u = X(1); v = X(2); w = X(3);
p = X(4); q = X(5); r = X(6);
phi = X(7); theta = X(8); psi = X(9);

Va    = sqrt(u^2 + v^2 + w^2);
alpha = atan2(w, u);
beta  = asin(max(min(v/Va, 1), -1));   % clamped for robustness
Q     = 0.5 * 1.225 * Va^2;

%-------------------AERODINAMIK HESAPLAR-----------------------
CL = 4.3 * alpha + 0.15 * u2;
CD = 0.02 + 0.05 * CL^2;
CY = -0.15 * beta;

FA_b = [(-CD*cos(alpha) + CL*sin(alpha)) * Q * S;
         CY * Q * S;
        (-CD*sin(alpha) - CL*cos(alpha)) * Q * S];

MAcg_b = [0.103 * u1 * Q * S * b;
          (-0.20*alpha + 0.068*u2 - 0.07) * Q * S * cbar;
          -0.08 * beta * Q * S * b];

%-------------------MOTOR VE MOMENTLER-------------------------
F1 = u4 * 26.1;
F2 = u5 * 0;
FE1_b = [F1; 0; 0];
FE2_b = [F2; 0; 0];
FE_b  = FE1_b + FE2_b;

mew1 = [Xcg - Xapt1; -Ycg; Zcg - Zapt1];
mew2 = [Xcg - Xapt2; -Ycg; Zcg - Zapt2];
MEcg_b = cross(mew1, FE1_b) + cross(mew2, FE2_b);

%-------------------YERCEKIMI VE TUREVLER----------------------
Fg_b = m*g*[-sin(theta); cos(theta)*sin(phi); cos(theta)*cos(phi)];

Ib    = [0.252 0 0; 0 0.052 0; 0 0 0.301];
invIb = [3.9683 0 0; 0 19.2308 0; 0 0 3.3223]; % avoid inv() in codegen

% FIX 1: initialise XDOT before subscript assignment
XDOT = zeros(9, 1);

XDOT(1:3) = (1/m)*(FA_b + FE_b + Fg_b) - cross(X(4:6), X(1:3));

omega = X(4:6);
omega = omega(:);   % force column no matter what
XDOT(4:6) = invIb * (MAcg_b + MEcg_b - cross(omega, Ib * omega));

T = [1  sin(phi)*tan(theta)   cos(phi)*tan(theta);
     0  cos(phi)             -sin(phi);
     0  sin(phi)/cos(theta)   cos(phi)/cos(theta)];

XDOT(7:9) = T * X(4:6);
% XDOT is already 9×1 — no transpose needed
end