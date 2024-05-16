#pragma once

#include <SFML/Audio.hpp>

#include <string>

#include <vector>
#include <complex>

class FileManager {
private:
	sf::SoundBuffer sound_buffer;

	std::vector<double> data;
public:
	FileManager(void);
	FileManager(const std::string& _file_name);

	bool loadFromFile(const std::string& _file_name);
	
	const sf::Int16* getSamples(void) const;
	sf::Uint64 getSampleCount(void) const;
	unsigned int getSampleRate(void) const;
	unsigned int getChannelCount(void) const;
	sf::Time getDuration(void) const;

	std::vector<double> getData(void) const;
	void setData(std::vector<double>);
};

