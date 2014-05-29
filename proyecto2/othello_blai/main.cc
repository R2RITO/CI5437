/*
 *  Copyright (C) 2012 Universidad Simon Bolivar
 * 
 *  Permission is hereby granted to distribute this software for
 *  non-commercial research purposes, provided that this copyright
 *  notice is included with any such distribution.
 *  
 *  THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 *  EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE
 *  SOFTWARE IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU
 *  ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.
 *  
 *  Blai Bonet, bonet@ldc.usb.ve
 *
 *  Last revision: 11/08/2012
 *
 */

#include "othello_cut.h" // won't work correctly until .h is fixed!
#include "MinMax.h"
#include "Negamax.h"
#include "AlphaBeta.h"
#include "Scout.h"
#include "NegaScout.h"
#include <iostream>
#include <climits>

using namespace std;

int main(int argc, const char **argv) {
    state_t state;
    cout << "Principal variation:" << endl;
    MinMax_ meh;
    Negamax_ neh;
    AlphaBeta_ beh;
    Scout_ peh;
    NegaScout_ qeh;

    for( int i = 0; PV[i] != -1; ++i ) {
        
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        cout << "***********************************************\n";
        if (i > 18) {
            
            if (player) {
                cout << "Valor de MaxMin: " << meh.MaxMin(state,33-i,player) << endl;
            } else {
                cout << "Valor de MinMax: " << meh.MinMax(state,33-i,player) << endl;
            }
        }

        if (i > 18 ) {
            cout << "Valor de Negamax: " << neh.Negamax(state,33-i,player) << endl;

        }

        if (i > 18) {
            cout << "Valor de AlphaBeta: " << beh.AlphaBeta(state, 33-i, INT_MIN, INT_MAX, player) << endl;
        }

        if (i > 18) {
            cout << "Valor de Scout: " << peh.scout(state, 33-i, player) << endl;
        }

        if (i > 18) {
            cout << "Valor de NegaScout: " << qeh.NegaScout(state, 33-i, INT_MIN, INT_MAX, player) << endl;
        }

        cout << "***********************************************\n";
        cout << state;
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);
        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
        
    }


    //cout << "Valor de AlphaBeta: " << beh.AlphaBeta(state, 0, INT_MIN, INT_MAX, true) << "\n" << endl;
    //cout << "Valor AlphaBeta: " << meh.AlphaBeta(state,3,-99999, 99999, true) << endl;
    
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;


    if( argc > 1 ) {
        int n = atoi(argv[1]);
        cout << endl << "Apply " << n << " random movements at empty board:";
        state = state_t();
        for( int i = 0; i < n; ++i ) {
            bool player = i % 2 == 0; // black moves first
            int pos = state.get_random_move(player);
            state = state.move(player, pos);
            cout << " " << pos;
        }
        cout << endl << state;
    }

    return 0;
}

