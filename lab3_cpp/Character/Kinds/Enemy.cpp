//
// Created by vadim on 24.10.2023.
//

#include "Enemy.h"


//std::ostream &operator<<(std::ostream &c, Enemy &enemy) {
//    enemy.print(c);
//    return c;
//}

std::vector<Cell *> Enemy::lee(Matrix<Cell> &matr, Cell *to) {
    if (to == nullptr) return {};
//    std::cout << "Я тут\n";
    int WALL = -1;
    int BLANK = -2;
    int W = matr.getCols();
    int H = matr.getRows();
    int ax = getCell()->getPoint().x;
    int ay = getCell()->getPoint().y;
    int bx = to->getPoint().x;
    int by = to->getPoint().y;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int d, x, y, k;
    bool stop;
    int px[W * H], py[W * H];
    int grid[matr.getRows()][matr.getCols()];
    if (matr.getElementByAdress(ay, ax)->getType() == TypeOfPoint::wall ||
        matr.getElementByAdress(ay, ax)->getType() == TypeOfPoint::wall)
        throw std::invalid_argument("Character can't be in this cell!");  // ячейка (ax, ay) или (bx, by) - стена
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (matr.getElementByAdress(i, j)->getType() == TypeOfPoint::tile || matr.getElementByAdress(i, j)->getType() == TypeOfPoint::stock) grid[i][j] = BLANK;
            else grid[i][j] = WALL;
        }
    }
    d = 0;
    grid[ay][ax] = 0;            // стартовая ячейка помечена 0
    do {
        stop = true;               // предполагаем, что все свободные клетки уже помечены
        for (y = 0; y < H; ++y)
            for (x = 0; x < W; ++x)
                if (grid[y][x] == d)                         // ячейка (x, y) помечена числом d
                {
                    for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным соседям
                    {
                        int iy = y + dy[k], ix = x + dx[k];
                        if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
                            grid[iy][ix] == BLANK) {
                            stop = false;              // найдены непомеченные клетки
                            grid[iy][ix] = d + 1;      // распространяем волну
                        }
                    }
                }
        d++;
    } while (!stop && grid[by][bx] == BLANK);

    if (grid[by][bx] == BLANK) throw std::invalid_argument("Character can't be in this cell!"); // путь не найден

    // восстановление пути
    int len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
    x = bx;
    y = by;
    d = len;
    while (d > 0) {
        px[d] = x;
        py[d] = y;                   // записываем ячейку (x, y) в путь
        d--;
        for (k = 0; k < 4; ++k) {
            int iy = y + dy[k], ix = x + dx[k];
            if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
                grid[iy][ix] == d) {
                x = x + dx[k];
                y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
                break;
            }
        }
    }
    px[0] = ax;
    py[0] = ay;                  // теперь px[0..len] и py[0..len] - координаты ячеек пути
    std::vector<Cell *> answer;
    for (int i = 0; i < len; i++) {
//        std::cout << py[i] << " " << px[i] << "\n";
//        std::cout << matr.getElementByAdress(py[i], px[i])->getPoint().x;
        answer.push_back(matr.getElementByAdress(py[i], px[i]));
    }
//    std::cout << "END\n";
    return answer;
}
