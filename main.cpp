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
static const int gameBoardSize = 12;

static const string alphabet = "abcdefghijklmnopqrstuvwxyz";

char poprzedniRuch[gameBoardSize][gameBoardSize];

void skopiujWartosci(char t1[gameBoardSize][gameBoardSize], char t2[gameBoardSize][gameBoardSize]){
    for (int i = 0; i < gameBoardSize; i++){
        for (int j = 0; j < gameBoardSize; j++){
            t1[i][j] = t2[i][j];
        }
    }
}

void rysujSkrajnyRzad(){
    cout<<" ";
    for (int i = 0; i < gameBoardSize*2 + 5; ++i) {
        cout<<"-";
    }
    cout<< " "<<endl;
}

void tabela(char t[gameBoardSize][gameBoardSize]){

    //pierwszy rząd poziomy
    rysujSkrajnyRzad();

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
    rysujSkrajnyRzad();
}

bool pobierz(char t[gameBoardSize][gameBoardSize], int & kto, char znak1, char znak2){
    char poz[2];
    if(!(kto%2))
        cout<<"Kolko, ";
    else
        cout<<"Krzyzyk, ";
    do{
        cout<<"Podaj pozycje, ktora zaznaczyc (np. a1): "<<endl;
        cin>>poz;

        //cofanie ruchu
        if(poz[0]=='q') {
            skopiujWartosci(t, poprzedniRuch);
            return true;
        }
    }while((poz[0]<'a' || poz[0]>(char)alphabet[gameBoardSize]) || (poz[1]<'1' || poz[1]>(char)gameBoardSize));

    if(t[poz[1]-'1'][poz[0]-'a']!=' '){
        cout<< endl <<"Pole "<<poz<<" bylo juz uzupelnione."<<endl;
        return pobierz(t, kto, znak1, znak2);
    }

    if(!(kto++%2))
        t[poz[1]-'1'][poz[0]-'a']=znak1;
    else
        t[poz[1]-'1'][poz[0]-'a']=znak2;

    return true;
}

bool rozwiazanie(char t[gameBoardSize][gameBoardSize]){
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

bool postawWRogu(char t[gameBoardSize][gameBoardSize]){
    bool ruchZrobiony = false;
    if(t[0][0] == 'O'){
        if(t[0][2] == ' ' && t[0][1] == ' '){
            t[0][2] = 'O';
            ruchZrobiony = true;
        }else if(t[2][0] == ' ' && t[1][0] == ' '){
            t[2][0] = 'O';
            ruchZrobiony = true;
        }
    }else if(t[0][2] == 'O'){
        if(t[0][0] == ' ' && t[0][1] == ' '){
            t[0][0] = 'O';
            ruchZrobiony = true;
        }else if(t[2][2] == ' ' && t[1][2] == ' '){
            t[2][2] = 'O';
            ruchZrobiony = true;
        }
    }else if(t[2][0] == 'O'){
        if(t[0][0] == ' ' && t[1][0] == ' '){
            t[0][0] = 'O';
            ruchZrobiony = true;
        }else if(t[2][2] == ' ' && t[2][1] == ' '){
            t[2][2] = 'O';
            ruchZrobiony = true;
        }
    }else if(t[2][2] == 'O'){
        if(t[0][2] == ' ' && t[1][2] == ' '){
            t[0][2] = 'O';
            ruchZrobiony = true;
        }else if(t[2][0] == ' ' && t[2][1] == ' '){
            t[2][0] = 'O';
            ruchZrobiony = true;
        }
    }else if(t[0][0] == 'X' && t[2][0] == 'X' && t[0][2] == 'X' && t[2][2] == 'X'){
        ruchZrobiony = false;
    }else{
        while(!ruchZrobiony){
            int random = rand() % 4 + 1;
            if(random == 1 && t[0][0] == ' '){
                t[0][0] = 'O';
                ruchZrobiony = true;
            }else if(random == 2 && t[0][2] == ' '){
                t[0][gameBoardSize - 1] = 'O';
                ruchZrobiony = true;
            }else if(random == 3 && t[2][0] == ' '){
                t[2][0] = 'O';
                ruchZrobiony = true;
            }else if(random == 4 && t[2][2] == ' '){
                t[2][2] = 'O';
                ruchZrobiony = true;
            }
        }
    }
    return ruchZrobiony;
}

bool koncz(char t[gameBoardSize][gameBoardSize], char znak){
    int vertical = 0, horizontal = 0, diagonal = 0;
    int blankVertical = 0, blankHorizontal = 0, blankDiagonal = 0;
    int blankVerticalPoz = 0, blankHorizontalPoz = 0, blankDiagonalPoz = 0;
    for (int i = 0; i < gameBoardSize; ++i) {
        for (int j = 0; j < gameBoardSize; ++j) {
            if(t[i][j] == znak){
                horizontal++;
            }else if(t[i][j] == ' '){
                blankHorizontal++;
                blankHorizontalPoz = j;
            }

            if(t[j][i] == znak){
                vertical++;
            }else if(t[j][i] == znak){
                blankVertical++;
                blankVerticalPoz = j;
            }
        }
        if(t[i][i] == znak){
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
    bool ruchZrobiony = false;
    while(!ruchZrobiony){
        int randomX = rand() % gameBoardSize;
        int randomY = rand() % gameBoardSize;

        if(t[randomY][randomX] == ' '){
            t[randomY][randomX] = 'O';
            ruchZrobiony = true;
        }
    }

}

void AdvancedAI(char t[gameBoardSize][gameBoardSize], int ruch){
        if(ruch < 3){
            postawWRogu(t);
        }else{
            if(!koncz(t, 'O'))
                if(!koncz(t, 'X'))
                    if(!postawWRogu(t))
                        randomMoves(t);
        }
}

int main(){
    srand(time(NULL));

    char tab[gameBoardSize][gameBoardSize];
    for(int i=0; i<gameBoardSize; i++) for(int j=0; j<gameBoardSize; tab[i][j++]=' ');
    skopiujWartosci(poprzedniRuch, tab);
    int kto = 0;
    int ruch = 1;
    bool koniec=false;

    int poziomTrudnosci = 0;

    cout << "Wybierz poziom trudnosci: ";
    cin >> poziomTrudnosci;

    bool AI = true;

    int temp = 0;
    int i = 0;
    while(!koniec) {
        if (i % 2 == 0) {
            skopiujWartosci(poprzedniRuch, tab);
            if (poziomTrudnosci == 0) {
                randomMoves(tab);
            } else if (poziomTrudnosci == 1) {
                if(temp%2 == 0) {
                    randomMoves(tab);
                }else {
                    AdvancedAI(tab, ruch);
                }
                temp++;
            } else if (poziomTrudnosci == 2) {
                AdvancedAI(tab, ruch);
            }
        ruch++;
        kto += 1;

        tabela(tab);
        koniec = rozwiazanie(tab);
        }
        if(i%2 == 1){
            //Mozliwość wyboru znaków do gry
            pobierz(tab, kto, 'O', 'X');
            if(AI){
                tabela(tab);
                cout << "Ruch komputera (nacisnij dowolny klawisz aby kontynuowac)";
                getch();
            }
            koniec=rozwiazanie(tab);
        }
        i++;
    }
    tabela(tab);
    return 0;
}