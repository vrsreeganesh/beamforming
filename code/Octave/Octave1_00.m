%% Basic Setup 
clc; clear all; close all;
addpath("./include/")

%% Loading the files
timeaxis 	= csvread("../csv-files/timeaxis-Objective1.csv");
newmat		= csvread("../csv-files/newmat-Objective1.csv");
waxis		= csvread("../csv-files/waxis-Objective1.csv");
newmatfft	= fReadCSV("../csv-files/Fourier-Objective1.csv");

%% Plotting
plotwidth	= 1515;
plotheight	= 500;

figure(1)
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(timeaxis, newmat);
xlabel("time, in seconds",  "fontsize", 16);
ylabel("amplitude",         "fontsize", 16);
ylim([1.2 * min(newmat), 1.2 * max(newmat)]);
saveas(gcf, "../Figures/y-objective1.png");

figure(2);
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(waxis, abs(newmatfft) );
xlabel("frequency, in Hz",  "fontsize", 16);
ylabel("magnitude",         "fontsize", 16);
xlim([min(waxis), max(waxis)]);
saveas(gcf, "../Figures/abs-yfft-objective1.png");

figure(3);
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(waxis, angle(newmatfft) );
xlabel("frequency, in Hz",  "fontsize", 16);
ylabel("phase",         	"fontsize", 16);
xlim([min(waxis), max(waxis)]);
saveas(gcf, "../Figures/phase-yfft-objective1.png");