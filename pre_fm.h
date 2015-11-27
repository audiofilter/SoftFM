// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#pragma once

#include <cstdint>
#include <vector>

#include "rotate90.h"
#include <spuce/filters/fir_decim.h>

class pre_fm
{
public:
  pre_fm(unsigned int downsample=1);
  // Down-convert + Down-sample
  void process(const std::vector<std::complex<double>>& samples_in,
               std::vector<std::complex<double>>& if_out);

private:
  rotate90            m_rotator;
  std::vector<std::complex<double>>  m_buf_iftuned;
  spuce::fir_decim<std::complex<double>>  m_iffilter;
};

