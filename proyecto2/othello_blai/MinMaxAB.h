#include "othello_cut.h"
#include <iostream>
#include <climits>

class MinMax_ {

public:

    int MinMax(state_t state, int depth, bool player) {

        if (state.terminal() || depth == 0) {
            return state.value();
        }

        int value = INT_MAX;
        state_t children;
        int res_maxmin = 0;

        for( int pos = 0; pos < DIM; ++pos ) {
          
            if((player && state.is_black_move(pos)) || (!player && state.is_white_move(pos))) {
                children = state.move(player,pos);
                res_maxmin = MaxMin(children,depth-1,!player);
                value = (value <= res_maxmin) ? value : res_maxmin;
            }
        }
        
        if (value == INT_MAX) {
            value = MinMax(state, depth-1, !player);
        }

        return value;
    }

    int MaxMin(state_t state, int depth, bool player) {

        if (state.terminal() || depth == 0) {
            return state.value();
        }

        int value = INT_MIN;
        state_t children;
        int res_minmax = 0;

        for( int pos = 0; pos < DIM; ++pos ) {
            if((player && state.is_black_move(pos)) || (!player && state.is_white_move(pos))) {
                children = state.move(player,pos);
                res_minmax = MinMax(children,depth-1,!player);
                value = (value >= res_minmax) ? value : res_minmax;
            }
        }

        if (value == INT_MIN) {
            value = MinMax(state, depth-1, !player);
        }

        return value;
    }

};
