#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <cstdint>
typedef unsigned int uint;
using namespace std;

struct card
{
    string name; // AT
    uint value;  // 13
};
class Player
{
private:
    vector<int> _stack;
    vector<card> _hand;

public:
    Player(vector<card>& deck);
    ~Player();
    void draw_card(vector<card>& deck);
    uint hand_size();
    uint stack_size();
    void fill_stack();
    bool check_hand(uint cardValue);
    bool check_stack(uint cardValue);
    void take_card(card playCard);
    inline card operator[](uint i) const
    {
        return _hand[i];
    }
    inline uint operator()(uint i) const
    {
        return _stack[i];
    }
    card giveCard(uint cardValue);
};
uint Player::stack_size()
{
    return _stack.size();
}
uint Player::hand_size()
{
    return uint(_hand.size());
}
void Player::draw_card(vector<card>& deck)
{
    _hand.push_back(deck.at(deck.size() - 1));
    deck.pop_back();
}
Player::Player(vector<card>& deck)
{
    for (uint i = 0; i < 7; i++)
    {
        draw_card(deck);
    }
}
Player::~Player()
{
    while (hand_size())
    {
        _hand.pop_back();
    }
}
card Player::giveCard(uint cardValue)
{
    for (uint i = 0; i < _hand.size(); i++)
    {
        if (_hand[i].value == cardValue)
        {
            card tempVariable = _hand[i];
            _hand[i] = _hand[_hand.size() - 1];
            _hand.pop_back();
            return tempVariable;
        }
    }
}
void Player::take_card(card playCard)
{
    _hand.push_back(playCard);
}
bool Player::check_hand(uint cardValue)
{
    for (uint i = 0; i < _hand.size(); i++)
    {
        if (_hand[i].value == cardValue)
            return true;
    }
    return false;
}
bool Player::check_stack(uint cardValue)
{
    for (uint i = 0; i < _stack.size(); i++)
    {
        if (_stack[i] == cardValue)
            return true;
    }
    return false;
}
void Player::fill_stack()
{
    for (uint i = 2; i < 15 && !check_stack(i); i++)
    {
        uint count = 0;
        for (uint j = 0; j < hand_size(); j++)
        {
            if (_hand[j].value == i)
                count++;
            if (count == 4)
            {
                for (uint k = 0; k < 4; k++)
                {
                    giveCard(i);
                }
                _stack.push_back(i);
                cout << "Dodano do stosu: " << _stack[stack_size() - 1] << endl;
            }
        }
    }
}
void display_creators()
{
    cout << "######  ZADANIE10 ########" << endl;
    cout << "##########################" << endl;
    cout << "####JEDRZEJ BORKOWSKI#####" << endl;
    cout << "##########188943##########" << endl;
    cout << "##########################" << endl;
    cout << "##########################" << endl;
    cout << "####JAKUB DRASZKIEWICZ####" << endl;
    cout << "##########193732##########" << endl;
    cout << "##########################" << endl
        << endl;
}
uint menu()
{
    uint choice;
    display_creators();
    cout << "Game Menu" << endl;
    cout << "1. <--- New game" << endl;
    cout << "2. <--- Exit" << endl;
    do
    {
        cin >> choice;
    } while (choice < 1 || choice > 2);
    return choice;
}
void take_card(Player& graczZabierajacy, Player& graczOddajacy, uint cardValue)
{
    if (graczOddajacy.check_hand(cardValue) && !graczOddajacy.check_stack(cardValue))
    {
        graczZabierajacy.take_card(graczOddajacy.giveCard(cardValue));
        cout << graczZabierajacy[graczZabierajacy.hand_size() - 1].name << ' ';
        take_card(graczZabierajacy, graczOddajacy, cardValue);
    }
}
int symbolToNumber(char symbol)
{
    int cardValue;
    switch (symbol)
    {
    case '0':
        cardValue = 10;
        break;
    case 'j':
    case 'J':
        cardValue = 11;
        break;
    case 'd':
    case 'D':
        cardValue = 12;
        break;
    case 'k':
    case 'K':
        cardValue = 13;
        break;
    case 'a':
    case 'A':
        cardValue = 14;
        break;
    default:
        cardValue = symbol - '0';
        break;
    }
    return cardValue;
}
void generate_random_deck(vector<card>& deck)
{
    const string mapColors[] = { "P", "T", "k", "K" }; // pik/trefl/karo/kier
    card randomCard;
    for (uint i = 2; i <= 10; i++)
    {
        for (uint j = 0; j < 4; j++)
        {
            randomCard.name = to_string(i);
            randomCard.name.append(mapColors[j]);
            randomCard.value = i;
            deck.push_back(randomCard);
        }
    }
    const string mapFigures[] = { "J", "D", "K", "A" };
    for (uint i = 0; i < 4; i++)
    {
        for (uint j = 0; j < 4; j++)
        {
            randomCard.name = mapFigures[i];
            randomCard.name.append(mapColors[j]);
            randomCard.value = 11 + i;
            deck.push_back(randomCard);
        }
    }

    random_shuffle(deck.begin(), deck.end());
}
void displaySymbolnotValue(int i)
{
    char symbol;
    switch (i)
    {
    case 11:
        symbol = 'J';
        break;
    case 12:
        symbol = 'D';
        break;
    case 13:
        symbol = 'K';
        break;
    case 14:
        symbol = 'A';
        break;
    case 10:
        cout << 10 << " ";
        break;
    default:
        symbol = i + 48;
    }
    if (i != 10)
        cout << symbol << " ";
}
void displayGame(Player& gracz, Player& komputer)
{
    cout << endl
        << "Stosy komputera: ";
    for (int i = 0; i < komputer.stack_size(); i++)
    {
        displaySymbolnotValue(komputer(i));
    }
    cout << endl
        << "Twoje stosy: ";
    for (int i = 0; i < gracz.stack_size(); i++)
    {
        displaySymbolnotValue(gracz(i));
    }
    cout << endl;
    cout << "Twoje karty: ";
    for (uint i = 0; i < gracz.hand_size(); i++)
    {
        cout << gracz[i].name << " ";
    }
    cout << endl
        << "Karty komputera: ";
    for (uint i = 0; i < komputer.hand_size(); i++)
    {
        cout << komputer[i].name << ' ';
    }
}
// string barrier()
// {
//     string inputString{};
//     do
//     {
//         cin >> inputString;
//         if((inputString != "A" && inputString != "K" && inputString != "J" && inputString != "D")){

//         }
//     } while ((inputString != "A" && inputString != "K" && inputString != "J" && inputString != "D"));
//     return inputString;
// }
int gameplay()
{
    vector<card> gameDeck;
    generate_random_deck(gameDeck);
    Player gracz(gameDeck);
    Player komputer(gameDeck);
    do
    {
        displayGame(gracz, komputer);
        cout << endl
            << "Pytaj o: ";
        string cardSymbol;
        uint cardValue = 0;
        card playCard;
        cin >> cardSymbol;
        if (cardSymbol.size() == 2)
            cardValue = 10;
        else
            cardValue = symbolToNumber(cardSymbol[0]);
        if (komputer.check_hand(cardValue))
        {
            do
            {
                cout << "KONPUTER: Dobra trzymaj i tak przegrasz: ";
                take_card(gracz, komputer, cardValue);
                displayGame(gracz, komputer);
                cout << endl
                    << "Następne zapytanie: ";
                cin >> cardSymbol;
                if (cardSymbol.size() == 2)
                    cardValue = 10;
                else
                    cardValue = symbolToNumber(cardSymbol[0]);

            } while (komputer.check_hand(cardValue));
        }

        cout << "KALKULATOR NA STERYDACH: lopsiajucha nie mam takiej karty" << endl;
        gracz.draw_card(gameDeck);

        gracz.fill_stack();
        cardValue = rand() % 12 + 2;
        cout << endl
            << "KONPUTER: Daj " << cardValue << " MALPO NACZELNA" << endl;
        if (gracz.check_hand(cardValue))
        {
            do
            {
                cout << endl
                    << "TY: Dobra masz : ";
                take_card(komputer, gracz, cardValue);
                displayGame(gracz, komputer);
                cardValue = rand() % 12 + 2;
                cout << endl
                    << "A daj mi jeszcze " << cardValue << endl;

            } while (gracz.check_hand(cardValue));
        }

        cout << endl
            << "TY: Nie mam tej karty LESZCZU" << endl;
        komputer.draw_card(gameDeck);

        komputer.fill_stack();

    } while (gameDeck.size() > 0);
    if (komputer.stack_size() > gracz.stack_size())
    {
        cout << "PRZEGRAGLES";
    }
    else if (komputer.stack_size() < gracz.stack_size())
    {
        cout << "WYGRALES";
    }
    else {
        cout << "REMIS";
    }
    cout << endl;
    return 1;
}
int main()
{
    srand(time(NULL));
    uint choice = 0;
    do
    {
        choice = menu();
        if (choice == 1)
        {
            gameplay();
        }
    } while (choice != 2);
    return 0;
}
