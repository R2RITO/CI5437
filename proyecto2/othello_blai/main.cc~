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
#include "NegaMaxAB.h"
#include <iostream>
#include <climits>
#include <ctime>

using namespace std;

int main(int argc, const char **argv) {
    state_t state;
    cout << "Principal variation:" << endl;
    MinMax_ meh;
    Negamax_ neh;
    AlphaBeta_ beh;
    Scout_ peh;
    NegaScout_ qeh;
    NegaMaxAB_ ph;

    int cota = 20;
    clock_t ini;
    clock_t fin;
    float resT;

    cout.precision(5);

    std::vector<state_t> estados;
    bool player;
    for( int i = 0; PV[i] != -1; ++i ) {
        
        player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        estados.push_back(state);
        cout << state;
        cout << (player ? "Black" : "White")
             << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
             << endl;
        state = state.move(player, pos);
        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;        

    }

    for (int i=estados.size()-1; i >= 0; i--) {

        state = estados[i];

        cout << "***********************************************\n";
        cout << "Profundidad: "<< 33-i << endl;

        if (player) {
            ini = clock();
            cout << "Valor de MaxMin: ";
            cout << meh.useMaxMin(state,33-i,player); 
            cout << " NodosGenerados: " << meh.nodosGenerados;
            fin = clock();
            resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
            cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;
        } else {
            ini = clock();
            cout << "Valor de MinMax: " ;
            cout << meh.useMinMax(state,33-i,player) ;
            cout << " NodosGenerados: " << meh.nodosGenerados;
            fin = clock();
            resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
            cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;            

        }
        
        ini = clock();
        cout << "Valor de Negamax: ";
        cout << neh.useNegamax(state,33-i,player);
        cout << " NodosGenerados: " << neh.nodosGenerados;
        fin = clock();
        resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
        cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;

        if (player) {
            ini = clock();
            cout << "Valor de NegaMaxAB: ";
            cout << ph.useNegaMaxAB(state,33-i,player,INT_MIN,INT_MAX) ;
            cout << " NodosGenerados: " << ph.nodosGenerados;
            fin = clock();
            resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
            cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;

        } else {
            ini = clock();
            cout << "Valor de NegaMaxAB: " ;
            cout << (-1)*ph.useNegaMaxAB(state,33-i,player,INT_MIN,INT_MAX);
            cout << " NodosGenerados: " << ph.nodosGenerados;
            fin = clock();
            resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
            cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;
        }

        ini = clock();
        cout << "Valor de AlphaBeta: " ;
        cout << beh.useAlphaBeta(state, 33-i, INT_MIN, INT_MAX, player) ;
        cout << " NodosGenerados: " << beh.nodosGenerados;
        fin = clock();
        resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
        cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;

        ini = clock();
        peh.nodosGenerados = 0;
        cout << "Valor de Scout: " << peh.useScout(state, 33-i, player); 
        cout << " NodosGenerados: " << peh.nodosGenerados;
        fin = clock();
        resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
        cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;

        ini = clock();
        qeh.nodosGenerados = 0;
        cout << "Valor de NegaScout: " ;
        cout << qeh.useNegaScout(state, 33-i, INT_MIN, INT_MAX, player);
        cout << " NodosGenerados: " << qeh.nodosGenerados;
        fin = clock();
        resT = (double)(fin-ini)/(CLOCKS_PER_SEC/1000);
        cout << " Tiempo: " << fixed << resT << " Milisegundos." << endl;

        cout << "***********************************************\n";

        player = !player;
    }

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

