#pragma once

#include <array>

class CodeGenerator {
public:
    virtual ~CodeGenerator() = default;
    
    // Generate a secret code with 4 distinct digits (0-9)
    virtual std::array<int, 4> generateCode() = 0;
};