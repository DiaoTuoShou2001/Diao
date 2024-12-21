// guandao.cpp
#include "guandao.h"
#include <iostream>

guandao::guandao(int id, const std::string &name, double length, bool maint, int startStationId, int endStationId)
        : id(id), name(name), length(length), maint(maint), startStationId(startStationId), endStationId(endStationId) {}

int guandao::getId() const { return id; } // Corrected method name
const std::string& guandao::getName() const { return name; }
double guandao::getLength() const { return length; } // Corrected method name
bool guandao::getMaint() const { return maint; }
int guandao::getStartStationId() const { return startStationId; }
int guandao::getEndStationId() const { return endStationId; }



void guandao::setName(const std::string &name) { this->name = name; }
void guandao::setLength(double length) { this->length = length; }
void guandao::setMaint(bool maint) { this->maint = maint; }
void guandao::setStartStationId(int stationId) { this->startStationId = stationId; }
void guandao::setEndStationId(int stationId) { this->endStationId = stationId; }


void guandao::display() const {
    std::cout << "Pipe ID: " << id << ", Name: " << name
              << ", Length: " << length << ", Maintenance: " << maint << "\n";
}
