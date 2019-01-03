#include "cell.h"
#include "Utility.h"

Cell::Cell(std::shared_ptr< std::vector< std::vector<double> > > data, vec2<int> pos) : data(data), pos(pos)
{
}

std::map<Direction, Edge> Cell::getEdges(double thresh)
{
    std::map<Direction, Edge> edges;
    std::vector< std::vector< double> >& img = *data;
    double tl = img[pos.y+1][pos.x];
    double tr = img[pos.y+1][pos.x+1];
    double br = img[pos.y][pos.x+1];
    double bl = img[pos.y][pos.x];

    int bl_in = bl >= thresh ? 0 : 1;
    int br_in = br >= thresh ? 0 : 1;
    int tl_in = tl >= thresh ? 0 : 1;
    int tr_in = tr >= thresh ? 0 : 1;

    int type = bl_in | (br_in << 1) | (tr_in << 2) | (tl_in << 3);

    double top = Utility::reverseInterpolate(tl, tr, thresh);
    double right = Utility::reverseInterpolate(br, tr, thresh);
    double left = Utility::reverseInterpolate(bl, tl, thresh);
    double bottom = Utility::reverseInterpolate(bl, br, thresh);
    double center = Utility::centerValue(tl, tr, br, bl);

    switch(type) {
        case 1:
            edges[Direction::bottom] = {
                .nextEntry = Direction::right,
                .delta = {-1, 0},
                .path = {
                    {bottom, 0}, 
                    {0, left}
                }
            };
            break;
        case 2:
            edges[Direction::right] = {
                .nextEntry = Direction::top,
                .delta = {0, -1},
                .path = {
                    {1, right}, 
                    {bottom, 0}
                }
            };
            break;
        case 3:
            edges[Direction::right] = {
                .nextEntry = Direction::right,
                .delta = {-1, 0},
                .path = {
                    {1, right}, 
                    {0, left}
                }
            };
            break;
        case 4:
            edges[Direction::top] = {
                .nextEntry = Direction::left,
                .delta = {1, 0},
                .path = {
                    {top, 1}, 
                    {1, right}
                }
            };
            break;
        case 5:
            if (center >= thresh) {
                edges[Direction::top] = {
                    .nextEntry = Direction::left,
                    .delta = {1, 0},
                    .path = {
                        {top, 1}, 
                        {1, right}
                    }
                };
                edges[Direction::bottom] = {
                    .nextEntry = Direction::right,
                    .delta = {-1, 0},
                    .path = {
                        {bottom, 0}, 
                        {0, left}
                    }
                };
            }
            else {
                edges[Direction::top] = {
                    .nextEntry = Direction::right,
                    .delta = {-1, 0},
                    .path = {
                        {top, 1}, 
                        {0, left}
                    }
                };
                edges[Direction::bottom] = {
                    .nextEntry = Direction::left,
                    .delta = {1, 0},
                    .path = {
                        {bottom, 0}, 
                        {1, right}
                    }
                };
            }
            break;
        case 6:
            edges[Direction::top] = {
                .nextEntry = Direction::top,
                .delta = {0, -1},
                .path = {
                    {top, 1}, 
                    {bottom, 0}
                }
            };
            break;
        case 7:
            edges[Direction::top] = {
                .nextEntry = Direction::right,
                .delta = {-1, 0},
                .path = {
                    {top, 1}, 
                    {0, left}
                }
            };
            break;
        case 8:
            edges[Direction::left] = {
                .nextEntry = Direction::bottom,
                .delta = {0, 1},
                .path = {
                    {0, left}, 
                    {top, 1}
                }
            };
            break;
        case 9:
            edges[Direction::bottom] = {
                .nextEntry = Direction::bottom,
                .delta = {0, 1},
                .path = {
                    {bottom, 0}, 
                    {top, 1}
                }
            };
            break;
        case 10:
            if (center >= thresh) {
                edges[Direction::right] = {
                    .nextEntry = Direction::top,
                    .delta = {0, -1},
                    .path = {
                        {1, right}, 
                        {bottom, 0}
                    }
                };
                edges[Direction::left] = {
                    .nextEntry = Direction::bottom,
                    .delta = {0, 1},
                    .path = {
                        {0, left}, 
                        {top, 1}
                    }
                };
            }
            else {
                edges[Direction::right] = {
                    .nextEntry = Direction::bottom,
                    .delta = {0, 1},
                    .path = {
                        {1, right}, 
                        {top, 1}
                    }
                };
                edges[Direction::left] = {
                    .nextEntry = Direction::top,
                    .delta = {0, -1},
                    .path = {
                        {0, left}, 
                        {bottom, 0}
                    }
                };
            }
            break;
        case 11:
            edges[Direction::right] = {
                .nextEntry = Direction::bottom,
                .delta = {0, 1},
                .path = {
                    {1, right}, 
                    {top, 1}
                }
            };
            break;
        case 12:
            edges[Direction::left] = {
                .nextEntry = Direction::left,
                .delta = {1, 0},
                .path = {
                    {0, left},
                    {1, right}
                }
            };
            break;
        case 13:
            edges[Direction::bottom] = {
                .nextEntry = Direction::left,
                .delta = {1, 0},
                .path = {
                    {bottom, 0}, 
                    {1, right}
                }
            };
            break;
        case 14:
            edges[Direction::left] = {
                .nextEntry = Direction::top,
                .delta = {0, -1},
                .path = {
                    {0, left},
                    {bottom, 0}
                }
            };
            break;
    }

    return edges;
}