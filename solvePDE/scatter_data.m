clear
clc
close all
% Read the data from gridPoints.dat
data = readmatrix('gridPoints.dat'); 

% Extract columns from the data
IDs = data(:, 1);           % First column: Point IDs
x_coords = data(:, 2);       % Second column: x-coordinates
y_coords = data(:, 3);       % Third column: y-coordinates

% Plot the points with fine markers
figure;
scatter(x_coords, y_coords, 5, '.', 'MarkerEdgeColor', [0 0.4 0.8]); % Fine scatter plot

% Plot settings for better visualization
title('Fine Grid Points Representation');
xlabel('X Coordinate');
ylabel('Y Coordinate');
grid on;          % Enable grid
axis equal;       % Maintain aspect ratio
set(gca, 'FontSize', 12); % Adjust font size for readability

% Save the figure as a high-quality PDF
print('GridPointsPlot', '-dpdf', '-painters'); % Save as PDF

% Display the number of points and a sample of the first few points
disp(['Total number of points: ', num2str(size(data, 1))]);
disp('First 5 points from gridPoints.dat:');
disp(table(IDs(1:5), x_coords(1:5), y_coords(1:5), ...
     'VariableNames', {'ID', 'X', 'Y'}));
