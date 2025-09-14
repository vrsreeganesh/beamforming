%% Basic Setup 
clc; clear all; close all;
addpath("./include/")

%% Loading the files
timeaxis 	= csvread("../csv-files/timeaxis-Objective2.csv");
newmat		= csvread("../csv-files/newmat-Objective2.csv");

%% Plotting
plotwidth	= 1515;
plotheight	= 500;

figure(1)
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(timeaxis, newmat);
xlabel("time, in seconds",  "fontsize", 16);
ylabel("amplitude",         "fontsize", 16);
ylim([1.1 * min(newmat(:)), 1.1 * max(newmat(:))]);
saveas(gcf, "../Figures/newmat-Objective2.png");
