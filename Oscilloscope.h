#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H


#include <SFML/Graphics.hpp>
#include <cmath>

class Oscilloscope {
private:
	std::pair<int, int> position;
	int length;
	double height;

	sf::VertexArray line;
public:

	Oscilloscope(void);
	Oscilloscope(int, int, int, double);

	std::pair<int, int> getPosition(void) const;
	void setPosition(std::pair<int, int> _position);
	int getLength(void) const;
	void setLength(int _length);
	sf::VertexArray getVertexArray(void) const;
	void setVertexArray(sf::VertexArray _line);

	void drawTest(void);
	void drawOscilloscope(std::vector<double> data);
	void drawOscilloscope(const sf::Int16* data, int sample_size);
};

#endif // !OSCILLOSCOPE_H