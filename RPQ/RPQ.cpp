#include <iostream>
#include <vector>
#include <fstream>
#include <string>


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
   
    std::vector<Task> tasks;
    std::vector<int32_t> order = { 1,2,3,4,5,6,7 }; //Cmax = 58


    if (loadFromFile("Data\\Test1.txt", tasks))
    {

        for (int32_t i = 0; i < tasks.size(); i++)
        {
            std::cout << tasks[i].id << " " << tasks[i].r << " " << tasks[i].p << " " << tasks[i].q << std::endl;
        }
    }


    std::cout << "\nCost: " << getCost(tasks, order) << std::endl;
}




