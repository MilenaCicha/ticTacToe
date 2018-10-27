#include <string>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "GameTable/GameTable.h"


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



int userPrompt(int tableSize){
    int field;
    do {
        std::cin.clear();
        std::cin.ignore(100,'\n');
        std::cout << "Podaj liczbe od 1 do "<<(tableSize*tableSize)<<"\n";
        showFieldNumbers(tableSize);
    }while (!(std::cin >> field) or field-1 > tableSize*tableSize);
    return field;
}


void move(char letter, GameTable::GameTable &gameTable){

    int field = userPrompt(gameTable.returnTableSize());
    field = field - 1;

    while(!gameTable.validMove(field))
    {
        std::cout<<"Nieprawidlowy ruch. Podaj numer pola na ktorym nie ma zadnego znaku\n";
        field=userPrompt(gameTable.returnTableSize());
        field = field - 1;
    }

    gameTable.returnTable()[field/gameTable.returnTableSize()][field%gameTable.returnTableSize()] = letter;

}

void checkIfNextMove(GameTable::GameTable &gameTable, char playerLetter, bool &nextMoveFound, int &field){
    while(!nextMoveFound && field < gameTable.returnMaxMoves()){
        if(gameTable.validMove(field)){
            gameTable.returnTable()[field/gameTable.returnTableSize()][field%gameTable.returnTableSize()] = playerLetter;
            nextMoveFound = gameTable.winningConditions(playerLetter);
            if(not nextMoveFound){
                gameTable.returnTable()[field/gameTable.returnTableSize()][field%gameTable.returnTableSize()] =' ';
            }

        }
        ++field;
    }
}




void computerMove(char player1Letter, char player2Letter, GameTable::GameTable &gameTable){
    int field = 0;
    bool nextMoveFound = false;

    //SPRAWDZA CZY KOMPUTER MOZE WYGRAC NASTEPNY RUCH
    checkIfNextMove(gameTable,player2Letter,nextMoveFound,field);

    //SPRAWDZA CZY CZLOWIEK MOZE WYGRAC NASTEPNY RUCH - JESLI TAK, KOMPUTER ZAJMUJE MIEJSCE
    if(!nextMoveFound){
//        checkIfNextMove(gameTable,player1Letter,nextMoveFound,field);
        while(!nextMoveFound && field < gameTable.returnMaxMoves()){
            if(gameTable.validMove(field)){
                gameTable.returnTable()[field/gameTable.returnTableSize()][field%gameTable.returnTableSize()] = player1Letter;
                nextMoveFound = gameTable.winningConditions(player1Letter);
                if(not nextMoveFound){
                    gameTable.returnTable()[field/gameTable.returnTableSize()][field%gameTable.returnTableSize()] =' ';
                }
                else{
                    gameTable.returnTable()[field/gameTable.returnTableSize()][field%gameTable.returnTableSize()] = player2Letter;
                }
            }
            ++field;
        }
    }

    //SPRAWDZA NASTEPNA NAJLEPSZA POZYCJE JESLI NIE MA ZWYCIESTWA W NASTEPNYM RUCHU
    if(!nextMoveFound){
        field = 0;

        while(!nextMoveFound && field < gameTable.returnTableSize()) {
            if (gameTable.validMove(field)) {
                for(int row = 0, col = gameTable.returnTableSize()-1; row <  gameTable.returnTableSize(); ++row, --col ) {
                    gameTable.returnTable()[row][col] = player2Letter;
                    nextMoveFound = true;
                }

            } else
                ++field;
        }

    }

}
void game(GameTable::GameTable &gameTable,char player1Letter, char player2Letter,int maxMoves,int playerChoice){

    for (int i = 1; i <= maxMoves; ++i) {
        if (i % 2 == 1){
            std::cout<<std::endl;
            std::cout<<"Tura Gracza 1\n";
            move(player1Letter, gameTable);
        }
        else{
            if(playerChoice == 1){
                std::cout<<std::endl;
                std::cout<<"Tura Gracza 2\n";
                move(player2Letter, gameTable);
            }
            else{
                std::cout<<std::endl;
                std::cout<<"Tura Komputera\n";
                computerMove(player1Letter, player2Letter, gameTable);
            }

        }

        gameTable.showTable();


        if(gameTable.winningConditions(player1Letter)) {
            std::cout << "Wygrywa " << player1Letter << "!\n";
            return;
        }
        if(gameTable.winningConditions(player2Letter)) {
            std::cout << "Wygrywa " << player2Letter << "!\n";
            return;
        }

    }
    if(!gameTable.winningConditions(player1Letter) && !gameTable.winningConditions(player2Letter))
        std::cout<<"Remis!\n";

}
int main(){


    unsigned tableSize;

    char continueGame = 'Y';
    char player1Letter;
    char player2letter;
    int playerChoice;
    std::cout<<"     ------------------------------------------\n";
    std::cout<<"\t"<<"Witaj w grze w kolko i krzyzyk.\t\n";
    std::cout<<"     ------------------------------------------\n";


    std::cout<<"Podaj rozmiar tablicy, jesli chcesz podac rozmiar np 3 x 3 wpisz 3, jesli 4 x 4, podaj 4, itd.\n";
    std::cin>>tableSize;
    GameTable::GameTable gameTable(tableSize);



    do{
        std::cin.clear();
        std::cin.ignore(100,'\n');
        std::cout<<"Czy grasz z druga osoba czy chcesz zagrac z komputerem? Wybierz 1 dla czlowieka lub 2 dla komputera\n";

    }while(!(std::cin >> playerChoice) and playerChoice != 1 and playerChoice != 2);

    do {
        gameTable.fillTable();
        do {
            std::cout << "Wybiera Gracz 1. O czy X?\n";
            std::cin >> player1Letter;
            player1Letter = char(toupper(player1Letter));
        } while (player1Letter != 'X' and player1Letter != 'O');

        if (player1Letter == 'X') {

            if (playerChoice == 1)
            std::cout << "Wybrales X. Gracz 2 gra O.\n";
            else
                std::cout << "Wybrales X. Komputer gra O.\n";
            player2letter = 'O';
        } else if (player1Letter == 'O') {
            if (playerChoice == 1)
            std::cout << "Wybrales O. Gracz 2 gra X.\n";
            else
                std::cout << "Wybrales O. Komputer gra X.\n";
            player2letter = 'X';
        }

        game(gameTable,player1Letter,player2letter,gameTable.returnMaxMoves(),playerChoice);
        std::cout << "Czy chcesz zagrac ponownie? Y/N\n";
        std::cin >> continueGame;
        continueGame = toupper(continueGame);


    }while(continueGame == 'Y');



    std::cout<<"Dziekuje za gre!\n";



}

