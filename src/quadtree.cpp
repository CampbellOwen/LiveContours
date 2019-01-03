#include "quadtree.h"

QuadTree::QuadTree(std::shared_ptr< std::vector< std::vector<double> > > data, vec2<int> pos, vec2<int> delta) : data(data), pos(pos)
{
    std::vector< std::vector<double> >& img = *data;
    int msb_x = 0;
    int msb_y = 0;

    if (delta.x > 1) {
        msb_x = msb(delta.x);
        if ((1 << msb_x) == delta.x) {
            msb_x--;
        }
    }
    if (delta.y > 1) {
        msb_y = msb(delta.y);
        if ((1 << msb_y) == delta.y) {
            msb_y--;
        }
    }

    int new_dx = 1 << msb_x;
    int new_dy = 1 << msb_y;

    if (delta.x == 1 && delta.y == 1) {
        lowerbound = std::min({
            img[pos.y][pos.x], 
            img[pos.y][pos.x+1],
            img[pos.y+1][pos.x],
            img[pos.y+1][pos.x+1]
        });
        upperbound = std::max({
            img[pos.y][pos.x], 
            img[pos.y][pos.x+1],
            img[pos.y+1][pos.x],
            img[pos.y+1][pos.x+1]
        });
        cell = std::make_unique<Cell>(data, pos);
    }
    else {
        a = std::make_unique<QuadTree>(data, pos, vec2<int>{new_dx, new_dy});
        upperbound = a->upperbound;
        lowerbound = a->lowerbound;

        if ((delta.x - new_dx) > 0) {
            b = std::make_unique<QuadTree>(data, vec2<int>{pos.x + new_dx, pos.y}, vec2<int>{delta.x - new_dx, new_dy});
            upperbound = std::max(upperbound, b->upperbound);
            lowerbound = std::min(lowerbound, b->lowerbound);

            if (delta.y - new_dy) {
                c = std::make_unique<QuadTree>(data, vec2<int>{pos.x + new_dx, pos.y + new_dy}, vec2<int>{delta.x - new_dx, delta.y - new_dy});
                upperbound = std::max(upperbound, c->upperbound);
                lowerbound = std::min(lowerbound, c->lowerbound);
            }
        }
        if ((delta.y - new_dy) > 0) {
            d = std::make_unique<QuadTree>(data, vec2<int>{pos.x, pos.y + new_dy}, vec2<int>{new_dx, delta.y - new_dy});
            upperbound = std::max(upperbound, d->upperbound);
            lowerbound = std::min(lowerbound, d->lowerbound);
        }
    }
}

std::vector<Cell> QuadTree::CellsAboveThreshold(int thresh)
{
    std::vector<Cell> cells;
    if (upperbound < thresh) {
        return cells;
    }

    if (!a && !b && !c && !d) {
        cells.push_back(*cell);
    }
    else {
        if (a) {
            std::vector<Cell> extra = a->CellsAboveThreshold(thresh);            
            cells.insert(std::end(cells), std::begin(extra), std::end(extra));
        }
        if (b) {
            std::vector<Cell> extra = b->CellsAboveThreshold(thresh);            
            cells.insert(std::end(cells), std::begin(extra), std::end(extra));
        }
        if (c) {
            std::vector<Cell> extra = c->CellsAboveThreshold(thresh);            
            cells.insert(std::end(cells), std::begin(extra), std::end(extra));
        }
        if (d) {
            std::vector<Cell> extra = d->CellsAboveThreshold(thresh);            
            cells.insert(std::end(cells), std::begin(extra), std::end(extra));
        }
    }

    return cells;
}

std::unique_ptr<Cell>& QuadTree::getCell()
{
    return cell;
}

int QuadTree::msb(int num)
{
    int msb = 0;
    while(num) {
        num = num >> 1;
        msb++;
    }
    return msb-1;
}