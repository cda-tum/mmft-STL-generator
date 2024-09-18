/**
 * @file jsonReader.h
 */

#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace stl {

/**
 * @brief Construct and store the nodes in the network as defined by the json string
 * @param[in] jsonString json string
 * @param[in] network network object
*/
void readNodes (json jsonString, Network& network);

/**
 * @brief Construct and store the channels in the network as defined by the json string
 * @param[in] jsonString json string
 * @param[in] network network object
*/
void readChannels (json jsonString, Network& network);

}   // namespace porting
