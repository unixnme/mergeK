#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>

using Queue_t = std::pair<std::string, std::ifstream*>;

class Compare {
public:
    bool operator()(const Queue_t& a, const Queue_t& b) {
        return a.first > b.first;
    }
};

int main(int argc, const char** argv) {
    std::priority_queue<Queue_t, std::vector<Queue_t>, Compare> priorityQueue;

    std::vector<std::ifstream> files(argc - 1);
    std::string line;
    for (int i=1; i<argc; i++) {
        auto &ifs = files[i-1];
        ifs = std::ifstream{argv[i]};
        if (std::getline(ifs, line)) {
            priorityQueue.emplace(std::make_pair(
                    line, &ifs
                    ));
        }
    }
    std::string prev;
    while (!priorityQueue.empty()) {
        const auto& item = priorityQueue.top();
        if (item.first != prev)
            std::cout << item.first << std::endl;
        prev = item.first;

        auto &ifs = *item.second;
        if (std::getline(ifs, line)) {
            priorityQueue.emplace(std::make_pair(
                    line, &ifs
            ));
        }

        priorityQueue.pop();
    }

    return 0;
}