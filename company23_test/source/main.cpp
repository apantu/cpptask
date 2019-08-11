#include "Application.h"
#include <iostream>

int main()
{
	Application ui;

	try
	{
		ui.run();
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception: " << ex.what() << std::endl;
	}

	return 0;
}
