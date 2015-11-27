// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#pragma once

#include <cstdint>
#include <vector>
#include <complex>
#include <spuce/filters/fir_decim.h>

class pre_fm
{
public:
  pre_fm(unsigned int downsample=1);
  // just down-sample
  void process(const std::vector<std::complex<double>>& samples_in,
               std::vector<std::complex<double>>& if_out);

private:
  spuce::fir_decim<std::complex<double>>  m_iffilter;
};

