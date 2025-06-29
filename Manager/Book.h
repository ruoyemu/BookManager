#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<cerrno>
#include<cstring>
#include"Person.h"

class Book
{
    friend Book add(const Book &lhs, const Book &rhs); //添加相同图书
    friend void Add();
    friend void FileAdd();
    friend void Delect(); //删除图书
    friend Book Search(); //查询图书
    friend void Borrow(); //借阅图书
    friend void Return(); //归还图书
    friend std::istream &read(std::istream &is, Book &item); //添加图书
    friend std::istream &read(std::ifstream &is, Book &item); //添加图书(文件流)
    friend std::ostream &print(std::ostream &os, const Book &item); //显示图书
    friend void display(); //显示所有图书
    friend void display_borrow(); //显示被借阅的全部图书
public:
//构造函数
    Book(const std::string &s1, const std::string &s2, const std::string &s3) :
    isbn(s1), title(s2), author(s3){}
    //Book() = default;
    Book() : Book("", "", "") {}
    Book(const std::string &s) : Book(s, "", "") {}
    Book(std::istream &is) : Book() { read(is, *this);}
//成员函数
    //访问函数
    std::string GetIsbn() const { return isbn;}
    std::string GetTitle() const { return title;}
    std::string GetAuthor() const { return author;}
    bool IsAvailable() const { return available;}
    //应用函数
    void SetAvailable(bool av) {
        available = av;
    }
    Book &combine(const Book&); //同样的书，合在一起
    bool operator==(const Book& other) const { //重载==
        return isbn == other.isbn &&
               title == other.title &&
               author == other.author;
    }

private:
    //inline double avg_price() const { return units_sole ?revenue/units_sole :0 ;}
    std::string isbn;
    // unsigned units_sole = 0;
    // double revenue = 0;
    std::string title;
    std::string author;
    int sum = 0;
    bool available; //是否可借
    std::vector<Person> people; //该书的全部借阅者

};

std::vector<Book> books; //存储所有书籍
std::vector<Book> BorrowBook; //存储借阅书籍

Book& Book::combine(const Book& rhs)
{
    //units_sole += rhs.units_sole;
    //revenue += rhs.revenue;
    ++sum;
    return *this;
}

std::istream &read(std::istream &is, Book &item)
{
    //double price = 0;
    // is >> item.isbn >> item.units_sole >> price;
    // item.revenue = item.units_sole*price
    std::cout << "请输入图书ISBN: ";
    is >> item.isbn;
    std::cout << "请输入图书名: ";
    is >> item.title;
    std::cout << "请输入作者名: ";
    is >> item.author;
    item.SetAvailable(true); //默认将新加入的图书设为可借
    ++item.sum;
    // item.revenue = item.units_sole*price;
    return is;
}

std::istream &read(std::ifstream &is, Book &item)
{
    //double price = 0;
    // is >> item.isbn >> item.units_sole >> price;
    // item.revenue = item.units_sole*price;
    is >> item.isbn >> item.title >> item.author;
    item.SetAvailable(true); //默认将新加入的图书设为可借
    ++item.sum;
    books.push_back(item);
    // item.revenue = item.units_sole*price;
    return is;
}

std::ostream &print(std::ostream &os, const Book &item)
{
    // os << item.isbn << " " << item.units_sole << " " << item.revenue << " ";
    // os << item.avg_price();
    os << "ISBN: " << item.isbn << " " << "图书名: " <<  item.title << " " << "作者: " << item.author 
    << " " << (item.available ? "可借" : "无剩余或不可借") << std::endl;
    if(item.available) {
        os << "剩余: " << item.sum << std::endl;
    }
    return os;
}

Book add(const Book &lhs, const Book &rhs)
{
    Book ans = lhs;
    ans.combine(rhs);
    return ans;
}

void Delect() {
    std::string isbn;
    std:: cin >> isbn;
    for(auto it = books.begin(); it != books.end(); ++it) {
        if(it->GetIsbn() == isbn) {
            books.erase(it);
            std::cout << "删除成功" << std::endl;
            return ;
        }
    }
    std::cout << " 删除失败,无此图书" << std::endl;
}
Book Search() {
    std::string keyword; //关键词
    std::cout << "请输入要查询的书名或作者或ISBN: ";
    std::cin >> keyword;
    for(auto it = books.begin(); it != books.end(); ++it) {
        if(it->GetIsbn() == keyword || it->GetTitle() == keyword || it->GetAuthor() == keyword) {
            print(std::cout, *it);
            return *it;
        }
    }
    std::cout << "未找到相关图书!" << std::endl;
    return Book();
}

void Borrow() {
    while(true) {
        Book book = Search();
        if(book.sum == 0 || !book.available) {
            std::cout << "此书无剩余或不可借阅!" << " " << "继续借阅输入1, 退出输入0:";
            char choice;
            while(true) {
                std::cin >> choice;
                if(choice == '1') {
                    break;
                } else if(choice == '0') {
                    return ;
                } else {
                    std::cout << "输入错误,请重新输入(继续借阅输入1, 退出输入0):";
                    std::cin.clear();
                }
            }
        } else {
            --book.sum;
            if(book.sum == 0) {
                book.SetAvailable(false);
            }
            std::cout << "借阅人:" << " " << "地址:" << " " << "电话号码:";
            Person BorrowPeople;
            print(std::cout, BorrowPeople);
            book.people.push_back(BorrowPeople);
            BorrowBook.push_back(book);
            std::cout << "借阅成功!";
        }
    }
    return ;
}

void Return() {
    std::string isbn;
    std::cout << "请输入要还书的ISBN:";
    std::cin >> isbn;
    for(auto it = BorrowBook.begin(); it != BorrowBook.end(); ++it) {
        if(it->GetIsbn() == isbn) {
            while(true){
                Person BorrowPeople;
                std::cout << "借阅人:" << " " << "地址:" << " " << "电话号码:";
                read(std::cin, BorrowPeople);
                for(auto p_it = it->people.begin(); p_it != it->people.end(); ++p_it) { //查询对应借阅人
                    if(*p_it == BorrowPeople) {
                        it->people.erase(p_it);
                        ++it->sum;
                        it->SetAvailable(true);
                        if(it->people.empty()) {
                        BorrowBook.erase(it);
                        }
                    std::cout << "归还完成!";
                    return ;
                    }
                }
                std::cout << "未找到此借阅人!" << " " << "继续归还输入1, 退出输入0:";
                char choice;
                while(true) {
                    std::cin >> choice;
                    if(choice == '1') { 
                        break;
                    } else if(choice == '0') {
                        return ;
                    } else {
                        std::cout << "输入错误,请重新输入(继续归还输入1, 退出输入0):";
                        std::cin.clear();
                    }
                }
            }
        }
    }
    std::cout << "该书未被借阅!";
    return ;
}

void display() {
    for(auto it = books.begin(); it != books.end(); ++it) {
        print(std::cout, *it);
    }
    return ;
}

void display_borrow() {
    for(auto it = BorrowBook.begin(); it != BorrowBook.end(); ++it) {
        print(std::cout, *it);
    }
    return ;
}

void FileAdd()
{
    std::cout << "请输入要添加的图书文件名: ";
    std::string filename;
    std::cin >> filename;
    std::ifstream in(filename);

    std::cout << "尝试打开文件: [" << filename << "]" << std::endl;
    if(!in.is_open()) {
        std::cerr << "无法打开文件: " << filename << std::endl;
        std::cerr << "错误代码: " << errno << " - " << strerror(errno) << std::endl;
        return;
    }
    if(std::cin) {         //确保有数据处理
        Book total;
        read(in, total);
        //double price = 0;
        //读取多条记录
        Book trans;
        while(read(in, trans)) {
            if((std::find(books.begin(), books.end(), trans)) != books.end())
            {
                auto it = std::find(books.begin(), books.end(), trans);
                it->combine(trans);
                print(std::cout, *it);
            }
            else {
                print(std::cout, total);
                total = trans;
            }
        }
        //打印最后一条记录
        print(std::cout, total);
        in.close();
        return ;
    }
    //没有输入 失败
    else {
        std::cerr << "No Data!" << std::endl;
    }
    return ;
}

void Add() {
    Book total;
    //double price = 0;
    //读取第一条记录，确保有数据处理
    if(read(std::cin, total)) {
        books.push_back(total);
        std::cout << "停止添加请输入'EOF'(按Enter执行下一步): ";
        std::cin.ignore(); //清除缓冲区的换行符
        std::string choice;
        std::getline(std::cin, choice);
        //读取多条记录
        Book trans;
        while(choice != "EOF") {
            read(std::cin, trans);
            if(std::find(books.begin(), books.end(), trans) != books.end())
            {
                auto it = std::find(books.begin(), books.end(), trans);
                it->combine(trans);
                print(std::cout, *it);
            }
            else {
                books.push_back(trans);
                print(std::cout, total);
                total = trans;
            }
            // std::cout << "停止添加请输入'EOF'(按Enter执行下一步): ";
            // std::cin.ignore(); //清除缓冲区的换行符
            // std::getline(std::cin, choice);
        }
        //打印最后一条记录
        print(std::cout, total);
        std::cin.clear();
    }
    //没有输入 失败
    else {
        std::cerr << "No Data!" << std::endl;
    }
    return ;
}
