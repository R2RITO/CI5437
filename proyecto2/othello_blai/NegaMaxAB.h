#include "othello_cut.h"
#include <iostream>
#include <climits>

class NegaMaxAB_ {

public:

    unsigned long long nodosGenerados;
    
    int NegaMaxAB(state_t state, int depth, bool color,int alpha,int beta) {
        
        nodosGenerados++; 
         
        if (state.terminal() || depth == 0) {
            //std::cout << "ee es" << state.value();
            return ((color ? 1 : -1) * state.value());
        }
          
	    int m = alpha;
        int res_negamax_ab;
        state_t children;
        bool tmp = false;

        for( int pos = 0; pos < DIM; ++pos ) {
        	
        	if((color && state.is_black_move(pos))||(!color && state.is_white_move(pos))) {
                tmp = true;
                children = state.move(color,pos);
                res_negamax_ab = (-1) * NegaMaxAB(children,depth-1,!color,(-1)*beta,(-1)*m);
                if (res_negamax_ab > m ) m = res_negamax_ab;
                if (color) {if (m>=beta) return m;}
              } 
        }
        
        if (!tmp ) {
            m = (-1)*NegaMaxAB(state, depth-1, !color,(-1)*beta,(-1)*m);
        }

        return m;
    }
     int useNegaMaxAB(state_t state, int depth, bool player,int alpha,int beta) {
        nodosGenerados = 0;
        return NegaMaxAB(state,depth,player,alpha,beta);
    }

};
