#pragma once
#ifndef __QTM_CORE_HPP__
#define __QTM_CORE_HPP__

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <vector>

#include <boost/core/noncopyable.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/matrix.hpp>

namespace qtm {

template <typename type> 
type clamp(type num, type min_value, type max_value) {
  return std::max(std::min(num, max_value), min_value);
}

class qtm final : private boost::noncopyable {
private:
  std::uint64_t channel_count_, queue_size_;
  double la_, mu_, nu_;
  std::int64_t n_;
  boost::numeric::ublas::vector<double> final_states_;

  bool is_fs_outdated_;

  static boost::numeric::ublas::matrix<double>
  matrix_init(std::uint64_t channel_count, std::uint64_t queue_size, double la,
              double mu, double nu, std::int64_t n);

public:
  explicit qtm(std::uint64_t channel_count, std::uint64_t queue_size, double la,
               double mu, double nu = 0, std::int64_t n = -1);
  ~qtm(void) = default;

  std::uint64_t const &channel_count(void) const;
  std::uint64_t const &queue_size(void) const;
  std::int64_t const &n(void) const;
  double const &la(void) const;
  double const &mu(void) const;
  double const &nu(void) const;

  void channel_count(std::uint64_t channel_count_);
  void queue_size(std::uint64_t queue_size_);
  void n(std::int64_t n_);
  void la(double la_);
  void mu(double mu_);
  void nu(double nu_);

  std::vector<double> const final_states(void) const;
  bool is_fs_outdated(void) const;
  std::vector<double> calc_final_states(void);
};

}; // namespace qtm

#endif // !__QTM_CORE_HPP__
