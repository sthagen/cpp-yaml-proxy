
#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>

auto CONFIG = R"(---
- just: write some
- yaml: 
  - [here, and]
  - {it: has, a: 42}
)";

int main() {
    YAML::Node config = YAML::Load(CONFIG);
    std::cout << "Parsed YAML:\n" << config << "\n";
}
