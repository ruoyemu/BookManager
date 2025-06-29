#include<iostream>
#include<fstream>
#include<string>
#include"Book.h"

void Menu() {
    std::cout << "\n===== 图书管理系统 =====" << std::endl;
    std::cout << "    1.  添加图书" << std::endl;
    std::cout << "    2.  删除图书" << std::endl;
    std::cout << "    3.  查找图书" << std::endl;
    std::cout << "    4.  借阅图书" << std::endl;
    std::cout << "    5.  归还图书" << std::endl;
    std::cout << "    6.  显示图书" << std::endl;
    std::cout << "    0.  退出系统" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "请选择操作: ";
};

void AddMeue() {
    std::cout << "\n==== 添加图书 ====" << std::endl;
    std::cout << " 1.文件添加图书" << std::endl;
    std::cout << " 2.直接添加图书" << std::endl;
    std::cout << " 0.   退出" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "请选择操作: ";
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        FileAdd();
        break;
    case 2:
        Add();
    case 0:
        break;
    default:
        std::cout << "无效选择,请重新输入!" << std::endl;
    }
}
void DisplayMnue() {
    std::cout << "\n==== 显示图书 ====" << std::endl;
    std::cout << " 1.显示全部图书" << std::endl;
    std::cout << " 2.显示借阅图书" << std::endl;
    std::cout << " 0.   退出" << std::endl;
    std::cout << "===================" << std::endl;
    std::cout << "请选择操作: ";
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        display();
        break;
    case 2:
        display_borrow();
    case 0:
        break;
    default:
        std::cout << "无效选择,请重新输入!" << std::endl;
    }
}

void Continue() {
    std::cout << "继续操作请输入1: ";
    char choice;
    while(true) {
        std::cin >> choice;
        if(choice == '1') {
            break;
        } else {
            std::cout << "输入错误,请重新输入(继续操作-输入1): ";
            std::cin.clear();
        }
    }
}

int main() {
    int choice;
    do {
        Menu();
        std::cin >> choice;
        std::cin.ignore(); //清除缓冲区的换行符
        switch(choice) {
            case 1:
                AddMeue();
                Continue();
                break;
            case 2:
                Delect();
                Continue();
                break;
            case 3:
                Search();
                Continue();
                break;
            case 4:
                Borrow();
                Continue();
                break;
            case 5:
                Return();
                Continue();
                break;
            case 6:
                DisplayMnue();
                Continue();
                break;
            case 0:
                std::cout << "感谢您使用本系统!" << std::endl;
                break;
            default:
                std::cout << "无效选择,请重新输入!" << std::endl;
        }

    } while(choice != 0);
    return 0;
}