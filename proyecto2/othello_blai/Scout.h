#include "othello_cut.h"
#include <iostream>
#include <climits>

class Scout_ {

    bool TEST(state_t state, int depth, int value, bool player) {

        if ( depth == 0 || state.terminal()) return state.value() > value;

        state_t children;   

        for( int pos = 0; pos < DIM; ++pos ) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                children = state.move(player,pos);
                if (player && TEST(children, depth-1, value, !player)) return true;
                if (!player && !TEST(children, depth-1, value, !player)) return false;
            }        
        }
        return !player;
    }

    int scout(state_t state, int depth, bool player) {

        if ( depth == 0 || state.terminal()) return state.value();

        int pos = 0;
        int value =0;
        state_t children;

        for (pos = 0; pos < DIM; ++pos) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                children = state.move(player,pos);
                value = scout(children,depth-1,!player);
                break;
            }
        }

        for (pos = pos; pos < DIM; ++pos) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                children = state.move(player,pos);
                if (player && TEST(children, depth-1, value, player)) { // ahi va ese player? Ver cuaderno, que es > ???
                    value = scout(children, depth-1, !player); // Es not player?
                } else if (!player && TEST(children, depth-1, value, player)) {
                    value = scout(children,depth-1, !player);
                }
            }
        }
    }

};
