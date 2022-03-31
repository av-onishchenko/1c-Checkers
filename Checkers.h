#include "Cell.cpp"

struct ResultWay{
    int len_;
    std::vector<int> way_;

    ResultWay(int len): len_(len){};
};

class Checkers {
public:
    Checkers(int level);

    std::string PlayerMove(const std::string &from, const std::string &to);

    std::string MyMove();

    std::string CurrentScore() const;
private:
    enum MoveResult {
        incorrect, completed, one_more, win
    };

    bool HaveToEat(const std::string& color);

    void UpdateCells(const std::set<Position>& cells);

    ResultWay MaxWay(bool is_damn, int pos, int parent);

    void MakeMyMove(const std::vector<int>& way);

    void Move(const Position& from, const Position& to, bool is_hard);

    MoveResult HaveToEatCase(const Position& from, const Position& to);

    MoveResult HaveNotEatCase(const Position& from, const Position& to);

    MoveResult WhiteMove(const Position& from, const Position& to);

private:
    std::vector<Cell> field_;
    int level_ = 1;
    int white_score_ = 0;
    int black_score_ = 0;

};