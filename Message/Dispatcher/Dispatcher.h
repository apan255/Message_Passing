#ifndef DISPATCHER_H
#define DISPATCHER_H
/////////////////////////////////////////////////////////////////////
//  Dispatcher.h - Display Message Passing Project                 //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////
/*
Module operation:
====================
This module handles the dispatching mecahnism where it deques the messages in the Receivers blocking queue
and enqueue it into the sender's queue

Public interface:
=====================
Dispatcher(){}					         // Constructor
void addToMessages(Message& msg);		// Enqueue the message to the blocking queue
void getMessages();						// Dequee the messages from the blocking queue and send to the sender
void start();							// start the dispatcher thread
void detach();							// detaches the thread
~Dispatcher();					        // destructor

Build Process:
==========================
- devenv Dispatcher.sln

Required files:
=========================
- MessageCommunication.h
- Sockets.h, Sockets.cpp, Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp
- Message.h, Message.cpp. Header.h
- Sender.h, Receiver.h
- FileSystem.h, FileSystem.cpp

Maintanence History:
=========================
ver 1.0 - 13 Apr 2015
- first release
*/
#include "../Sockets/Sockets.h"
#include <string>
#include <sstream>
#include "../Message/Message.h"
#include "../FileSystem/FileSystem.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../Sender/Sender.h"


using namespace FileSystem;
using namespace ApplicationHelpers;
namespace MessagePassing
{
	class Dispatcher
	{
	public:
		Dispatcher(){}                          // Consturctor
		void addToMessages(Message& msg);		// Enqueue the message to the blocking queue
		void getMessages();						// Dequee the messages from the blocking queue and send to the sender
		void start();							// start the dispatcher thread
		void detach();							// detaches the thread
		~Dispatcher();					        // destructor
	private:
		std::thread* dispatcher;
		BlockingQueue<Message> bq_;

	};
}
#endif 