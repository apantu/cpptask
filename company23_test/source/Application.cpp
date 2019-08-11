#include "Application.h"
#include "MessageQueueHandler.h"
#include "InputTranslator.h"
#include <string>
#include <iostream>
#include <thread>

Application::Application()
	: mStop(false)
	, mMessageQueue(1000)
	, mMessageProcessor(new MessageQueueHandler())
{
	std::cout << "Programm started." << std::endl;
}

Application::~Application()
{
	std::cout << "Programm stopped." << std::endl;
}

void Application::run()
{
	mMessageProcessor->addUI(this);
	mMessageProcessor->addMessageQueue(&mMessageQueue);

	std::thread messageProcessing(&MessageQueueHandler::run, mMessageProcessor.get());

	std::string command;

	while (!mStop)
	{
		try
		{
			getline(std::cin, command);

			std::unique_ptr<Message> message(InputTranslator::translate(command));

			mMessageQueue.push(message.release());
		}
		catch (const std::exception& ex)
		{
			std::cout << "Exception: " << ex.what() << std::endl;
		}
	}

	if (messageProcessing.joinable())
		messageProcessing.join();
}

void Application::stop()
{
	mMessageProcessor->stop();
	mStop = true;
}

void Application::print(const std::string& message_)
{
	std::lock_guard<std::mutex> guard(mMutex);
	std::cout << message_ << std::endl;
}
