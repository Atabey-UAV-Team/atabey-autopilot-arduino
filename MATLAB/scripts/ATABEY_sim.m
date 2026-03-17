clc, clear, close all

% MATLAB klasörü altında çalıştırın
addpath('sistemDinamikleri')
addpath('simulinkModelleri')
simTime = 60;

% TRIM
x0 = [15;   % u
    0;      % v
    0;      % w
    0;      % p
    0;      % q
    0;      % r
    0;      % phi
    0;      % theta
    0;];    % psi

u = [25*pi/180;
    0;
    0;
    1;];

% KONTROL SINIRLARI
u1max = 25*pi/180;       % Aileron min/max derecesi
u1min = -1*u1max;

u2max = 20*pi/180;       % Stabilizer min/max derecesi
u2min = -1*u2max;

u3max = 20*pi/180;       % Rudder min/max derecesi
u3min = -1*u3max;

u4min = 0;              % Motor çalışma aralığı
u4max = 1;

%% SİMÜLASYON
clc
endResults = sim("ATABEY_sistem_modeli.slx")

%% PLOT
clc; close all;

X_ts = endResults.SimulatedOutputs;
U_ts = endResults.SimulatedInputs;
time = X_ts.Time;

% 3D timeseries to 2D numeric arrays (time × states/inputs)
X_data = squeeze(permute(X_ts.Data, [3 1 2]));
U_data = reshape(U_ts.Data, U_ts.Length, []);
U_data = U_data(:, 1:4);

% --- Kontrol Girdileri ---
figure('Name','Kontrol Girdileri','NumberTitle','off')
numInputs = size(U_data, 2);
for i = 1:numInputs
    subplot(numInputs, 1, i)
    plot(time, U_data(:,i), 'LineWidth', 1.5)
    hold on
    yline(eval(['u' num2str(i) 'min']), '--r', 'Min')
    yline(eval(['u' num2str(i) 'max']), '--g', 'Max')
    grid on
    xlabel('Simülasyon Zamanı [s]')
    ylabel(['u_' num2str(i)])
    title(['Kontrol Girdisi: u_' num2str(i)])
    legend('Girdi','Min Limit','Max Limit')
end

% --- Sistem Durumları (3×3) ---
figure('Name','Sistem Durumları','NumberTitle','off')
numStates = size(X_data, 2);   % should be 9
nRows = 3;
nCols = 3;
for i = 1:numStates
    subplot(nRows, nCols, i)
    plot(time, X_data(:,i), 'LineWidth', 1.5)
    grid on
    xlabel('Simülasyon Zamanı [s]')
    ylabel(['x_' num2str(i)])
    title(['Durum: x_' num2str(i)])
end