#include "Oscilloscope.h"

Oscilloscope::Oscilloscope(void)
	:position(0, 0), length(441), height(100), line(sf::Lines, 0)
{
}

Oscilloscope::Oscilloscope(int _x, int _y, int _length, double _height)
	:position(_x, _y), length(_length), height(_height), line(sf::Lines, 0)
{
}

std::pair<int, int> Oscilloscope::getPosition(void) const {
	return this->position;
}
void Oscilloscope::setPosition(std::pair<int, int> _position) {
	this->position = _position;
}
int Oscilloscope::getLength(void) const {
	return this->length;
}
void Oscilloscope::setLength(int _length) {
	this->length = _length;
}

sf::VertexArray Oscilloscope::getVertexArray(void) const {
	return this->line;
}

void Oscilloscope::setVertexArray(sf::VertexArray _line) {
	this->line = _line;
}

void Oscilloscope::drawTest(void) {
	for (int i = 0; i < line.getVertexCount(); i++) {
		this->line[i].color = sf::Color::Color(255, 255, 255, 255);
		this->line[i] = sf::Vector2f(this->position.first + i, this->position.second - 100.0 * sin(i / 450.0 * 3.14));
	}
}

void Oscilloscope::drawOscilloscope(std::vector<double> data) {
	for (int i = 0; i < data.size(); i++) {
		this->line[i] = sf::Vector2f((double) i / data.size() * getLength() + this->position.first,
			(double)height * (-data[i]) + this->position.second);
	}
}

void Oscilloscope::drawOscilloscope(const sf::Int16* data, int sample_size)
{
	for (int i = 0; i < sample_size; i++) {
		this->line[i] = sf::Vector2f(i, data[i] / 100.0);
	}
}