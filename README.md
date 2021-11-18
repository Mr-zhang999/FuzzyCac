# FuzzyCac
基于matlab底层的模糊控制算法

基于matlab底层的模糊控制算法 采用C#调用，需要修改FuzzuCac内容，具体为函数名称及参数传入部分 头部增加 //_declspec(dllexport) double cacFuzzy(double d1, double d2, double d3);

函数名称改为：double cacFuzzy(double d1, double d2, double d3) 参数传入：
dataMatrix[0][0] = d1; dataMatrix[0][1] = d2; dataMatrix[0][2] = d3;

C#调用方式： class fuzzydll { 
[DllImport("dlltest.dll", EntryPoint = "cacFuzzy", CallingConvention = CallingConvention.Cdecl)] 
private static extern double cacFuzzy(double d1, double d2, double d3);
public double fuzzyDllCac(double d1, double d2, double d3) { 
double a = cacFuzzy( d1, d2, d3); return a; } 
}
