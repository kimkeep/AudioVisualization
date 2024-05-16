#ifndef RECORDER_H
#define RECORDER_H

#include <iostream>
#include <vector>
#include <complex>

#include <SFML/Audio.hpp>

class Recorder : public sf::SoundRecorder {
private:
    std::vector<double> data;
    std::vector<double> buffer;
public:
    Recorder(int buffer_size);

    std::vector<double> getData(void) const;
    void setData(std::vector<double>);
    std::vector<double> getBuffer(void) const;
    void setBuffer(std::vector<double>);

    virtual bool onStart();
    virtual void onStop();
    virtual bool onProcessSamples(const sf::Int16* samples, std::size_t _sample_size);

};

#endif // !RECORDER_H