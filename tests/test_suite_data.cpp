#include <boost/test/unit_test.hpp>

#include <qtm-calc/data.hpp>

/**
 * qtm::qtm_data tests
 */
BOOST_AUTO_TEST_SUITE(test_suite_data)

/**
 * qtm::qtm_data calcs tests
 */
BOOST_AUTO_TEST_SUITE(test_suite_data_calc)

/**
 * qtm::qtm_data::calc_avg_queue() test
 */
BOOST_AUTO_TEST_CASE(check_avg_queue) {
  auto comp = 0.2857142857142857;

  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.calc_final_states();
  auto ret = qtm::qtm_data::calc_avg_queue(qtm);

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_data::check_ete() test
 */
BOOST_AUTO_TEST_CASE(check_ete) {
  auto comp = 0.71428571428571419;

  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.calc_final_states();
  auto ret = qtm::qtm_data::calc_ete(qtm);

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_data::check_avg_time_queue() test
 */
BOOST_AUTO_TEST_CASE(check_avg_time_queue) {
  auto comp = 0.71428571428571419;

  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.calc_final_states();
  auto ret = qtm::qtm_data::calc_avg_time_queue(qtm);

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_data::calc_perc_served_req() test
 */
BOOST_AUTO_TEST_CASE(check_perc_served_req) {
  auto comp = 0.7142857142857143;

  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.calc_final_states();
  auto ret = qtm::qtm_data::calc_perc_served_req(qtm);

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_data::check_avg_count_served_req() test
 */
BOOST_AUTO_TEST_CASE(check_avg_count_served_req) {
  auto comp = 1.7142857142857142;

  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.calc_final_states();
  auto ret = qtm::qtm_data::calc_avg_count_served_req(qtm);

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_data::check_avg_count_req() test
 */
BOOST_AUTO_TEST_CASE(check_avg_count_req) {
  auto comp = 1.7142857142857142;

  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.calc_final_states();
  auto ret = qtm::qtm_data::calc_avg_count_req(qtm);

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_data::check_avg_count_unserved_req() test
 */
BOOST_AUTO_TEST_CASE(check_avg_count_unserved_req) {
  auto comp = 1.5760463582836595;

  qtm::qtm qtm(4, 20, 37.75, 12);
  qtm.calc_final_states();
  auto ret = qtm::qtm_data::calc_avg_count_unserved_req(qtm);

  BOOST_TEST(comp == ret);
};

BOOST_AUTO_TEST_SUITE_END() // test_suite_data_calc

BOOST_AUTO_TEST_SUITE_END() // test_suite_data
