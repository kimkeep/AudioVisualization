#ifndef MAIN_FRAME_H
#define MAIN_FRAME_H

#include "FileManager.h"
#include "Recorder.h"

#include "Oscilloscope.h"
#include "Spectrogram.h"

#include "Transform.h"

#include <SFML/Graphics.hpp>
#include <TGUI/AllWidgets.hpp>

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include <TGUI/AllWidgets.hpp>


class MainFrame {
private:
	const int buffer_size = 1024;

	enum class State {
		NONE,
		USING_FILE,
		USING_REC
	};
	State state;



	sf::ContextSettings settings;
	sf::RenderWindow main_window;
	
	tgui::Gui gui{ this->main_window };

	tgui::BitmapButton::Ptr rec_button;
	tgui::EditBox::Ptr file_name_box;
	tgui::ChatBox::Ptr box;

	tgui::Knob::Ptr pitch_shift_knob;
	tgui::Knob::Ptr time_stretch_knob;


	FileManager file_manager;
	Recorder rec;

	Oscilloscope osc;
	Spectrogram spec;

	Transform::FFT fft;
	Transform::STFT stft;

	Window::Window* window;

public:
	MainFrame(void);
	virtual ~MainFrame(void);

	void setGui(void);

	std::string getFileName(void) const;
	
	void controlRecord(void);
	void controlFileManage(void);

	int executeMainFrame(void);
};

#endif // !MAIN_FRAME_H