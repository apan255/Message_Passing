/////////////////////////////////////////////////////////////////////
//  Display.cpp - Display Xml Document Project                     //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 2, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include "Message.h"
using namespace MessagePassing;

std::string Message::toString(int i)
{
	std::ostringstream conv;
	conv << i;
	return conv.str();
}

std::string Message::getMessage(){
	return message_;
}
std::string Message::getDstIPAddress(){
	return msgHeader_.getDstIP();
}

std::string Message::getDstPort(){
	return msgHeader_.getDstPort();
}

std::string Message::getSrcPort(){
	return msgHeader_.getSrcPort();
}

MsgHeader& Message::getHeader(){
	return msgHeader_;
}

void Message::setCommand(Command cmd)
{

	msgHeader_.setCommand(cmd);
}
void Message::setDstIPAndPort(std::string ip, std::string port)
{
	msgHeader_.setDstIPAndPort(ip, port);
}
void Message::setSrcIPAndPort(std::string ip, std::string port)
{
	msgHeader_.setSrcIPAndPort(ip, port);
}
void Message::setFileNameAndType(std::string FileName, FileType fileType)
{
	msgHeader_.setFileNameAndType(FileName, fileType);
}
void Message::setBodylength(size_t length)
{
	msgHeader_.setBodylength(length);
}

void Message::setMessage(std::string msg){
	message_ = msg;
}
std::string Message::constructHeader(){
	std::string msgHead = "";
	try{
		msgHead = "COMMAND:" + msgHeader_.getCommand() + "\n" +
			"SRCIP:" + msgHeader_.getSrcIP() + "\n" +
			"SRCPORT:" + msgHeader_.getSrcPort() + "\n" +
			"DSTIP:" + msgHeader_.getDstIP() + "\n" +
			"DISPORT:" + msgHeader_.getDstPort() + "\n" +
			"FILENAME:" + msgHeader_.getFileName() + "\n" +
			"FILETYPE:" + msgHeader_.getFileType() + "\n" +
			"BODYLENGTH:" + msgHeader_.getBodylength() + "\n";
	}
	catch (std::exception e){
		std::cout << e.what();
	}
	msgHead += "\n";
	return msgHead;
}

void Message::messageInterpret(std::string messg){
	std::istringstream msg(messg);
	while (!msg.eof())
	{
		std::string line;
		getline(msg, line);
		if (line == "")
			break;
		size_t s = line.find(':');
		std::string value = line.substr(s + 1, line.length() - (s + 1));
		std::string name = line.substr(0, s);
		msgHeader_.setParameters(name, value);
	}
}
#ifdef TEST_MESSAGE
//----< Calling Message Passing Main >-------------------------------------------
int main(int argc, char* argv[])
{
	try{
		std::cout << " I am here \n";
		Message messg;
		std::string srcAddr = "127.0.0.1", srcPort = "8484", targetAddr = "127.0.0.1", targetPort = "8181";
		messg.setCommand(DisplayMessage);
		messg.setDstIPAndPort(targetAddr, targetPort);
		messg.setMessage(" Hello I am sender");

		MsgHeader head = messg.getHeader();
		std::cout << "I am here" << head.getCommand();
	}
	catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif

