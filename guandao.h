// guandao.h
#ifndef GUANDAO_H
#define GUANDAO_H

#include <string>

class guandao {
    int startStationId;
    int endStationId;
public:
    guandao(int id, const std::string &name, double length, bool maint, int i, int i1);
    int getStartStationId() const;
    int getEndStationId() const;
    int getId() const; // Corrected method name
    const std::string& getName() const;
    double getLength() const; // Corrected method name
    bool getMaint() const;

    void setName(const std::string &name);
    void setLength(double length);
    void setMaint(bool maint);

    void display() const;
    void setStartStationId(int stationId);
    void setEndStationId(int stationId);
    int id;
    double length;
    std::string name;
    bool maint;
};

#endif // GUANDAO_H
