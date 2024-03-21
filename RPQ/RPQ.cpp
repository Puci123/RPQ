#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>
#include <limits.h>
#include <sstream>
#include <filesystem>
#include <regex>




struct  Task
{
    int32_t id = -1;
    int32_t r = -1;
    int32_t p = -1;
    int32_t q = -1;
};

bool loadFromFile(const std::string& path, std::vector<Task>& tasks) 
{
    std::ifstream file;
    std::string line;
    int32_t id = 0;
   

    file.open(path);

    if (!file.is_open()) return false;

    std::getline(file, line);

    while (std::getline(file, line))
    {
        
        int32_t temp[3]{-1};
        int32_t pos = 0;
        int8_t i = 0;

        
        while (pos < line.size())
        {
            pos = line.find(' ');
            temp[i++] = std::stoi(line.substr(0, pos));
            line.erase(0, pos + 1);



        }

        tasks.push_back(Task{id++, temp[0], temp[1],temp[2] });

    }

    return true;
}

int32_t getCost(const std::vector<Task>& tasks)
{
    int32_t costT = 0;
    int32_t costU = 0;


    for (int32_t i = 0; i < tasks.size(); i++)
    {
        costT = std::max(costT, tasks[i].r ) + tasks[i].p;
        costU = std::max(costU, costT + tasks[i].q);
    }

    return costU;
}


int32_t orderTask(std::vector<Task>& tasks, int32_t n = 10)
{

    int32_t bestResult = 1000000;
    int32_t costValue = 0;
    
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {return a.r < b.r; });

    for (int a = 0; a < 10; a++)
    {
        for (int i = 0; i < tasks.size() - 1; i++) {
            for (int j = i + 1; j < tasks.size(); j++) 
            {
                Task temp = tasks[i];
                tasks[i] = tasks[j];
                tasks[j] = temp;


                costValue = getCost(tasks);
                if (costValue < bestResult) 
                {
                    bestResult = costValue;
                }
                else 
                {
                    tasks[j] = tasks[i];
                    tasks[i] = temp;
                }
            }
        }
    }

    return bestResult;
}


std::string printTasks(const std::vector<Task>& tasks)
{
    std::stringstream ss;

    for (int32_t i = 0; i < tasks.size(); i++)
    {
        ss << tasks[i].id << " ";
    }

    return ss.str();
}

int32_t  test(const std::string& path, float& totalDiuration) 
{
    std::vector<Task> tasks;
    int32_t cost = 0;
    
    std::regex regex("\\\\.*\\.txt$");
    std::smatch match;

    if (std::regex_search(path, match, regex))
    {
        std::string filename = match.str().substr(1);

        if (loadFromFile(path, tasks))
        {
            auto m_StartPoint = std::chrono::high_resolution_clock::now();
            cost = orderTask(tasks);
            auto m_EndPoint = std::chrono::high_resolution_clock::now();
            auto  m_Diuration = std::chrono::duration_cast<std::chrono::microseconds>(m_EndPoint - m_StartPoint).count() / 1000000.f;

            std::cout << "\033[1;32m[" << filename << "]\033[0m" << " koszt:" << cost << " czas wykonia : " << m_Diuration << "s" << std::endl;
            std::cout << "Uporzadkowanie zadan: " << printTasks(tasks) << std::endl << std::endl;

            totalDiuration += m_Diuration;

        }
        else
        {
            std::cout << "\033[1;31m[" << path << "]\033[0m" << " nie mozna otworzyc pliku" << std::endl;
        }
    }
    else
    {
        std::cout << "\033[1;31m[" << path << "]\033[0m" << " nieprawidlowa sciezka pliku " << std::endl;
    }

    return cost;
}


int main()
{

    float totalDiuration = 0;
    int32_t totalCost = 0;
    std::string targetDir = "Data";

    for (const auto& entry: std::filesystem::directory_iterator(targetDir))
    {
        totalCost += test(entry.path().string(), totalDiuration);
    }


    std::cout << "=========================================================" << std::endl;
    std::cout << "Calkowity koszt: " << totalCost << std::endl;
    std::cout << "Calkowity czas: " << totalDiuration << "s" << std::endl;


}





