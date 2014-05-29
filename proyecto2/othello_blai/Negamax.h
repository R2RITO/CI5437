#include "othello_cut.h"
#include <iostream>
#include <climits>

class Negamax_ {

public:

    int Negamax(state_t state, int depth, bool color) {

        //std::cout << "PROFUNDIDAD: " << depth << std::endl;// << state;

        if (state.terminal() || depth == 0) {
            return (color ? 1 : -1) * state.value();
        }

        int value = INT_MIN;
        state_t children;
        int res_negamax = 0;
        bool tmp = false;
        //std::cout << "Empece negamax: " << color << std::endl;
        for( int pos = 0; pos < DIM; ++pos ) {
            if((color && state.is_black_move(pos))||(!color && state.is_white_move(pos))) {
                tmp = true;
                children = state.move(color,pos);
                res_negamax = (-1) * Negamax(children,depth-1,!color);
                //std::cout << "COMPARO: " << value << " con : " << res_negamax << std::endl;
                value = (value >= res_negamax) ? value : res_negamax;
                //std::cout << "Me quede con: " << value << std::endl;
                
            }
        }

        if (!tmp) {
            value = (-1) * Negamax(state, depth-1, !color);
        }

        return value;
    }


};
