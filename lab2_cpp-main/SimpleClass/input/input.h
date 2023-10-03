//
// Created by vadim on 17.09.2023.
//
#include <iostream>
#ifndef _INPUT_H
#define _INPUT_H



template<class T>
int getNum(T &a) {
    if (std::cin >> a && std::cin.good()) return 0;
    else {
        std::cin.clear();
        std::cin.sync();
        return 1;
    }
}

void help();

#endif //_INPUT_H
