#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <complex>

class Spectrogram{
private:
	std::pair<int, int> position;
	double length;
	double height;

	sf::VertexArray spectrogram_line;
	std::vector<sf::VertexArray> spectrogram_lines;
public:
	Spectrogram(void);
	Spectrogram(int _x, int _y, double _length, double _height);

	std::pair<int, int> getPosition(void) const;
	void setPosition(std::pair<int, int> _position);
	int getLength(void) const;
	void setLength(int _length);
	sf::VertexArray getVertexArray(void) const;
	void setVertexArray(sf::VertexArray _line);

	void drawSpectrogram(std::vector<std::complex<double>> _data);
	void drawSpectrogram(std::vector<std::vector<std::complex<double>>> _data);
};

