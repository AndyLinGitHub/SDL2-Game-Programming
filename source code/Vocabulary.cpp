//
//  Vocabulary.cpp

#include "Vocabulary.hpp"
Vocabulary:: Vocabulary(){
    computer_voc[0] = new int [12];computer_voc[0] = voc1;
    computer_voc[1] = voc2;
    computer_voc[2] = voc3;
    computer_voc[3] = voc4;
    computer_voc[4] = voc5;
    computer_voc[5] = voc6;
    computer_voc[6] = voc7;
    computer_voc[7] = voc8;
    computer_voc[8] = voc9;
    computer_voc[9] = voc10;
    finance_voc[0] = voc11;
    finance_voc[1] = voc12;
    finance_voc[2] = voc13;
    finance_voc[3] = voc14;
    finance_voc[4] = voc15;
    finance_voc[5] = voc16;
    finance_voc[6] = voc17;
    finance_voc[7] = voc18;
    finance_voc[8] = voc19;
    finance_voc[9] = voc20;
    science_voc[0] = voc21;
    science_voc[1] = voc22;
    science_voc[2] = voc23;
    science_voc[3] = voc24;
    science_voc[4] = voc25;
    science_voc[5] = voc26;
    science_voc[6] = voc27;
    science_voc[7] = voc28;
    science_voc[8] = voc29;
    science_voc[9] = voc30;
    voc_level[0] = finance_voc;
    voc_level[1] = science_voc;
    voc_level[2] = computer_voc;
    voc_size[0] = size_of_finance_words;
    voc_size[1] = size_of_science_words;
    voc_size[2] = size_of_computer_words;
    font_array[0] = finance_font;
    font_array[1] = science_font;
    font_array[2] = computer_font;
    
}

Vocabulary:: ~Vocabulary()
{
    for(int i = 0; i < 10 ;i++) {
        computer_voc[i] = NULL;
        finance_voc[i] = NULL;
        science_voc[i] = NULL;
    }
    for(int i = 0; i < 3 ;i++) {
        voc_level[i] = NULL;
        voc_size[i] = NULL;
        font_array[i] = NULL;
    }
}
