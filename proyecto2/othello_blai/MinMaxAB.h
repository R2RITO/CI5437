#include "othello_cut.h"
#include <iostream>
#include <climits>

class MinMaxAB_ {

public:

    int MinMax(state_t state, int depth, bool player, int alpha, int beta) {

        if (state.terminal() || depth == 0) {
            return state.value();
        }

        int value = INT_MAX;
        int res_maxmin = 0;

        std::vector<state_t> children = state.get_children(state, player);

        for( int pos = 0; pos < children.size(); ++pos ) {
            res_maxmin = MaxMin(children[pos],depth-1,!player, beta, value);
            if (res_maxmin < value) value = res_maxmin;
            if (value >= beta) return value;
        }
        
        if (children.empty()) {
            value = MinMax(state, depth-1, !player, alpha, beta);
        }

        return value;
    }

    int MaxMin(state_t state, int depth, bool player, int alpha, int beta) {

        if (state.terminal() || depth == 0) {
            return state.value();
        }

        int value = INT_MIN;
        int res_minmax = 0;

        std::vector<state_t> children = state.get_children(state, player);

        for( int pos = 0; pos < children.size(); ++pos ) {
            res_minmax = MinMax(children[pos],depth-1,!player, value, alpha);
            if (res_minmax > value) value = res_minmax;
            if (value <= alpha) return value;
        }

        if (children.empty()) {
            value = MinMax(state, depth-1, !player, alpha, beta);
        }

        return value;
    }

};
