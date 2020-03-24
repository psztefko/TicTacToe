#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
using namespace std;

/*
 * Do poniższego zadania (gra w kółko i krzyżyk) dodać następujące możliwości:
 *DONE    1. Uwzględnienie remisu (obecnie w przypadku remisu wygrywa ostatni zagrywający -- obecnie kółko).
 *DONE    2. Wybór znaków do grania (zamiast kółka i krzyżyka -- proszę pamiętać, że nie mogą to być dwa identyczne znaki.
 *DONE    3. Zmienna wielkość planszy (wielkość planszy podawana przed kompilacją, w formie stałej globalnej, a więc: const N=wielkość).
 *DONE   4. Gra jednego użytkownika z komputerem (przynajmniej dla ustalonej planszy 3x3).
 *DONE    5. Dodanie poziomów do gry komputera (1. łatwy (losowy), 2. średni (w pewnym procencie losowy), 3. trudny (optymalny)).
 *DONE    6. Dodać możliwość cofnięcia ruchu.
 */



//Wybór wielkości planszy
static const int gameBoardSize = 3;

static const string alphabet = "abcdefghijklmnopqrstuvwxyz";

char previousMove[gameBoardSize][gameBoardSize];



void copyTab(char t1[gameBoardSize][gameBoardSize], char t2[gameBoardSize][gameBoardSize]){
    for (int i = 0; i < gameBoardSize; i++){
        for (int j = 0; j < gameBoardSize; j++){
            t1[i][j] = t2[i][j];
        }
    }
}

void drawExtremeRow(){
    cout<<" ";
    for (int i = 0; i < gameBoardSize*2 + 5; ++i) {
        cout<<"-";
    }
    cout<< " "<<endl;
}

void drawTable(char t[gameBoardSize][gameBoardSize]){

    //pierwszy rząd poziomy
    drawExtremeRow();

    //rząd z nazwami kolumn
    cout<<"|   ";
    for (int i = 0; i < gameBoardSize; ++i) {
    cout<<alphabet[i] << " ";
    }
    cout<<"  |" << endl;

    //wyświetlenie zawartości tablicy
    for (int i = 0; i < gameBoardSize; ++i) {
        cout<<"| " << i + 1 << " ";
        for (int j = 0; j < gameBoardSize; ++j) {
            cout<<t[i][j] << " ";
        }
        cout<<"  |" << endl;
    }

    //ostatni rząd poziomy
    drawExtremeRow();
}

bool getTab(char t[gameBoardSize][gameBoardSize], int & who, char znak1, char znak2){
    char poz[2];
    if(!(who % 2))
        cout<<"Kolko, ";
    else
        cout<<"Krzyzyk, ";
    do{
        cout<<"Podaj pozycje, ktora zaznaczyc (np. a1): "<<endl;
        cin>>poz;

        //cofanie ruchu
        if(poz[0]=='q') {
            copyTab(t, previousMove);
            return true;
        }
    }while((poz[0]<'a' || poz[0]>(char)alphabet[gameBoardSize]) || (poz[1]<'1' || poz[1]>(char)alphabet[gameBoardSize]));

    if(t[poz[1]-'1'][poz[0]-'a']!=' '){
        cout<< endl <<"Pole "<<poz<<" bylo juz uzupelnione."<<endl;
        return getTab(t, who, znak1, znak2);
    }

    if(!(who++ % 2))
        t[poz[1]-'1'][poz[0]-'a']=znak1;
    else
        t[poz[1]-'1'][poz[0]-'a']=znak2;

    return true;
}

bool solution(char t[gameBoardSize][gameBoardSize]){
    int bz=0;
    bool x, y;
    bool p1=true, p2=true;
    for(int i=0; i<gameBoardSize; i++){
        x=true; y=true;
        for(int j=1; j<gameBoardSize; j++){
            if(t[i][j]!=t[i][j-1])
                x=false;
            if(t[j][i]!=t[j-1][i])
                y=false;
            if(t[i][j]==' '){
                bz++;
                x=false;
            }
            if(t[j][i]==' ')
                y=false;
        }
        if(x){
            cout<< endl << "Wygrywa: "<<t[i][0] << endl;
            return true;
        }
        if(y){
            cout<< endl << "Wygrywa: "<<t[0][i] << endl;
            return true;
        }
        if(i<gameBoardSize - 1){
            if(t[i][i]!=t[i+1][i+1] || t[i][i]==' ')
                p1=false;
            if(t[i][gameBoardSize - 1 -i]!=t[i+1][1-i] || t[i][gameBoardSize - 1 -i]==' ')
                p2=false;
        }
    }

    for(int i=0; i<gameBoardSize; i++)
        if(t[i][0]==' ')
            bz++;

    if(bz==0){
        cout<< endl <<"Remis. Plansza jest juz pelna." << endl;
        return true;
    }else if(p1){
        cout<< endl << "Wygrywa: "<<t[0][0] << endl;
        return true;
    }else if(p2){
        cout<< endl << "Wygrywa: "<<t[0][2] << endl;
        return true;
    }
    return false;
}

bool putInCorner(char t[gameBoardSize][gameBoardSize]){
    bool moveMade = false;
    if(t[0][0] == 'O'){
        if(t[0][2] == ' ' && t[0][1] == ' '){
            t[0][2] = 'O';
            moveMade = true;
        }else if(t[2][0] == ' ' && t[1][0] == ' '){
            t[2][0] = 'O';
            moveMade = true;
        }
    }else if(t[0][2] == 'O'){
        if(t[0][0] == ' ' && t[0][1] == ' '){
            t[0][0] = 'O';
            moveMade = true;
        }else if(t[2][2] == ' ' && t[1][2] == ' '){
            t[2][2] = 'O';
            moveMade = true;
        }
    }else if(t[2][0] == 'O'){
        if(t[0][0] == ' ' && t[1][0] == ' '){
            t[0][0] = 'O';
            moveMade = true;
        }else if(t[2][2] == ' ' && t[2][1] == ' '){
            t[2][2] = 'O';
            moveMade = true;
        }
    }else if(t[2][2] == 'O'){
        if(t[0][2] == ' ' && t[1][2] == ' '){
            t[0][2] = 'O';
            moveMade = true;
        }else if(t[2][0] == ' ' && t[2][1] == ' '){
            t[2][0] = 'O';
            moveMade = true;
        }
    }else if(t[0][0] == 'X' && t[2][0] == 'X' && t[0][2] == 'X' && t[2][2] == 'X'){
        moveMade = false;
    }else{
        while(!moveMade){
            int random = rand() % 4 + 1;
            if(random == 1 && t[0][0] == ' '){
                t[0][0] = 'O';
                moveMade = true;
            }else if(random == 2 && t[0][2] == ' '){
                t[0][gameBoardSize - 1] = 'O';
                moveMade = true;
            }else if(random == 3 && t[2][0] == ' '){
                t[2][0] = 'O';
                moveMade = true;
            }else if(random == 4 && t[2][2] == ' '){
                t[2][2] = 'O';
                moveMade = true;
            }
        }
    }
    return moveMade;
}

bool tryToFinish(char t[gameBoardSize][gameBoardSize], char character){
    int vertical = 0, horizontal = 0, diagonal = 0;
    int blankVertical = 0, blankHorizontal = 0, blankDiagonal = 0;
    int blankVerticalPoz = 0, blankHorizontalPoz = 0, blankDiagonalPoz = 0;
    for (int i = 0; i < gameBoardSize; ++i) {
        for (int j = 0; j < gameBoardSize; ++j) {
            if(t[i][j] == character){
                horizontal++;
            }else if(t[i][j] == ' '){
                blankHorizontal++;
                blankHorizontalPoz = j;
            }

            if(t[j][i] == character){
                vertical++;
            }else if(t[j][i] == character){
                blankVertical++;
                blankVerticalPoz = j;
            }
        }
        if(t[i][i] == character){
            diagonal++;
        }else if(t[i][i] == ' ') {
            blankDiagonal++;
            blankDiagonalPoz = i;
        }


        if(vertical == 2 && blankVertical == 1){
            t[blankVerticalPoz][i] = 'O';
            return true;
        }else if(horizontal == 2 && blankHorizontal == 1){
            t[i][blankHorizontalPoz] = 'O';
            return true;
        }else if(diagonal == 2 && blankDiagonal == 1){
            t[blankDiagonalPoz][blankDiagonalPoz] = 'O';
            return true;
        }

        vertical = 0;
        blankVertical = 0;
        horizontal = 0;
        blankHorizontal = 0;
    }

    return false;
}

void randomMoves(char t[gameBoardSize][gameBoardSize]) {
    bool moveMade = false;
    while(!moveMade){
        int randomX = rand() % gameBoardSize;
        int randomY = rand() % gameBoardSize;

        if(t[randomY][randomX] == ' '){
            t[randomY][randomX] = 'O';
            moveMade = true;
        }
    }

}

void AdvancedAI(char t[gameBoardSize][gameBoardSize], int move){
        if(move < 3){
            putInCorner(t);
        }else{
            if(!tryToFinish(t, 'O'))
                if(!tryToFinish(t, 'X'))
                    if(!putInCorner(t))
                        randomMoves(t);
        }
}

int main(){
    srand(time(NULL));

    char tab[gameBoardSize][gameBoardSize];
    for(int i=0; i<gameBoardSize; i++) for(int j=0; j<gameBoardSize; tab[i][j++]=' ');
    copyTab(previousMove, tab);
    int who = 0;
    int move = 1;
    bool end = false;

    int difficultyLevel = 0;

    cout << "Wybierz poziom trudnosci: ";
    cin >> difficultyLevel;

    bool AI = true;

    int temp = 0;
    int i = 0;
    while(!end) {
        if (i % 2 == 0) {
            copyTab(previousMove, tab);
            if (difficultyLevel == 0) {
                randomMoves(tab);
            } else if (difficultyLevel == 1) {
                if(temp%2 == 0) {
                    randomMoves(tab);
                }else {
                    AdvancedAI(tab, move);
                }
                temp++;
            } else if (difficultyLevel == 2) {
                AdvancedAI(tab, move);
            }
        move++;
            who += 1;

            drawTable(tab);
            end = solution(tab);
        }
        if(i%2 == 1){
            //Mozliwość wyboru znaków do gry
            getTab(tab, who, 'O', 'X');
            if(AI){
                drawTable(tab);
                cout << "Ruch komputera (nacisnij dowolny klawisz aby kontynuowac)";
                getch();
            }
            end= solution(tab);
        }
        i++;
    }
    drawTable(tab);
    return 0;
}