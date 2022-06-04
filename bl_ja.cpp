//
// Created by Is isDamont on 04.06.2022.
//
#include "head.h"

void Card::Flip() {
    if(position){
        position = false;
    }else{
        position = true;
    }
}

Card::Card(int _meaning, int _suit, bool _position ) : meaning_(_meaning), suit_(_suit), position(_position) {}

int Card::GetValue() const {return meaning_/10;}

int Card::get_meaning(Card *card_col) {
    if (card_col->position){
        return 0;
    }else{
    return card_col->meaning_/10;
    }
}

int Card::out_operator_meaning() const {
    if(position){
        std::cout << "XX ";    //regular_card_2 = 20, regular_card_3 = 30, regular_card_4 = 40, regular_card_5 = 50,
       return 0;               //regular_card_6 = 60, regular_card_7 = 70, regular_card_8 = 80, regular_card_9 = 90,
    } else{                    //regular_card_10 = 100, Jack = 101, Queen = 102, King = 103, Ace = 110
        switch(meaning_) {
            case 20:
                std::cout << "Card 2, ";
                break;
            case 30:
                std::cout << "Card 3, ";
                break;
            case 40:
                std::cout << "Card 4, ";
                break;
            case 50:
                std::cout << "Card 5, ";
                break;
            case 60:
                std::cout << "Card 6, ";
                break;
            case 70:
                std::cout << "Card 7, ";
                break;
            case 80:
                std::cout << "Card 8, ";
                break;
            case 90:
                std::cout << "Card 9, ";
                break;
            case 100:
                std::cout << "Card 10, ";
                break;
            case 101:
                std::cout << "Jack, ";
                break;
            case 102:
                std::cout << "Queen, ";
                break;
            case 103:
                std::cout << "King, ";
                break;
            case 110:
                std::cout << "Ace, ";
                break;
            default:
                std::cerr << "Error: __no card__ ";
                return 0;
        }
        switch(suit_){  //Hearts, Spades, Diamonds, Clubs
            case 0:
                std::cout << "Hearts ";
                return GetValue();
            case 1:
                std::cout << "Spades ";
                return GetValue();
            case 2:
                std::cout << "Diamonds ";
                return GetValue();
            case 3:
                std::cout << "Clubs ";
                return GetValue();
            default:
                std::cerr << "Error: __no suit__ ";
        }
    }
   return 0;
}

std::ostream &operator<<(std::ostream &out, Card &card_) {
    out << card_.out_operator_meaning();
    return out;
}


Hand::Hand() = default;

void Hand::Add(Card *new_card) {
    cards.push_back(new_card);
}

void Hand::Clear() {
    cards.clear();
}

int Hand::GetValue() const {
    int sum = 0;
    for (auto & card : cards) {
        if(sum>= 21 && Card::get_meaning(card) == 11){sum = sum + 1;}  // Ace равен 1 при сумме от 21
        else{sum = sum + Card::get_meaning(card);}
    }
    return sum;
}

void Hand::first_card_flip() {
   cards[0]->Flip();
}

void GenericPlayer::set_name(std::string _name, std::bitset<1> _bot, std::bitset<1> _dealer) {
    name = std::move(_name);
    bot = _bot;
    dealer = _dealer;
}

void GenericPlayer::score_pp(){
 score++;
}

unsigned GenericPlayer::get_score() const{
    return score;
}

std::string GenericPlayer::getName() const {
    return name;
}


bool GenericPlayer::IsBoosted() {
    if (GetValue() > 21){
        return true;
    }else{
        return false;
    }
}

void GenericPlayer::Bust() {
    if(IsBoosted()){
    std::cout<< getName() << ", got busted!" << std::endl;
    }else{
        std::cout<< getName() << ", Ok !" <<std::endl;
    }
}

std::ostream &operator<<(std::ostream &out, GenericPlayer &GenericPlayer_) {
    out << GenericPlayer_.out_operator_name_sum();
    return out;
}

int GenericPlayer::out_operator_name_sum() {
    if(dealer==1){std::cout<<"Dealer: " << getName()<< std::endl;}
    else if(bot==1){std::cout<<"Bot: " << getName()<< std::endl;}
    else{std::cout<<"Name: " << getName()<< std::endl;}
    std::cout<<"Cards | Meaning"<<std::endl;
    std::cout<<"---------------"<<std::endl;
    for(auto & card : cards){
     if(card -> out_operator_meaning() == 0){
         std::cout << "| " << "X";
         std::cout<<std::endl;
     }else{
     std::cout << "| " << card -> GetValue();
     std::cout<<std::endl;
     }
    }
    std::cout<<"---------------"<<std::endl;
    std::cout<<"sum total: ";
    return GetValue();
}

void GenericPlayer::score_zero() {
score = 0;
}


bool Player::IsHitting()  {
    int need_a_card;
    std::cout << getName() <<", need one more card? (1 or any numbers - yes, 0 - no): ";
    std::cin >> need_a_card;
    return need_a_card != 0;
}

void Player::Win() {
    score_pp();
    std::cout<< getName() << ", Won!" << std::endl;
    system("pause");

}

void Player::Lose() const {
    std::cout<< getName() << ", Lose!" << std::endl;
    system("pause");
}

void Player::Push() const {
    std::cout<< getName() << ", you have played in a draw!" << std::endl;
    system("pause");
}

Player::Player(std::string _name, std::bitset<1> _bot, std::bitset<1> _dealer) {
    set_name(std::move(_name),_bot,_dealer);
}


void House::FlipFirstCard() {
    first_card_flip();
}

bool House::IsHitting() {
    if (GetValue() <= 16){
        return true;
    }else{
        return false;
    }
}

Deck::Deck(){
    cards.reserve(52);
    Populate();
}
Deck::~Deck() = default;

void Deck::Populate(){
    Clear();
    for (int i = 0; i <= 3; ++i){
        for (int j = 20; j <=110; j=j+10){
            if(j==110){
                Add(new Card(101,i)); //Jack
                Add(new Card(102,i)); //Queen
                Add(new Card(103,i)); //King
            }
            Add(new Card(j,i));
        }
    }
}

void Deck::Shuffle(){
    shuffle(cards.begin(),cards.end(), std::mt19937(std::random_device()()));
}

void Deck::Deal(Hand& Hand_){
    if (!cards.empty()){
        Hand_.Add(cards.back());
        cards.pop_back();
    }
    else{
        std::cout << "Out of cards. Unable to deal.";
    }
}

void Deck::AdditionalCards(GenericPlayer& GenericPlayer_){
    std::cout << std::endl;                        // продолжает раздавать карты до тех пор, пока у игрока не случается
    while (!(GenericPlayer_.IsBoosted())){        // перебор или пока он хочет взять еще одну карту
        if(!GenericPlayer_.IsHitting()){
            break;
        }
        Deal(GenericPlayer_);
        std::cout << GenericPlayer_ << std::endl;
        std::cout << std::endl;
        if (GenericPlayer_.IsBoosted()){
            GenericPlayer_.Bust();
        }
    }
}

/////////Game////////

Game::Game(const std::vector<std::string>& names){  // создает вектор игроков из вектора с именами
    std::vector<std::string>::const_iterator pName;
    for (pName = names.begin(); pName != names.end(); ++pName){
        m_Players.emplace_back(*pName);
    }
   // srand(static_cast<unsigned int>(time(nullptr)));  // запускает генератор случайных чисел
    m_Deck.Populate();
    m_Deck.Shuffle();
}
Game::~Game() = default;

void Game::Play(bool new_game){
    m_House.set_name("Yulia", 0, 1); // Имя Дилера и обозначение
    std::vector<Player>::iterator pPlayer;

    if(new_game){ // если флаг новой игры, обнуляем очки и пересоздаем колоду
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
            pPlayer->score_zero();
        }
        m_Deck.Populate();
        m_Deck.Shuffle();
    }

// таблица с очками
    std::cout<<std::endl;
    std::cout<<"Score:"<<std::endl;
    std::cout<<"-------"<<std::endl;
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
        std::cout<<pPlayer->getName()<<": "<< pPlayer->get_score()<<std::endl;
    }
    std::cout<<"-------"<<std::endl;
    std::cout<<std::endl;
// !таблица с очками

// раздает каждому по две стартовые карты

    for (int i = 0; i < 2; ++i){
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
            m_Deck.Deal(*pPlayer);
        }
        m_Deck.Deal(m_House);
    }
    m_House.FlipFirstCard();  // прячет первую карту дилера
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){  // открывает руки всех игроков
        std::cout << *pPlayer << std::endl;
        std::cout<<std::endl;
    }
    std::cout << m_House << std::endl;  // раздает игрокам дополнительные карты
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
        m_Deck.AdditionalCards(*pPlayer);
    }
    m_House.FlipFirstCard();   // показывает первую карту дилера
    std::cout << std::endl << m_House;
    std::cout << std::endl;
    m_Deck.AdditionalCards(m_House);  // раздает дилеру дополнительные карты
    if (m_House.IsBoosted()){
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){
            if (!(pPlayer->IsBoosted())){
                pPlayer->Win();
                std::cout << std::endl;
            }
        }
    }
    else{
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){    // сравнивает суммы очков
            if (!(pPlayer->IsBoosted())){                                            // всех оставшихся игроков
                if (pPlayer->GetValue() > m_House.GetValue()){                       // с суммой очков дилера
                    pPlayer->Win();
                    std::cout << std::endl;
                }
                else if (pPlayer->GetValue() < m_House.GetValue()){
                    pPlayer->Lose();
                    std::cout << std::endl;
                }
                else{
                    pPlayer->Push();
                }
            }
        }
    }
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer){   // очищает руки всех игроков
        pPlayer->Clear();
    }
    m_House.Clear();
}


int game_menu(bool next){
    std::cout<<"_____________________"<<std::endl;
    std::cout<<"Menu: "<<std::endl;
    if(next){
        std::cout<<"1 - Continue a last game"<<std::endl;
        std::cout<<"2 - Play a new game"<<std::endl;
        std::cout<<"3 - *Play with bot (in developing)"<<std::endl;
        std::cout<<"4 - Quit game"<<std::endl;
        std::cout<<"_____________________"<<std::endl;
    }else{
    std::cout<<"1 - Play a new game"<<std::endl;
    std::cout<<"2 - *Play with bot (in developing)"<<std::endl;
    std::cout<<"3 - Quit game"<<std::endl;
        std::cout<<"_____________________"<<std::endl;
    }
    int type_of_game = 0;
    std::cin>>type_of_game;

    switch(type_of_game) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        default:
            std::cout << "this type of game is not exist yet !!!";
            system("pause");
            return 100;
    }

}

void init_game(unsigned type_of_game){
    unsigned num_of_players = 0;
    if(type_of_game == 1){
        std::cout<<"ver.0.1alpha"<<std::endl;
        std::cout<<"Before we get started, enter a number of players (no more than 7): ";
        std::cin>>num_of_players;
        if(num_of_players > 7){num_of_players=7;}
        std::cout<<std::endl;
        std::cout<<num_of_players<<" -- OK!! sets";
        std::cout<<std::endl;
    Names::names.reserve(num_of_players);
    std::string player;
    unsigned buf = num_of_players;
    while(num_of_players!=0){
        std::cout<<"Enter a name of player "<<buf-num_of_players+1<<": ";
        std::cin>>player;
        Names::names.push_back(player);
        num_of_players--;
        }
        std::cout<<std::endl;
        std::cout<<"Starting game..."<<std::endl;
        std::cout<<std::endl;
        for(auto & name : Names::names){
            std::cout<<"Welcome to game, "<< name <<" !"<<std::endl;
        }
    }
    ///
    if(type_of_game == 2){
        std::cout<<"Game with bots in developing =("<<std::endl;
        system("pause");
    }
    ///
}
