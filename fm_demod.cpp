// Copyright (c) 2015 Tony Kirke.  Boost Software License - Version 1.0  (http://www.opensource.org/licenses/BSL-1.0)
#include <cassert>
#include <cmath>
#include <complex>
#include <spuce/filters/design_iir.h>
#include <spuce/filters/design_fir.h>
#include "fm_demod.h"

using namespace std;
using namespace spuce;

fm_demod::fm_demod()
{
  const double sample_rate_pcm = 48000;
  
  static constexpr double deemphasis = 50;
	iir_coeff *LPF = design_iir("butterworth", "LOW_PASS", 1,
                              1.0/(M_PI*deemphasis * sample_rate_pcm * 1.0e-6));
  
	m_deemph_mono.realloc(*LPF);

	iir_coeff *HPF = design_iir("butterworth", "HIGH_PASS", 2, 30.0/sample_rate_pcm);
	m_dcblock_mono.realloc(*HPF);
  
	// 4
	int rate = 4;
	auto taps = design_fir("remez","LOW_PASS", 4*rate+1, 0.125, 0, 0.1, 100.0);
	m_resample_mono.set_taps(taps);
	m_resample_mono.set_rate(rate);

}

void fm_demod::process(const std::vector<std::complex<double>>& samples_in,
                        std::vector<double>& audio)
{
  std::vector<double> fm_disc_out;
  std::vector<double> buf_mono;
  m_phasedisc.process(samples_in, fm_disc_out);
  
  // Down-sample by 4 to audio rate
  m_resample_mono.process(fm_disc_out, buf_mono);
  
  // DC blocking and de-emphasis.
  for (size_t i=0;i<buf_mono.size();i++) {
    buf_mono[i] = m_dcblock_mono.clock(buf_mono[i]);
    buf_mono[i] = m_deemph_mono.clock(buf_mono[i]);
  }
	
  mono_to_interleaved_stereo(buf_mono, audio);
}

// Duplicate mono signal in left/right channels.
void fm_demod::mono_to_interleaved_stereo(const std::vector<double>& samples_mono,
                                          std::vector<double>& audio)
{
  unsigned int n = samples_mono.size();
  audio.resize(2*n);
  for (unsigned int i = 0; i < n; i++) {
    double m = samples_mono[i];
    audio[2*i]   = m;
    audio[2*i+1] = m;
  }
}


