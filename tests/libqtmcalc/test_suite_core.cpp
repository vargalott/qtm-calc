#include <boost/test/unit_test.hpp>

#include <qtm-core.hpp>

/**
 * qtm::qtm_core tests
 */
BOOST_AUTO_TEST_SUITE(test_suite_core)

/**
 * qtm::clamp() test
 */
BOOST_AUTO_TEST_CASE(check_clamp) {
  std::vector<std::uint64_t> comp = {3, 3, 3, 3, 4, 5, 5, 5, 5, 5};
  std::vector<std::uint64_t> ret;

  for (std::size_t i = 0; i < 10; ++i) {
    ret.push_back(qtm::clamp<std::uint64_t>(i, 3, 5));
  }

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_core getters tests
 */
#pragma region
BOOST_AUTO_TEST_SUITE(test_suite_core_getters)

/**
 * qtm::qtm_core::channel_count() test
 */
BOOST_AUTO_TEST_CASE(check_channel_count_getter) {
  qtm::qtm qtm(2, 1, 10., 5.);

  BOOST_TEST(qtm.channel_count() == 2);
};

/**
 * qtm::qtm_core::queue_size() test
 */
BOOST_AUTO_TEST_CASE(check_queue_size_getter) {
  qtm::qtm qtm(2, 1, 10., 5.);

  BOOST_TEST(qtm.queue_size() == 1);
};

/**
 * qtm::qtm_core::la() test
 */
BOOST_AUTO_TEST_CASE(check_la_getter) {
  qtm::qtm qtm(2, 1, 10., 5.);

  BOOST_TEST(qtm.la() == 10.);
};

/**
 * qtm::qtm_core::mu() test
 */
BOOST_AUTO_TEST_CASE(check_mu_getter) {
  qtm::qtm qtm(2, 1, 10., 5.);

  BOOST_TEST(qtm.mu() == 5.);
};

/**
 * qtm::qtm_core::nu() test
 */
BOOST_AUTO_TEST_CASE(check_nu_getter) {
  qtm::qtm qtm(2, 1, 10., 5., 1.5);

  BOOST_TEST(qtm.nu() == 1.5);
};

/**
 * qtm::qtm_core::n() test
 */
BOOST_AUTO_TEST_CASE(check_n_getter) {
  qtm::qtm qtm(2, 1, 10., 5., 1.5, 7);

  BOOST_TEST(qtm.n() == 7);
};

BOOST_AUTO_TEST_SUITE_END() // test_suite_core_getters
#pragma endregion

/**
 * qtm::qtm_core setters tests
 */
#pragma region
BOOST_AUTO_TEST_SUITE(test_suite_core_setters)

/**
 * qtm::qtm_core::channel_count(value) test
 */
BOOST_AUTO_TEST_CASE(check_channel_count_setter) {
  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.channel_count(3);

  BOOST_TEST(qtm.channel_count() == 3);
};

/**
 * qtm::qtm_core::queue_size(value) test
 */
BOOST_AUTO_TEST_CASE(check_queue_size_setter) {
  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.queue_size(2);

  BOOST_TEST(qtm.queue_size() == 2);
};

/**
 * qtm::qtm_core::la(value) test
 */
BOOST_AUTO_TEST_CASE(check_la_setter) {
  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.la(11.);

  BOOST_TEST(qtm.la() == 11.);
};

/**
 * qtm::qtm_core::mu(value) test
 */
BOOST_AUTO_TEST_CASE(check_mu_setter) {
  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.mu(6.);

  BOOST_TEST(qtm.mu() == 6.);
};

/**
 * qtm::qtm_core::nu(value) test
 */
BOOST_AUTO_TEST_CASE(check_nu_setter) {
  qtm::qtm qtm(2, 1, 10., 5., 1.5);
  qtm.nu(2.5);

  BOOST_TEST(qtm.nu() == 2.5);
};

/**
 * qtm::qtm_core::n(value) test
 */
BOOST_AUTO_TEST_CASE(check_n_setter) {
  qtm::qtm qtm(2, 1, 10., 5., 1.5, 7);
  qtm.n(8);

  BOOST_TEST(qtm.n() == 8);
};

BOOST_AUTO_TEST_SUITE_END() // test_suite_core_setters
#pragma endregion

/**
 * qtm::qtm_core::calc_final_states() test
 *  -- same as qtm::qtm_core::final_states()
 */
BOOST_AUTO_TEST_CASE(check_final_states) {
  std::vector<double> comp = {0.14285714285714285, 0.2857142857142857,
                              0.2857142857142857, 0.2857142857142857};

  qtm::qtm qtm(2, 1, 10., 5.);
  auto ret = qtm.calc_final_states();

  BOOST_TEST(comp == ret);
};

/**
 * qtm::qtm_core::is_fs_outdated() test
 */
BOOST_AUTO_TEST_CASE(check_is_fs_outdated) {
  qtm::qtm qtm(2, 1, 10., 5.);
  qtm.calc_final_states();

  qtm.la(1.); // change internal

  BOOST_TEST(qtm.is_fs_outdated());
};

BOOST_AUTO_TEST_SUITE_END() // test_suite_core
