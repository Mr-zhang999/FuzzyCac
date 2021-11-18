#include  "fis.h"
//_declspec(dllexport) double cacFuzzy(double d1, double d2, double d3);
//#include<iostream>
//using namespace std;
//#include <stdio.h>
//double cacFuzzy(double d1, double d2, double d3)
double main()
{
    FIS* fis;
    int i, j;
    int debug = 1;

    double** dataMatrix, ** fisMatrix, ** outputMatrix;
    char* fis_file, * data_file;
    int data_row_n, data_col_n, fis_row_n, fis_col_n;

    //  data_file = "dataMatrixFile.txt";
    fis_file = "fisMatrixFile.txt";

    /* 从文件读入输入数据矩阵和模糊矩阵，将其放入二维矩阵中*/
    fisMatrix = returnFismatrix(fis_file, &fis_row_n, &fis_col_n);

    //将传入参数放进二维矩阵,
    //data_row_n 为输入参数行数，即一组数据，若同时输入多组参数，需修改
    //data_col_n  为输入参数个数，参数个数变化，需修改
    data_row_n = 1;
    data_col_n = 3;
    dataMatrix = (DOUBLE**)fisCreateMatrix(data_row_n, data_col_n, sizeof(DOUBLE));
    //dataMatrix[0][0] = d1;
    //dataMatrix[0][1] = d2;
    //dataMatrix[0][2] = d3;    
    dataMatrix[0][0] = 1;
    dataMatrix[0][1] = 2;
    dataMatrix[0][2] = 3;

    /* build FIS data structure 建立模糊数据结构*/
    fis = (FIS*)fisCalloc(1, sizeof(FIS));
    /*将fisMatrix中的数据导入到fis中*/
    fisBuildFisNode(fis, fisMatrix, fis_col_n, MF_POINT_N);

    /* error checking 错误检测*/
    if (data_col_n < fis->in_n) {
        printf("Given FIS is a %d-input %d-output system.\n",
            fis->in_n, fis->out_n);
        printf("Given data file does not have enough input entries.\n");
        fisFreeMatrix((void**)dataMatrix, data_row_n);
        fisFreeMatrix((void**)fisMatrix, fis_row_n);
        fisFreeFisNode(fis);
        fisError("Exiting ...");
    }
    /* fisDebugging 调试数据输出*/
    if (debug)
        fisPrintData(fis);

    /* create output matrix 创建输出矩阵5x1*/
    outputMatrix = (double**)fisCreateMatrix(data_row_n, fis->out_n, sizeof(double));

    /* evaluate FIS on each input vector 获取输入->开始模糊推理->输出矩阵*/
    for (i = 0; i < data_row_n; i++)
        getFisOutput(dataMatrix[i], fis, outputMatrix[i]);

    /* print output vector 得到输出并打印*/
    for (i = 0; i < data_row_n; i++) {
        for (j = 0; j < fis->out_n; j++) {
            printf("%.12f ", outputMatrix[i][j]);
            double res = outputMatrix[i][j];
            return res;
        }

        // printf("\n");
    }

    ///* clean up memory 清理内存*/
    //fisFreeFisNode(fis);
    //fisFreeMatrix((void**)dataMatrix, data_row_n);
    //fisFreeMatrix((void**)fisMatrix, fis_row_n);
    //fisFreeMatrix((void**)outputMatrix, data_row_n);
    //getchar();
    //return  0;
}
