#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <deque>
#include <Windows.h>

std::pair<int,int> losujJedzenie(const std::deque<std::pair<int,int>>& waz);
void rysujPlansze(const std::deque<std::pair<int,int>>& waz, std::pair<int,int> jedzenie);

int main() {
    srand(time(NULL));
    int kierunek = 3;
    int maxDlugosc = 1;
    std::deque<std::pair<int,int>> waz;
    waz.push_back({5,15});
    std::pair<int,int> jedzenie = losujJedzenie(waz);

    while(true) {
        if (_kbhit()) {
            char klawisz = getch();
            if (klawisz == -32 || klawisz == 224) {
                char strzalka = getch();
                switch(strzalka) {
                    case 72: if(kierunek != 1) kierunek = 0; break;
                    case 80: if(kierunek != 0) kierunek = 1; break;
                    case 75: if(kierunek != 3) kierunek = 2; break;
                    case 77: if(kierunek != 2) kierunek = 3; break;
                }
            } else if (klawisz == 27) break;
        }

        int x = waz.front().first;
        int y = waz.front().second;

        switch(kierunek) {
            case 0: x--; break;
            case 1: x++; break;
            case 2: y--; break;
            case 3: y++; break;
        }

        if (x == 0 || x == 9 || y == 0 || y == 29) {
            std::cout << "Koniec gry - uderzenie w sciane\n";
            break;
        }

        for (auto& cz : waz) {
            if (cz.first == x && cz.second == y) {
                std::cout << "Koniec gry - uderzenie w siebie\n";
                goto KONIEC;
            }
        }

        waz.push_front({x,y});

        if (x == jedzenie.first && y == jedzenie.second) {
            maxDlugosc++;
            jedzenie = losujJedzenie(waz);
        }

        if ((int)waz.size() > maxDlugosc) {
            waz.pop_back();
        }

        system("cls");
        rysujPlansze(waz, jedzenie);
        Sleep(150);
    }
KONIEC:
    return 0;
}

void rysujPlansze(const std::deque<std::pair<int,int>>& waz, std::pair<int,int> jedzenie) {
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 30; j++) {
            if (i == 0 || i == 9 || j == 0 || j == 29) {
                std::cout << "#";
            } else if (i == jedzenie.first && j == jedzenie.second) {
                std::cout << "*";
            } else {
                bool czyWaz = false;
                for (auto& cz : waz) {
                    if (cz.first == i && cz.second == j) {
                        std::cout << "O";
                        czyWaz = true;
                        break;
                    }
                }
                if (!czyWaz)
                    std::cout << " ";
            }
        }
        std::cout << "\n";
    }
}

std::pair<int,int> losujJedzenie(const std::deque<std::pair<int,int>>& waz) {
    int x, y;
    bool kolizja;
    do {
        kolizja = false;
        x = (rand() % 8) + 1;
        y = (rand() % 28) + 1;
        for (auto& cz : waz) {
            if (cz.first == x && cz.second == y) {
                kolizja = true;
                break;
            }
        }
    } while (kolizja);
    return {x, y};
}
