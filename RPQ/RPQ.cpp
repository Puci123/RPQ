﻿#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <chrono>


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


int main()
{
   
    std::vector<Task> tasks, tasksSortByR, tasksSortByP, tasksSortByQ;
    std::vector<int32_t> order; //Cmax = 58
    uint8_t numberOfTasks = 24;

    auto start = std::chrono::high_resolution_clock::now();

    if (loadFromFile("Data\\P2.txt", tasks))
    {
        tasksSortByR = tasks;
        tasksSortByP = tasks;
        tasksSortByQ = tasks;

        int32_t bestResult = 1000000;
        int32_t costValue = 0;

        std::sort(tasksSortByR.begin(), tasksSortByR.end(), [](const Task& a, const Task& b) {
            return a.r < b.r;
        });

        for (int a = 0; a < 10; a++) {
            for (int i = 0; i < tasksSortByR.size() - 1; i++) {
                for (int j = i + 1; j < tasksSortByR.size(); j++) {
                    Task temp = tasksSortByR[i];
                    tasksSortByR[i] = tasksSortByR[j];
                    tasksSortByR[j] = temp;


                    costValue = getCost(tasksSortByR);
                    if (costValue < bestResult) {
                        bestResult = costValue;
                    }
                    else {
                        tasksSortByR[j] = tasksSortByR[i];
                        tasksSortByR[i] = temp;
                    }
                }
            }
        }

        std::cout << "Cost of tasksSortByR: " << bestResult << std::endl;

        //std::sort(tasksSortByP.begin(), tasksSortByP.end(), [](const Task& a, const Task& b) {
        //    return a.p < b.p;
        //});
        //std::sort(tasksSortByQ.begin(), tasksSortByQ.end(), [](const Task& a, const Task& b) {
        //    return a.q < b.q;
        //});

    }
    else {
        std::cout << "Nie otworzono pliku" << std::endl;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.f;

    std::cout << "Czas calego programu: " << duration << "s" << std::endl;
}




