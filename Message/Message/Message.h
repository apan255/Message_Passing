#ifndef MESSG_H
#define MESSG_H
/////////////////////////////////////////////////////////////////////
//  Message.h - Conatin Message Information                        //
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
This module defines a class that provides services to store and fetch Message Information.

Public Interface:
=================
Message Message;                                               // Message  Construction
std::string str = Message.toString(int i);                     // Conversion int to String
Message.messageInterpret(std::string msg);                     // Interpreting Message and storing to header
std::string str = Message.constructHeader();                   // Constructing Message from header and returning string
std::string str = Message.getMessage();                        // Getting Message for transfer
Message.setMessage(std::string msg);                           // Setting Message for transfer
MsgHeader& MsgHeader = Message.getHeader();                    // Returning Header

Build Process:
==============
Required files
- Message.h, Message.cpp,
- MsgHeader.h, MsgHeader.cpp,
- AppHelpers.h, AppHelpers.cpp

Build commands
- devenv Message.vcxproj /debug rebuild

Maintenance History:
====================
ver 1.0 : 11 April 2015
- first release
*/
#include <map>
#include <vector>
#include "../MsgHeader/MsgHeader.h"
#include "../ApplicationHelpers/AppHelpers.h"

namespace MessagePassing
{
	class Message
	{
	public:
		std::string toString(int i);                       // Conversion int to String
		Message();                                         // Message Constructor
		void messageInterpret(std::string msg);            // Interpreting Message and storing to header 
		std::string constructHeader();                     // Constructing Message from header and returning string
		std::string getMessage();                          // Getting Message for transfer
		void setMessage(std::string msg);                  // Setting Message for transfer
		MsgHeader& getHeader();                            // Returning Header
		~Message(){}                                       // Destructor       
		void Message::parseString(std::string& str, char start);
	private:    
		MsgHeader msgHeader_;
		std::string message_;
		bool isHeaderReceived;
	};
}
#endif



