#ifndef SERVEREXECUTIVE_H
#define SERVEREXECUTIVE_H
/////////////////////////////////////////////////////////////////////
//  ExecutiveServer.h - Execute Server side                        //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a class that provides services to provide application for server side

Public Interface:  
=================
ExecutiveServer(std::size_t srcport, std::string targetport, Socket::IpVer ipv);  // Constuctor for executive server side
~ExecutiveServer();                                                               // Destructor
void stop();                                                                      // stops the sender
void start(Message& msg);                                                         // Starts the executive server side

Build Process :
== == == == == == ==
Required files
- Sockets.h, Sockets.cpp,
-Receiver.h, Receiver.cpp,
-AppHelpers.h, AppHelpers.cpp,
-BlockingQueue.h, BlockingQueue.cpp,
-Display.h, Display.cpp,
-Message.h, Message.cpp
- Dispatcher.h, Dispatcher.cpp

Build commands
- devenv ExecutiveServer.vcxproj / debug rebuild

Maintenance History :
== == == == == == == == == ==
ver 1.0 : 11 April 2015
- first release
*/
#include <iostream>
#include <string>
#include "../Message/Message.h"
#include "../Sockets/Sockets.h"
#include "../Display/Display.h"
#include "../Reciever/Reciever.h"
#include "../Sender/Sender.h"
#include "../BlockingQueue/BlockingQueue.h"

using namespace std;
namespace MessagePassing
{
	class ExecutiveServer
	{
	public:
		ExecutiveServer(std::size_t srcport, std::string targetport, Socket::IpVer ipv);  // Constuctor for executive server side
		~ExecutiveServer();                                                               // Destructor
		void stop();                                                                      // stops the sender
		void start(Message& msg);                                                         // Starts the executive server side
		 
	private:
		SocketSystem* ss;
		size_t srcPort;
		std::string srcIP;
		std::string dstport;
		std::string dstIP;
		Display display;
		Receiver* receiver;
		Dispatcher* dispatcher_;
		Sender* sender;
		string file;
		Message msg;
	};
}
#endif
