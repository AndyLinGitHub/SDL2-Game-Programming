#ifndef Vocabulary_hpp
#define Vocabulary_hpp

#include <stdio.h>


class Vocabulary{
public:
    Vocabulary();
    ~Vocabulary();
    int** voc_level[3];
    int* voc_size[3];
    int size_of_computer_words[10] = {12,13,12,9,8,8,9,11,12,10};
    int size_of_finance_words[10] = {6,7,10,5,6,11,9,13,8,8};
    int size_of_science_words[10] = {10,6,6,9,7,9,7,12,8,6};
    const char** font_array[3] = {};
private:
    enum Letter{A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
    int voc1[12] = {H,U,N,G,Y,U,N,H,S,I,E,H}; // 教授名字
    int voc2[13] = {C,O,N,F,I,G,U,R,A,T,I,O,N}; // 系統設定
    int voc3[12] ={I,N,C,O,M,P,A,T,I,B,L,E}; // 不相容
    int voc4[9] = {B,A,N,D,W,I,D,T,H}; // 頻寬
    int voc5[8] = {P,R,O,T,O,C,O,L}; // 通訊協定
    int voc6[8] = {R,E,T,R,I,E,V,E}; // 檢索
    int voc7[9] = {H,E,U,R,I,S,T,I,C}; //啟發式的方法
    int voc8[11] = {C,Y,B,E,R,N,E,T,I,C,S}; // 模控學
    int voc9[12] = {A,U,T,H,E,N,T,I,C,A,T,E}; // 認證
    int voc10[10] = {R,E,S,O,L,U,T,I,O,N}; // 解析度
    
    int voc11[6] = {L,E,D,G,E,R}; // 總帳
    int voc12[7] = {P,R,O,V,I,S,O}; // 但書
    int voc13[10] ={A,S,S,E,S,S,M,E,N,T}; // 評估
    int voc14[5] = {R,E,M,I,T}; // 匯款
    int voc15[6] = {M,A,R,G,I,N}; // 保證金
    int voc16[11] = {S,T,O,C,K,H,O,L,D,E,R}; // 股東
    int voc17[9] = {A,R,B,I,T,R,A,G,E}; //套利
    int voc18[13] = {S,U,B,C,O,N,T,R,A,C,T,E,R}; // 轉包商
    int voc19[8] = {D,I,V,I,D,E,N,D}; // 股息
    int voc20[8] = {S,T,A,G,N,A,N,T}; // 不景氣
    
    int voc21[10] = {P,A,R,A,S,I,T,I,S,M}; // 寄生
    int voc22[6] = {L,I,C,H,E,N}; // 地衣
    int voc23[6] ={P,O,R,O,U,S}; // 多孔隙的
    int voc24[9] = {H,E,R,B,I,C,I,D,E}; // 除草劑
    int voc25[7] = {N,E,P,T,U,N,E}; // 海王星
    int voc26[9] = {D,E,P,L,E,T,I,O,N}; // 枯竭
    int voc27[7] = {P,O,L,A,R,I,S}; //北極星
    int voc28[12] = {C,H,R,O,M,O,S,P,H,E,R,E}; // 色球層
    int voc29[8] = {N,E,U,T,R,I,N,O}; // 微中子
    int voc30[6] = {P,L,A,S,M,A}; // 電漿

    int* computer_voc[10] = {};
    int* science_voc[10] = {};
    int* finance_voc[10] = {};
    
    const char* computer_font[10] = {
        "HUNG YUN HSIEH 謝宏昀",
        "CONFIGURATION 系統設定",
        "INCOMPATIBLE 不相容",
        "BANDWIDTH 頻寬",
        "PROTOCOL 通訊協定",
        "RETRIEVE 檢索",
        "HEURISTIC 啟發式的方法",
        "CYBERNETICS 模控學",
        "AUTHENTICATE 認證",
        "RESOLUTION 解析度"};
    
    const char* finance_font[10] = {
        "LEDGER 總帳",
        "PROVISO 但書",
        "ASSESSMENT 評估",
        "REMIT 匯款",
        "MARGIN 保證金",
        "STOCKHOLDER 股東",
        "ARBITRAGE 套利",
        "SUBCONTRACTER 轉包商",
        "DIVIDEND 股息",
        "STAGNANT 不景氣"};
    
    const char* science_font[10] = {
        " PARASITISM 寄生",
        "LICHEN 地衣",
        "POROUS 多孔隙的",
        "HERBICIDE 除草劑",
        "NEPTUNE 海王星",
        "DEPLETION 枯竭",
        "POLARIS 北極星",
        "CHROMOSPHERE 色球層",
        "NEUTRINO 微中子",
        "PLASMA 電漿",
    };

};
#endif /* Vocabulary_hpp */
