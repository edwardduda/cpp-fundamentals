#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<std::vector<int>> create_image_v(const std::string &img_file);
void printMatrix(const std::vector<std::vector<int>> &matrix);
std::vector<int> create_check_sum_v(const std::string &checksum_file);
int validate_image(const std::vector<std::vector<int>> &image, const std::vector<int> checksum);

int main(int argc, char* argv[]) {
    if(argc != 3){
        std::cout << "Not enought arguments\n";
        return -1;
    }
    std::vector<std::vector<int>> image = create_image_v(argv[1]);
    std::vector<int> checksum = create_check_sum_v(argv[2]);
    
    return validate_image(image, checksum);
}

int validate_image(const std::vector<std::vector<int>> &image, const std::vector<int> checksum){
    
    if(image.size() != checksum.size()){
        std::cerr << "The image and checksum need the same number of rows." 
        << image.size()
         << " "
        << checksum.size()
        << std::endl;
        return -2;
    }
    
    for(size_t row = 0; row < image.size(); row++){
        int sum = 0;
        for(size_t column = 0; column < image[row].size(); column++){
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

    std::cout << "Pass" << std::endl;
    return 0;
}

std::vector<int> create_check_sum_v(const std::string &checksum_file){
    std::vector<int> check_sum_v;

    std::fstream file(checksum_file);
    if(!file){
        std::cerr << "Not able to open file." << std::endl;
        return check_sum_v;
    }

    int row_sum;
    while (file >> row_sum) {
        check_sum_v.push_back(row_sum);
    }

    file.close();

    return check_sum_v;
}

std::vector<std::vector<int>> create_image_v(const std::string &img_file){
    
    std::vector<std::vector<int>>ascii_vector;

    std::fstream file(img_file);
    if(!file){
        std::cerr << "Not able to open file." << std::endl;
        return ascii_vector;
    }
    std::string img_format;
    file >> img_format;
    if(img_format != "P3"){
        std::cerr << "File format error. Expected P3 but got " << img_format << std::endl;
        return ascii_vector;
    }

    int columns, rows, max_val;
    file >> columns >> rows >> max_val;
    if(columns < 1 || rows < 1 || max_val < 0){
        std::cerr << "Specifications can not be negative.";
        return ascii_vector;
    }

    for (int row = 0; row < rows; row++){
        std::vector<int> row_values;
        for(int column = 0; column < columns * 3; column++){
            int pixel_value;
            file >> pixel_value;
            row_values.push_back(pixel_value);
        }
        ascii_vector.push_back(row_values);
    }

    file.close();
    
    return ascii_vector;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}




