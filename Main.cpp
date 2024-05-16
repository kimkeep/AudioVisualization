#include "AllInOne.h"
int main(void) {
	int exit_number = 0;

	MainFrame main_frame;
	exit_number = main_frame.executeMainFrame();


	std::cout << "return number : " << exit_number << "\n";
	switch (exit_number) {
	case -1:
		std::cout << "invaild exit" << "\n";
		break;
	case 0:
		break;
	case 1:
		break;
	default:
		break;
	}

	return 0;
}