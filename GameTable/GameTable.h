#pragma once

namespace GameTable{
class GameTable{

    unsigned tableSize;
    int maxMoves;
    int getMaxMoves();
    char** table ;
public:
    GameTable(unsigned new_tableSize);
    ~GameTable();
    void fillTable();
    void showTable();
    bool validMove(int& field);
    bool winningConditions(const char& playerLetter);
    int returnMaxMoves(){return maxMoves;}
    unsigned returnTableSize(){return tableSize;}
    char** returnTable(){return table;}
};
}

