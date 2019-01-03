#pragma once
#include <vector>
#include <memory>
#include <optional>
#include "cell.h"
#include "Utility.h"

class QuadTree
{
    public:
        QuadTree(std::shared_ptr< std::vector< std::vector<double> > > data, vec2<int> pos, vec2<int> delta);
        std::vector<Cell> CellsAboveThreshold(int thresh);
        std::unique_ptr<Cell>& getCell();
    private:
        int msb(int num);
        std::shared_ptr< std::vector< std::vector<double> > > data;
        vec2<int> pos;
        std::unique_ptr<QuadTree> a;
        std::unique_ptr<QuadTree> b;
        std::unique_ptr<QuadTree> c;
        std::unique_ptr<QuadTree> d;
        std::unique_ptr<Cell> cell;
        double lowerbound;
        double upperbound;
};