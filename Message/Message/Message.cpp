/////////////////////////////////////////////////////////////////////
//  Message.cpp - Conatin Message Information                      //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <sstream>
#include "Message.h"
using namespace MessagePassing;

//----< Message Constructor  >---------------------------------------------------
Message::Message(){
	isHeaderReceived = false;
}

//----< Conversion int to String  >----------------------------------------------
std::string Message::toString(int i)
{
	std::ostringstream conv;
	conv << i;
	return conv.str();
}

//----< Getting Message for transfer  >----------------------------------------------
std::string Message::getMessage(){
	return message_;
}

//----< Setting Message for transfer  >----------------------------------------------
void Message::setMessage(std::string msg){
	message_ = msg;
}

//----< Constructing Message from header and returning string >----------------------
std::string Message::constructHeader(){
	std::string msgHead = "";
	try{
		msgHead = "COMMAND:" + msgHeader_.getCommand() + ";" +
			"SRCIP:" + msgHeader_.getSrcIP() + ";" +
			"SRCPORT:" + msgHeader_.getSrcPort() + ";" +
			"DSTIP:" + msgHeader_.getDstIP() + ";" +
			"DISPORT:" + msgHeader_.getDstPort() + ";" +
			"FILENAME:" + msgHeader_.getFileName() + ";" +
			"FILETYPE:" + msgHeader_.getFileType() + ";" +
			"BODYLENGTH:" + msgHeader_.getBodylength() + ";";
	}
	catch (std::exception e){
		std::cout << e.what();
	}
	return msgHead;
}

//-------< Parses the string on the start char >------------------------------
void Message::parseString(std::string& str, char start)
{
	size_t s = str.find(start);
	if (!str.empty() && str[str.length() - 1] == '\n') {
		str.erase(str.length() - 1);
	}
	std::string value = str.substr(s + 1, str.length() - (s + 1));
	std::string name = str.substr(0, s);
	msgHeader_.setParameters(name, value);
}

//----< Interpreting Message and storing to header >-----------------------------
void Message::messageInterpret(std::string messg){
	std::stringstream ss(messg);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(ss, item, ';')) {
		elems.push_back(item);
	}
	for (auto tok : elems)
		parseString(tok, ':');
}

//----< Retruning Header Ref >----------------------------------------------------
MsgHeader& Message::getHeader(){
	return msgHeader_;
}

#ifdef TEST_MESSAGE
//----< Calling Message Passing Main >-------------------------------------------
int main(int argc, char* argv[])
{
	try{
		std::cout << "\n\n ########################## TESTING MESSAGE PACKAGE #################################### \n\n";
		Message messg;
		std::string srcAddr = "127.0.0.1", srcPort = "8484", targetAddr = "127.0.0.1", targetPort = "8181";
		messg.getHeader().setCommand(MessageSend);
		messg.getHeader().setDstIPAndPort(targetAddr, targetPort);
		messg.setMessage(" Hello I am sender");
		MsgHeader head = messg.getHeader();
		std::cout << " \n Command is =" << head.getCommand();
		std::cout << " \n Message is =" << messg.getMessage();
		std::cout << " \n\n\n";
	}
	catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif

