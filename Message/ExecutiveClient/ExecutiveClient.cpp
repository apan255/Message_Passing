/////////////////////////////////////////////////////////////////////
//  ExecutiveClient.cpp - Execute client side                      //
//                                                                 //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2013                                 //
//  Platform:      Dell, Windows 8.1                               //
//  Application:   Scope analysis, OOD Assignment 3, Spring2015    //
//  Author:		   Ankur Pandey                                    //
/////////////////////////////////////////////////////////////////////

#include "ExecutiveClient.h"
using namespace MessagePassing;

//-------<Starts the receiver and sender>------------------------------
void ExecutiveClient::start(Message msg){
	receiver->connect(srcPort);
	while (!sender->connect(dstIP, dstport)){
		display.printHeader("\n Not able to connect to server");
		::Sleep(100);
	}
	sender->msgSend(msg);
	sender->start();
	sender->wait();

	if (msg.getHeader().getDstPort2() != ""){
		::Sleep(400);
		Sender SenderNewDst;
		dstport = msg.getHeader().getDstPort2();
		msg.getHeader().setDstIPAndPort(dstIP, dstport);
		while (!SenderNewDst.connect(dstIP, dstport)){
			display.printHeader("\n Not able to connect to server");
			::Sleep(100);
		}
		SenderNewDst.msgSend(msg);
		SenderNewDst.start();
		SenderNewDst.wait();
	}
}

//-------< Construct which constructs the receiver and sender>------------------------------
ExecutiveClient::ExecutiveClient(std::size_t srcPort, std::string targetport, Socket::IpVer ipv) :
dispatcher_(new Dispatcher()), receiver(new Receiver(srcPort, ipv, *dispatcher_)),
sender(new Sender()), srcIP("localhost"), srcPort(srcPort), dstIP("localhost"),
dstport(targetport), ss(new SocketSystem()){
}

//-------< Deletes the pointer of receiver and sender>------------------------------
ExecutiveClient::~ExecutiveClient(){
	delete receiver;
	delete ss;
	delete sender;
	delete dispatcher_;
}

//-------<Stops the sender>------------------------------
void ExecutiveClient::stop(){
	::Sleep(4000);
	sender->stop();
}


#ifdef TEST_EXECLIENT
//----< Calling Client Main >-------------------------------------------
int main(int argc, char* argv[]){
	try{
		Display display;
		int cnt = 0;
		Verbose v(true);
		Message msg;
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
		ExecutiveClient client(stoi(msg.getHeader().getSrcPort()), msg.getHeader().getDstPort(), Socket::IpVer::IP6);
		client.start(msg);
		Cosmetic cosmetic;
		::Sleep(2000);
		client.stop();
	}
	catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif