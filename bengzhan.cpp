// bengzhan.cpp
#include "bengzhan.h"
#include <iostream>

bengzhan::bengzhan(int id, const std::string &name, int number, int worknumber, double efficiency)
        : id(id), name(name), number(number), worknumber(worknumber), efficiency(efficiency) {}

int bengzhan::getId() const { return id; } // Corrected method name
const std::string& bengzhan::getName() const { return name; }
int bengzhan::getNumber() const { return number; }
int bengzhan::getWorknumber() const { return worknumber; }
double bengzhan::getXiaolv() const { return efficiency; }

void bengzhan::setName(const std::string &name) { this->name = name; }
void bengzhan::setNumber(int number) { this->number = number; }
void bengzhan::setWorknumber(int worknumber) { this->worknumber = worknumber; }
void bengzhan::setXiaolv(double efficiency) { this->efficiency = efficiency; }

void bengzhan::display() const {
    std::cout << "Station ID: " << id << ", Name: " << name
              << ", Number of Sites: " << number << ", Number of Jobs: " << worknumber
              << ", Efficiency: " << efficiency << "\n";
}
