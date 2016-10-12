/////////////////////////////////////////////////////////////////////
//  Dispatcher.cpp - Pass Message to Sender                        //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////


#include "Dispatcher.h"
using namespace std;

//-------< Starts the Dispatcher Thread >------------------------------
void MessagePassing::Dispatcher::start()
{
	try{
		dispatcher = new std::thread(&Dispatcher::getMessages, this);
	}
	catch (std::exception e){
		std::cout << e.what();
	}
}

//-------< Destroys the dispatcher thread >------------------------------
MessagePassing::Dispatcher::~Dispatcher()
{
	delete dispatcher;
}

//-------< Add Messages to the queue >------------------------------
void MessagePassing::Dispatcher::addToMessages(Message& msg)
{
	bq_.enQ(msg);
}

//-------< Dequeue the messages from the queue and sends to the sender >------------------------------
void MessagePassing::Dispatcher::getMessages()
{
	if (bq_.size() > 0)
	{
		SocketConnecter s_;
		Sender sender;
		Message msg = bq_.deQ();
		sender.connect(msg.getHeader().getDstIP(), msg.getHeader().getDstPort());
		sender.start();
		sender.msgSend(msg);
		sender.wait();
	}
}

//-------< Detaches the Dispatcher Thread >------------------------------
void MessagePassing::Dispatcher::detach()
{
	try{
		dispatcher->detach();
	}
	catch (std::exception e){
		std::cout << e.what();
	}

}


//-------< TEST_STUB >------------------------------

#ifdef TEST_DISPATCHER
#include "../Sender/Sender.h"
using namespace MessagePassing;
int main()
{
	Display disp;
	Verbose v(true);
	SocketSystem ss;
	Message messg;
	std::string srcAddr = "127.0.0.1", srcPort = "8484", targetAddr = "localhost", targetPort = "9080";
	//Command cmd = DisplayMessage;
	messg.getHeader().setCommand(MessageSend);
	messg.getHeader().setDstIPAndPort(targetAddr, targetPort);
	messg.setMessage(" Hello I am sender");
	Sender sender;
	//sender.msgSend(messg);
	//sender.start();

	Message messg2;
	messg2.getHeader().setCommand(UploadFile);
	messg2.getHeader().setDstIPAndPort(targetAddr, targetPort);
	Sender sender2;
	std::string path = "..\\..\\TEST_FOLDER\\TextDoc.txt";
	File file(path);
	FileInfo fileinfo(path);
	std::string filename = fileinfo.name();
	std::cout << "filename =" << filename;
	messg2.getHeader().setFileNameAndType(filename, text);
	size_t filesize = fileinfo.size();
	std::ostringstream convert;   // stream used for the conversion
	convert << filesize;
	messg2.getHeader().setBodylength(convert.str());
	while (!sender2.connect("localhost", "8484"))
	{
		disp.printString("Couldnot connect to server");
		::Sleep(100);
	}
	sender2.msgSend(messg2);
	sender2.start();
	sender2.wait();
	return 0;
}
#endif