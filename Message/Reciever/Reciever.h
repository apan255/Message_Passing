#ifndef RECEIVER_H
#define RECEIVER_H
/////////////////////////////////////////////////////////////////////
//  Reciever.h -  Recieves Information end point in blocking call  //
//                And send back to client                          //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module defines a class that provides services to  receives, interprets 
and handles appropriately incoming messages, be it a file or a plain text message.
If a file message is received, the header indicates the length of the body and 
then the bytes are stored in the buffer. Once the end of file of received the 
entire buffer is written together at once thus preventing data to be garbled from multiple
clients sending the same file.

Public Interface:  Class Receiver:
=================
	Receiver(int port, Socket::IpVer ipv, Dispatcher& dispatcher);         // Reciever constructor
	void connect(int port);                                                // connect to the port
	virtual ~Receiver();                                                   // Destructor
	void sendMessage(Message msg);                                         // Enqueue the messages to the blocking queue

Public Interface:  Class ClientHandler:
=================
-Listens and creates new thread for processing request for each new incoming socket requests on the receiving port
    ClientHandler(BlockingQueue<Message>& q, Dispatcher& dispatcher);       // Client Handler constructor  
	void operator()(Socket& socket_);                                       // Client Handler thread starts running this
	size_t ClientHandler::stringToInt(std::string str);                     // string to int
	void writeToFile(MessageId id, Message messg, char* byte);              // Writes the file to destination directory
	void processMessage(Socket& socket, Message& msg);                      // Process the messsages of acknowledgement and End of File
	char* socketBufferHandler(Socket& socket);                              // Reads data from the Socket
	MessageId getMessageIdentifier(Message&);                               // Generate Identifier of file

Build Process :
== == == == == == ==
Required files
- Sockets.h, Sockets.cpp,
-Receiver.h, Receiver.cpp,
-AppHelpers.h, AppHelpers.cpp,
-BlockingQueue.h, BlockingQueue.cpp,
-Display.h, Display.cpp,
-Message.h, Message.cpp
-Dispatcher.h, Dispatcher.cpp

Build commands
- devenv Receiver.vcxproj / debug rebuild

Maintenance History :
== == == == == == == == == ==
ver 1.0 : 11 April 2015
- first release
*/
#include "../sockets/sockets.h"
#include <string>
#include <sstream>
#include <thread>
#include <mutex>
#include "../FileSystem/FileSystem.h"
#include "../ApplicationHelpers/AppHelpers.h"
#include "../Message/Message.h"
#include "../Display/Display.h"
#include "../BlockingQueue/BlockingQueue.h"
#include "../Dispatcher/Dispatcher.h"


namespace MessagePassing
{
	/////////////////////////////////////////////////////////////////////////////
	// Server's client handler class
	// - must be callable object so we've built as a functor
	// - passed to SocketListener::start(CallObject& co)
	// - Client handling thread starts by calling operator()

	class ClientHandler  
	{
	public:
		using MessageId = std::string;
		ClientHandler(BlockingQueue<Message>& q, Dispatcher& dispatcher);       // Client Handler constructor  
		void operator()(Socket& socket_);                                       // Client Handler thread starts running this
		size_t ClientHandler::stringToInt(std::string str);                     // string to int
		void writeToFile(MessageId id, Message messg, char* byte);              // Writes the file to destination directory
		void processMessage(Socket& socket, Message& msg);                      // Process the messsages of acknowledgement and End of File
		char* socketBufferHandler(Socket& socket);                              // Reads data from the Socket
		MessageId getMessageIdentifier(Message&);                               // Generate Identifier of file

	private:
		void processCmd(Message messg, Socket& socket_, Command cmd_val);       // Process command 
		std::string filePath;
		BlockingQueue<Message>& bq_;
		Dispatcher& dispatcher_;
		std::map<MessageId, std::vector<char*>> messageMap_;
		size_t bufferSize_;
		Display disp;
	};

	///////////////////////////////////////////////////
	// Receiver

	class Receiver 
	{
	public:
		Receiver(int port, Socket::IpVer ipv, Dispatcher& dispatcher);    // Reciever constructor
		void connect(int port);                                           // connect to the port
		virtual ~Receiver();                                              // Destructor
		void sendMessage(Message msg);                                    // Enqueue the messages to the blocking queue
	private:
		SocketListener listener_;
		int port_;
		BlockingQueue<Message> queue_;
		ClientHandler client_; 
		std::thread* thread_;
	};
}
#endif



