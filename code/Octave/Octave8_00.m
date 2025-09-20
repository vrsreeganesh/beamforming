%% Basic Setup
clc; clear all; close all;

%% Loading the files
angle_axis		= csvread("../csv-files/angle_axis-Objective8.csv");
sum_matrix		= csvread("../csv-files/sum_matrix-Objective8.csv");
sum_matrix		= 20 * log10(sum_matrix);

%% Plotting
plotwidth	= 1515;
plotheight	= 500;

figure(1)
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(angle_axis, sum_matrix, "LineWidth", 2);
xlabel("Azimuthal Angle, in degrees",  "fontsize", 16);
ylabel("amplitude",         "fontsize", 16);
saveas(gcf, "../Figures/sum-matrix-Objective8.png");