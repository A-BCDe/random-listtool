#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <string_view>
#include <vector>

constexpr int swap_cnt = 5;

int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cerr << "Requires input and output file name." << std::endl;
        return 1;
    }

    std::ifstream in(argv[1]);
    if(!in.is_open()) {
        std::cerr << "There is no file named \"" << argv[1] << "\"." << std::endl;
        return 1;
    }
    
    std::vector<std::string> data;
    std::string line;
    while(std::getline(in, line)) {
        size_t l = 0;
        size_t r = line.size();

        while(line[l] == ' ' && l < r) l++;
        while(line[r - 1] == ' ' && line[r - 1] == '\n' && l < r) r--;
        auto const s = line.substr(l, r - l);

        if(s == "") continue;
        data.push_back(s);
    }
    in.close();

    auto i = data.size();

    std::ofstream out(argv[2]);
    std::random_device rd;
    std::mt19937_64 rnd(rd());
    std::uniform_int_distribution<size_t> range(0, i);

    while(i--) {
        auto const idx = range(rnd);
        auto const tmp = data[i];
        data[i] = data[idx];
        data[idx] = tmp;
        out << data[i] << std::endl;
    }
    out.close();
}