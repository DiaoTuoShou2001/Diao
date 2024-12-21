#ifndef PIPEMANAGER_H
#define PIPEMANAGER_H

#include <vector>
#include <string>
#include "guandao.h"
#include "bengzhan.h"

class PipeManager {
private:
    std::vector<guandao> pipes;   // 管道列表
    std::vector<bengzhan> stations; // 泵站列表

public:
    // 构造函数和析构函数
    PipeManager();
    ~PipeManager();

    // 数据加载和保存
    void loadData(const std::string& filename = "data.txt");
    void saveData(const std::string& filename = "data.txt");

    // 管道操作
    void addPipe(int id, const std::string& name, double length, bool maint, int startStationId = -1, int endStationId = -1);
    void editPipe(int id);
    void deletePipe(int id);
    void batchModifyPipes(const std::string& filterName = "", bool* filterMaint = nullptr, double newLength = -1, bool* newMaint = nullptr);

    // 泵站操作
    void addStation(int id, const std::string& name, int number, int worknumber, double efficiency);
    void editStation(int id);
    void deleteStation(int id);

    // 搜索功能
    void searchPipes(const std::string& filterName = "", bool* filterMaint = nullptr);
    void searchStations(const std::string& filterName = "", double* minEfficiency = nullptr, double* maxEfficiency = nullptr);

    // 管道与泵站关联
    void setPipeStations(int pipeId, int startStationId, int endStationId);

    // 获取数据
    const std::vector<guandao>& getPipes() const { return pipes; }
    const std::vector<bengzhan>& getStations() const { return stations; }



};

#endif // PIPEMANAGER_H
