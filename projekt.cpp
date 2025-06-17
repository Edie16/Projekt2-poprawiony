#include <iostream>
#include <cstdlib>
#include <time.h> //ctime
#include <string>
#include <unordered_map>
#include <vector>

//autorzy: Edie Kulik 203578 Aleksander Rorbach 203749 ACiR

using namespace std;

string tab[8][12];

class Samolot
{
public:
    static char literki;
    char literka;
    int kierunek; //0 -z lewej do prawej 1 -z prawej do lewej
    int faza; //(-1 - opadanie 0 - lot stabilny 1 - wznoszenie)
    int ilePol;
    int x, y;
    int czyWzniesc;
    Samolot() : literka(' '), kierunek(0), faza(0), ilePol(0), x(0), y(0), czyWzniesc(0) {}
    void dodaj(string tab[8][12])
    {
        literka = literki;
        if (literki == 'Z') literki = 'A';
        else literki = literki + 1;

        kierunek = rand()%2;
        if(kierunek == 0) x = 0;
        else x = 11;
        bool kolizja;
        int proby;
        do
        {
            kolizja = false;
            y = rand()%8;
            if(x == 0)
            {
                switch(y)
                {
                case 0:
                    if(tab[y][x+1] != "     " || tab[y+1][x+1] != "     " || tab[y][x] != "     " || tab[y+1][x] != "     ") kolizja = true;
                    break;
                case 7:
                    if(tab[y][x+1] != "     " || tab[y-1][x+1] != "     " || tab[y][x] != "     " || tab[y-1][x] != "     ") kolizja = true;
                    break;
                default:
                    if(tab[y-1][x+1] != "     " || tab[y][x+1] != "     " || tab[y+1][x+1] != "     " || tab[y-1][x] != "     " || tab[y][x] != "     " || tab[y+1][x] != "     ") kolizja = true;
                    break;
                }
            }
            if(x == 11)
            {
                switch(y)
                {
                case 0:
                    if(tab[y][x-1] != "     " || tab[y+1][x-1] != "     " || tab[y][x] != "     " || tab[y+1][x] != "     ") kolizja = true;
                    break;
                case 7:
                    if(tab[y][x-1] != "     " || tab[y-1][x-1] != "     " || tab[y][x] != "     " || tab[y-1][x] != "     ") kolizja = true;
                    break;
                default:
                    if(tab[y-1][x-1] != "     " || tab[y][x-1] != "     " || tab[y+1][x-1] != "     " || tab[y-1][x] != "     " || tab[y][x] != "     " || tab[y+1][x] != "     ") kolizja = true;
                    break;
                }
            }
            proby++;
            if (proby > 100) break;
        }
        while(kolizja);

        if (y == 0)
        {
            faza = rand()%2-1;
        }
        else if (y == 7)
        {
            faza = rand()%2;
        }
        else
        {
            faza = rand()%3-1;
        }

        if (faza == 0)
        {
            ilePol = 0;
        }
        else if (faza == -1)
        {
            if (y < 7)
                ilePol = rand() % (7 - y) + 1;
            else
            {
                ilePol = 0;
                faza = 0;
            }
        }
        else
        {
            if (y > 0)
                ilePol = rand() % y + 1;
            else
            {
                ilePol = 0;
                faza = 0;
            }
        }
        czyWzniesc = 0;
    }
    void przesun()
    {
        if (czyWzniesc == 0)
        {
            if(kierunek == 0)
            {
                x=x+1;
            }
            else
            {
                x=x-1;
            }
            if(ilePol != 0) czyWzniesc = 1;
        }
        else
        {
            if(faza == -1)
            {
                y=y+1;
            }
            else
            {
                y=y-1;
            }
            czyWzniesc = 0;
            ilePol = ilePol - 1;
            if (ilePol == 0) faza = 0;

        }
    }
    void DodajDoTablicy(string tab[8][12])
    {
        string symbol;
        if(x == 0|| x == 11)
        {
            tab[y][x] = "    " + string(1, literka);
        }
        else
        {
            if(kierunek == 0)
            {
                symbol = "(" + string(1, literka) + to_string(ilePol) + ")";
                if(faza == -1)
                {
                    symbol = symbol + "\\";
                }
                else if(faza == 0)
                {
                    symbol =  "=" + symbol;
                }
                else
                {
                    symbol = symbol + "/";
                }
                tab[y][x] = symbol;

            }
            else
            {
                symbol = "(" + string(1, literka) + to_string(ilePol) + ")";
                if(faza == -1)
                {
                    symbol = "/" + symbol;
                }
                else if(faza == 0)
                {
                    symbol = symbol + "=";
                }
                else
                {
                    symbol = "\\" + symbol;
                }
                tab[y][x] = symbol;
            }
        }
    }
    void wykonajRozkaz(char typ, int wartosc)
    {
        int faza1 = faza;
        int ilePol1 = ilePol;
        if (typ == '/')
        {
            faza = 1;
            ilePol = wartosc;
        }
        if (typ == '\\')
        {
            faza = -1;
            ilePol = wartosc;
        }
        if (typ == 'c')
        {
            faza = faza1;
            ilePol = ilePol1;
        }
    }

};

char Samolot::literki = 'A';

void wypelnij(string tab[8][12])
{
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<12; j++)
        {
            if(j==0||j==11) tab[i][j]="     ";
            else tab[i][j]="     ";
        }
    }
}

void rysuj(string tab[8][12])
{
    for(int i=1; i<=13; i++)
    {
        cout << "-----";
    }
    cout <<endl;
    for(int i=0; i<8; i++)
    {
        cout << tab[i][0] <<"|";
        for(int j=1; j<11; j++)
        {
            cout << tab[i][j];
        }
        cout <<"|" << tab[i][11] <<endl;
    }
    for(int i=1; i<=13; i++)
    {
        cout << "-----";
    }
}

bool czyKolizja(string tab[8][12])
{
    for(int i=0; i<8; i++)
    {
        for(int j=1; j<11; j++)
        {
            if(tab[i][j] != "     ")
            {
                if(i == 0)
                {
                    if (tab[i][j-1] != "     " || tab[i+1][j-1] != "     " || tab[i+1][j] != "     " || tab[i+1][j+1] != "     " || tab[i][j+1] != "     ") return true;
                }
                else if(i == 7)
                {
                    if (tab[i][j-1] != "     " || tab[i-1][j-1] != "     " || tab[i-1][j] != "     " || tab[i-1][j+1] != "     " || tab[i][j+1] != "     ") return true;
                }
                else
                {
                    if(tab[i-1][j-1] != "     " || tab[i-1][j] != "     " || tab[i-1][j+1] != "     " || tab[i][j+1] != "     " || tab[i+1][j+1] != "     " || tab[i+1][j] != "     " || tab[i+1][j-1] != "     " || tab[i][j-1] != "     " ) return true;
                }
            }
        }
    }
    return false;
}


int main()
{
    srand(time(NULL));
    unordered_map <char, Samolot> samoloty;
    vector <char> do_usuniecia;
    wypelnij(tab);
    string komenda;

    Samolot pierwszy;
    pierwszy.dodaj(tab);
    samoloty[pierwszy.literka] = pierwszy;

    Samolot drugi;
    drugi.dodaj(tab);
    samoloty[drugi.literka] = drugi;

    while (!czyKolizja(tab))
    {
        system("cls");
        wypelnij(tab);

        for (auto& para : samoloty)
        {
            para.second.przesun();

            int kierunek = para.second.kierunek;
            int x = para.second.x;

            if ((kierunek == 0 && x == 11)||(kierunek == 1 && x == 0))
            {
                do_usuniecia.push_back(para.first);
            }
        }

        for (auto& para : samoloty)
        {
            para.second.DodajDoTablicy(tab);
        }

        rysuj(tab);

        if (rand() % 5 == 0 && samoloty.size() < 5)
        {
            Samolot s;
            s.dodaj(tab);
            samoloty[s.literka] = s;
        }

        for (char litera : do_usuniecia)
        {
            samoloty.erase(litera);
        }

        do_usuniecia.clear();

        while(true)
        {
            cout << endl << "Podaj komende: ";
            getline(cin, komenda);

            if (komenda == " ") break;

            if (komenda.length() == 3)
            {
                char l = komenda[0];
                char typ = komenda[1];
                int wartosc = komenda[2] - '0';
                if (samoloty.count(l)) samoloty[l].wykonajRozkaz(typ, wartosc);
            }

            if (komenda.length() == 2)
            {
                char l =komenda[0];
                char typ = komenda [1];
                int wartosc = 0;
                if (samoloty.count(l)) samoloty[l].wykonajRozkaz(typ, wartosc);
            }
        }

    }
    cout << endl << "KOLIZJA! KONIEC GRY.";
    return 0;
}