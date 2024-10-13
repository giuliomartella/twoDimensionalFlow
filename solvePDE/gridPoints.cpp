#include "gridPoints.hpp"
#include <vector>
#include <cmath>


bool point::innerCondition(const list& innerBoundary) const {
    //ray casting algorithm
    int n = innerBoundary.size();
    bool inside = false;

    
    for (int i = 0, j = n - 1; i < n; j = i++) {
        const point& pi = innerBoundary[i];
        const point& pj = innerBoundary[j];

        
        bool intersect = ((pi.coordinates[1] > coordinates[1]) != 
                          (pj.coordinates[1] > coordinates[1])) &&
                         (coordinates[0] < (pj.coordinates[0] - pi.coordinates[0]) * 
                         (coordinates[1] - pi.coordinates[1]) / 
                         (pj.coordinates[1] - pi.coordinates[1]) + pi.coordinates[0]);

        
        if (intersect) {
            inside = !inside;
        }
    }

    return inside;
}



list list::setBox(const double& xMin, const double& yMin, const double& xMax, const double& yMax)
{
    int nDots = 100;
    list outerBoundary;
    outerBoundary.reserve(4 * nDots);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < nDots; j++)
        {
            point p;
            p.ID = i * nDots + j;

            if (i == 0)
            {
                p.coordinates[0] = xMin;
                p.coordinates[1] = yMin + j * (yMax - yMin) / nDots;
            }
            else if (i == 1)
            {
                p.coordinates[0] = xMin + j * (xMax - xMin) / nDots;
                p.coordinates[1] = yMax;
            }
            else if (i == 2)
            {
                p.coordinates[0] = xMax;
                p.coordinates[1] = yMax - j * (yMax - yMin) / nDots;
            }
            else if (i == 3)
            {
                p.coordinates[0] = xMax - j * (xMax - xMin) / nDots;
                p.coordinates[1] = yMin;
            }

            outerBoundary.push_back(p);
        }
    }
    return outerBoundary;
}

list list::setStandardBox()
{
    return setBox(-10.0, -10.0, 10.0, 10.0); 
}

list list::setCylinder()
{
    int nDots = 100;
    const double pi = 3.141592653589793;
    list innerBoundary;
    innerBoundary.reserve(nDots);
    double radius = 1.0;
    double xCenter = 0.0;
    double yCenter = 0.0;
    for (int i = 0; i < nDots; i++)
    {
        point p;
        p.ID = i;
        p.coordinates[0] = xCenter + radius * cos(2.0 * pi * i / nDots);
        p.coordinates[1] = yCenter + radius * sin(2.0 * pi * i / nDots);
        innerBoundary.push_back(p);
    }

    return innerBoundary;
}

list list::setBoxScattered(const double& xMin, const double& yMin, const double& xMax, const double& yMax)
{
    int nDots = 200;
    list scatteredList;
    scatteredList.reserve(nDots * nDots);
    int id = 0;
    for (int i = 0; i < nDots; i++)
    {
        for (int j = 0; j < nDots; j++)
        {
            point p;
            p.ID = id;
            p.coordinates[0] = xMin + i * (xMax - xMin) / nDots;
            p.coordinates[1] = yMin + j * (yMax - yMin) / nDots;
            scatteredList.push_back(p);
            id++;
        }
    }
    return scatteredList;
}

list list::setStandardBoxScattered()
{
    return setBoxScattered(-10.0, -10.0, 10.0, 10.0); 
}

void list::setAirfoilScattered()
{
    list scatteredList = *this; 
    list innerBoundary = setCylinder();
    const double pi = 3.141592653589793;
    int nTheta = 20;
    int nDots = 20;
    double theta, rho;
    int id = scatteredList.size();

    for (int i = 0; i < innerBoundary.size(); i++)
    {
        for (int j = 0; j < nTheta; j++)
        {
            theta = 2.0 * pi * j / nTheta;
            for (int k = 0; k < nDots; k++)
            {
                rho = 0.5 * (1 - cos(k * pi / nDots)); // Chebyshev–Gauss–Lobatto nodes
                point p;
                p.ID = id;
                p.coordinates[0] = innerBoundary[i].coordinates[0] + rho * cos(theta);
                p.coordinates[1] = innerBoundary[i].coordinates[1] + rho * sin(theta);
                scatteredList.push_back(p);
                id++;
            }
        }
    }

    *this = scatteredList; 
}

list list::selectGridPoints(const list& scatteredList)
{
    list gridPoints;
    int id = 0;
    list cylinderBoundary = setCylinder();
    list standardBoxBoundary = setStandardBox();

    for (const auto& pt : scatteredList)
    {
        bool innerCondition = !pt.innerCondition(cylinderBoundary);
        bool outerCondition = pt.innerCondition(standardBoxBoundary);

        if (innerCondition && outerCondition)
        {
            point p = pt;
            p.ID = id;
            gridPoints.push_back(p);
            id++;
        }
    }
    return gridPoints;
}

list list::createGrid()
{
    // Create scattered points
    list scatteredList = list().setStandardBoxScattered();

    // Add airfoil points to the scattered list
    scatteredList.setAirfoilScattered();

    // Select valid grid points
    list gridPoints = list().selectGridPoints(scatteredList);

    return gridPoints;
    }