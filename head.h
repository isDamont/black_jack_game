//
// Created by Is isDamont on 04.06.2022.
//
#ifndef BL_JA_HEAD_H
#define BL_JA_HEAD_H

#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <algorithm>
#include <Windows.h>
#include <random>
#include <utility>

class Card {
public:
    enum suit{
        Hearts, Spades, Diamonds, Clubs
    };
    enum meaning{  // делить на 10
        regular_card_2 = 20, regular_card_3 = 30, regular_card_4 = 40, regular_card_5 = 50, regular_card_6 = 60,
        regular_card_7 = 70, regular_card_8 = 80, regular_card_9 = 90, regular_card_10 = 100, Jack = 101, Queen = 102,
        King = 103, Ace = 110
    };

    Card(int _meaning, int _suit, bool _position = false);
    void Flip();
    [[nodiscard]] int GetValue() const;
    static int get_meaning(Card *card_col);

//   перегрузка вывода
    [[nodiscard]] int out_operator_meaning() const;
    friend std::ostream& operator<<(std::ostream &out, Card& card_);
//   перегрузка вывода

private:
    int meaning_ = 0;
    bool position = false;
    int suit_ = 0;

};

class Hand {
public:
    Hand();
    void Add(Card* new_card);
    void Clear();
    [[nodiscard]] int GetValue() const;
    void first_card_flip();

protected:
    std::vector<Card*> cards;
};

class GenericPlayer : public Hand{
public:
    GenericPlayer() = default;
    virtual bool IsHitting() = 0;
    bool IsBoosted();
    void Bust();
    void set_name(std::string _name, std::bitset<1> _bot, std::bitset<1> _dealer);
    [[nodiscard]] std::string getName() const;

//   перегрузка вывода
    [[nodiscard]] int out_operator_name_sum();
    friend std::ostream& operator<<(std::ostream &out, GenericPlayer& GenericPlayer_);
//   !перегрузка вывода

    void score_pp();
    void score_zero();
    [[nodiscard]] unsigned get_score() const;
private:
    unsigned score = 0;
    std::string name;
    std::bitset<1> bot;
    std::bitset<1> dealer;
};

class Player : public GenericPlayer{
public:
    explicit Player(std::string _name, std::bitset<1> _bot = 0, std::bitset<1> _dealer = 0);
    bool IsHitting() override; // virtual bool IsHitting() const
    void Win();
    void Lose() const;
    void Push() const;
};

class House : public GenericPlayer{
public:
    bool IsHitting() override; // virtual bool IsHitting() const
    void FlipFirstCard();
};

class Deck : public Hand {
public:
    Deck();
    virtual ~Deck();
    void Populate();
    void Shuffle();
    void Deal(Hand& aHand);
    void AdditionalCards(GenericPlayer& aGenericPlayer);
};

class Game
{
public:
    explicit Game(const std::vector<std::string>& names);
    ~Game();

    void Play(bool new_game);

private:
    Deck m_Deck;
    House m_House;
    std::vector<Player> m_Players;
};

struct Names{
    inline static std::vector<std::string> names;
};

int game_menu(bool next);
void init_game(unsigned type_of_game);

#endif //BL_JA_HEAD_H

