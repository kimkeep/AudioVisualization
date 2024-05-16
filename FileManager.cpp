#include "FileManager.h"

FileManager::FileManager(void) {
}

FileManager::FileManager(const std::string& _file_name) {
	loadFromFile(_file_name);
}

bool FileManager::loadFromFile(const std::string& _file_name)
{

	if (!this->sound_buffer.loadFromFile(_file_name)) {
		printf("Can't Load File");
		exit(-1);
	}
	printf("Sample Rate : %d\n", getSampleRate());
	printf("Sample Count  : %d\n", getSampleCount());
	printf("Sample Duration : %f(s)\n", (double)getSampleCount() / getSampleRate());
	
	data.resize(getSampleCount());

	for (int i = 0; i < getSampleCount(); i++) {
		data[i]=((double)this->sound_buffer.getSamples()[i] / INT16_MAX);
	}
}

const sf::Int16* FileManager::getSamples(void) const {
	return this->sound_buffer.getSamples();
}

sf::Uint64 FileManager::getSampleCount(void) const {
	return this->sound_buffer.getSampleCount();
}

unsigned int FileManager::getSampleRate(void) const {
	return this->sound_buffer.getSampleRate();
}

unsigned int FileManager::getChannelCount(void) const {
	return this->sound_buffer.getChannelCount();
}

sf::Time FileManager::getDuration(void) const {
	return this->sound_buffer.getDuration();
}

std::vector<double> FileManager::getData(void) const {
	return this->data;
}
void FileManager::setData(std::vector<double> _data) {
	this->data = _data;
}