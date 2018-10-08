#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>



struct TableStruct{

    int tableSize;
    char** table;
};





void showFieldNumbers(int tableSize)
{
    int counter{1};
    for (int i=1; i<=tableSize; ++i)
    {
        if(counter < 10)
            std::cout<<"  "<<counter;
        else
            std::cout <<" "<< counter;
        counter++;

        for (int j=2; j<=tableSize; ++j)
        {
            std::cout <<std::right<< std::setw(4) << counter;
            counter++;
        }
        std::cout << std::endl;
    }
}

char** fillTable(int tableSize){
    char** table = new char*[tableSize];
    for (int i=0; i<tableSize; ++i)
        table[i] = new char[tableSize+1];

    for(int rows = 0; rows < tableSize; ++rows){
        for(int cols = 0; cols < tableSize; ++cols){
            table[rows][cols]= ' ';

        }
        table[rows][tableSize] = '\0';
    }

    return table;
}
void showTable(TableStruct* gameTable){
    int tableSize = gameTable->tableSize;
    for (int rows = 0; rows < tableSize; ++rows){
        for(int cols =0; cols < tableSize-1; ++cols){
            std::cout<<" "<<gameTable->table[rows][cols]<<" |";
        }
        std::cout<<" "<<gameTable->table[rows][tableSize-1]<<std::endl;
        if(rows < tableSize - 1)
            std::cout<< std::string(4*tableSize-1,'-')<<"\n";
    }
}


void move(char letter, TableStruct* gameTable){

    int tableSize = gameTable->tableSize;
    char** table = gameTable->table;
    int field;
    std::cout<<"Podaj numer od 1 do "<< (tableSize*tableSize)<<", gdzie chcesz umiescic swoj znak\n";
    showFieldNumbers(tableSize);
    std::cin>>field;
    field = field - 1;


    while(table[field/tableSize][field%tableSize] == 'X' or table[field/tableSize][field%tableSize] == 'O'){
        std::cout<<"Nieprawidlowy ruch. Podaj numer pola na ktorym nie ma zadnego znaku\n";
        std::cin>>field;
        field = field - 1;
    }
    table[field/tableSize][field%tableSize] = letter;

}

bool winningConditions(char playerLetter, TableStruct* gameTable){
    int tableSize = gameTable->tableSize;
    char** table = gameTable->table;
    //SPRAWDZA WARUNKI -->
    for(int row = 0; row <tableSize;++row){
        bool allInRowPlayerLetter = table[row][0] == playerLetter;
        for(int col = 1; col < tableSize && allInRowPlayerLetter; ++col){
            allInRowPlayerLetter = table[row][col] == playerLetter;
        }
        if (allInRowPlayerLetter)
            return true;
    }

    //                 ^
    //SPRAWDZA WARUNKI |
    //                 |
    for(int col = 0; col <tableSize;++col){
        bool allInColPlayerLetter = table[0][col] == playerLetter;
        for(int row = 1; row < tableSize && allInColPlayerLetter; ++row){
            allInColPlayerLetter = table[row][col] == playerLetter;
        }
        if (allInColPlayerLetter)
            return true;
    }

    //SPRAWDZA SKOSY
    bool allInCrossPlayerLetter = table[0][0]== playerLetter;
    for(int indeks = 1; indeks < tableSize && allInCrossPlayerLetter; ++indeks)
    {
        allInCrossPlayerLetter = table[indeks][indeks]== playerLetter;
    }
    if(allInCrossPlayerLetter)
        return true;

    allInCrossPlayerLetter = table[0][tableSize-1]== playerLetter;
    for(int row = 1, col = tableSize-2; row < tableSize && allInCrossPlayerLetter; ++row, --col ){
        allInCrossPlayerLetter = table[row][col] == playerLetter;
    }

    return allInCrossPlayerLetter;

}
void game(TableStruct* gameTable,char player1Letter, char player2Letter,int maxMoves){

    for (int i = 1; i <= maxMoves; ++i) {
        if (i % 2 == 1){
            std::cout<<std::endl;
            std::cout<<"Tura Gracza 1\n";
            move(player1Letter, gameTable);
        }
        else{
            std::cout<<std::endl;
            std::cout<<"Tura Gracza 2\n";
            move(player2Letter, gameTable);
        }

        showTable(gameTable);


        if(winningConditions(player1Letter, gameTable)) {
            std::cout << "Wygrywa " << player1Letter << "!\n";
            return;
        }
        if(winningConditions(player2Letter, gameTable)) {
            std::cout << "Wygrywa " << player2Letter << "!\n";
            return;
        }

    }
    if(!winningConditions(player1Letter,gameTable) && !winningConditions(player2Letter,gameTable))
        std::cout<<"Remis!\n";

}
int main(){
    int tableSize{0};
    int maxMoves{0};

    TableStruct gameTable;


    char continueGame = 'Y';
    char player1Letter;
    char player2letter;

    std::cout<<"     ------------------------------------------\n";
    std::cout<<"\t"<<"Witaj w grze w kolko i krzyzyk.\t\n";
    std::cout<<"     ------------------------------------------\n";

    std::cout<<"Podaj rozmiar tablicy, jesli chcesz podac rozmiar np 3 x 3 wpisz 3, jesli 4 x 4, podaj 4, itd.\n";
    std::cin>>tableSize;

    maxMoves = tableSize*tableSize;

    gameTable.tableSize = tableSize;
    gameTable.table = fillTable(maxMoves);

    do {
        gameTable.table = fillTable(maxMoves);
        do {
            std::cout << "Wybiera Gracz 1. O czy X?\n";
            std::cin >> player1Letter;
            player1Letter = char(toupper(player1Letter));
        } while (player1Letter != 'X' and player1Letter != 'O');

        if (player1Letter == 'X') {
            std::cout << "Wybrales X. Gracz 2 gra O.\n";
            player2letter = 'O';
        } else if (player1Letter == 'O') {
            std::cout << "Wybrales O. Gracz 2 gra X.\n";
            player2letter = 'X';
        }

        game(&gameTable,player1Letter,player2letter,maxMoves);
        std::cout << "Czy chcesz zagrac ponownie? Y/N\n";
        std::cin >> continueGame;
        continueGame = toupper(continueGame);


    }while(continueGame == 'Y');

    for(int row = 0; row < tableSize; ++row){
        delete[] gameTable.table[row];
    }
    delete gameTable.table;

    std::cout<<"Dziekuje za gre!\n";



}
