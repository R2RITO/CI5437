#include "othello_cut.h"
#include <iostream>
#include <climits>

class Scout_ {

public: 

    long nodosGenerados;

    bool TEST_MAYOR(state_t state, int depth, int value, bool player) {

        if ( depth == 0 || state.terminal()) return (state.value() > value);

        state_t children;   
        bool tmp = false;

        for( int pos = 0; pos < DIM; ++pos ) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                tmp = true;
                children = state.move(player,pos);
                if (player && TEST_MAYOR(children, depth-1, value, !player)) return true;
                if (!player && !TEST_MAYOR(children, depth-1, value, !player)) return false;
            }        
        }

        if (!tmp) {
            return TEST_MAYOR(state,depth-1,value,!player);
        }

        return !player;
    }

    bool TEST_MENOR(state_t state, int depth, int value, bool player) {

        if ( depth == 0 || state.terminal()) return (state.value() < value);

        state_t children;   
        bool tmp = false;
        for( int pos = 0; pos < DIM; ++pos ) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                tmp = true;
                children = state.move(player,pos);
                if (player && !TEST_MENOR(children, depth-1, value, !player)) return false;
                if (!player && TEST_MENOR(children, depth-1, value, !player)) return true;
            }        
        }

        if (!tmp) {
            return TEST_MENOR(state,depth-1,value,!player);
        }

        return player;
    }

    int scout(state_t state, int depth, bool player) {

        nodosGenerados++;

        if ( depth == 0 || state.terminal()) return state.value();

        int pos = 0;
        int value =0;
        state_t children;
        bool tmp = false;
        int partial = 0;

        

        for (pos = 0; pos < DIM; ++pos) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                children = state.move(player,pos);
                value = scout(children,depth-1,!player);
                tmp = true;
                break;
            }
        }
        pos++;
        for (pos; pos < DIM; ++pos) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                children = state.move(player,pos);
                if (player && TEST_MAYOR(children, depth-1, value, !player)) {
                    partial = scout(children, depth-1, !player); 
                    value = (partial > value) ? partial : value;
                } else if (!player && TEST_MENOR(children, depth-1, value, !player)) {
                    partial = scout(children,depth-1, !player);
                    value = (partial < value) ? partial : value;
                }
            }
        }                        

        if (!tmp) {
            value = scout(state,depth-1,!player);
        }

        return value;
    }

};
