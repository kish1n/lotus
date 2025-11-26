#pragma once

#include <iostream>
#include <string>

inline void fatal(std::string err) {
    std::cerr << err << std::endl;
    std::terminate();
}
