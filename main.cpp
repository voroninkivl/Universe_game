//
//  main.cpp
//  Extra_exercise
//
//  Created by Кирилл Воронин on 29.12.2023.
//

#include <iostream>

int count_alives(int N, int M, int* after_step[]) {   //подсчет живых клеток на игровом поле в виде матрицы
    int count = 0;
    for (int x = 0; x < N; x++) {
        for (int y = 0; y < M; y++) {
            if (after_step[x][y] == '1') count++;
        }
    }
    return count;
}


int count_neighbors(int N, int M, int x, int y, int* universe[]) {   //функция производит подсчет соседей
    int count = 0;
    int xa = 0, xb = 0, xc = 0, ya = 0, yb = 0, yc = 0;

    if (x == 0) {
        xa = N - 1;
    }
    else {
        xa = x - 1;
    }
    xb = x;
    if (x == N - 1) {
        xc = 0;
    }
    else {
        xc = x + 1;
    }
    if (y == 0) {
        ya = M - 1;
    }
    else {
        ya = y - 1;
    }
    yb = y;
    if (y == M - 1) {
        yc = 0;
    }
    else {
        yc = y + 1;
    }

    if (universe[xa][ya] == 1)
        count++;
    if (universe[xa][yb] == 1)
        count++;
    if (universe[xa][yc] == 1)
        count++;
    if (universe[xb][ya] == 1)
        count++;
    if (universe[xb][yc] == 1)
        count++;
    if (universe[xc][ya] == 1)
        count++;
    if (universe[xc][yb] == 1)
        count++;
    if (universe[xc][yc] == 1)
        count++;

    return count;
}

int main() {

    int n = 0, m = 0, x = 0, y = 0, step = 0;
    //задаем размерность игрового поля в виде матрицы
    std::cout << "Укажите число строк: ";
    std::cin >> n;
    std::cout << "Укажите число столбцов: ";
    std::cin >> m;

    srand((unsigned)time(nullptr));
    int** universe = nullptr;
    universe = (int**)malloc(m * sizeof(int*));

    int** after_step = nullptr;
    after_step = (int**)malloc(m * sizeof(int*));

    //создаем игровое поле в виде матрицы
    for (x = 0; x < n; x++) {
        universe[x] = (int*)malloc(n * sizeof(int));
        after_step[x] = (int*)malloc(n * sizeof(int));
    }
    
    //для наглядности выводим игровое поле
    std::cout << "Вселенная:  " << std::endl;
    for (x = 0; x < n; x++) {
        for (y = 0; y < m; y++)
        {
            universe[x][y] = rand() % 2;
            std::cout << universe[x][y] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //запускаем игру
    while (step < 1000) {
        step++;

        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                int count_n = count_neighbors(n, m, x, y, universe);
                if (universe[x][y] == 1) {
                    if (count_n == 2 || count_n == 3) {   //если на игрововм поле в виде матрицы рядом с клеткой 2 или 3 соседа то она остается живой
                        after_step[x][y] = '1';
                    }
                    else {
                        after_step[x][y] = ' ';
                    }
                }
                else {
                    if (count_n == 3) {
                        //если рядом с клеткой на игровом поле находятся 3 соседа то она оживает
                        after_step[x][y] = '1';
                    }
                    else {
                        after_step[x][y] = ' ';
                    }
                }

            }
        }

        if (step == 1 || step == 10 || step == 100 || step == 1000) {     //выводим шаги для наглядности
            printf("Шаг %d: живых %d\n", step, count_alives(n, m, after_step));
            for (int x = 0; x < n; x++) {
                for (int y = 0; y < m; y++) {
                    printf("%c", after_step[x][y]);
                }
                printf("\n");
            }
            std::cout << std::endl;
        }

        int alive = 0;
        //проверка есть ли кто живой на игровом поле в виде матрицы
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (after_step[x][y] == '1') {
                    alive = 1;
                    break;
                }
            }
            if (alive) break;
        }

        int the_same = 1;
        //проверка есть ли изменения на игровом поле в следующем шаге
        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if ((universe[x][y] == 1 && after_step[x][y] == ' ') || (universe[x][y] == 0 && after_step[x][y] == '1')) {
                    the_same = 0;
                    break;
                }
            }
            if (!the_same) break;
        }

        //если все клетки мертвы или нет изменений на игровом поле, то игра завершается
        if (!alive || the_same) {
            break;
        }

        for (int x = 0; x < n; x++) {
            for (int y = 0; y < m; y++) {
                if (after_step[x][y] == '1') {
                    universe[x][y] = 1;
                } 
                else {
                    universe[x][y] = 0;
                }

            }
        }
    }

    printf("Конец игры на шаг %d\n", step);

    //освобождаем выделенную память
    for (int count = 0; count < n; count++) {
        delete[] universe[count];
    }
    delete[] universe;

    for (int count = 0; count < n; count++) {
        delete[] after_step[count];
    }
    delete[] after_step;

    return 0;
}

