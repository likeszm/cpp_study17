/*
* 名称: 内存管理测试
* 
* 收获:
* 1、对于数组的动态内存分配,套娃实现高维的思想
* 2、[]自带解引用功能,比如int array[5]; int *p = array;可以用p[2]访问;
* 
*/

#include <iostream>

void memory_test_1(void);
void memory_test_2(void);
void memory_test_3(void);
void memory_test_4(void);
void memory_test_5(void);
void memory_test_6(void);
void memory_test_7(void);
void memory_test_8(void);


int main()
{
    //memory_test_1();
    //memory_test_2();
    //memory_test_3();
    //memory_test_4();
    //memory_test_5();
    //memory_test_6();
    //memory_test_7();
    //memory_test_8();



    std::cout << "\n测试完成\n";
    return 0;
}

void memory_test_1(void)
{
    std::cout << "尝试创建: " << std::endl;
    int* p_int = NULL;
    if (!(p_int = new int))
    {
        std::cout << "创建失败,退出!" << std::endl;
        exit(1);
    }
    
    *p_int = 1112;
    std::cout << "*p_int = " << *p_int << std::endl;

    delete p_int;
    p_int = NULL;
}

void memory_test_2(void)
{
    std::cout << "尝试{}初始化: " << std::endl;
    double* pi = new double{ 3.1415926 };

    std::cout << "*pi = " << *pi << std::endl;

    delete pi;
    pi = NULL;
}

void memory_test_3(void)
{
    std::cout << "分配数组空间：" << std::endl;
    int* p_array = new int[10]{ 1,2,3,4,5,6,7,8,9,0 };

    for (int i = 0 ; i < 10; i++)
    {
        std::cout << "array[" << i << "] = " << *(p_array + i) << std::endl;
    }

    delete [] p_array;      //别忘了[]
    p_array = NULL;
}

void memory_test_4(void)
{
    std::cout << "尝试()初始化：" << std::endl;
    int* p = new int();
    std::cout << "*p = " << *p << std::endl;
    delete p;
    p = new int{ 7 };
    std::cout << "*p = " << *p << std::endl;
}

void memory_test_5(void)
{
    int array[5] = { 1, 2,3,4,5 };
    int* p = array;

    std::cout << "array[2] = " << array[2] << std::endl;

    array[2]++;
    std::cout << "array[2] = " << array[2] << std::endl;
    
    (*(p + 2))++;
    std::cout << "array[2] = " << array[2] << std::endl;
    
    p[2] ++;
    std::cout << "array[2] = " << array[2] << std::endl;


}

void memory_test_6(void)
{
    //申请
    int** p_array = new int* [6]();
    for (int i = 0 ; i < 6; i++)
    {
        *(p_array + i) = new int[9]();
    }

    //写入数据
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            p_array[i][j] = i * 10 + j;
        }
    }

    //显示
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            std::cout << "a[" << i << "][" << j << "] = " << p_array[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    //释放
    for (int i = 0; i < 6; i++)
    {
        delete [] *(p_array + i);
    }
    delete[] p_array;
    p_array = NULL;
}

void memory_test_7(void)
{
    //自创金子塔型数组

    //所有的9换成了i+1即可

    //申请
    int** p_array = new int* [6]();
    for (int i = 0; i < 6; i++)
    {
        *(p_array + i) = new int[i + 1]();
    }

    //填值
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            p_array[i][j] = i * 10 + j;
        }
    }

    //打印
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            std::cout << "a[" << i << "][" << j << "] = " << p_array[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    //释放
    for (int i = 0; i < 6; i++)
    {
        delete[] * (p_array + i);
    }
    delete[] p_array;
    p_array = NULL;

}

void memory_test_8(void)
{
    //创建
    const int LEN_1 = 3, LEN_2 = 5, LEN_3 = 7;
    int*** p_array = new  int **[LEN_1]();      //创建最高维度的索引数组
    for (int i = 0; i < LEN_1; i++)             //填充最高维度的索引数组
    {
        p_array[i] = new int* [LEN_2];          //创建次高维度的索引数组
        for (int j = 0; j < LEN_2; j++)         //填充次高维度的索引数组
        {
            p_array[i][j] = new int[LEN_3]();   //最低维度的一维数组直接生成
        }
    }

    //使用
    for (int i = 0; i < LEN_1; i++)
    {
        for (int j = 0; j < LEN_2; j++)
        {
            for (int k = 0; k < LEN_3; k++)
            {
                p_array[i][j][k] = i * 100 + j * 10 + k;
            }
        }
    }

    for (int i = 0; i < LEN_1; i++)
    {
        for (int j = 0; j < LEN_2; j++)
        {
            for (int k = 0; k < LEN_3; k++)
            {
                std::cout<< p_array[i][j][k] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << "-------------------------------" << std::endl;
    }

    //释放
    for (int i = 0; i < LEN_1; i++)
    {
        for (int j = 0; j < LEN_2; j++)
        {
           delete [] p_array[i][j]; //从最低维度的数组开始释放
        }
         delete [] p_array[i];      //清除一个次高维度的索引
    }
    delete[] p_array;               //清除最高维度的索引
    p_array = NULL;
}
