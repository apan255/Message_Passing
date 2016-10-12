/////////////////////////////////////////////////////////////////////
//  MsgHeader.cpp - Conatin Message Header Information             //
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
#include "MsgHeader.h"

using namespace MessagePassing;

//----< Message Header Construction >-  ------------------------------
MsgHeader::MsgHeader(){
	command_ = 0;
	srcIP = "";
	srcPort = "";
	dstIP = "";
	dstPort = "";
	fileName = "";
	FileType_ = 0;
	bodyLength_ = "";
}

//----< To String Conversion >----------------------------------------
std::string MsgHeader::toString(int i)
{
	std::ostringstream conv;
	conv << i;
	return conv.str();
}

//----< Setting Parameters >-------------------------------------------
void MsgHeader::setParameters(std::string name, std::string value){
	if (name.compare("COMMAND") == 0){
		Command cmd_val = static_cast<Command>(atoi(value.c_str()));
		command_ = cmd_val;
		if (value == "UploadFile")
			command_ = Command::UploadFile;
	}
	else if (name.compare("FILETYPE") == 0){
		FileType file_val = static_cast<FileType>(atoi(value.c_str()));
		FileType_ = file_val;
	}
	else if (name.compare("BODYLENGTH") == 0)
		bodyLength_ = value.c_str();

	setParametersHelper(name, value);
}

//----< Setting Parameters Helper >------------------------------------------------
void MsgHeader::setParametersHelper(std::string name, std::string value){
		
	if (name.compare("SRCIP") == 0)
			srcIP = value;
		else if (name.compare("SRCPORT") == 0)
			srcPort = value;
		else if (name.compare("DSTIP") == 0)
			dstIP = value;
		else if (name.compare("DISPORT") == 0)
			dstPort = value;
		else if (name.compare("DISPORT2") == 0)
			distPort2 = value;
		else if (name.compare("FILENAME") == 0)
			fileName = value;
}

//----< Setting Command >------------------------------------------------
void MsgHeader::setCommand(int cmd)
{
	command_ = cmd;
}

//----< Setting Destination IP and Destination Port >--------------------
void MsgHeader::setDstIPAndPort(std::string ip, std::string port)
{
	dstIP = ip;
	dstPort = port;
}

//----< Setting Source IP and Source Port >------------------------------
void MsgHeader::setSrcIPAndPort(std::string ip, std::string port)
{
	srcIP = ip;
	srcPort = port;
}

//----< Setting File Name and file Type >---------------------------------
void MsgHeader::setFileNameAndType(std::string FileName, int fileType)
{
	fileName = FileName;
	FileType_ = fileType;
}

//----< setting Body Length>---------------------------------------------
void MsgHeader::setBodylength(std::string length)
{
	bodyLength_ = length;
}

//----< Getting Command  >-----------------------------------------------
std::string MsgHeader::getCommand()
{
	return toString(command_);
}

//----< Getting File Name >-----------------------------------------------
std::string MsgHeader::getFileName(){
	return fileName;
}

//----< Getting File Type >-----------------------------------------------
std::string MsgHeader::getFileType(){
	return toString(FileType_);
}

//----< Getting Body Length >------------------------------------------
std::string MsgHeader::getBodylength(){
	return bodyLength_;
}

//----< Getting Destination IP >------------------------------------------
std::string MsgHeader::getDstIP(){
	return dstIP;
}

//----< Getting Destination Port >------------------------------------------
std::string MsgHeader::getDstPort(){
	return dstPort;
}

//----< Getting Destination Port Second>-------------------------------------
std::string MsgHeader::getDstPort2(){
	return distPort2;
}

//----< Getting Source IP >------------------------------------------------
std::string MsgHeader::getSrcIP(){
	return srcIP;
}

//----< Getting Source Port >------------------------------------------------
std::string MsgHeader::getSrcPort(){
	return srcPort;
}

#ifdef TEST_MSGHEADER
//----< Calling MshHeader Main >---------------------------------------------
int main(int argc, char* argv[])
{
	try{
		std::cout << "\n\n ########################## TESTING HEADER PACKAGE #################################### \n\n";
		std::string srcAddr = "127.0.0.1", srcPort = "8484", targetAddr = "127.0.0.1", targetPort = "8181";
		MsgHeader head;
		head.setCommand(MessageSend);
		head.setDstIPAndPort(targetAddr, targetPort);
		head.setParameters("SRCIP", "8888");
		std::cout << "\n I am here Command =  " << head.getCommand() << "\n";
	}
	catch (std::exception& ex){
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	return 0;
}
#endif
