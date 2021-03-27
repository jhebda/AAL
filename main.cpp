#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <set>
#include <vector>

using namespace std;

int SIZE = 32;

void draw_series(int);            //losuje SIZE cyfr i zapisuje je do pliku
void load_series(list<int> &);    //wczytuje cyfry z pliku do listy
void print_list(list<int> &);     //wypisuje zawartosc listy
list<int> move_4(list<int>, int); //przesuwa cztery kolejne cyfry zaczynajac od podanej pozycji na koniec listy
int find_min(list<int> &, int);   //zwraca pozycje najmniejszej nieposortowana cyfry
bool sort(list<int> &);           //sortuje liste


list<int> to_list(int num)      //zamienia inta na listę pojedyńczych cyfr
{
    list<int> list;
    while (num != 0)
    {
        list.push_front(num % 10);
        num /= 10;
    }
    return list;
}

int to_int(list<int> list)      //zamienia listę cyfr na inta
{
    int num = 0;
    while (!list.empty())
    {
        num = num * 10 + list.front();
        list.pop_front();
    }
    return num;
}

int main()
{
    list<int> list;

    //draw_series(SIZE);
    load_series(list);
    print_list(list);
    cout<<sort(list)<<endl;
/*
    set<int> poss;  //przechowuje permutacje piwrwotnego ciagu
    vector<int> vec;    //przechowuje nowe mozliwe permutacje
    int size = 114322;  //pierwotny ciag, pozniej jego dlugosc
    poss.insert(size);
    vec.push_back(size);
    size = to_list(size).size();

    int counter = 1, tmp;
    while (!vec.empty())
    {
        //getchar();
        tmp = vec.back();
        vec.pop_back();
        for (int i = 0; i < size - 4; i++)  //przechodzi przez wszystkie mozlowe przesunięcia dla danej dlugosci "polki"
            if (poss.find(to_int(move_4(to_list(tmp), i))) == poss.end())   //czy permutacja wystspila wczesniej
            {
                vec.push_back(to_int(move_4(to_list(tmp), i)));
                poss.insert(to_int(move_4(to_list(tmp), i)));
                
                counter++;
            }
    }

    cout << counter << endl;
    for (auto it = poss.begin(); it != poss.end(); it++)
        cout << *it << endl;
*/
    return 0;
}

void draw_series(int howMany)
{
    ofstream myFile("data.txt");

    for (int i = 0; i < howMany; i++)
        myFile << rand() % 4 << " ";

    myFile.close();
}

void load_series(list<int> &numbers)
{
    int num;
    ifstream myFile("data.txt");

    SIZE = 0;

    while (myFile >> num)
    {
        numbers.push_back(num);
        SIZE++;
    }

    myFile.close();
}

void print_list(list<int> &numbers)
{
    for (int i = 0; i < SIZE; i++)
        if (i < 10)
            cout << " " << i << " ";
        else
            cout << i << " ";
    cout << endl;
    for (auto const &i : numbers)
        cout << " " << i << " ";
    cout << endl;
}

list<int> move_4(list<int> numbers, int pos)
{
    if (pos < numbers.size() - 4)
    {
        std::list<int>::iterator b, e;
        b = e = numbers.begin();
        advance(b, pos);
        advance(e, pos + 4);
        numbers.splice(numbers.end(), numbers, b, e);
    }
    else
        cout << "wrong posision: " << pos << endl;
    return numbers;
}

int find_min(list<int> &numbers, int correct)
{
    int min, pos = 0, i = 0;
    std::list<int>::iterator it = numbers.begin();
    advance(it, correct);
    min = *it;
    for (; it != numbers.end(); ++it)
    {
        if (*it < min)
        {
            min = *it;
            pos = i;
        }
        i++;
    }
    return pos;
}

bool sort(list<int> &numbers)
{
    int corr = 0, pos, padd, zs;
    while (corr != SIZE)
    {
        //getchar();
        pos = find_min(numbers, corr);
        if (pos % 4 != 0)
        {
            zs = (SIZE - corr - 1) - (SIZE - corr - 1) / 4 * 4;
            padd = pos - 3 + zs;
            if (padd < 0)
            {
                numbers = move_4(numbers, corr);
            }
            else
            {
                padd = corr + padd;
                if (padd >= SIZE - 4)
                {
                    padd = corr;
                    if (padd >= SIZE - 4)
                        return false;
                }

                 numbers = move_4(numbers, padd);

                for (int i = (SIZE - corr - 1) / 4; i > 0; i--)
                     numbers = move_4(numbers, corr);
                corr++;
            }
        }
        else
        {
            for (int i = pos / 4; i > 0; i--)
                 numbers = move_4(numbers, corr);
            corr++;
        }
        printf("SIZE: %d corr: %d left: %d\n", SIZE, corr, SIZE - corr);
        print_list(numbers);
    }
    return true;
}