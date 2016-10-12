/////////////////////////////////////////////////////////////////////
//  ExecutiveServer.cpp - Execute Server side                      //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////
#include "ExecutiveServer.h"

//-------<Starts the executive server side>------------------------------
void MessagePassing::ExecutiveServer::start(Message& msg){
	receiver->connect(srcPort);

	while (!sender->connect("localhost", dstport)){
		display.printHeader("\n Not able to connect to server");
		::Sleep(100);
	}
	if (msg.getHeader().getDstPort() != ""){
		dstport = msg.getHeader().getDstPort();
		while (!sender->connect("localhost", dstport)){
			display.printHeader("\n Not able to connect to server");
			::Sleep(100);
		}
	}
}

//-------<Stops the sender>------------------------------
void MessagePassing::ExecutiveServer::stop(){
	::Sleep(3000);
	sender->stop();
}

//-------< Constuctor for executive server side>------------------------------
MessagePassing::ExecutiveServer::ExecutiveServer(std::size_t srcPort, std::string targetport, Socket::IpVer ipv) :dispatcher_(new Dispatcher()),
receiver(new Receiver(srcPort, ipv, *dispatcher_)), sender(new Sender()), srcIP("localhost"), srcPort(srcPort),
dstIP("localhost"), dstport(targetport), ss(new SocketSystem()){
}

//-------< destructor for  sender side executive>------------------------------
MessagePassing::ExecutiveServer::~ExecutiveServer(){
	delete sender;
	delete dispatcher_;
	delete receiver;
	delete ss;
}

#ifdef TEST_EXECSERVER
//----< Calling Client Main >-------------------------------------------------------
int main(int argc, char* argv[]){
	try{
		MessagePassing::Display display;
		Verbose v(true);
		MessagePassing::Message msg;
		if (argc < 5){
			display.printHeader("Invalid Entry, Please provide Command, SourcePort, Destination Port and File Name \n");
			return 0;
		}
		std::string message;
		for (int i = 0; i < argc; i++){
			message += argv[i];
			message += ";";
		}
		msg.messageInterpret(message);
		if ((msg.getHeader().getSrcPort() == "") || msg.getHeader().getDstPort() == "" || msg.getHeader().getFileName() == ""){
			display.printHeader("Invalid number of input \n");
			return 0;
		}
		std::string target_Port = msg.getHeader().getDstPort();
		size_t srcPort = stoi(msg.getHeader().getSrcPort());
		string FileName = msg.getHeader().getFileName();
		if (target_Port == "")
			target_Port = "9089";
		if (msg.getHeader().getSrcPort() == "")
			srcPort = 9761;
		if (FileName == "")
			FileName = "No.txt";
		MessagePassing::ExecutiveServer server(srcPort, target_Port, Socket::IpVer::IP6);
		server.start(msg);
		Cosmetic cosmetic;
		::Sleep(2000);
		server.stop();
	}catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif