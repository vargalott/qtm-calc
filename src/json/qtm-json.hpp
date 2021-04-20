#pragma once
#ifndef __QTM_JSON_HPP__
#define __QTM_JSON_HPP__

#include <fstream>
#include <iostream>
#include <string>

#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include <qtm-data.hpp>

namespace qtm {

/**
 * Performing json operations for a queuing system
 *
 * ...
 *
 * Implements a method for reading and writing json data for a queuing system
 */
class qtm_json final : private boost::noncopyable {
private:
  boost::property_tree::ptree root_in;
  boost::property_tree::ptree root_out;

  /**
   * Perform reading json file from a given path
   *
   * @param[in] path Path to the json file
   */
  void read(std::string path);
  /**
   * Perform processing of given data from method read() and
   * preparing data to writing by method write()
   */
  void process(void);
  /**
   * Perform writing json file from a given path
   *
   * @param[in] path Path to the json file
   */
  void write(std::string path);

public:
  qtm_json(void) = default;
  ~qtm_json(void) = default;

  /**
   * Perform the data processing from a given json file
   * and write the json result from a given path
   *
   * @param[in] in Path to input json file
   * @param[in] out Path to output json file
   */
  void run(std::string in, std::string out);
};

}; // namespace qtm

#endif // !__QTM_JSON_HPP__
