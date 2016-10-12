#ifndef EXECUTIVECLIENT_H
#define EXECUTIVECLIENT_H
/////////////////////////////////////////////////////////////////////
//  ExecutiveClient.h - Execute client side                        //
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
This module defines a class that provides services to provide application for client side

Public Interface:
=================
ExecutiveClient(std::size_t srcport, std::string targetport, Socket::IpVer ipv); // Constuctor for executive client side
~ExecutiveClient();                                                              // destructor
void start(Message msg);                                                         // Starts the executive client side
void stop();                                                                     // stops the client

Build Process :
== == == == == == ==
Required files
- Sockets.h, Sockets.cpp,
-Sender.h, Sender.cpp,
-AppHelpers.h, AppHelpers.cpp,
-BlockingQueue.h, BlockingQueue.cpp,
-Display.h, Display.cpp,
-Message.h, Message.cpp
- Dispatcher.h, Dispatcher.cpp

Build commands
- devenv ExecutiveClient.vcxproj / debug rebuild

Maintenance History :
== == == == == == == == == ==
ver 1.0 : 11 April 2015
- first release
*/

#include <iostream>
#include <string>
#include <thread>
#include "../Message/Message.h"
#include "../Sockets/Sockets.h"
#include "../Reciever/Reciever.h"
#include "../Sender/Sender.h"
#include "../Display/Display.h"
#include "../BlockingQueue/BlockingQueue.h"

using namespace std;
namespace MessagePassing
{
	class ExecutiveClient
	{
	public:
		ExecutiveClient(std::size_t srcport, std::string targetport, Socket::IpVer ipv); // Constuctor for executive client side
		~ExecutiveClient();                                                              // destructor
		void start(Message msg);                                                         // Starts the executive client side
		void stop();                                                                     // stops the client

	private:
	
		size_t srcPort;
		std::string srcIP;
		std::string dstport;
		std::string dstport2;
		std::string dstIP;
		Message msg;
		Display display;
		SocketSystem* ss;
		Receiver* receiver;
		string file;
		Dispatcher* dispatcher_;
		Sender* sender;
	};
}
#endif
