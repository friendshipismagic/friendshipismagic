/*
 * UDPtestClass.cpp
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#include "UDPtestClass.h"

UDPtestClass::UDPtestClass() {
	// TODO Auto-generated constructor stub

}

void UDPtestClass::testRoutine(){
	//Creating the server
	UDPAgent udpServer(UDPAgent::DEFAULT_PORT);
	udpServer.AddObserver(this);
	udpServer.start();

	//Creating the client
	UDPAgent udpClient(UDPAgent::DEFAULT_PORT+100,"localhost", UDPAgent::DEFAULT_PORT);
	udpClient.AddObserver(this);
	udpClient.start();



	sf::Packet pkt;
	pkt <<"Hello from client!";
	std::cout <<"======= Sending from client" << std::endl;
	for(int i =0; i<5; i++){
		//std::cout <<"N°" << i+1 << " ";
		udpClient.send(pkt);
		std::this_thread::sleep_for (std::chrono::milliseconds(500));
	}

	pkt  = sf::Packet();
	pkt <<"Hello from Server!";
	std::cout <<"======= Sending from server" << std::endl;
	for(int i =0; i<5; i++){
			//std::cout <<"N°" << i+1 << " ";
			udpServer.send(pkt);
			std::this_thread::sleep_for (std::chrono::milliseconds(500));
	}

	//boucle qui attend 2sec
	for (int i =0; i<2000;i++){

		if(packetBuf.empty() == false){
			//std::cout<< "not empty"<<std::endl;
			pkt = packetBuf.front();
			packetBuf.pop();
			string str;
			pkt >> str;
			std::cout << "Popped from buf :" << str << std::endl;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

}

UDPtestClass::~UDPtestClass() {
	// TODO Auto-generated destructor stub
}
void UDPtestClass::Notify(sf::Packet pkt){
	//std::cout << "notify appelé" << std::endl;
	/*
	std::string str;
	pkt >> str;
	std::cout << str << std::endl;
	*/
	//std::cout << "buf filled with one packet" << std::endl;
	packetBuf.push(pkt);
}
