#include "othello_cut.h"
#include <iostream>
#include <climits>

class AlphaBeta_ {

public:

    unsigned long long nodosGenerados;

    int useAlphaBeta(state_t state, int depth, int alpha, int beta, bool player) {
        nodosGenerados = 0;
        return AlphaBeta(state,depth,alpha,beta,player);
    }


    int AlphaBeta(state_t state, int depth, int alpha, int beta, bool player) {

        nodosGenerados++;

        if (depth == 0 || state.terminal()) {
            return state.value();
        }

        int partial_result = 0;
        state_t children;

        bool tmp = false;

        if (player) {
            for( int pos = 0; pos < DIM; ++pos ) {
                if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                    tmp = true;
                    children = state.move(player,pos);
                    partial_result = AlphaBeta(children, depth-1, alpha, beta, !player);
                    alpha = (alpha >= partial_result) ? alpha : partial_result;
                    if (alpha >= beta) break;
                }
            }
            if (!tmp) { 
                alpha = AlphaBeta(state,depth-1,alpha,beta,!player);
            }    
            return alpha;
        } else {
            for( int pos = 0; pos < DIM; ++pos ) {
                
                if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                    tmp = true;
                    children = state.move(player,pos);
                    partial_result = AlphaBeta(children, depth-1, alpha, beta, !player);
                    beta = (beta <= partial_result) ? beta : partial_result;
                    if (alpha >= beta) break;
                }
            }
            
            if (!tmp) { 
                beta = AlphaBeta(state,depth-1,alpha,beta,!player);
            }             
            return beta;
        }
    }
};
