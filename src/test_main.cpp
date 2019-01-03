#include "quadtree.h"
#include "Utility.h"
#include <vector>
#include <iostream>
#include <memory>

int main()
{
    std::cout << "Hello world!" << std::endl;
    auto data = std::make_shared<std::vector<std::vector<double> > > (std::vector<std::vector<double> >({ 
        std::vector<double>({1,2,3,2,1}),
        std::vector<double>({2,3,4,3,2}), 
        std::vector<double>({3,4,5,4,3}), 
        std::vector<double>({2,3,4,3,2}),
        std::vector<double>({1,2,3,2,1})
    }));

    QuadTree tree(data, {0, 0}, {4, 4});
    std::vector<Cell> cells = tree.CellsAboveThreshold(5);
    for (auto cell : cells) {
        auto edges = cell.getEdges(5);
        std::cout << "{" << cell.pos.x << ", " << cell.pos.y << "}, ";
        
    }
    return 0;
}