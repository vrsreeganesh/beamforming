%% Basic Setup
clc; clear all; close all;

%% Loading the files
angleaxis     		= csvread("../Figures/angleaxis-Objective4.csv");
anglematrix   		= csvread("../Figures/anglematrix-Objective4.csv");
anglematrixinDB   	= 20 * log10(anglematrix);

%% Plotting the signals
plotwidth	= 1515;
plotheight	= 500;

figure(1);
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(angleaxis, anglematrixinDB, "LineWidth", 2);
xlabel("Angles, in degrees",  "fontsize", 16);
ylabel("Gain, in dB",         "fontsize", 16);
ylim([min(anglematrixinDB) - 1e-1 * range(anglematrixinDB),  
	  max(anglematrixinDB) + 1e-1 * range(anglematrixinDB)]);
xlim([min(angleaxis) - 1e-2 * range(angleaxis),
	  max(angleaxis) + 1e-2 * range(angleaxis)]);
saveas(gcf, "../Figures/anglematrixinDB-Objective4.png");