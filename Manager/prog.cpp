#include<iostream>
#include<fstream>
#include<string>
#include"Book.h"


int FileAdd(int argc, char *argv[])
{
    if(argc < 2)
    {
        std::cerr << "请提供文件名作为参数" << std::endl;
        return -1;
    }
    std::ifstream in(argv[1]);
    if(!in)
    {
        std::cerr << "无法打开文件" << argv[1] << std::endl;
        return -1;
    }
    std::ofstream out(argv[2], std::ofstream::app);
    if(!out)
    {
        std::cerr << "无法打开文件" << argv[2] << std::endl;
        return -1;
    }
    Book total;
    //double price = 0;
    //读取第一条记录，确保有数据处理
    if(read(in, total)) {
        Book trans;
        //读取多条记录
        while(read(in, trans))
        {
            if(total.GetIsbn() == trans.GetIsbn())
            {
                total.combine(trans);
            }
            else {
                print(out, total);
                total = trans;
            }
        }
        //打印最后一条记录
        print(out, total);
        in.close();
    }
    //没有输入 失败
    else {
        std::cerr << "No Data!" << std::endl;
        return -1;
    }
    return 0;
}

int Add() {
    Book total;
    //double price = 0;
    //读取第一条记录，确保有数据处理
    if(read(std::cin, total)) {
        Book trans;
        //读取多条记录
        while(read(std::cin, trans))
        {
            if(total.GetIsbn() == trans.GetIsbn())
            {
                total.combine(trans);
            }
            else {
                print(std::cout, total);
                total = trans;
            }
        }
        //打印最后一条记录
        print(std::cout, total);
        std::cin.clear();
    }
    //没有输入 失败
    else {
        std::cerr << "No Data!" << std::endl;
        return -1;
    }
    return 0;
}