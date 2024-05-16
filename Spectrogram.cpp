#include "Spectrogram.h"

Spectrogram::Spectrogram(void)
	:position(0, 0), length(100), height(100)
{
}

Spectrogram::Spectrogram(int _x, int _y, double _length, double _height)
	:position(_x, _y), length(_length), height(_height), spectrogram_line(sf::Lines, 22050)
{
}

std::pair<int, int> Spectrogram::getPosition(void) const {
	return this->position;
}

void Spectrogram::setPosition(std::pair<int, int> _position) {
	this->position = _position;
}

int Spectrogram::getLength(void) const {
	return this->length;
}

void Spectrogram::setLength(int _length) {
	this->length = _length;
}

sf::VertexArray Spectrogram::getVertexArray(void) const {
	return this->spectrogram_line;
}

void Spectrogram::setVertexArray(sf::VertexArray _line) {
	this->spectrogram_line = _line;
}

void Spectrogram::drawSpectrogram(std::vector<std::complex<double>> _data) {
	std::vector<double> spectrum(_data.size());
	for (size_t i = 0; i < _data.size(); i++) {
		spectrum[i] = std::abs(_data[i]);
	}

	int N = spectrum.size();
	
	for (size_t i = 0; i < N/2; i++) {
		this->spectrogram_line[i] = sf::Vector2f((double)i / (N/2)* length + getPosition().first,
			-(height*spectrum[i]) + getPosition().second);
	}

}

void Spectrogram::drawSpectrogram(std::vector<std::vector<std::complex<double>>> _data) {

}