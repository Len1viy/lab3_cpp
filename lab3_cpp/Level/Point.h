//
// Created by vadim on 16.10.2023.
//

#ifndef LAB3_CPP_POINT_H
#define LAB3_CPP_POINT_H

typedef struct Point {
    int x;
    int y;
} Point;

typedef enum Side{
    player,
    enemy
} Side;

typedef enum Direction {
    left,
    right,
    up,
    down
} Direction;


#endif //LAB3_CPP_POINT_H
