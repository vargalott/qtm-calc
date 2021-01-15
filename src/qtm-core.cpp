#include "qtm-core.hpp"

namespace qtm {

double clamp(double num, double min_value, double max_value) {
  return std::max(std::min(num, max_value), min_value);
};

[[nodiscard]] boost::numeric::ublas::matrix<double>
qtm::matrix_init(size_t channel_count, size_t queue_size, double la, double mu,
                 double nu, ptrdiff_t n) {
  size_t total_count = channel_count + queue_size;
  boost::numeric::ublas::matrix<double> matrix;
  size_t mu_index = 0;
  ptrdiff_t max_n = n;

  // formation of mu and la
  for (size_t i = 0; i < total_count + 1; ++i) {
    matrix.resize(i + 1, total_count + 1);
    for (size_t j = 0; j < total_count + 1; ++j) {
      if (i == j + 1) {
        if (n != -1) {
          matrix.insert_element(i, j, clamp(n * 1. / max_n, 0, max_n) * la);
          n -= 1;
        } else {
          matrix.insert_element(i, j, la);
        }
      } else if (i == j - 1) {
        mu_index = clamp(mu_index + 1, 0, channel_count);
        matrix.insert_element(i, j, mu_index * mu);
      } else {
        matrix.insert_element(i, j, 0.);
      }
    }
  }

  // formation of nu
  ptrdiff_t nu_index = queue_size;
  for (ptrdiff_t i = total_count - 1; i > 0 - 1; --i) {
    for (ptrdiff_t j = total_count; j > 0; --j) {
      if (i == j - 1) {
        matrix(i, j) += nu_index * nu;
        nu_index = clamp(nu_index - 1, 0, queue_size - 1);
      }
    }
  }

  // diagonal
  for (size_t i = 0; i < total_count + 1; ++i) {
    for (size_t j = 0; j < total_count + 1; ++j) {
      if (j != i) {
        matrix(i, i) += matrix(j, i);
      }
    }
    matrix(i, i) *= -1;
  }

  return matrix;
};

qtm::qtm(size_t channel_count, size_t queue_size, double la, double mu,
         double nu, ptrdiff_t n)
    : channel_count_(channel_count), queue_size_(queue_size), la_(la), mu_(mu),
      nu_(nu), n_(n){};

size_t const &qtm::channel_count(void) const { return this->channel_count_; };
size_t const &qtm::queue_size(void) const { return this->queue_size_; };
ptrdiff_t const &qtm::n(void) const { return this->n_; };

double const &qtm::la(void) const { return this->la_; };
double const &qtm::mu(void) const { return this->mu_; };
double const &qtm::nu(void) const { return this->nu_; };

std::vector<double> const qtm::final_states(void) const {
  std::vector<double> v(this->final_states_.size());
  std::copy(this->final_states_.begin(), this->final_states_.end(), v.begin());
  return v;
};

/*[[nodiscard]]*/ std::vector<double> qtm::calc_final_states(void) {
  auto a = this->matrix_init(this->channel_count_, this->queue_size_, this->la_,
                             this->mu_, this->nu_, this->n_);

  size_t total_count = this->channel_count_ + this->queue_size_ + 1;

  a.resize(a.size1() + 1, a.size2() + 1);
  for (std::size_t i = 0; i < a.size1() - 1; ++i) {
    a(i, a.size2() - 1) = 1. / total_count;
  }
  for (std::size_t i = 0; i < a.size2() - 1; ++i) {
    a(a.size1() - 1, i) = 1.;
  }
  a(a.size1() - 1, a.size2() - 1) = 0.;

  boost::numeric::ublas::vector<double> b(total_count + 1);
  for (std::size_t i = 0; i < total_count; ++i) {
    b(i) = 0.;
  }
  b(total_count) = 1.;

  boost::numeric::ublas::permutation_matrix<double> pm(a.size1());
  boost::numeric::ublas::lu_factorize(a, pm);
  boost::numeric::ublas::lu_substitute(a, pm, b);

  boost::numeric::ublas::vector_slice<boost::numeric::ublas::vector<double>> b_(
      b, boost::numeric::ublas::slice(0, 1, total_count));

  this->final_states_ = b_;

  return this->final_states();
};

}; // namespace qtm
