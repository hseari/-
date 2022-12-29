#include <iostream>

int count_alives(int N, int M, int* after_step[]) {   //подсчет живых
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (after_step[i][j] == '1') count++;
        }
    }
    return count;
}


int count_neighbors(int N, int M, int i, int j, int* universe[]) {   //подсчет соседей
    int a = universe[i][j],
        count = 0;
    int ia, ib, ic, ja, jb, jc;

    ia = i == 0 ? N - 1 : i - 1;
    ib = i;
    ic = i == N - 1 ? 0 : i + 1;
    ja = j == 0 ? M - 1 : j - 1;
    jb = j;
    jc = j == M - 1 ? 0 : j + 1;

    if (universe[ia][ja] == 1) 
        count++;
    if (universe[ia][jb] == 1) 
        count++;
    if (universe[ia][jc] == 1) 
        count++;
    if (universe[ib][ja] == 1) 
        count++;
    if (universe[ib][jc] == 1) 
        count++;
    if (universe[ic][ja] == 1) 
        count++;
    if (universe[ic][jb] == 1) 
        count++;
    if (universe[ic][jc] == 1) 
        count++;

    return count;
}

int main(void) {

    setlocale(LC_ALL, "Russian");
    int n, m, i, j, step = 0;

    std::cout << "Укажите число строк: ";  //задаем размерность матрице
    std::cin >> n;
    std::cout << "Укажите число столбцов: ";
    std::cin >> m;

    srand((unsigned)time(NULL));
    int** universe = NULL;
    universe = (int**)malloc(m * sizeof(int*));

    int** after_step = NULL;
    after_step = (int**)malloc(m * sizeof(int*));

    //создаем матрицу
    for (i = 0; i < n; i++) {
        universe[i] = (int*)malloc(n * sizeof(int));
        after_step[i] = (int*)malloc(n * sizeof(int));
    }

    //выводим ее
    std::cout << "Вселенная:  " << std::endl;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
        {
            universe[i][j] = rand() % 2;
            std::cout << universe[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //начинаем игру
    while (step < 1000) {
        step++;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int c_n = count_neighbors(n, m, i, j, universe);
                if (universe[i][j] == 1) {
                    if (c_n == 2 || c_n == 3) {   //если рядом 2 или 3 соседа то клетка остается живой
                        after_step[i][j] = '1';  
                    }
                    else {
                        after_step[i][j] = ' ';
                    }
                }
                else { 
                    if (c_n == 3) {               //если рядом 3 соседа то клетка оживает
                        after_step[i][j] = '1';
                    }
                    else {
                        after_step[i][j] = ' ';
                    }
                }

            }
        }

        if (step == 1 || step == 10 || step == 100 || step == 1000) {     //вывод шагов
            printf("Шаг %d: живых %d\n", step, count_alives(n, m, after_step));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    printf("%c", after_step[i][j]);
                }
                printf("\n");
            }
            std::cout << std::endl;
        }

        int alive = 0;
        //проверка есть ли кто живой
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (after_step[i][j] == '1') {
                    alive = 1;
                    break;
                }
            }
            if (alive) break;
        }

        int the_same = 1;
        //проверка есть ли изменения в следующем шаге
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if ((universe[i][j] == 1 && after_step[i][j] == ' ') ||
                    (universe[i][j] == 0 && after_step[i][j] == '1')) {
                    the_same = 0;
                    break;
                }
            }
            if (!the_same) break;
        }

        //если все мертвы или нет изменений во вселенной, то завершаем игру
        if (!alive || the_same) {
            break;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                universe[i][j] = after_step[i][j] == '1' ? 1 : 0;
            }
        }
    }

    printf("Конец игры на шаг %d\n", step);

    //освобождаем память
    for (i = 0; i < n; i++) {
        free(universe[i]);
    }
    free(universe);

    for (i = 0; i < n; i++) {
        free(after_step[i]);
    }
    free(after_step);

    return 0;
}