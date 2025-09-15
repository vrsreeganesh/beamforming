%% Basic Setup
clc; clear all;

%% Loading the files
timearray		= csvread("../csv-files/t-Objective3.csv");
yarray			= csvread("../csv-files/y-Objective3.csv");
matrix			= csvread("../csv-files/matrix-Objective3.csv");

ULAMatrix		= csvread("../csv-files/newmat-Objective3.csv");
FourierMatrix	= fReadCSV("../csv-files/Fourier-Objective3.csv");

angleaxis 		= csvread("../csv-files/angleaxis-Objective3.csv");
anglematrix 	= csvread("../csv-files/anglematrix-Objective3.csv");
anglematrixdB	= 10*log10(anglematrix);

%% Plotting the signals
plotwidth	= 1515;
plotheight	= 500;

figure(1);
set(gcf, 'Position', [0 0 plotwidth plotheight]);   % [left bottom width height]
plot(angleaxis, anglematrixdB, "LineWidth", 2);
xlabel("Angles, in degrees",  		"fontsize", 16);
ylabel("Absolute value, in dB",     "fontsize", 16);
ylim([min(anglematrixdB) - 1e-1 * range(anglematrixdB),  
	  max(anglematrixdB)  + 1e-1 * range(anglematrixdB)]);
xlim([min(angleaxis) - 1e-2 * range(angleaxis),
	  max(angleaxis) + 1e-2 * range(angleaxis)]);
saveas(gcf, "../Figures/anglematrixdB-Objective3.png");