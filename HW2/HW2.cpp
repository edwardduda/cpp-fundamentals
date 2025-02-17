#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<char>> create_image_v(const std::string &img_file);
void printMatrix(const std::vector<std::vector<char>> &matrix);
std::vector<char> create_check_sum_v(const std::string &checksum_file);
int validate_image(const std::vector<std::vector<char>> &image, const std::vector<char> checksum);

int main(int argc, char* argv[]) {
    if(argc != 3){
        std::cout << "Not enought arguments\n";
        return 1;
    }
    std::vector<std::vector<char>> image = create_image_v(argv[1]);
    std::vector<char> checksum = create_check_sum_v(argv[2]);
    
    validate_image(image, checksum);

    printMatrix(image);

}

int validate_image(const std::vector<std::vector<char>> &image, const std::vector<char> checksum){
    
    if(image.size() != checksum.size()){
        std::cerr << "The image and checksum need the same number of rows." << std::endl;
        return -2;
    }
    
    for(size_t row = 0; row < image.size(); row++){
        int sum = 0;
        for(size_t column; column < image.size(); column++){
            sum += image[row][column];
        }

        if(sum != checksum[row]){
            std::cerr << "Image row and check row aren't equal. Expect sum: "
            << checksum[row]
            << "Actual: "
            << sum;
            return -3;
        }
        
    }
    return 0;
}
std::vector<char> create_check_sum_v(const std::string &checksum_file){
    std::vector<char> check_sum_v;

    std::fstream file(checksum_file);
    if(!file){
        std::cerr << "Not able to open file." << std::endl;
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
        std::cerr << "Not able to open file." << std::endl;
        return ascii_vector;
    }
    std::string line;
    int line_count = 0;
    while (std::getline(file, line)){
        if (line_count < 2) {
            line_count++;
            continue;
        }
        ascii_vector.push_back(std::vector<char>(line.begin(), line.end()));
    }

    file.close();
    
    return ascii_vector;
}


void printMatrix(const std::vector<std::vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char c : row) {
            std::cout << c ;
        }
        std::cout << std::endl;
    }
}




