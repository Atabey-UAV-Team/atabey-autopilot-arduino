clc, clear, close all

% MATLAB/ klasörü altında çalıştırın
addpath('sistemDinamikleri')
addpath('simulinkModelleri')

simTime = 1800;     % Saniye

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

u = [0;
    0;
    1;];

% KONTROL SINIRLARI
uServoMax = 20*pi/180;       % Aileron min/max derecesi
uServoMin = -1*uServoMax;

uMotorMin = 0;               % Motor çalışma aralığı
uMotorMax = 1;

%% SİMÜLASYON
clc
endResults = sim("ATABEY_sistem_modeli.slx")

%% PLOT
clc; close all;

X_ts = endResults.SimulatedOutputs;
U_ts = endResults.SimulatedInputs;
time = X_ts.Time;

% 3D timeseries to 2D numeric arrays
X_data = squeeze(permute(X_ts.Data, [3 1 2]));
U_data = reshape(U_ts.Data, U_ts.Length, []);
U_data = U_data(:, 1:3);

% --- Kontrol Girdileri ---
figure('Name','Kontrol Girdileri','NumberTitle','off')
numInputs = size(U_data, 2);

inputNames = {'Aileron', 'Elevator', 'Motor'};

for i = 1:numInputs
    subplot(numInputs, 1, i)
    plot(time, U_data(:,i), 'LineWidth', 1.5)
    hold on
    yline(eval(['u' num2str(i) 'min']), '--r', 'Min')
    yline(eval(['u' num2str(i) 'max']), '--g', 'Max')
    grid on
    xlabel('Simülasyon Zamanı [s]')
    ylabel(inputNames{i})
    title([inputNames{i}])
    legend('Girdi','Min Limit','Max Limit')
end

% --- Sistem Durumları (3×3) ---
figure('Name','Sistem Durumları','NumberTitle','off')
numStates = size(X_data, 2);   % should be 9
nRows = 3;
nCols = 3;

stateNames = {'u', 'v', 'w', 'p', 'q', 'r', '\phi', '\theta', '\psi'};

for i = 1:numStates
    subplot(nRows, nCols, i)
    plot(time, X_data(:,i), 'LineWidth', 1.5)
    grid on
    xlabel('Simülasyon Zamanı [s]')
    ylabel(stateNames{i}, 'Interpreter', 'tex')
    title([stateNames{i}], 'Interpreter', 'tex')
end