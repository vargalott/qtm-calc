#include <qtm-calc/core.hpp>

namespace qtm {

boost::numeric::ublas::matrix<double>
qtm::matrix_init(std::uint64_t channel_count, std::uint64_t queue_size,
                 double la, double mu, double nu, std::int64_t n) {
  std::uint64_t total_count = channel_count + queue_size;
  boost::numeric::ublas::matrix<double> matrix;
  size_t mu_index = 0;
  ptrdiff_t max_n = n;

  // formation of mu and la
  for (size_t i = 0; i < total_count + 1; ++i) {
    matrix.resize(i + 1, total_count + 1);
    for (size_t j = 0; j < total_count + 1; ++j) {
      if (i == j + 1) {
        if (n != -1) {
          matrix.insert_element(i, j, clamp<double>(n * 1. / max_n, 0, max_n) * la);
          n -= 1;
        } else {
          matrix.insert_element(i, j, la);
        }
      } else if (i == j - 1) {
        mu_index = clamp<std::size_t>(mu_index + 1, 0, channel_count);
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
        nu_index = clamp<std::ptrdiff_t>(nu_index - 1, 0, queue_size - 1);
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

qtm::qtm(std::uint64_t channel_count, std::uint64_t queue_size, double la,
         double mu, double nu, std::int64_t n)
    : channel_count_(channel_count), queue_size_(queue_size), la_(la), mu_(mu),
      nu_(nu), n_(n), is_fs_outdated_(true){};

std::uint64_t qtm::channel_count(void) const {
  return this->channel_count_;
};
std::uint64_t qtm::queue_size(void) const { return this->queue_size_; };
std::int64_t qtm::n(void) const { return this->n_; };
double qtm::la(void) const { return this->la_; };
double qtm::mu(void) const { return this->mu_; };
double qtm::nu(void) const { return this->nu_; };

void qtm::channel_count(std::uint64_t channel_count_) {
  this->channel_count_ = channel_count_;
  this->is_fs_outdated_ = true;
};
void qtm::queue_size(std::uint64_t queue_size_) {
  this->queue_size_ = queue_size_;
  this->is_fs_outdated_ = true;
};
void qtm::n(std::int64_t n_) {
  this->n_ = n_;
  this->is_fs_outdated_ = true;
};
void qtm::la(double la_) {
  this->la_ = la_;
  this->is_fs_outdated_ = true;
};
void qtm::mu(double mu_) {
  this->mu_ = mu_;
  this->is_fs_outdated_ = true;
};
void qtm::nu(double nu_) {
  this->nu_ = nu_;
  this->is_fs_outdated_ = true;
};

std::vector<double> const qtm::final_states(void) const {
  if (this->final_states_.empty()) {
    throw std::runtime_error("final states calculation was not performed");
  }
  std::vector<double> v(this->final_states_.size());
  std::copy(this->final_states_.begin(), this->final_states_.end(), v.begin());
  return v;
};
bool qtm::qtm::is_fs_outdated(void) const { return this->is_fs_outdated_; };
std::vector<double> qtm::calc_final_states(void) {
  auto a = this->matrix_init(this->channel_count_, this->queue_size_, this->la_,
                             this->mu_, this->nu_, this->n_);

  std::uint64_t total_count = this->channel_count_ + this->queue_size_ + 1;

  a.resize(a.size1() + 1, a.size2() + 1);
  for (std::size_t i = 0; i < a.size1() - 1; ++i) {
    a(i, a.size2() - 1) = 1. / total_count;
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

  this->is_fs_outdated_ = false;

  return this->final_states();
};

}; // namespace qtm


#ifdef _PYQTMCALC_ENABLE_PYBIND11_EXPORT

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

/**
 * Perform initialization of the pybind11 binding module
 */
void init_module_qtm_core(pybind11::module_ &m) {
  m.doc() = "qtm-core wrapper";

  pybind11::class_<qtm::qtm>(m, "qtm", pybind11::is_final())
      // channel_count, queue_size, la, mu, nu;  default nu = 0, n = -1
      .def(pybind11::init<std::uint64_t, std::uint64_t, double, double>())
      // channel_count, queue_size, la, mu, nu, nu;  default n = -1
      .def(pybind11::init<std::uint64_t, std::uint64_t, double, double, double>())
      // channel_count, queue_size, la, mu, nu, nu, n
      .def(pybind11::init<std::uint64_t, std::uint64_t, double, double, double, std::int64_t>())

      .def("channel_count",
           static_cast<std::uint64_t (qtm::qtm::*)(void) const>(&qtm::qtm::channel_count),
           pybind11::return_value_policy::copy)
      .def("queue_size",
           static_cast<std::uint64_t (qtm::qtm::*)(void) const>(&qtm::qtm::queue_size),
           pybind11::return_value_policy::copy)
      .def("n",
           static_cast<std::int64_t (qtm::qtm::*)(void) const>( &qtm::qtm::n),
           pybind11::return_value_policy::copy)
      .def("la",
           static_cast<double (qtm::qtm::*)(void) const>(&qtm::qtm::la),
           pybind11::return_value_policy::copy)
      .def("mu",
           static_cast<double (qtm::qtm::*)(void) const>(&qtm::qtm::mu),
           pybind11::return_value_policy::copy)
      .def("nu",
           static_cast<double (qtm::qtm::*)(void) const>(&qtm::qtm::nu),
           pybind11::return_value_policy::copy)

      .def("channel_count", 
           static_cast<void (qtm::qtm::*)(std::uint64_t)>(&qtm::qtm::channel_count))
      .def("queue_size", 
           static_cast<void (qtm::qtm::*)(std::uint64_t)>(&qtm::qtm::queue_size))
      .def("n", 
           static_cast<void (qtm::qtm::*)(std::int64_t)>(&qtm::qtm::n))
      .def("la", 
           static_cast<void (qtm::qtm::*)(double)>(&qtm::qtm::la))
      .def("mu", 
           static_cast<void (qtm::qtm::*)(double)>(&qtm::qtm::mu))
      .def("nu", 
           static_cast<void (qtm::qtm::*)(double)>(&qtm::qtm::nu))

      .def("final_states", &qtm::qtm::final_states,
           pybind11::return_value_policy::move)
      .def("is_fs_outdated", &qtm::qtm::is_fs_outdated,
           pybind11::return_value_policy::copy)
      .def("calc_final_states", &qtm::qtm::calc_final_states,
           pybind11::return_value_policy::move);
};

#endif // _PYQTMCALC_ENABLE_PYBIND11_EXPORT
