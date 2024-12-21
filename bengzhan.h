// bengzhan.h
#ifndef BENGZHAN_H
#define BENGZHAN_H

#include <string>

class bengzhan {
public:
    bengzhan(int id, const std::string &name, int number, int worknumber, double efficiency);

    int getId() const; // Corrected method name
    const std::string& getName() const;
    int getNumber() const;
    int getWorknumber() const;
    double getXiaolv() const;

    void setName(const std::string &name);
    void setNumber(int number);
    void setWorknumber(int worknumber);
    void setXiaolv(double efficiency);

    void display() const;

    int id;
    int number;
    double efficiency;
    int worknumber;
    std::string name;
};

#endif // BENGZHAN_H
