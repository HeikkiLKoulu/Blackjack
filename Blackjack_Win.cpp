#include <iostream>  
#include <random>
#include <windows.h>
#include <vector>

class GameParticipant 
{
    public:
        std::vector<int> cards;
        int points;
        bool stand = false;
};
GameParticipant player;
GameParticipant dealer;
std::string cardP1, cardP2, cardP3, cardP4, cardP5, cardP6, carda = " _____  |A .  || /.\\ ||(_._)||  |  ||____A|", card2 = " _____  |2    ||  ^  ||     ||  ^  ||___ 2|", card3 = " _____  |3    || ^ ^ ||     ||  ^  ||___ 3|", card4 = " _____  |4    || ^ ^ ||     || ^ ^ ||____4|", card5 = " _____  |5    || ^ ^ ||  ^  || ^ ^ ||____5|", card6 = " _____  |6    || ^ ^ || ^ ^ || ^ ^ ||____6|", card7 = " _____  |7    || ^ ^ ||^ ^ ^|| ^ ^ ||____7|", card8 = " _____  |8    ||^ ^ ^|| ^ ^ ||^ ^ ^||____8|", card9 = " _____  |9    ||^ ^ ^||^ ^ ^||^ ^ ^||____9|", card10 = " _____  |10^  ||^ ^ ^||^ ^ ^||^ ^ ^||___10|", cardj = " _____  |J  ww|| ^ {)||(.)%%|| | % ||__%%J|", cardq = " _____  |Q  ww|| ^ {(||(.)%%|| |%%%||_%%%Q|", cardk = " _____  |K  WW|| ^ {)||(.)%%|| |%%%||_%%%K|", cardque = " _____  |?    ||     ||     ||     ||____?|";
enum winCase 
{
    playerWin,
    dealerWin,
    playerBust,
    dealerBust,
    playerBlackjack,
    dealerBlackjack,
    standoff,
    nothing
};
// Draws one random card for the player, and add the card to the players total card value and array of cards
GameParticipant drawCard(GameParticipant target){
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> card(1,13);

    int cardNumber = card(rng);

    switch (cardNumber) 
    {
        case 1:
            target.cards.push_back(1);
            if (target.points <= 10) {
                target.points += 11;
            } 
            else {
                target.points += 1;
            }
            break;
        case 11:
            target.cards.push_back(11);
            target.points += 10;
            break;
        case 12:
            target.cards.push_back(12);
            target.points += 10;
            break;
        case 13: 
            target.cards.push_back(13);
            target.points += 10;
            break;
        default:
            target.cards.push_back(cardNumber);
            target.points += cardNumber;
            break;
    };
    return target;
}

// Checks if the player or dealer has busted, depending on the input
bool bust(GameParticipant target) 
{
    if (target.points > 21) 
    {
        return true;
    } 
    else 
    {
        return false;
    }
    return false;
}
// Checks if target has a blackjack
bool blackjack(GameParticipant target) 
{
    if (target.cards.size() > 1)
    {
        if (target.cards[0] == 1 && target.cards[1] >= 10) 
        {
            return true;
        }
        else if (target.cards[0] >= 10 && target.cards[1] == 1) 
        {
            return true;
        }
        return false;
    }else 
    {
        return false;
    }
}
// Checks if the game has ended
winCase returnHowSomebodyWon() 
{
    if (blackjack(player) == true) 
    {   
        dealer = drawCard(dealer);
        if (blackjack(dealer) == false)
        {
            return playerBlackjack;
        } else 
        {
            return standoff;
        }
    }
    if (blackjack(player) == false && blackjack(dealer) == true) 
    {
        return dealerBlackjack;
    }
    else if (bust(dealer) == true) 
    {
        return dealerBust;
    }
    else if (bust(player) == true) 
    {
        return playerBust;
    }
    else if (bust(player) == false && dealer.points < player.points && dealer.points >= 17) 
    {
        return playerWin;
    }
    else if (player.points < dealer.points && player.stand == true and dealer.points >= 17 and bust(dealer) == false) 
    {
        return dealerWin;
    }
    else if (player.points == dealer.points && player.stand == true && dealer.points >= 17) 
    {
        return standoff;
    }
    return nothing;
}
// Returns if target has lost
bool hasLost(std::string input)
{
    if (input == "player")
    {
        if (returnHowSomebodyWon() == playerBust || returnHowSomebodyWon() == dealerWin || returnHowSomebodyWon() == dealerBlackjack)
        {
            return true;
        } 
        else
        {
            return false;
        }
    }
    else if (input == "dealer")
    {
        if (returnHowSomebodyWon() == dealerBust || returnHowSomebodyWon() == playerWin || returnHowSomebodyWon() == playerBlackjack)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}
// Checks if Somebody has won
bool somebodyHasWon()
{
    if (returnHowSomebodyWon() != nothing)
    {
        return true;
    } 
    else
    {
        return false;
    }
}

// Prints a card

void printCards(std::vector<std::string> cards)
{
    for (int i = 0; i < 37; i += 7)
    {
        for (int j = 0; j < cards.size(); j++)
        {
            std::cout << cards[j].substr(i, 7);
        }
        std::cout << '\n';
        if (i == 0) {i++;}
    }
}
// Adds a card to the print queue

void displayCard(std::vector<int> inputCard) 
{
    std::vector<std::string> cards;
    for (int i = 0; i < inputCard.size(); i++) 
    {
        switch (inputCard[i]) 
        {
            case 0:
                cards.push_back(cardque);
                break;
            case 1:
                cards.push_back(carda);
                break;
            case 2:
                cards.push_back(card2);
                break;
            case 3:
                cards.push_back(card3);
                break;
            case 4:
                cards.push_back(card4);
                break;
            case 5:
                cards.push_back(card5);
                break;
            case 6:
                cards.push_back(card6);
                break;
            case 7:
                cards.push_back(card7);
                break;
            case 8:
                cards.push_back(card8);
                break;
            case 9:
                cards.push_back(card9);
                break;
            case 10:
                cards.push_back(card10);
                break;
            case 11:
                cards.push_back(cardj);
                break;
            case 12:
                cards.push_back(cardq);
                break;
            case 13:
                cards.push_back(cardk);
                break;
            default:
                break;
        }
    }
    printCards(cards);
}

// Changes the color of the console when needed

void changeConsoleColor(std::string input)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (input == "white")
    {
        SetConsoleTextAttribute(hConsole, 15);
        return;
    }
    if (somebodyHasWon() == false)
    {
        SetConsoleTextAttribute(hConsole, 15);
    }
    else if (hasLost(input) == false)
    {
        SetConsoleTextAttribute(hConsole, 2);
    }
    else 
    {
        SetConsoleTextAttribute(hConsole, 4);
    }
}

// Prints out the game

void displayGame() 
{
    changeConsoleColor("white");
    std::cout << "-----------------------\n";
    changeConsoleColor("dealer");
    std::cout << dealer.points << '\n';
    displayCard(dealer.cards);
    std::cout << '\n';

    changeConsoleColor("white");
    std::cout << "-----------------------\n";
    changeConsoleColor("player");
    std::cout << player.points << '\n';
    displayCard(player.cards);
    std::cout << '\n';
}
// Prints game result
void printResult(winCase result)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
    switch (result)
    {
        case nothing:
            break;
        case playerWin:
            std::cout << "-----------------------\nYou won with " << player.points << " points!\n" << "-----------------------\n";
            break;
        case dealerWin:
            std::cout << "-----------------------\nDealer won with " << dealer.points << " points!\n"<< "-----------------------\n";
            break;
        case playerBust:
            std::cout << "-----------------------\nPlayer went bust!\n-----------------------\n" ;
            break;
        case dealerBust:
            std::cout << "-----------------------\nDealer went bust!\n-----------------------\n";
            break;
        case playerBlackjack:
            std::cout << "-----------------------\nPlayer won with blackjack!\n-----------------------\n";
            break;
        case dealerBlackjack:
            std::cout << "-----------------------\nDealer won with blackjack!\n-----------------------\n";
            break;
        case standoff:
            std::cout << "-----------------------\nStandoff!\n-----------------------\n";
            break;
        default:
            break;
    }
}
// displays the game
void clearAndDisplayGame()
{
    system("cls");
    displayGame();
}
// Resets values of the game
void resetGame()
{
    player.stand = false;
    dealer.stand = false;
    player.cards.clear();
    dealer.cards.clear();
    dealer.points = 0;
    player.points = 0;
}
// Sets up the game by giving out cards
void setup()
{
    dealer = drawCard(dealer);
    player = drawCard(player);
    player = drawCard(player);
    dealer.cards.push_back(0);
    clearAndDisplayGame();
}
// Makes the player draw cards until they stand
void playerHitOrStandLoop()
{
    char input1;
    while (true)
    {
        if (somebodyHasWon() == true)
        {
            Sleep(1000);
            break;
        }
        std::cout << "(S)tand or (H)it: ";
        std::cin >> input1;
        if (input1 == 's' || input1 == 'S')
        {
            player.stand = true;
            break;
        } 
        else if (input1 == 'h' || input1 == 'H')
        {
            player = drawCard(player);
            system("cls");
            displayGame();
        }
    }
}
// Makes the dealer draw cards
void dealerDrawCardsLoop() 
{
    dealer.cards.erase(std::next(dealer.cards.begin()));

    while (somebodyHasWon() == false)
    {
        dealer = drawCard(dealer);
        clearAndDisplayGame();
        Sleep(1000);
        if (dealer.points > 16) {dealer.stand = true;}
    }
}
// Finishes the game and resets it
void endgame()
{  
    system("cls");
    printResult(returnHowSomebodyWon());
    Sleep(1000);
    resetGame();
}

// The games loop

int main () 
{
    while (true)
    {
        setup();
        playerHitOrStandLoop();
        if (somebodyHasWon() == true)
        {
            goto endGame;
        }
        dealerDrawCardsLoop();
        endGame: 
            endgame();
    }
}