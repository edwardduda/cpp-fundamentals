#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

std::vector<std::vector<int>> create_image_v(const std::string &img_file);
void printMatrix(const std::vector<std::vector<int>> &matrix);
std::vector<int> create_check_sum_v(const std::string &checksum_file);
int validate_image(const std::vector<std::vector<int>> &image, const std::vector<int> checksum);
void normalize_image(std::vector<std::vector<int>> &image, int max_possible_val);
void write_normalized_image(const std::string &output_file, const std::vector<std::vector<int>> &image, int columns, int rows, int max_val);

int g_columns = 0, g_rows = 0, g_max_val = 0;
int main(int argc, char* argv[]) {
    if(argc != 3){
        std::cout << "Not enought arguments\n";
        return -1;
    }
    std::vector<std::vector<int>> image = create_image_v(argv[1]);
    
    if(image.empty()){
        // Error messages already printed in create_image_v.
        return -1;
    }

    normalize_image(image, g_max_val);

    write_normalized_image(argv[2], image, g_columns, g_rows, g_max_val);

    std::cout << "Image normalized and written successfully." << std::endl;
    return 0;
}

int validate_image(const std::vector<std::vector<int>> &image, const std::vector<int> checksum){
    
    if(image.size() != checksum.size()){
        std::cerr << "The image and checksum need the same number of rows." 
        << image.size()
         << " "
        << checksum.size()
        << std::endl;
        return -1;
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
            return -1;
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

void normalize_image(std::vector<std::vector<int>> &image, int max_possible_val){
    int min_val = max_possible_val, max_val = 0;

    for(const auto &row : image){
        for(int val : row){
            if(val < min_val){
                min_val = val;
            }
            if(val > max_val){
                max_val = val;
            }
        }
    }

    if(max_val == min_val){
        std::cerr << "All pixels have the same intensity. Normalization will fail." << std::endl;
        for(auto &row : image){
            for(auto &val : row){
                val = 0;
            }
        }
        return;
    }

    for(auto &row : image){
        for(auto &val : row) {
            double normalized = (static_cast<double>(val - min_val) / (max_val - min_val)) * max_possible_val;
            val = static_cast<int>(std::round(normalized));
        }
    }
}

void write_normalized_image(const std::string &outputfile, const std::vector<std::vector<int>> &image, int columns, int rows, int max_val){
    std::ofstream file(outputfile);
    if(!file){
        std::cerr << "Error: Unable to open output file." << std::endl;
        std::exit(-1);
    }

    file << "P3" << "\n";
    file << columns << " " << rows << "\n";
    file << max_val << "\n";

    for(const auto &row : image){
        for(int val : row){
            file << val << " ";
        }
        file << "\n";
    }

    file.close();

}
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}




