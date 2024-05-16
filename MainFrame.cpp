#include "MainFrame.h"

MainFrame::MainFrame(void)
	:state(State::NONE), rec(buffer_size), osc(0, 150, 800, 100), spec(50, 500, 700, 1)
{
	window = new Window::Hann();

	this->settings.antialiasingLevel = 4;
	this->main_window.create(sf::VideoMode(800, 600), "MainFrame", sf::Style::Close , settings);

	this->main_window.setVerticalSyncEnabled(true);
	this->main_window.setFramerateLimit(60);

	setGui();
}

void MainFrame::setGui(void) {
	gui.setWindow(this->main_window);

	//rec Button
	rec_button = tgui::BitmapButton::create("rec");
	rec_button->setPosition(0,0);
	rec_button->setSize(50, 50);

	//file_name EditBox
	file_name_box = tgui::EditBox::create();
	file_name_box->setPosition(50, 0);
	file_name_box->setSize(300, 50);
	file_name_box->setDefaultText("example.wav");

	box = tgui::ChatBox::create();
	box->setPosition(0,50);
	box->setSize(800, 200);

	gui.add(rec_button);
	gui.add(file_name_box);
	//gui.add(box);
}

MainFrame::~MainFrame(void) {
	delete window;
}

std::string MainFrame::getFileName(void) const {
	tgui::String file_name = this->file_name_box->getText();
	return file_name.toStdString();
}


void MainFrame::controlRecord(void) {
	if (state!=State::USING_REC) {
		rec.start();
		state = State::USING_REC;
		osc.setVertexArray(sf::VertexArray(sf::Lines, buffer_size));
		spec.setVertexArray(sf::VertexArray(sf::Lines, rec.getBuffer().size()));
	}
	else {
		state = State::NONE;
		rec.stop();
		osc.setVertexArray(sf::VertexArray(sf::Lines, 0));
		spec.setVertexArray(sf::VertexArray(sf::Lines, 0));
	}
}

void MainFrame::controlFileManage(void) {
	if (state == State::USING_REC) {
		rec.stop();
	}	state = State::USING_FILE;
	if (getFileName() == "") {
		state = State::NONE;
		osc.setVertexArray(sf::VertexArray(sf::Lines, 0));
		spec.setVertexArray(sf::VertexArray(sf::Lines, 0));
	}
	else {
		std::string file_name = "./AudioFiles/" + getFileName();
		file_manager.loadFromFile(file_name);

		std::vector<std::complex<double>> fft_data = fft(Utility::realToComplex(Window::windowing(*window, file_manager.getData())));

		osc.setVertexArray(sf::VertexArray(sf::Lines, file_manager.getSampleCount()));
		spec.setVertexArray(sf::VertexArray(sf::Lines, fft_data.size()/2));
		spec.drawSpectrogram(fft_data);
		std::vector<std::string> infos = {
			"delta_t:" + std::to_string(double(512) / file_manager.getSampleRate()),
			"delta_f:" + std::to_string(double(file_manager.getSampleRate()) / 1024),
			"path:" + file_name
		};
		Transform::save_spectrogram(stft(file_manager.getData(), 1024, 512), infos, getFileName()+"_spectrogram.csv");
	}
}


int MainFrame::executeMainFrame(void)
{
	
	while (this->main_window.isOpen())
	{
		sf::Event event;

		//event Ã³¸®
		while (main_window.pollEvent(event))
		{
			gui.handleEvent(event);

			if (event.type == sf::Event::Closed) {
				main_window.close();
			}	//close the window
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				printf("Escape Pressed\n");
				main_window.close();
			}	//close the window with Escape key press

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
				printf("SpaceBar Pressed\n");
				controlRecord();
			}	//rec control with Space key press

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				printf("Enter Pressed\n");
				controlFileManage();
			}	//file select with Enter key press
		}
		//displaying

		this->main_window.clear();
		switch (state) {
		case MainFrame::State::NONE:
			rec_button->setText("rec\noff");
			break;

		case MainFrame::State::USING_FILE:
			rec_button->setText("rec\noff");
			osc.drawOscilloscope(file_manager.getData());
			break;

		case MainFrame::State::USING_REC:
			rec_button->setText("rec\non");
			osc.drawOscilloscope(rec.getBuffer());
			spec.drawSpectrogram(
				fft(
				Utility::realToComplex(
				Window::windowing(*window, rec.getBuffer()))));
			break;

		default:
			break;
		}

		this->main_window.draw(osc.getVertexArray());
		this->main_window.draw(spec.getVertexArray());
		this->gui.draw();
		this->main_window.display();
	}
	rec.stop();

	return 1;
}
