#include <qtm-calc/data.hpp>

namespace qtm {

void qtm_data::calc_fs_if_outdated(qtm &qtm) {
  if (qtm.is_fs_outdated()) {
    qtm.calc_final_states();
  }
}

double qtm_data::calc_avg_queue(qtm &qtm) {
  qtm_data::calc_fs_if_outdated(qtm);

  std::uint64_t i = 1;
  double res = 0.;
  for (auto &state :
       // just slicing { final_states[channel_count+1:] }
       ([](std::vector<double> vec, std::size_t f) -> std::vector<double> {
         return std::vector<double>(vec.begin() + f, vec.end());
       })(qtm.final_states(), qtm.channel_count() + 1)) {
    res += i * state;
    i = clamp<std::uint64_t>(i + 1, 1, qtm.queue_size());
  }
  return res;
};

double qtm_data::calc_ete(qtm &qtm) {
  qtm_data::calc_fs_if_outdated(qtm);

  std::uint64_t i = 0;
  double res = 0.;
  for (auto &state : qtm.final_states()) {
    res += i * state;
    i = clamp<std::uint64_t>(i + 1, 0, qtm.channel_count());
  }
  res /= qtm.channel_count();
  return res;
};

double qtm_data::calc_avg_time_queue(qtm &qtm) {
  qtm_data::calc_fs_if_outdated(qtm);

  return qtm_data::calc_avg_queue(qtm) / qtm.channel_count() * qtm.mu();
};

double qtm_data::calc_perc_served_req(qtm &qtm) {
  qtm_data::calc_fs_if_outdated(qtm);

  return 1. - qtm.final_states().back();
};

double qtm_data::calc_avg_count_served_req(qtm &qtm) {
  qtm_data::calc_fs_if_outdated(qtm);

  std::uint64_t i = 0;
  double res = 0.;
  for (auto &state : qtm.final_states()) {
    res += state * i;
    if (i < qtm.channel_count() + 1) {
      ++i;
    }
  }
  return res;
};

double qtm_data::calc_avg_count_req(qtm &qtm) {
  qtm_data::calc_fs_if_outdated(qtm);

  std::uint64_t i = 0;
  double res = 0.;
  for (auto &state : qtm.final_states()) {
    res += state * i;
    ++i;
  }
  return res;
};

double qtm_data::calc_avg_count_unserved_req(qtm &qtm) {
  qtm_data::calc_fs_if_outdated(qtm);

  return qtm_data::calc_avg_count_req(qtm) - qtm_data::calc_avg_count_served_req(qtm);
};

}; // namespace qtm


#ifdef _PYQTMCALC_ENABLE_PYBIND11_EXPORT

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

/**
 * Perform initialization of the pybind11 binding module
 */
void init_module_qtm_data(pybind11::module_ &m) {
  m.doc() = "qtm-data wrapper";

  pybind11::class_<qtm::qtm_data,
                   std::unique_ptr<qtm::qtm_data, pybind11::nodelete>>(
      m, "qtm_data", pybind11::is_final())
      .def_static("calc_avg_queue", &qtm::qtm_data::calc_avg_queue,
                  pybind11::return_value_policy::copy)
      .def_static("calc_ete", &qtm::qtm_data::calc_ete,
                  pybind11::return_value_policy::copy)
      .def_static("calc_avg_time_queue", &qtm::qtm_data::calc_avg_time_queue,
                  pybind11::return_value_policy::copy)
      .def_static("calc_perc_served_req", &qtm::qtm_data::calc_perc_served_req,
                  pybind11::return_value_policy::copy)
      .def_static("calc_avg_count_served_req",
                  &qtm::qtm_data::calc_avg_count_served_req,
                  pybind11::return_value_policy::copy)
      .def_static("calc_avg_count_req", &qtm::qtm_data::calc_avg_count_req,
                  pybind11::return_value_policy::copy);
};

#endif // _PYQTMCALC_ENABLE_PYBIND11_EXPORT
