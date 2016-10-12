#ifndef SENDER_H
#define SENDER_H
/////////////////////////////////////////////////////////////////////
//  Sender.h -  Sender Information end point in blocking call      //
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
This module defines a class that provides services to send message to  end point in blocking call.

Public Interface:
=================
Sender Sender;                                                 // Sender  Construction
bool val = Sender.sendBlock(Message& msg);		   			   // send the file and its header to the socket
bool val = Sender.msgSend(Message& message);		   		   // process the message from queue
bool val = Sender.connect(std::string ip, std::string port);   // connect the sender to specific IP and Port
bool val = Sender.sendString(Message& msg);				       // creates the string from msg and sends to receiver
virtual ~Sender();											   // destructor
Sender.start();												   // starts a new thread for the Sender
Sender.run();												   // deques the message from the blocking queue
Sender.stop();												   // creates a stop message
Sender.wait();												   // calls join on the sender thread

Build Process:
==============
Required files
- Sender.h, Sender.cpp,
- FileSystem.h, FileSystem.cpp,
- AppHelpers.h, AppHelpers.cpp,
- BlockingQueue.h, BlockingQueue.cpp,
- Display.h, Display.cpp,
- Message.h, Message.cpp

Build commands
- devenv Sender.vcxproj /debug rebuild

Maintenance History:
====================
ver 1.0 : 11 April 2015
- first release
*/

#include <string>
#include <sstream>
#include <thread>
#include "../sockets/sockets.h"
#include "../FileSystem/FileSystem.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../BlockingQueue/BlockingQueue.h"
#include "../Display/Display.h"
#include "../Message/Message.h"

using namespace FileSystem;

namespace MessagePassing{
	class Sender
	{
	public:
		Sender();                                                       // Constructs the instance of the Socket
		bool connect(std::string ip, std::string port);                 // Connect to specified ip and port
		virtual ~Sender();                                              // destructor
		bool sendString(Message msg);                                  // send the message string
		bool sendBlock(Message msg);                                   // Sends blocks of file to the socket
		void start();                                                   // Starting Sender thread over run method 
		void stop();                                                    // stopping sender  
		void run();                                                     // Run the Sender thread
		void msgSend(Message& msg);                                     // message send to blocking queue
		void wait();                                                    // Wait sender to compelete
	private:
		bool acknowledgementCheck(Message& msg);                        // Checking acknowledgement recieved
		SocketConnecter *SocketCon_;
		BlockingQueue<Message> queue_;
		std::thread* t;
		Display disp;
	};
}
#endif SENDER_H