#include "othello_cut.h"
#include <iostream>
#include <climits>

class MinMax_ {

public:

    int MinMax(state_t state, int depth) {

        if (state.terminal() || depth == 0) {
            return state.value();
        }

        int value = INT_MAX;
        state_t children;
        int res_maxmin = 0;

        for( int pos = 0; pos < DIM; ++pos ) {
            if(state.is_black_move(pos)) {
                children = state.move(true,pos);
                res_maxmin = MaxMin(children,depth-1);
                value = (value <= res_maxmin) ? value : res_maxmin;
            }
        }
        return value;
    }

    int MaxMin(state_t state, int depth) {

        if (state.terminal() || depth == 0) {
            return state.value();
        }

        int value = INT_MAX;
        state_t children;
        int res_minmax = 0;

        for( int pos = 0; pos < DIM; ++pos ) {
            if(state.is_white_move(pos)) {
                children = state.move(false,pos);
                res_minmax = MinMax(children,depth-1);
                value = (value >= res_minmax) ? value : res_minmax;
            }
        }
        return value;
    }

};
