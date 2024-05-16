#include "Recorder.h"

Recorder::Recorder(int buffer_size)
	:SoundRecorder(), buffer(buffer_size,0)
{
	this->setProcessingInterval(sf::microseconds(1));
	this->stop();
}

std::vector<double> Recorder::getData(void) const {
	return this->data;
}

void Recorder::setData(std::vector<double> _data) {
	this->data = _data;
}

std::vector<double> Recorder::getBuffer(void) const {
	return this->buffer;
}

void Recorder::setBuffer(std::vector<double> _buffer) {
	this->buffer = _buffer;
}

bool Recorder::onStart()
{
	data.clear();
	printf("Recording Start\n");
	std::cout << "Device Name : " << this->getDevice() << "\n";
	printf("Channel Count : %d\n", this->getChannelCount());
	printf("Sampling Rate : %d\n", this->getSampleRate());
	printf("Buffer Size : %d\n", this->getBuffer().size());
	return true;
}

void Recorder::onStop() {
	printf("Recoring Stop\n");
	for (int i = 0; i < this->data.size(); i++) {
		data[i] = 0;
	}
}

bool Recorder::onProcessSamples(const sf::Int16* _samples, std::size_t _sample_size)
{
	std::vector<double> v;
	for (int i = 0; i < _sample_size; i++) {
		v.push_back((double)_samples[i] / INT16_MAX);
		buffer.erase(buffer.begin());
		buffer.push_back((double)_samples[i] / INT16_MAX);
	}
	setData(v);

	return true;
}