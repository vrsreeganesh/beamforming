%% Basic Setup
clc; clear all; close all;

%% Loading the files
angleaxis		= csvread("../csv-files/angle-axis-Objective9.csv");
angleMatrix		= 10 * log10(csvread("../csv-files/angle-matrix-Objective9.csv"));

%% Plotting
plotwidth	= 1515;
plotheight	= 500;

figure(1);
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(angleaxis, angleMatrix, "LineWidth",2);
xlim([min(angleaxis) 		- 1e-2 * range(angleaxis),
	  max(angleaxis) 		+ 1e-2 * range(angleaxis)]);
ylim([min(angleMatrix) 		- 1e-1 * range(angleMatrix),  
	  max(angleMatrix)  	+ 1e-1 * range(angleMatrix)]);
xlabel("Azimuthal Angle, in degrees",  	"fontsize", 16);
ylabel("Beampattern",         			"fontsize", 16);
saveas(gcf, "../Figures/BeamPattern-Octave9.png");