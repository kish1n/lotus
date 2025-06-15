export module lotus:base;

import std;

export inline void fatal(std::string err) {
    std::cerr << err << std::endl;
    std::terminate();
}
