#include <iostream>
#include <fstream>
#include <vector>
#include <string>


int main(int argc, char* argv[]) {
    if(argc != 3){
        return 1;
    }
}

std::vector<std::vector<char>> create_image_v(const std::string &file_name){
    
    std::vector<std::vector<char>>ascii_vector;

    std::fstream file(file_name);
    if(!file){
        std::cerr << "Not able to open file.";
        return ascii_vector;
    }
    std::string line;
    while (std::getline(file, line)){
        ascii_vector.push_back(std::vector<char>(line.begin(), line.end()));
    }

    file.close();

    return ascii_vector;
}

int calculate_row_sum(){
    //pass
}



