#include "Transform.h"


std::complex<double> Utility::realToComplex(double data) {
	return data;
}
vec_complex Utility::realToComplex(vec_real data) {
	return vec_complex(data.begin(), data.end());
}

//Fast Fourier Transform
vec_complex Transform::FFT::operator() (vec_complex data) {
	size_t N = data.size();
	if (N == 1) {
		return data;
	}

	vec_complex even_data(N / 2), odd_data(N / 2);

	for (size_t i = 0; i < N / 2; i++) {
		even_data[i] = data[i * 2];
		odd_data[i] = data[i * 2 + 1];
	}
	//홀수, 짝수번째 데이터를 저장하는 벡터

	vec_complex even_fft = this->operator() (even_data);
	vec_complex odd_fft = this->operator() (odd_data);

	vec_complex result(N);
	//출력 데이터

	for (size_t i = 0; i < N / 2; i++) {
		Complex t = std::polar(1.0, -2 * PI * i / N) * odd_fft[i];
		result[i] = even_fft[i] + t;
		result[i + N / 2] = even_fft[i] - t;
	}
	
	return result;
}

//Invert Fast Fourier Transform
vec_complex Transform::IFFT::operator() (vec_complex _data)
{
	int N = _data.size();
	if (N == 1) return _data;

	vec_complex even(N / 2), odd(N / 2);
	for (int i = 0; i < N / 2; ++i) {
		even[i] = _data[i * 2];
		odd[i] = _data[i * 2 + 1];
	}

	vec_complex even_ifft = this->operator()(even);
	vec_complex odd_ifft  = this->operator()(odd);

	vec_complex result(N);
	for (int k = 0; k < N / 2; ++k) {
		Complex t = std::polar(1.0, 2 * PI * k / N) * odd_ifft[k];
		result[k] = even_ifft[k] + t;
		result[k + N / 2] = even_ifft[k] - t;
	}
	for (int i = 0; i < N; ++i) {
		result[i] /= 2;
	}
	
	return result;
}



mat_complex Transform::STFT::operator()(vec_real data, int frame_size, int hop_size)
{
	mat_complex result;
	Window::Window* window = new Window::Hann();
	
	for (int i = 0; i < data.size() - frame_size; i += hop_size) {
		vec_real frame(data.begin()+i, data.begin() + i + frame_size);
		
		result.push_back(
			FFT() (
			Utility::realToComplex(
			Window::windowing(*window, frame))));
		printf("%d\n", result.size());
	}
	

	return result;
}


void Transform::save_spectrogram(mat_complex spec, std::vector<std::string> infos, std::string name) {
	std::ofstream file;
	file.open(name);

	for (size_t i = 0; i < infos.size(); i++)
		file << infos[i] << (i == infos.size() - 1 ? "\n" : ",");
	for (auto& row : spec) {
		for (auto& elem : row) {
			file << std::abs(elem) << ',';
		}
		file << '\n';
	}
	file.close();
}








std::vector<double> Window::Rectangular::operator()(int N) {
	return std::vector<double>(N,1);
}



std::vector<double> Window::Triangular::operator()(int N) {
	std::vector<double> window(N);
	
	for (int n = 0; n < N; n++) {
		window[n] = (1 - abs( (n - N / 2) / (N / 2) ));
	}
	
	return window;
}

std::vector<double> Window::Sine::operator()(int N) {
	std::vector<double> window(N);

	for (int n = 0; n < N; ++n) {
		window[n] = sin(PI * n / (N - 1));
	}

	return window;
}


std::vector<double> Window::Hann::operator()(int N)
{
	std::vector<double> window(N);

	for (int n = 0; n < N; ++n) {
		window[n] = 0.5 * (1 - cos(2 * PI * n / (N - 1)));
	}

	return window;
}

std::vector<double> Window::Hamming::operator()(int N)
{
	std::vector<double> window(N);

	for (int n = 0; n < N; ++n) {
		window[n] = 0.54 - 0.46 * cos(2 * PI * n / (N - 1));
	}

	return window;
}


std::vector<double> Window::windowing(Window& window_function, std::vector<double> frame) {
	std::vector<double> window = window_function(frame.size());
	
	for (int i = 0; i < frame.size(); i++) {
		frame[i] *= window[i];
	}

	return frame;
}
