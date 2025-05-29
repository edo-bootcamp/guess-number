#include "code_generator.h"
#include <random>
#include <algorithm>

class RandomCodeGenerator : public CodeGenerator {
public:
    std::array<int, 4> generateCode() override {
        // Initialize array with digits 0-9
        std::array<int, 10> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        // Set up random number generator
        std::random_device rd;
        std::mt19937 gen(rd());
        
        // Shuffle the digits
        std::shuffle(digits.begin(), digits.end(), gen);
        
        // Take the first 4 digits as our secret code
        std::array<int, 4> code;
        for (int i = 0; i < 4; ++i) {
            code[i] = digits[i];
        }
        
        return code;
    }
};
