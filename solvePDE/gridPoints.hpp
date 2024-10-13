#ifndef GRIDPOINTS_HPP
#define GRIDPOINTS_HPP

#include <vector>
#include <string>

class list;

class point
{
    friend class list;
public:
    point() :
        ID(0),
        coordinates{0.0, 0.0}
    {
    }
    double coordinates[2];
    int ID;

    bool innerCondition(const list& innerBoundary) const;
private:
    
};

class list : public std::vector<point>
{
public:
    list() : std::vector<point>()
    {
    }

    
    list setBox(const double& xMin, const double& yMin, const double& xMax, const double& yMax);
    list setStandardBox();
    list setCylinder();

    list setBoxScattered(const double& xMin, const double& yMin, const double& xMax, const double& yMax);
    list setStandardBoxScattered();
    void setAirfoilScattered();

    list selectGridPoints(const list& scatteredList);

    list createGrid();
};

#endif
