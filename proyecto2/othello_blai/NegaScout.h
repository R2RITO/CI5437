#include "othello_cut.h"
#include <iostream>
#include <climits>

class NegaScout_ {

public:

    unsigned long long nodosGenerados;

    int NegaScout(state_t state, int depth, int alpha, int beta, bool player) {
        
        nodosGenerados++;

        if ( depth == 0 || state.terminal()) { return (player?1:-1)*(state.value()); }

        state_t children;
        int m = INT_MIN;
        int n = beta;
        bool tmp = false;
        int t;

        for( int pos = 0; pos < DIM; ++pos ) {
            if((player && state.is_black_move(pos))||(!player && state.is_white_move(pos))) {
                tmp = true;
                children = state.move(player,pos);
                t = (-1) * NegaScout(children, depth-1,(-1)*n,(-1)*((m>alpha)?m:alpha),!player);
                if (t>m) {
                    if ((n == beta) || (depth < 3) || (t >= beta)) {
                        m = t;
                    } else {
                        m = (-1)*NegaScout(children,depth-1,(-1)*beta,(-1)*t,!player);
                    }
                }
                if (player && m >= beta) return m;
                //if (!player && m <= alpha) return m;
                n = (alpha>m?alpha:m)+1;
            }
        }

        if (!tmp) {
            m = (-1) * NegaScout(state,depth-1,alpha,beta,!player);
        }
    
        return m;
    }

    int useNegaScout(state_t state, int depth, int alpha, int beta, bool player) {
        nodosGenerados = 0;
        return NegaScout(state, depth, alpha, beta, player);
    }


};
