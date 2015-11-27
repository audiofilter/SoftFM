#pragma once
// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#include <vector>
#include <complex>

class rotate90 {
 public:
  rotate90() { phase = 0; }

  void process(const std::vector<std::complex<double> >& samples_in, std::vector<std::complex<double> >& samples_out);

 private:
  unsigned int phase;
};
