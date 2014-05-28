#include "othello_cut.h"
#include <iostream>
#include <climits>

class Negamax_ {

public:

    int Negamax(state_t state, int depth, bool color) {

        if (state.terminal() || depth == 0) {
            return state.value();
        }

        int value = INT_MIN;
        state_t children;
        int res_negamax = 0;

        for( int pos = 0; pos < DIM; ++pos ) {
            if((color && state.is_black_move(pos))||(!color && state.is_white_move(pos))) {
                children = state.move(color,pos);
                res_negamax = (-1) * Negamax(children,depth-1,!color);
                value = (value >= res_negamax) ? value : res_negamax;
            }
        }
        return value;
    }


};