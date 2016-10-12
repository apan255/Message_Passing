/////////////////////////////////////////////////////////////////////
//  Reciever.cpp -  Recieves Information end point in blocking call//
//                And send back to client                          //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include "Reciever.h"

using namespace ApplicationHelpers;
using namespace MessagePassing;

//-------< Process the messsages of acknowledgement and End of File >------------------------------
void ClientHandler::processMessage(Socket& socket_, Message& message)
{

	std::string cmd = message.getHeader().getCommand();
	Command cmd_val = Command::NONE;
	if (cmd == "1" || cmd == "2" || cmd == "3" || cmd == "4" || cmd == "5" || cmd == "6")
		cmd_val = static_cast<Command>(atoi(cmd.c_str()));
	if (cmd_val == FileEnded)
	{
		Message ack;
		ack.getHeader().setCommand(Acknowledge);
		ack.getHeader().setDstIPAndPort(message.getHeader().getSrcIP(), message.getHeader().getSrcPort());
		ack.getHeader().setFileNameAndType(message.getHeader().getFileName(), atoi(message.getHeader().getFileType().c_str()));
		if (socket_.sendString(ack.constructHeader()))
			disp.printHeader("ACK sent back to " + message.getHeader().getSrcPort() + " for file: " +
			FileSystem::Path::getName(message.getHeader().getFileName()));
	}
	if (cmd_val == Acknowledge){
		disp.printHeader("File Acknowledgement Received FileName : " + message.getHeader().getFileName() + " Client:" + message.getHeader().getSrcIP());
	}
	if (cmd_val == MessageSend){
		Message ack;
		ack.getHeader().setCommand(Acknowledge);
		ack.getHeader().setDstIPAndPort(message.getHeader().getSrcIP(), message.getHeader().getSrcPort());
		ack.getHeader().setFileNameAndType(message.getHeader().getFileName(), atoi(message.getHeader().getFileType().c_str()));
		std::string MsgBody = socket_.recvString('\n');
		disp.printHeader("\n Message recieved from Client Msg=" + MsgBody + "\n");
	}
}

//-------< Reads data from the Socket >------------------------------
char* ClientHandler::socketBufferHandler(Socket& socket_)
{
	while (true)
	{
		if (socket_.bytesWaiting() == 0)
			break;
		char* buffer = new char[bufferSize_];
		if (socket_.recv(bufferSize_, buffer))
			return buffer;
		else
			return nullptr;
		if (socket_ == INVALID_SOCKET)
			return nullptr;
	}
	return nullptr;
}

//--------------< Writes the file to destination directory >--------------------
void ClientHandler::writeToFile(MessageId id, Message msg, char* byte){

	std::string path = msg.getHeader().getFileName();
	std::string filename = Path::getName(path);

	std::string command = msg.getHeader().getCommand();
	std::string fileType = msg.getHeader().getFileType();;
	std::ofstream ofstream;
	std::string filePath_ = filePath + "_" + msg.getHeader().getDstPort();
	if (!(Directory::exists(filePath_)))
		Directory::create(filePath_);
	Command cmd_val = static_cast<Command>(atoi(command.c_str()));
	FileType file_Type = static_cast<FileType>(atoi(command.c_str()));
	if (file_Type == text)
		ofstream.open(filePath_ + "//" + filename, std::ios::out | std::ios::binary | std::ofstream::app | std::ofstream::ate);
	else if (file_Type == binary)
		ofstream.open(filePath_ + "//" + filename, std::ios::out | std::ios::binary | std::ofstream::app | std::ofstream::ate);
	if (ofstream.good()){
		ofstream.write(byte, stoi(msg.getHeader().getBodylength()));
		ofstream.close();
	}
	else{
		disp.printHeader("\n Unable to Write File");
	}
}

//-------< Generate Identifier of file >------------------------------
ClientHandler::MessageId ClientHandler::getMessageIdentifier(Message& msg)
{
	return  msg.getHeader().getFileName() + "@" + msg.getHeader().getSrcPort();
}

//-------< Constructor >------------------------------
Receiver::Receiver(int port, Socket::IpVer ipv, Dispatcher& comm) :listener_(port, ipv), client_(queue_, comm), port_(port){
}

//-------< Enqueue the messages to the blocking queue >------------------------------
void  Receiver::sendMessage(Message msg)
{
	queue_.enQ(msg);
}

//-------< Client Handler constructor  >---------------------------------------------
ClientHandler::ClientHandler(BlockingQueue<Message>& q, Dispatcher& dispatcher) : bq_(q), dispatcher_(dispatcher){
	filePath = ".//SERVER_DIRECTORY";
}

//-------< connectting to the port >--------------------------------------------------
void Receiver::connect(int port)
{
	::Sleep(1000);
	try{
		Verbose v(true);
		listener_.start(client_);
	}
	catch (std::exception ex){
		Verbose::show(ex.what());
	}
}

//-------< destructor >---------------------------------------------------------------
Receiver::~Receiver(){
}

//-------< Converts String to Integer >-----------------------------------------------
size_t ClientHandler::stringToInt(std::string str)
{
	std::istringstream iss(str);
	iss >> bufferSize_;
	return bufferSize_;
}

//----< Client Handler thread starts running this  >------------------------------------
void ClientHandler::operator()(Socket& socket_)
{
	while (true){
		if (socket_.bytesWaiting() == 0)
			continue;
		::Sleep(100);
		Message messg;
		std::string recvMsg = socket_.recvString('\n');
		messg.messageInterpret(recvMsg);
		MsgHeader msgHeader = messg.getHeader();
		std::string cmd = msgHeader.getCommand();
		Command cmd_val = Command::NONE;
		if (cmd == "1" || cmd == "2" || cmd == "3" || cmd == "4" || cmd == "5" || cmd == "6")
			cmd_val = static_cast<Command>(atoi(cmd.c_str()));
		MessageId msgId;
		msgId = getMessageIdentifier(messg);
		if (UploadFile == cmd_val){
			bufferSize_ = stringToInt(messg.getHeader().getBodylength());
			char* content = socketBufferHandler(socket_);
			std::string path = messg.getHeader().getFileName();
			std::string filename = Path::getName(path);
			disp.printString("Writing to File : " + filename + " Received from " + messg.getHeader().getSrcPort());
			writeToFile(msgId, messg, content);
			continue;
		}
		processCmd(messg,socket_,cmd_val);
		if (socket_ == INVALID_SOCKET)
			break;
		processMessage(socket_, messg);
	}
	Verbose::show("ClientHandler socket connection closing");
	socket_.shutDown();
	socket_.close();
	Verbose::show("ClientHandler thread terminating");
}

//-------< Process commands break >---------------------------------------
void ClientHandler::processCmd(Message messg, Socket& socket_, Command cmd_val)
{
	if (FileEnded == cmd_val)
		disp.printHeader(" File End Command recieved . Passing acknowledgement ");
}

#ifdef TEST_RECIEVER
//-------< Reciever main test >---------------------------------------
int main()
{
	try
	{
		Verbose v(true);
		std::cout << "\n\n ########################## TESTING RECIEVER PACKAGE #################################### \n\n";
		SocketSystem ss;
		int clientPort = 8484;
		Dispatcher Dispatcher_;
		Receiver rerc(clientPort, Socket::IP6, Dispatcher_);
		rerc.connect(clientPort);
		Display display;
		display.printHeader("Press ank key:");
		std::cin.get();
	}
	catch (std::exception& ex)
	{
		Verbose::show("  Exception caught:", always);
		Verbose::show(std::string("\n  ") + ex.what() + "\n\n");
	}
}
#endif

