@echo off
Title SERVER-1

echo *************************************************************************
echo For Demonstrating project requirement 4 : Package Message exists 
echo which constructes and interpretes messages  
echo *************************************************************************

echo *************************************************************************
echo For Demonstrating project requirement 6: Package Reciever and sender exists 
echo which encapsulate the communication channel facilities into easy to use for 
echo server and reciever  
echo *************************************************************************

echo *************************************************************************
echo Demonstrating project requirement 3, 5 and 7 with transporting binary (testImage.png) and text files (TestDoc.txt , Messa.cpp)  
echo    
echo NOTE 1: Server Directory is SERVER_DIRECTORY_LISTENPORT eg. SERVER_DIRECTORY_8484
echo 
echo NOTE 2: 
echo     Server1 : Listens at port 8484 and sends at port: 9091 and 8081
echo     Server2 : Listens at port 9100 and sends at port: 9091
echo     Client1 : Listens at port 8081 and sends at port: 8484
echo     Client2 : Listens at port 9091 and sends at port: 9100 and 8484
echo
echo NOTE 3: 
echo     Client1 sends a file TestDoc.txt to Server1 and receives acknowledgement back
echo     Client2 sends a binary file testImage.png to Server1 and Messa.cpp to Server2 and receives acknowledgement back
echo     Server1 receives file from Client1 and Client2 and sends acknowledgement back to both
echo     Server2 receives file from Client2 and sends acknowledgement back to Client2
echo *************************************************************************


echo *************************************************************************
echo SERVER-1 
echo *************************************************************************
".\Message\Debug\ExecutiveServer.exe" "COMMAND:UploadFile" "SRCIP:localhost" "SRCPORT:8484" "FILENAME:.\\TEST_Folder\\TextDocument3.txt" "FILETYPE:binary" "DSTIP:localhost" "DISPORT:8081"

