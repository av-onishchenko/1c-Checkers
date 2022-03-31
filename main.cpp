#pragma once

#include <iostream>
#include "Checkers.cpp"


int main(){
    int level;
    std::cout << "Select the level of difficulty(1, 2, 3) " << std::endl;
    std::cin >> level;

    Checkers game(level);

    while(true){
        std::string action;
        std::cout << "Choose an action (move, find out the result, surrender)" << std::endl;
        std::cin >> action;
        if (action == "surrender"){
            std::cout << "Thanks for playing!";
            break;
        }
        if (action == "find out the result"){
            std::cout << game.CurrentScore() << std::endl;
            continue;
        }
        std::cout << "Enter you code " << std::endl;
        std::string to;
        std::string from;
        std::cin >> to >> from;
        std::string result = game.PlayerMove(to, from);
        std::cout << result << std::endl;
        if (result == "You are wining! Congratulations!"){
            break;
        }
        if (result == "Your move is completed. Now it's my tern"){
            std::string my_move_result = game.MyMove();
            std::cout << my_move_result << std::endl;
            if (my_move_result == "You are wining! Congratulations!"){
                break;
            }
        }
    }
}