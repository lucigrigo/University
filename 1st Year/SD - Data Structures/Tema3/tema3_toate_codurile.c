#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_INT 2147483647

void readData(FILE *, char *);
void writeData(int **, int, int, char *, int **, int **);
void kuhnAlgorithm(int **, int **, int, int, char *);
int computeCost(int *, int *);
void removeMins(int **, int, int);
void drawLines(int **, int, int, int **, int **);
int *countZeros(int *, int **, int, int);
int eliminateZeros(int **, int, int, int *, int *, int *, int **, int **);
void markZeros(int **, int, int, int, int);
int **updateMatrix(int **, int, int, int *, int *);
void printMatrix(int **, int, int);

int main(int argc, char *argv[])
{
    FILE *ffile = fopen(argv[1], "r");
    if (ffile == NULL)
    {
        printf("error openning input file\nexiting\n");
        exit(1);
    }
    readData(ffile, argv[2]);
    return 0;
}

void printMatrix(int **A, int M, int N)
{
    int i, j;
    printf("----\n");
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    printf("----\n");
}

void printVect(int *v, int M, int N)
{
    int i;
    printf("---\n");
    for (i = 0; i < M + N; i++)
    {
        printf("%d: %d\n", i, v[i]);
    }
    printf("---\n");
}

int onlyZero(int **A, int indexL, int indexC, int M, int N)
{
    int only = 1, i;
    for (i = 0; i < M; i++)
    {
        if (A[i][indexC] < 0 && i != indexL)
            only = 0;
    }
    return only;
}

void countMatches(int **A, int M, int N, int *inputVect)
{
    int i;
    for (i = 0; i < M + N; i++)
    {
        int j = 0, t = 0;
        if (i < M)
        {
            while (j < N)
            {
                if (A[i][j] == -1)
                    t++;
                j++;
            }
            inputVect[i] = t;
        }
        else
        {
            while (j < M)
            {
                if (A[j][i - M] == -1)
                    t++;
                j++;
            }
            inputVect[i] = t;
        }
    }
}

void markMatch(int **A, int M, int N, int indexL, int indexC)
{
    int i;
    for (i = 0; i < M; i++)
    {
        if (A[indexL][i] == -1)
            A[indexL][i] = 0;
    }
}

int inVector(int *v, int index, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (v[i] == index)
        {
            return 1;
        }
    }
    return 0;
}

void writeSolution(int **A, int M, int N, int *columns, char *outputFileName)
{
    FILE *ffile = fopen(outputFileName, "w");
    int i;
    for (i = 0; i < N; i++)
    {
        fprintf(ffile, "%d\n", columns[i]);
    }
    fclose(ffile);
}

void writeData(int **costMatrix, int M, int N, char *outputFileName, int **cities, int **plants)
{
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL)
    {
        printf("error writing results to file\nexiting\n");
        exit(1);
    }
    int i, j, cost = 0;
    int *nrZeros = (int *)calloc(M + N, sizeof(int));
    countMatches(costMatrix, M, N, nrZeros);
    int min = MAX_INT;
    for (i = 0; i < M + N; i++)
    {
        if (nrZeros[i] < min && nrZeros[i] != 0)
            min = nrZeros[i];
    }
    int *indexes = (int *)calloc(N, sizeof(int));
    // printf("%d\n", min);
    // printMatrix(costMatrix, M, N);
    // while (1)
    // {
    //     int found = 0;
    //     for (j = 0; j < N; j++)
    //     {
    //         if (nrZeros[j + M] == min)
    //         {
    //             found = 1;
    //             for (i = 0; i < M; i++)
    //             {
    //                 if (costMatrix[i][j] == -1)
    //                 {
    //                     // if(onlyZero(costMatrix, i, j, M, N))
    //                     //     fprintf(outputFile, "%d\n", i);
    //                     // printf("\t%d:%d \t %d\n", i, j, computeCost(cities[j], plants[i]));
    //                     indexes[j] = i;
    //                     cost += computeCost(cities[j], plants[i]);
    //                     markMatch(costMatrix, M, N, i, j);
    //                     countMatches(costMatrix, M, N, nrZeros);
    //                     min = MAX_INT;
    //                     for (i = 0; i < M + N; i++)
    //                     {
    //                         if (nrZeros[i] < min && nrZeros[i] != 0)
    //                             min = nrZeros[i];
    //                     }
    //                 }
    //             }
    //             countMatches(costMatrix, M, N, nrZeros);
    //             min = MAX_INT;
    //             for (i = 0; i < M + N; i++)
    //             {
    //                 if (nrZeros[i] < min && nrZeros[i] != 0)
    //                     min = nrZeros[i];
    //             }
    //         }
    //     }
    //     if (!found || min == MAX_INT)
    //         break;
    // }
    for (j = 0; j < N; j++)
    {
        for (i = 0; i < M; i++)
        {
            // int min = MAX_INT;
            if (costMatrix[i][j] == -1)
            {
                // if(computeCost(plants[i], cities[j]) < min &&
                //     !inVector(indexes, i, N)){
                //     min = computeCost(plants[i],cities[j]);
                indexes[j] = i;
                // }
                // printf("%d:%d\n", i + 1, j + 1);
                // fprintf(outputFile, "%d\n", i);
            }
        }
    }
    for (i = 0; i < N; i++)
    {
        fprintf(outputFile, "%d\n", indexes[i]);
    }
    // fprintf(outputFile, "%d\n", cost);
    // printVect(nrZeros, M, N);
    // printf("%d\n", cost);
    fclose(outputFile);
}

void readData(FILE *inputFile, char *outputFileName)
{
    int N, M;
    // citirea nr de orase si nr de centrale
    fscanf(inputFile, "%d %d\n", &N, &M);
    // citirea pozitiilor oraselor
    int **cities = (int **)malloc(N * sizeof(int *)), i;
    for (i = 0; i < N; i++)
    {
        cities[i] = (int *)malloc(2 * sizeof(int));
        fscanf(inputFile, "%d %d\n", &cities[i][0], &cities[i][1]);
    }
    // citirea pozitiilor centralelor
    int **plants = (int **)malloc(M * sizeof(int *));
    for (i = 0; i < M; i++)
    {
        plants[i] = (int *)malloc(2 * sizeof(int));
        fscanf(inputFile, "%d %d\n", &plants[i][0], &plants[i][1]);
    }
    fclose(inputFile);
    kuhnAlgorithm(cities, plants, N, M, outputFileName);
    // writeData(resultMatrix, M, N, outputFileName, cities, plants);
}

int computeCost(int *cityCoord, int *plantCoord)
{
    return (abs(cityCoord[0] - plantCoord[0]) +
            abs(cityCoord[1] - plantCoord[1]));
}

void removeMins(int **A, int M, int N)
{
    int i, j;
    for (i = 0; i < M; i++)
    {
        int min = MAX_INT;
        for (j = 0; j < N; j++)
        {
            if (A[i][j] < min)
                min = A[i][j];
        }
        for (j = 0; j < N; j++)
        {
            A[i][j] = A[i][j] - min;
        }
    }
    for (i = 0; i < N; i++)
    {
        int min = MAX_INT;
        for (j = 0; j < M; j++)
        {
            if (A[j][i] < min)
                min = A[j][i];
        }
        for (j = 0; j < M; j++)
        {
            A[j][i] = A[j][i] - min;
        }
    }
}

int *countZeros(int *nrZeros, int **A, int M, int N)
{
    int i;
    for (i = 0; i < M; i++)
    {
        int j = 0, t = 0;
        while (j < N)
        {
            if (A[i][j] == 0)
                t++;
            j++;
        }
        nrZeros[i] = t;
    }
    for (i = 0; i < N; i++)
    {
        int j = 0, t = 0;
        while (j < M)
        {
            if (A[j][i] == 0)
                t++;
            j++;
        }
        nrZeros[i + M] = t;
    }
    return nrZeros;
}

void markLine(int **A, int M, int N, int indexL, int indexC, int isLine, int *markedLin, int *markedCol)
{
    int i;
    if (isLine)
    {
        markedLin[indexL] = 1;
        // markedCol[indexC] = 1;
        for (i = 0; i < N; i++)
        {
            if (A[indexL][i] == 0)
                A[indexL][i] = -1;
        }
    }
    else
    {
        // markedLin[indexL] = 1;
        markedCol[indexC] = 1;
        for (i = 0; i < M; i++)
        {
            if (A[i][indexC] == 0)
                A[i][indexC] = -1;
        }
    }
}

int countZero(int **A, int M, int N, int indexL, int indexC)
{
    int nrL = 0, i, nrC = 0;
    for (i = 0; i < N; i++)
    {
        if (A[indexL][i] == 0)
            nrL++;
    }
    for (i = 0; i < M; i++)
    {
        if (A[i][indexC] == 0)
            nrC++;
    }
    return nrL > nrC;
}

int countCol(int **A, int indexC, int M)
{
    int nr = 0, i;
    for (i = 0; i < M; i++)
    {
        if (A[i][indexC] == 0)
            nr++;
    }
    return nr;
}

void markLin(int **A, int M, int N, int lineIndex, int columnIndex)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (A[lineIndex][i] == 0)
        {
            A[lineIndex][i] = -2;
        }
    }
}

void markCol(int **A, int M, int N, int lineIndex, int columnIndex)
{
    int i;
    for (i = 0; i < M; i++)
    {
        if (A[i][columnIndex] == 0)
        {
            A[i][columnIndex] = -2;
        }
    }
}

int searchZeros(int **A, int M, int N)
{
    int zeroFound = 0, i, j;
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (A[i][j] == 0)
                zeroFound = 1;
        }
    }
    return zeroFound;
}

void reverseMarkings(int *lines, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (lines[i] == 0)
        {
            lines[i] = 1;
        }
        else
        {
            lines[i] = 0;
        }
    }
}

int checkForOptimalSolution(int **A, int M, int N, int *markedLin, int *markedCol)
{
    int i, j;
    for (i = 0; i < M; i++)
    {
        int found = 0;
        for (j = 0; j < N; j++)
        {
            if (A[i][j] == -1)
            {
                found = 1;
            }
        }
        if (!found)
        {
            markedLin[i] = 1;
        }
    }
    while (1)
    {
        int stop = 1;
        for (i = 0; i < M; i++)
        {
            if (markedLin[i])
            {
                for (j = 0; j < N; j++)
                {
                    if (A[i][j] == -2 && !markedCol[j])
                    {
                        markedCol[j] = 1;
                        stop = 0;
                    }
                }
            }
        }
        for (j = 0; j < N; j++)
        {
            if (markedCol[j])
            {
                for (i = 0; i < M; i++)
                {
                    if (A[i][j] == -1 && !markedLin[i])
                    {
                        markedLin[i] = 1;
                        stop = 0;
                    }
                }
            }
        }

        // printVect(markedLin, M, 0);
        // printVect(markedCol, 0, N);
        if (stop)
            break;
    }

    int linesNr = 0, colsNr = 0;
    for (i = 0; i < M; i++)
    {
        if (!markedLin[i])
        {
            linesNr++;
        }
    }
    for (i = 0; i < N; i++)
    {
        if (markedCol[i])
            colsNr++;
    }

    if ((colsNr + linesNr) == M)
    {
        // printVect(markedLin, M, 0);
        // printVect(markedCol, 0, N);
        // printf("AICII\n\n\n\n");
        return 1;
    }
    else
    {
        reverseMarkings(markedLin, M);
        return 0;
    }
}

int eliminateZeros(int **A, int M, int N, int *nrZeros, int *markedLin, int *markedCol,
                   int **plants, int **cities)
{
    int i, count = 0, j;
    // for (j = 0; j < N; j++)
    // {
    //     if (!markedCol[j])
    //     {
    //         for (i = 0; i < M; i++)
    //         {
    //             if (!markedLin[i] && A[i][j] == 0)
    //             {
    //                 count++;
    //                 markLine(A, M, N, i, j, countZero(A, M, N, i, j), markedLin, markedCol);
    //             }
    //         }
    //     }
    // }
    while (1)
    {
        int found = 0;
        for (i = 0; i < M; i++)
        {
            int countZ = 0, index = -1;
            for (j = 0; j < N; j++)
            {
                if (A[i][j] == 0)
                {
                    countZ++;
                    index = j;
                }
            }
            if (countZ == 1)
            {
                found = 1;
                A[i][index] = -1;
                markCol(A, M, N, i, index);
                count++;
                // printf("linia %d\n", i);
            }
        }
        // printMatrix(A, M, N);
        // printf("cate se fac aici? %d \n", count);
        for (j = 0; j < N; j++)
        {
            int countZ = 0, index = -1;
            for (i = 0; i < M; i++)
            {
                if (A[i][j] == 0)
                {
                    // printf("%d : %d\n", i, j);
                    countZ++;
                    index = i;
                }
            }
            if (countZ == 1)
            {
                found = 1;
                A[index][j] = -1;
                markLin(A, M, N, index, j);
                count++;
                // printf("coloana %d\n", j);
            }
        }
        if (!found)
            break;
    }
    int arbitraryChoose = 0;
    if (searchZeros(A, M, N))
    {
        while (1)
        {
            int found = 0;
            for (i = 0; i < M; i++)
            {
                int index = -1, minCost = MAX_INT;
                for (j = 0; j < N; j++)
                {
                    if (A[i][j] == 0)
                    {
                        index = j;
                        // break;
                    }
                    // && computeCost(cities[i], plants[j]) < minCost)
                }
                if (index != -1)
                {
                    found = 1;
                    count++;
                    A[i][index] = -1;
                    markCol(A, M, N, i, index);
                    arbitraryChoose = 1;
                    // markLin(A, M, N, i, index);
                    for (j = 0; j < N; j++)
                    {
                        if (A[i][j] == 0)
                            A[i][j] = -2;
                    }
                    break;
                }
            }
            for (j = 0; j < N; j++)
            {
                int index = -1, minCost = MAX_INT;
                for (i = 0; i < M; i++)
                {
                    if (A[i][j] == 0)
                    {
                        index = i;
                        // break;
                    }
                    // && computeCost(cities[i], plants[j]) < minCost)
                }
                if (index != -1)
                {
                    found = 1;
                    count++;
                    A[index][j] = -1;
                    arbitraryChoose = 1;
                    markLin(A, M, N, index, j);
                    for (i = 0; i < M; i++)
                    {
                        if (A[i][j] == 0)
                            A[i][j] = -2;
                    }
                    break;
                }
            }
            if (!found)
                break;
        }
    }
    if (count == N && !arbitraryChoose)
    {
        // printf("aici se rupe\n");
        return 1;
    }
    else
    // if (count == N && arbitraryChoose)
    {
        return checkForOptimalSolution(A, M, N, markedLin, markedCol);
    }
    // else
    // {
    //     return 0;
    // }
    // printMatrix(A, M, N);
    // printf("cate se fac aici? %d \n", count);
    // printf("-------- %d\n", count);
    // printMatrix(A, M, N);
    // printf("nr of lines is %d\nsi liniile sunt\n", count);
    // return count;
}

int **updateMatrix(int **A, int M, int N, int *markedLin, int *markedCol)
{
    int min = MAX_INT, i, j;
    for (i = 0; i < M; i++)
    {
        if (!markedLin[i])
        {
            for (j = 0; j < N; j++)
            {
                if (!markedCol[j])
                {
                    if (A[i][j] < min && A[i][j] >= 0)
                    {
                        min = A[i][j];
                    }
                }
            }
        }
    }
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (!markedCol[j] && !markedLin[i])
            {
                // printf("se scade %d \t\t %d\n", i, j);
                A[i][j] = A[i][j] - min;
            }
        }
    }
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            // if (A[i][j] == -1 || A[i][j] == -2)
            //     A[i][j] = 0;
            if (markedCol[j] && markedLin[i])
            {
                // printf("se aduna %d \t\t %d\n", i, j);
                // printf("\t\t%d\n", A[i][j]);
                A[i][j] = A[i][j] + min;
                // printf("\t\t%d\n", A[i][j]);
            }
        }
    }
    // printf("minimul este %d\n", min);
    // printMatrix(A, M, N);
    return A;
}

void drawLines(int **A, int M, int N, int **plants, int **cities)
{
    while (1)
    {
        int *markedCol = (int *)calloc(N, sizeof(int)),
            *markedLin = (int *)calloc(M, sizeof(int)),
            *nrZeros = (int *)calloc(M + N, sizeof(int));
        if (markedCol == NULL || markedLin == NULL || nrZeros == NULL)
            exit(1);
        // printf("aici sta mult?\n");
        // printMatrix(A, M, N);
        if (eliminateZeros(A, M, N, nrZeros, markedLin, markedCol, plants, cities))
        {
            break;
        }
        else
        {
            // printMatrix(A, M, N);
            // printVect(markedLin, M, 0);
            // printVect(markedCol, 0, N);
            A = updateMatrix(A, M, N, markedLin, markedCol);
        }
        // break;
    }
    // printMatrix(A, M, N);

    // printf("\n");
}

int checkSolution(int *rows, int M, int *cols, int N)
{
    // int i, count = 0;
    // for (i = 0; i < M; i++)
    // {
    //     if (rows[i])
    //         count++;
    // }
    // for (i = 0; i < N; i++)
    // {
    //     if (cols[i])
    //         count++;
    // }
    // return count;
    // int i;
    // for(i = 0; i < M; i++){
    //     if(cols[rows[i]] != i)
    //         return 0;
    // }
    // return 1;
    // int i, count = 0;
    // for(i = 0; i < M; i++){
    //     if(rows[cols[i]] == i)
    //         count++;
    //     printf("--%d\n", count);
    // }
    // return count;
    return 1;
}

void makeZero(int *v1, int n1, int *v2, int n2)
{
    int i;
    for (i = 0; i < n1; i++)
        v1[i] = 0;
    for (i = 0; i < n2; i++)
        v2[i] = 0;
}

int match(int index, int *markedLin, int *markedCol, int *rowsLeft,
          int *columnsRight, int **A, int M, int N, int *visitedCols, int *visitedLins, int isColumn, int *count)
{
    if (visitedLins[index])
        return 0;
    // visitedLins[index] = 1;
    // printf("nodul curent este %d\n", index);
    printVect(visitedLins, M, 0);
    int i;
    for (i = 0; i < N; i++)
    {
        if (A[index][i] == 0 && columnsRight[i] == -1)
        {
            markedLin[index] = 1;
            rowsLeft[index] = i;
            // markedCol[i] = 0;
            columnsRight[i] = index;
            (*count)++;
            return 1;
        }
    }
    for (i = 0; i < N; i++)
    {
        if (A[index][i] == 0 &&
            match(columnsRight[i], markedLin, markedCol, rowsLeft, columnsRight, A, M, N, visitedCols, visitedLins, 0, count))
        {
            // markedLin[columnsRight[i]] = 0;
            markedLin[index] = 1;
            // markedCol[i] = 0;
            rowsLeft[index] = i;
            columnsRight[i] = index;
            //(*count)++;
            return 1;
        }
    }
    return 0;
}

void checkOrientation(int *markedLin, int *markedCol, int M, int N, int isRow, int **A, int index,
                      int *columnsRight, int *rowsLeft)
{
    int i;
    for (i = 0; i < N; i++)
    {
        if (!markedCol[i] && A[index][i] == 0)
        {
            markedCol[i] = 1;
            markedLin[columnsRight[i]] = 0;
            checkOrientation(markedLin, markedCol, M, N, 1, A, columnsRight[i], columnsRight, rowsLeft);
        }
    }
}

void kuhnAlgorithm(int **cities, int **plants, int N, int M, char *outputFileName)
{
    // alocarea matricei
    int **A = (int **)calloc(M, sizeof(int *)), i, j;
    for (i = 0; i < M; i++)
    {
        A[i] = (int *)calloc(M, sizeof(int));
    }
    // calcularea costurilor
    for (i = 0; i < M; i++)
    {
        for (j = 0; j < N; j++)
        {
            A[i][j] = computeCost(cities[j], plants[i]);
        }
    }
    // printMatrix(A, M, N);

    removeMins(A, M, M);
    // printMatrix(A, M, N);

    // drawLines(A, M, M, plants, cities);
    // printf("---\n\n---\n\n---\n\n");
    // return A;
    // return;
    int *rowsLeft = (int *)calloc(M, sizeof(int)),
        *columnsRight = (int *)calloc(N, sizeof(int));
    while (1)
    {
        int *markedLin = (int *)calloc(M, sizeof(int)),
            *markedCol = (int *)calloc(M, sizeof(int)),
            *visitedCols = (int *)calloc(N, sizeof(int)),
            *visitedLins = (int *)calloc(M, sizeof(int));
        if (markedLin == NULL || markedCol == NULL)
        {
            printf("eroare la alocarea memoriei\n");
            exit(1);
        }
        int count = 0;
        for (i = 0; i < M; i++)
        {
            rowsLeft[i] = -1;
            columnsRight[i] = -1;
        }
        while (1)
        {
            // count = 0;
            int found = 0;
            for (i = 0; i < M; i++)
            {
                visitedLins[i] = 0;
                visitedCols[i] = 0;
            }
            for (i = 0; i < M; i++)
            {
                if (rowsLeft[i] == -1)
                {
                    found = found | match(i, markedLin, markedCol, rowsLeft, columnsRight, A, M, M, visitedCols, visitedLins, 0, &count);
                }
            }
            if (!found)
                break;
            // printf("%d\n", count);
        }
        for (i = 0; i < M; i++)
        {
            if (!markedLin[i])
            {
                // checkOrientation(markedLin, markedCol, M, N, 1, A, i);
                checkOrientation(markedLin, markedCol, M, M, 1, A, i, columnsRight, rowsLeft);
            }
        }
        // printf("%d\n", count);
        // if (checkSolution(markedLin, M, markedCol, N) >= M)
        // if(checkSolution(rowsLeft, M, columnsRight, N))
        if (count == M)
            break;
        // printVect(rowsLeft, M, 0);
        // printVect(columnsRight, N, 0);
        // printVect(markedLin, M, 0);
        // printVect(markedCol, 0, N);
        // printMatrix(A, M, N);
        // printVect(columnsRight, 0, N);
        makeZero(rowsLeft, M, columnsRight, N);
        // //         printVect(markedLin, M, 0);
        // // printVect(markedCol, 0, N);
        updateMatrix(A, M, N, markedLin, markedCol);
        // printf("aicea\n");
        // break;
        free(markedLin);
        free(markedCol);
        free(visitedLins);
        free(visitedCols);
    }
    writeSolution(A, M, N, columnsRight, outputFileName);
}
