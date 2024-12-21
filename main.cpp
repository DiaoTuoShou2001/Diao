#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "jianmo.h"
#include "PipeManager.h"
#include "guandao.h"
#include "bengzhan.h"
#include "Graph.h"
#include "guandao.h"
#include "bengzhan.h"
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "jianmo.h"
#include "PipeManager.h"
#include "guandao.h"
#include "bengzhan.h"
#include "Graph.h"

int main() {
    PipeManager manager;
    // Load existing data from file
    const char *file1 = "/home/yingpan/sdb2/c3/c++/dz/data.txt";
    manager.loadData(file1);

    // 获取加载的数据
    const auto& pipes = manager.getPipes();
    const auto& stations = manager.getStations();

    std::cout << "Number of pipes loaded: " << pipes.size() << "\n";
    std::cout << "Number of stations loaded: " << stations.size() << "\n";

    while (true) {
        // Display menu options
        std::cout << "\nSelect operation:\n"
                     "1.  Update pipeline information\n"
                     "2.  Update station information\n"
                     "3.  Display all pipeline information\n"
                     "4.  Display all station information\n"
                     "5.  Save data to file\n"
                     "6.  Display specific pipeline information\n"
                     "7.  Display specific station information\n"
                     "8.  Delete pipeline information\n"
                     "9.  Build and display gas network graph\n"
                     "10. Batch Modify Pipeline\n"
                     "0.  End program\n";

        int choice;
        // Get user choice
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                std::string name;
                double length;
                bool maint;

                // 获取管道 ID
                std::cout << "\nInput pipe id number: ";
                std::cin >> id;

                // 检查输入是否有效
                if (std::cin.fail()) {
                    std::cerr << "Error: Invalid input for pipe ID. Please enter an integer.\n";
                    std::cin.clear(); // 清除错误状态
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 丢弃无效输入
                    break;
                }

                // 检查是否存在重复 ID
                bool exists = false;
                for (const auto &pipe : pipes) {
                    if (pipe.getId() == id) {
                        exists = true;
                        break;
                    }
                }

                if (exists) {
                    std::cerr << "\nError: Pipeline with this ID already exists.\n";
                    break;
                }

                // 获取管道名称
                std::cout << "\nEnter pipeline name: ";
                std::cin >> name;

                // 获取管道长度
                std::cout << "\nEnter pipeline length: ";
                std::cin >> length;

                // 检查输入是否有效
                if (std::cin.fail() || length <= 0) {
                    std::cerr << "Error: Invalid input for pipeline length. It must be a positive number.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                // 获取维护状态
                std::cout << "\nIs it under maintenance? Enter '1' for Yes or '0' for No: ";
                std::cin >> maint;

                // 检查输入是否有效
                if (std::cin.fail() || (maint != 0 && maint != 1)) {
                    std::cerr << "Error: Invalid input for maintenance status. Please enter '0' or '1'.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                // 添加管道信息
                manager.addPipe(id, name, length, maint);
                std::cout << "\nPipeline information updated successfully.\n";
            } break;

            case 2: {
                    int id, number, worknumber;
                    std::string name;

                    // 获取泵站 ID
                    std::cout << "Input station id: ";
                    std::cin >> id;

                    // 检查输入是否有效
                    if (std::cin.fail()) {
                        std::cerr << "Error: Invalid input for station ID. Please enter an integer.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }

                    // 获取泵站名称
                    std::cout << "Enter site name: ";
                    std::cin >> name;

                    // 获取站点总数
                    std::cout << "Enter the number of sites: ";
                    std::cin >> number;

                    // 检查输入是否有效
                    if (std::cin.fail() || number <= 0) {
                        std::cerr << "Error: Invalid input for the number of sites. It must be a positive integer.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }

                    // 获取工作站点数
                    std::cout << "Enter the number of jobs: ";
                    std::cin >> worknumber;

                    // 检查输入是否有效
                    if (std::cin.fail() || worknumber <= 0) {
                        std::cerr << "Error: Invalid input for the number of jobs. It must be a positive integer.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }

                    // 计算效率，并检查是否合理
                    if (worknumber > number) {
                        std::cerr << "Error: The number of jobs cannot exceed the total number of sites.\n";
                        break;
                    }

                    double xiaolv = static_cast<double>(worknumber) / number;

                    // 添加泵站信息
                    manager.addStation(id, name, number, worknumber, xiaolv);

                    std::cout << "Site information has been updated.\n";
                } break;
                case 3: {
                if (pipes.empty()) {
                    std::cout << "No pipelines available to display.\n";
                } else {
                    for (const auto &pipe : pipes) {
                        pipe.display();
                    }
                }
                break;
            }
            case 4: {
                if (stations.empty()) {
                    std::cout << "No stations available to display.\n";
                } else {
                    for (const auto &station : stations) {
                        station.display();
                    }
                }
                break;
            }
            case 5: { // 保存
                manager.saveData(file1);
                std::cout << "Data saved successfully.\n";
                break;
            }
            case 6: { // 搜索并操作管道
                int searchOption;
                std::cout << "Search pipelines by:\n"
                          << "1. ID\n"
                          << "2. Name or Maintenance Status\n"
                          << "Enter your choice: ";
                std::cin >> searchOption;

                if (std::cin.fail() || (searchOption != 1 && searchOption != 2)) {
                    std::cerr << "Error: Invalid choice. Please enter '1' or '2'.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                std::vector<guandao> filteredPipes;

                if (searchOption == 1) { // 按 ID 搜索
                    int id;
                    std::cout << "Enter the pipeline ID to search: ";
                    std::cin >> id;

                    if (std::cin.fail()) {
                        std::cerr << "Error: Invalid input for pipeline ID. Please enter an integer.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }

                    // 遍历管道列表，查找匹配的 ID
                    for (const auto &pipe : manager.getPipes()) {
                        if (pipe.getId() == id) {
                            filteredPipes.push_back(pipe);
                            pipe.display(); // 显示匹配的管道信息
                        }
                    }

                    if (filteredPipes.empty()) {
                        std::cout << "No pipeline found with ID: " << id << "\n";
                        break;
                    }

                } else if (searchOption == 2) { // 按名称或维修状态搜索
                    std::string filterName;
                    bool filterMaint;
                    bool useNameFilter = false, useMaintFilter = false;

                    // 询问用户是否按名称搜索
                    std::cout << "Do you want to search by name? Enter '1' for Yes, '0' for No: ";
                    int nameChoice;
                    std::cin >> nameChoice;

                    if (nameChoice == 1) {
                        useNameFilter = true;
                        std::cout << "Enter the pipeline name (or part of the name): ";
                        std::cin >> filterName; // 获取用户输入的名称过滤条件
                    }

                    // 询问用户是否按维修状态搜索
                    std::cout << "Do you want to search by maintenance status? Enter '1' for Yes, '0' for No: ";
                    int maintChoice;
                    std::cin >> maintChoice;

                    if (maintChoice == 1) {
                        useMaintFilter = true;
                        std::cout << "Enter '1' for pipelines under maintenance, '0' for not under maintenance: ";
                        int maintInput;
                        std::cin >> maintInput;

                        if (std::cin.fail() || (maintInput != 0 && maintInput != 1)) {
                            std::cerr << "Error: Invalid input for maintenance status. Please enter '0' or '1'.\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            break;
                        }

                        filterMaint = (maintInput == 1);
                    }

                    // 根据用户选择的过滤条件筛选管道
                    for (const auto &pipe : manager.getPipes()) {
                        bool matchName = !useNameFilter || pipe.getName().find(filterName) != std::string::npos;
                        bool matchMaint = !useMaintFilter || pipe.getMaint() == filterMaint;

                        if (matchName && matchMaint) {
                            filteredPipes.push_back(pipe);
                            pipe.display(); // 显示匹配的管道信息
                        }
                    }

                    if (filteredPipes.empty()) {
                        std::cout << "No pipelines found matching the criteria.\n";
                        break;
                    }
                }

                // 提供操作选项：删除或修改筛选结果
                std::cout << "What do you want to do with the filtered pipelines?\n"
                          << "1. Delete\n"
                          << "2. Modify\n"
                          << "0. Cancel\n";

                int actionChoice;
                std::cin >> actionChoice;

                if (actionChoice == 1) { // 删除操作
                    for (const auto &pipe : filteredPipes) {
                        manager.deletePipe(pipe.getId()); // 按 ID 删除管道
                    }
                    std::cout << "Selected pipelines have been deleted.\n";

                } else if (actionChoice == 2) { // 修改操作
                    for (auto &pipe : filteredPipes) {
                        manager.editPipe(pipe.getId()); // 按 ID 修改管道信息
                    }
                    std::cout << "Selected pipelines have been modified.\n";

                } else {
                    std::cout << "Operation canceled.\n";
                }

            } break;


            case 7: { // 搜索并操作泵站
                int searchOption;
                std::cout << "Search stations by:\n"
                          << "1. ID\n"
                          << "2. Name or Efficiency Range\n"
                          << "Enter your choice: ";
                std::cin >> searchOption;

                if (std::cin.fail() || (searchOption != 1 && searchOption != 2)) {
                    std::cerr << "Error: Invalid choice. Please enter '1' or '2'.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                std::vector<bengzhan> filteredStations;

                if (searchOption == 1) { // 按 ID 搜索
                    int id;
                    std::cout << "Enter the station ID to search: ";
                    std::cin >> id;

                    if (std::cin.fail()) {
                        std::cerr << "Error: Invalid input for station ID. Please enter an integer.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                    }

                    // 遍历泵站列表，查找匹配的 ID
                    for (const auto &station : manager.getStations()) {
                        if (station.getId() == id) {
                            filteredStations.push_back(station);
                            station.display(); // 显示匹配的泵站信息
                        }
                    }

                    if (filteredStations.empty()) {
                        std::cout << "No station found with ID: " << id << "\n";
                        break;
                    }

                } else if (searchOption == 2) { // 按名称或效率范围搜索
                    std::string filterName;
                    double minEfficiency = 0.0, maxEfficiency = 1.0;
                    bool useNameFilter = false, useEfficiencyFilter = false;

                    // 询问用户是否按名称搜索
                    std::cout << "Do you want to search by name? Enter '1' for Yes, '0' for No: ";
                    int nameChoice;
                    std::cin >> nameChoice;

                    if (nameChoice == 1) {
                        useNameFilter = true;
                        std::cout << "Enter the station name (or part of the name): ";
                        std::cin >> filterName; // 获取用户输入的名称过滤条件
                    }

                    // 询问用户是否按效率范围搜索
                    std::cout << "Do you want to search by efficiency range? Enter '1' for Yes, '0' for No: ";
                    int efficiencyChoice;
                    std::cin >> efficiencyChoice;

                    if (efficiencyChoice == 1) {
                        useEfficiencyFilter = true;
                        std::cout << "Enter minimum efficiency: ";
                        std::cin >> minEfficiency;
                        std::cout << "Enter maximum efficiency: ";
                        std::cin >> maxEfficiency;

                        if (std::cin.fail() || minEfficiency < 0 || maxEfficiency > 1 || minEfficiency > maxEfficiency) {
                            std::cerr << "Error: Invalid efficiency range. Please enter values between 0 and 1.\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            break;
                        }
                    }

                    // 根据用户选择的过滤条件筛选泵站
                    for (const auto &station : manager.getStations()) {
                        bool matchName = !useNameFilter || station.getName().find(filterName) != std::string::npos;
                        bool matchEfficiency = !useEfficiencyFilter ||
                                               (station.getXiaolv() >= minEfficiency && station.getXiaolv() <= maxEfficiency);

                        if (matchName && matchEfficiency) {
                            filteredStations.push_back(station);
                            station.display(); // 显示匹配的泵站信息
                        }
                    }

                    if (filteredStations.empty()) {
                        std::cout << "No stations found matching the criteria.\n";
                        break;
                    }
                }

                // 提供操作选项：删除或修改筛选结果
                std::cout << "What do you want to do with the filtered stations?\n"
                          << "1. Delete\n"
                          << "2. Modify\n"
                          << "0. Cancel\n";

                int actionChoice;
                std::cin >> actionChoice;

                if (actionChoice == 1) { // 删除操作
                    for (const auto &station : filteredStations) {
                        manager.deleteStation(station.getId()); // 按 ID 删除泵站
                    }
                    std::cout << "Selected stations have been deleted.\n";

                } else if (actionChoice == 2) { // 修改操作
                    for (auto &station : filteredStations) {
                        manager.editStation(station.getId()); // 按 ID 修改泵站信息
                    }
                    std::cout << "Selected stations have been modified.\n";

                } else {
                    std::cout << "Operation canceled.\n";
                }

            } break;

            case 8: { // 删除管道信息
                int id;
                std::cout << "Enter the ID of the pipeline to delete: ";
                std::cin >> id;

                // 检查输入是否有效
                if (std::cin.fail()) {
                    std::cerr << "Error: Invalid input for pipeline ID. Please enter an integer.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }

                // 调用 PipeManager 的 deletePipe 方法
                manager.deletePipe(id);
            } break;

            case 9: {
                Graph gasNetwork;
                // Build graph using PipeManager data
                jianmo::buildGraphFromData(gasNetwork, manager);  // 使用 jianmo 命名空间
                gasNetwork.display(); // Display the constructed graph

                return 0;
            }
            case 10: { // 批量修改管道
                std::string filterName;
                bool filterMaint;
                double newLength;
                bool newMaint;
                bool useNameFilter = false, useMaintFilter = false;

                // 询问用户是否按名称筛选
                std::cout << "Do you want to filter by name? Enter '1' for Yes, '0' for No: ";
                int nameChoice;
                std::cin >> nameChoice;

                if (nameChoice == 1) {
                    useNameFilter = true;
                    std::cout << "Enter the pipeline name (or part of the name): ";
                    std::cin >> filterName;
                }

                // 询问用户是否按维护状态筛选
                std::cout << "Do you want to filter by maintenance status? Enter '1' for Yes, '0' for No: ";
                int maintChoice;
                std::cin >> maintChoice;

                if (maintChoice == 1) {
                    useMaintFilter = true;
                    std::cout << "Enter '1' for pipelines under maintenance, '0' for not under maintenance: ";
                    int maintInput;
                    std::cin >> maintInput;
                    filterMaint = (maintInput == 1);
                }

                // 获取新长度
                std::cout << "Enter new length for the pipelines (enter '-1' to skip): ";
                std::cin >> newLength;

                // 获取新的维护状态
                std::cout << "Enter new maintenance status ('1' for Yes, '0' for No, '-1' to skip): ";
                int maintInput;
                std::cin >> maintInput;

                if (maintInput != -1) {
                    newMaint = (maintInput == 1);
                    manager.batchModifyPipes(useNameFilter ? filterName : "",
                                             useMaintFilter ? &filterMaint : nullptr,
                                             newLength > 0 ? newLength : -1,
                                             &newMaint);
                } else {
                    manager.batchModifyPipes(useNameFilter ? filterName : "",
                                             useMaintFilter ? &filterMaint : nullptr,
                                             newLength > 0 ? newLength : -1,
                                             nullptr);
                }
            } break;
            case 11: {
                //计算流量


                return 0;
            }
            case 0:
                return 0;
            default:
                std::cerr << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
