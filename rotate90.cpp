// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#include "rotate90.h"

void rotate90::process(const std::vector<std::complex<double> >& in, std::vector<std::complex<double> >& out) {
  out.resize(in.size());
  for (size_t j = 0; j < in.size(); j++) {
    switch (phase) {
    case 0:        out[j] = in[j];        break;
    case 1:        out[j] = std::complex<double>(-std::imag(in[j]),std::real(in[j])); break;
    case 2:        out[j] = -in[j];        break;
    case 3:        out[j] = std::complex<double>(std::imag(in[j]),-std::real(in[j])); break;
    }
    phase = (phase + 1) % 4;
  }
}
