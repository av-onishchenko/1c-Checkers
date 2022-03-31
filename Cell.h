#include <vector>
#include <string>
#include <set>
#include "Positions.cpp"

struct Figure{
    std::string color_ = "empty";
    bool is_damn_ = false;
    bool have_to_eat_ = false;

    Figure(const std::string& color);

    void Clear();
};

struct Cell {
    Cell(int line_, int column_, const std::string& color);

    void UpdateWhite();

    void UpdateAnother();

    void Update();
public:
    std::vector<Cell>* field_;
    Figure figure_;
    Position pos_{0, 0};
    std::set<Position> connected_cells_;
    std::set<Position> eages_front_;
    std::set<Position> eages_back_;
};
