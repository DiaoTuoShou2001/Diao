#include "PipeManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// 构造函数和析构函数
PipeManager::PipeManager() {}
PipeManager::~PipeManager() {}

// 数据加载
void PipeManager::loadData(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open data file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);
        std::string type;
        iss >> type;

        if (type == "PIPE") {
            int id, startStationId, endStationId;
            std::string name;
            double length;
            bool maint;
            if (iss >> id >> name >> length >> maint >> startStationId >> endStationId) {
                pipes.emplace_back(id, name, length, maint, startStationId, endStationId);
            } else {
                std::cerr << "Error parsing PIPE line: " << line << "\n";
            }
        } else if (type == "STATION") {
            int id, number, worknumber;
            double efficiency;
            std::string name;
            if (iss >> id >> name >> number >> worknumber >> efficiency) {
                stations.emplace_back(id, name, number, worknumber, efficiency);
            } else {
                std::cerr << "Error parsing STATION line: " << line << "\n";
            }
        }
    }

    inFile.close();
}

// 数据保存
void PipeManager::saveData(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open data file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& pipe : pipes) {
        outFile << "PIPE " << pipe.getId() << " "
                << pipe.getName() << " "
                << pipe.getLength() << " "
                << pipe.getMaint() << " "
                << pipe.getStartStationId() << " "
                << pipe.getEndStationId() << "\n";
    }

    for (const auto& station : stations) {
        outFile << "STATION " << station.getId() << " "
                << station.getName() << " "
                << station.getNumber() << " "
                << station.getWorknumber() << " "
                << station.getXiaolv() << "\n";
    }

    outFile.close();
}

// 添加管道
void PipeManager::addPipe(int id, const std::string& name, double length, bool maint,
                          int startStationId, int endStationId) {
    pipes.emplace_back(id, name, length, maint, startStationId, endStationId);
}

// 编辑管道
void PipeManager::editPipe(int id) {
    for (auto& pipe : pipes) {
        if (pipe.getId() == id) {
            std::string newName;
            double newLength;
            bool newMaint;

            std::cout << "Current Name: " << pipe.getName() << ". New Name: ";
            std::cin >> newName;
            std::cout << "Current Length: " << pipe.getLength() << ". New Length: ";
            std::cin >> newLength;
            std::cout << "Current Maintenance Status ("
                      << pipe.getMaint()
                      << "). New Maintenance Status (1 for yes, 0 for no): ";
            std::cin >> newMaint;

            pipe.setName(newName);
            pipe.setLength(newLength);
            pipe.setMaint(newMaint);

            std::cout << "Pipeline updated successfully.\n";
            return;
        }
    }
}

// 删除管道
void PipeManager::deletePipe(int id) {
    auto it = std::remove_if(pipes.begin(), pipes.end(), [id](const guandao& pipe) { return pipe.getId() == id; });

}
void PipeManager::addStation(int id, const std::string& name, int number, int worknumber, double efficiency) {
    stations.emplace_back(id, name, number, worknumber, efficiency);
}
void PipeManager::deleteStation(int id) {
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        if (it->getId() == id) {
            stations.erase(it);
            std::cout << "Station with ID " << id << " deleted successfully.\n";
            return;
        }
    }
    std::cerr << "Error: Station with ID " << id << " not found.\n";
}
void PipeManager::editStation(int id) {
    for (auto& station : stations) {
        if (station.getId() == id) {
            std::string newName;
            int newNumber, newWorknumber;
            double newEfficiency;

            std::cout << "Current Name: " << station.getName() << ". New Name: ";
            std::cin >> newName;
            std::cout << "Current Number of Sites: " << station.getNumber() << ". New Number of Sites: ";
            std::cin >> newNumber;
            std::cout << "Current Number of Jobs: " << station.getWorknumber() << ". New Number of Jobs: ";
            std::cin >> newWorknumber;

            newEfficiency = static_cast<double>(newWorknumber) / newNumber;

            station.setName(newName);
            station.setNumber(newNumber);
            station.setWorknumber(newWorknumber);
            station.setXiaolv(newEfficiency);

            std::cout << "Station updated successfully.\n";
            return;
        }
    }
    std::cerr << "Error: Station with ID " << id << " not found.\n";
}
void PipeManager::batchModifyPipes(const std::string& filterName, bool* filterMaint, double newLength, bool* newMaint) {
    for (auto& pipe : pipes) {
        bool matchName = filterName.empty() || pipe.getName().find(filterName) != std::string::npos;
        bool matchMaint = !filterMaint || (*filterMaint == pipe.getMaint());

        if (matchName && matchMaint) {
            if (newLength > 0) {
                pipe.setLength(newLength);
            }
            if (newMaint) {
                pipe.setMaint(*newMaint);
            }

            std::cout << "Modified PIPE: ID=" << pipe.getId()
                      << ", Name=" << pipe.getName()
                      << ", Length=" << pipe.getLength()
                      << ", Maintenance=" << pipe.getMaint() << "\n";
        }
    }
}
