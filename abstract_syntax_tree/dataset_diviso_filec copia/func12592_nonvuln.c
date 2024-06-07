double binomial_inversion(double count, double prob,
                          random::PhiloxRandom* gen) {
  using Eigen::numext::ceil;
  using Eigen::numext::log;
  using Eigen::numext::log1p;

  double geom_sum = 0;
  int num_geom = 0;

  Uniform uniform;
  typename Uniform::ResultType uniform_result;
  int16 uniform_remaining = 0;

  while (true) {
    UNIFORM(u);
    double geom = ceil(log(u) / log1p(-prob));
    geom_sum += geom;
    if (geom_sum > count) {
      break;
    }
    ++num_geom;
  }
  return num_geom;
}