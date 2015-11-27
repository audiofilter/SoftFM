// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#include <cassert>
#include <cmath>
#include <complex>
#include <spuce/filters/design_fir.h>
#include "pre_fm.h"

using spuce::design_fir;

pre_fm::pre_fm(unsigned int rate) 
{
	auto BF1 = design_fir("remez","LOW_PASS", 27, 0.0625, 0, 0.15, 100.0);
	m_iffilter.set_taps(BF1);
	m_iffilter.set_rate(rate);
}


void pre_fm::process(const std::vector<std::complex<double>>& samples_in,
                     std::vector<std::complex<double>>& if_out)
{
  m_rotator.process(samples_in, m_buf_iftuned);
  m_iffilter.process(m_buf_iftuned, if_out);
}


