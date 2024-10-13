#include <iostream>
#include <fstream>  // File handling
#include "gridPoints.hpp"

int main() {


    list gridPoints = list().createGrid();

    // Open a .dat file to save results
    std::ofstream outputFile("gridPoints.dat");
    if (!outputFile) {
        std::cerr << "Error: Unable to open gridPoints.dat\n";
        return 1;
    }

    // Write grid points to the .dat file
    // 62k elements
    for (const auto& point : gridPoints) {
        outputFile << point.ID << " " 
                   << point.coordinates[0] << " " 
                   << point.coordinates[1] << "\n";
    }

    std::cout << "Points saved to gridPoints.dat!\n";
    outputFile.close();  // Close the file

    return 0;
}

