#include <vector>
#include <string>
#include <cmath>
#include <set>

struct Position{
    Position(int line, int column);

    std::set<Position> ConnectedCells();

public:
    int line_;
    int column_;
    int index_;
};


Position GetCell(const std::string &num);

Position GetMiddleCell(const Position& from, const Position& to);
