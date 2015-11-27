#pragma once
// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)

#include <cstdint>
#include <vector>

#include "fm_discriminator.h"
#include "rotate90.h"
#include <spuce/filters/iir.h>
#include <spuce/filters/fir_decim.h>

//! FM demodulator that works at 4 times audio output rate
class fm_demod
{
public:

  fm_demod();
  void process(const std::vector<std::complex<double>>& samples_in,  std::vector<double>& audio);


private:
  void mono_to_interleaved_stereo(const std::vector<double>& samples_mono,  std::vector<double>& audio);
  
  rotate90            m_rotator;
  fm_discriminator  m_phasedisc;
  
  spuce::fir_decim<double>   m_resample_mono;
  spuce::iir<double>   m_dcblock_mono;
  spuce::iir<double>   m_deemph_mono;
};

