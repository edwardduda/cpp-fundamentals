#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<char>> create_image_v(const std::string &img_file);
void printMatrix(const std::vector<std::vector<char>> &matrix);
std::vector<char> create_check_sum_v(const std::string &checksum_file);

int main(int argc, char* argv[]) {
    if(argc != 3){
        std::cout << "Not enought arguments\n";
        return 1;
    }
    std::vector<std::vector<char>> image = create_image_v(argv[1]);

    printMatrix(image);

}
std::vector<char> create_check_sum_v(const std::string &checksum_file){
    std::vector<char> check_sum_v;

    std::fstream file(checksum_file);
    if(!file){
        std::cerr << "Not able to open file.";
        return check_sum_v;
    }

    char row_sum;
    while (file.get(row_sum)) {
        check_sum_v.push_back(row_sum);
    }

    file.close();

    return check_sum_v;
}

std::vector<std::vector<char>> create_image_v(const std::string &img_file){
    
    std::vector<std::vector<char>>ascii_vector;

    std::fstream file(img_file);
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

void printMatrix(const std::vector<std::vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}




