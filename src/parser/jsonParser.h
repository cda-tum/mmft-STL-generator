#include "nlohmann/json.hpp"

#include "jsonReader.h"

namespace parser {

/**
 * @brief Constructor of the Network from a JSON file
 * @param[in] jsonFile Location of the json file
 * @returns Network network
*/
arch::Network networkFromJSON(std::string jsonFile);

/**
 * @brief Define an existing Network from a JSON file
 * @param[in] jsonFile location of the json file
 * @param[in] network network object that needs to be defined
 * @returns Network network
*/
void networkFromJSON(std::string jsonFile, arch::Network& network);

/**
 * @brief Constructor of the Network from a JSON string
 * @param[in] json json string
 * @returns Network network
*/
arch::Network networkFromJSON(nlohmann::json jsonString);

}   // namesapce parser