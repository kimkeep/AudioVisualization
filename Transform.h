#pragma once

#include <fstream>

#include <cmath>

#include <vector>
#include <complex>

typedef std::complex<double> Complex;
typedef std::vector<Complex> vec_complex;
typedef std::vector<vec_complex> mat_complex;

typedef std::vector<double> vec_real;

const double PI = acos(-1);

namespace Utility {
	std::complex<double> realToComplex(double);
	vec_complex realToComplex(vec_real);
}


namespace Transform {
	class FFT {
	private:

	public:
		vec_complex operator() (vec_complex _data);
	};
	class IFFT {
	private:
	public:
		vec_complex operator() (vec_complex _data);
	};

	class STFT {
	private:
	public:
		mat_complex operator() (vec_real data, int frame_size, int hop_size);
	};

	class ISTFT {
	private:
	public:
		vec_real operator() (mat_complex data, int frame_size, int hop_size);
	};

	void save_spectrogram(mat_complex spec, std::vector<std::string> infos, std::string name);
};


namespace Window {
	class Window {
	private:
	public:
		virtual std::vector<double> operator() (int) = 0;
	};

	class Rectangular : public Window {
	private:
	public:
		virtual std::vector<double> operator() (int);
	};

	class Triangular : public Window {
	private:
	public:
		virtual std::vector<double> operator() (int);
	};

	class Sine : public Window {
	private:
	public:
		virtual std::vector<double> operator() (int);
	};

	class Hann : public Window {
	private:
	public:
		virtual std::vector<double> operator() (int);
	};

	class Hamming : public Window {
	private:
	public:
		virtual std::vector<double> operator() (int);
	};

	std::vector<double> windowing(Window&, std::vector<double>);
	std::vector<double> windowing(Window&, std::vector<double>, int);
};