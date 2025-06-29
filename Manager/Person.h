#include<iostream>
#include<string>
#include<vector>

class Person
{
    friend std::istream &read(std::istream &is, Person &item);
    friend std::ostream &print(std::ostream &os, const Person &item);
public:
    //构造函数
    Person(const std::string &n, const std::string &a, const std::string &p) : 
    personnel_name(n), personnel_address(a), personnel_phone(p) {}
    Person() = default;
    Person(const std::string &s) : personnel_name(s) {}
    Person(std::istream &is) { read(is, *this);}
    //成员函数
    bool operator==(const Person& other) const { //重载==
        return personnel_name == other.personnel_name && 
               personnel_address == other.personnel_address &&
               personnel_phone == other.personnel_phone;
    }
    std::string name() const { return personnel_name;}
    std::string address() const { return personnel_address;}
    std::string phone() const { return personnel_phone;}
private:
    std::string personnel_name;
    std::string personnel_address;
    std::string personnel_phone;
};

std::istream &read(std::istream &is, Person &item)
{
    is >> item.personnel_name >> item.personnel_address >> item.personnel_phone;
    return is;
}

std::ostream &print(std::ostream &os, const Person &item)
{
    os << item.personnel_name << " " << item.personnel_address << " " << item.personnel_phone << std::endl;
    return os;
}
