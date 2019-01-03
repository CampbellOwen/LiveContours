#pragma once
#include "Utility.h"
#include <vector>
#include <memory>
#include <map>
#include <utility>

enum Direction {
    right = 0,
    bottom,
    left,
    top,
    end
};

struct Edge 
{
    Direction nextEntry;
    vec2<int> delta;
    std::pair<vec2<double>, vec2<double>> path;
};

class Cell
{
public:
    Cell(std::shared_ptr< std::vector< std::vector<double> > > data, vec2<int> pos);
    std::map<Direction, Edge> getEdges(double thresh);
    vec2<int> pos;  

private:
    std::shared_ptr<std::vector< std::vector<double> > > data;
};
