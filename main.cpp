//
// Created by Is isDamont on 04.06.2022.
//
#include "head.h"

int main() {
    bool next = false;
    init_game(1);
    Game G(Names::names);
restart:
    switch (game_menu(next)) {
        case 1:
            if(next){G.Play(false);}
            else{break;}
            break;
        case 2:
            if(next){
                G.Play(true); //запуск с флагом новой игры
            }
            else{
                init_game(2);
                goto restart;
            }
            break;
        case 3:
            if(next){
                init_game(2);
                goto restart;
            }else{
            return 0;
            }
        case 4:
            if(next){
                return 0;
            }else{
                goto restart;
            }
        default:
            goto restart;
    }

    next = true;  // игра начата -> меню изменено для возможности продлить игру после выхода в меню
    G.Play(false);

    unsigned restart=1;
    do{
    std::cout<<"Enter 1 to continue, 2 to go to menu or any other key to quit the game: ";
    std::cin>>restart;
    if(restart == 1) {
        G.Play(false);
    }else if(restart == 2){
        goto restart;
        }
    }while (restart == 1 || restart == 2);

return 0;
}



