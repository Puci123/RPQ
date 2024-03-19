#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>


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


int32_t getCost(const std::vector<Task>& tasks, const std::vector<int32_t>& order)
{
    int32_t costT = 0;
    int32_t costU = 0;


    for (int32_t i = 0; i < order.size(); i++)
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

    for (int i = 0; i < numberOfTasks; i++) {
        order.push_back(i);
    }


    if (loadFromFile("Data\\P1.txt", tasks))
    {
        tasksSortByR = tasks;
        tasksSortByP = tasks;
        tasksSortByQ = tasks;

        std::sort(tasksSortByR.begin(), tasksSortByR.end(), [](const Task& a, const Task& b) {
            return a.r < b.r;
        });
        std::sort(tasksSortByP.begin(), tasksSortByP.end(), [](const Task& a, const Task& b) {
            return a.p < b.p;
        });
        std::sort(tasksSortByQ.begin(), tasksSortByQ.end(), [](const Task& a, const Task& b) {
            return a.q < b.q;
        });


        std::cout << "\nCost of tasksSortByR: " << getCost(tasksSortByR, order) << std::endl;
        std::cout << "\nCost of tasksSortByP: " << getCost(tasksSortByP, order) << std::endl;
        std::cout << "\nCost of tasksSortByQ: " << getCost(tasksSortByQ, order) << std::endl;
    }

}




