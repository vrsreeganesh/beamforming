%% Basic Setup
clc; clear all;

%% Loading the files
angleaxis		= csvread("../csv-files/angleaxis-Objective-6.csv");
anglegains		= csvread("../csv-files/anglematrix-Objective-6.csv");
anglegainsindB 	= 10 * log10(anglegains);

%% Plotting the signals
plotwidth	= 1515;
plotheight	= 500;

figure(1);
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(angleaxis, anglegainsindB, "LineWidth", 2);
xlabel("Angles, in degrees",  "fontsize", 16);
ylabel("Gain, in dB",         "fontsize", 16);
ylim([min(anglegainsindB) - 1e-1 * range(anglegainsindB), max(anglegainsindB) + 1e-1 * range(anglegainsindB)]);
xlim([min(angleaxis) - 1e-2 * range(angleaxis), max(angleaxis) + 1e-2 * range(angleaxis)]);
saveas(gcf, "../Figures/anglegainsindB-Objective6.png");