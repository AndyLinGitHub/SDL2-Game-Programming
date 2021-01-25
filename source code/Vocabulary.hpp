#ifndef Vocabulary_hpp
#define Vocabulary_hpp

#include <stdio.h>


class Vocabulary{
public:
    Vocabulary();
    ~Vocabulary();
    int** voc_level[3];
    int* voc_size[3];
    int size_of_computer_words[10] = {6,13,12,9,8,8,9,11,12,10};
    int size_of_finance_words[10] = {6,7,10,5,6,11,9,13,8,8};
    int size_of_science_words[10] = {10,6,6,9,7,9,7,12,8,6};
    const char** font_array[3] = {};
private:
    enum Letter{A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
    
    int voc1[6] = {A,P,A,C,H,E};
    int voc2[13] = {C,O,N,F,I,G,U,R,A,T,I,O,N};
    int voc3[12] ={I,N,C,O,M,P,A,T,I,B,L,E};
    int voc4[9] = {B,A,N,D,W,I,D,T,H};
    int voc5[8] = {P,R,O,T,O,C,O,L};
    int voc6[8] = {R,E,T,R,I,E,V,E};
    int voc7[9] = {H,E,U,R,I,S,T,I,C};
    int voc8[11] = {C,Y,B,E,R,N,E,T,I,C,S};
    int voc9[12] = {A,U,T,H,E,N,T,I,C,A,T,E};
    int voc10[10] = {R,E,S,O,L,U,T,I,O,N};
    int voc11[6] = {L,E,D,G,E,R};
    int voc12[7] = {P,R,O,V,I,S,O};
    int voc13[10] ={A,S,S,E,S,S,M,E,N,T};
    int voc14[5] = {R,E,M,I,T};
    int voc15[6] = {M,A,R,G,I,N};
    int voc16[11] = {S,T,O,C,K,H,O,L,D,E,R};
    int voc17[9] = {A,R,B,I,T,R,A,G,E};
    int voc18[13] = {S,U,B,C,O,N,T,R,A,C,T,E,R};
    int voc19[8] = {D,I,V,I,D,E,N,D};
    int voc20[8] = {S,T,A,G,N,A,N,T};
    int voc21[10] = {P,A,R,A,S,I,T,I,S,M};
    int voc22[6] = {L,I,C,H,E,N};
    int voc23[6] ={P,O,R,O,U,S};
    int voc24[9] = {H,E,R,B,I,C,I,D,E};
    int voc25[7] = {N,E,P,T,U,N,E};
    int voc26[9] = {D,E,P,L,E,T,I,O,N};
    int voc27[7] = {P,O,L,A,R,I,S};
    int voc28[12] = {C,H,R,O,M,O,S,P,H,E,R,E};
    int voc29[8] = {N,E,U,T,R,I,N,O};
    int voc30[6] = {P,L,A,S,M,A};

    int* computer_voc[10] = {};
    int* science_voc[10] = {};
    int* finance_voc[10] = {};
    
    const char* computer_font[10] = {"APACHE", "CONFIGURATION", "INCOMPATIBLE", "BANDWIDTH", "PROTOCOL", "RETRIEVE", "HEURISTIC","CYBERNETICS","AUTHENTICATE","RESOLUTION"};
    
    const char* finance_font[10] = {"LEDGER","PROVISO","ASSESSMENT","REMIT","MARGIN","STOCKHOLDER","ARBITRAGE","SUBCONTRACTER","DIVIDEND","STAGNANT"};
    
    const char* science_font[10] = {"PARASITISM","LICHEN","POROUS","HERBICIDE","NEPTUNE","DEPLETION","POLARIS","CHROMOSPHERE","NEUTRINO","PLASMA",};
    
};
#endif /* Vocabulary_hpp */
