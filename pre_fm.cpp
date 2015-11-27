// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#include "pre_fm.h"
#include <cmath>
#include <spuce/filters/design_fir.h>

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
  m_iffilter.process(samples_in, if_out);
}


