#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <array>
#include <string>
#include <sstream>

#include <doctest/doctest.h>

#include <yaml-cpp/yaml.h>

auto CONFIG = R"(---
- just: write some
- yaml: 
  - [here, and]
  - {it: has, a: 42}
)";


TEST_SUITE ("Example derived tests.") {
    TEST_CASE ("No error in parsing the example report.") {
        /* Example snippet:
         *
         * YAML::Node config = YAML::Load(CONFIG);
         * std::cout << "Parsed YAML:\n" << config << "\n";
         */
        YAML::Node config = YAML::Load(CONFIG);
        REQUIRE(config);
    }
}
