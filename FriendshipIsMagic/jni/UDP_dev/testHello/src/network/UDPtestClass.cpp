/*
 * UDPtestClass.cpp
 *
 *  Created on: 21 juin 2016
 *      Author: edwardvergara
 */

#include "UDPtestClass.h"


void UDPtestClass::testRoutine(PacketCommand& cmd){

	//*

	//Creating the server
	UDPAgent udpServer(UDPAgent::DEFAULT_PORT);
	udpServer.addObserver(this);

	//Creating the client
	UDPAgent udpClient(UDPAgent::DEFAULT_PORT+1,"137.194.57.129", UDPAgent::DEFAULT_PORT);
	//UDPAgent udpClient(UDPAgent::DEFAULT_PORT+100,"localhost", UDPAgent::DEFAULT_PORT);
	udpClient.addObserver(this);

	try{
		udpServer.start() ;
		udpClient.start();
	}
	catch (UDPException& e){
		std::cout << "Binding error";
		return;
	}




	Player player;
	player.setFirstName("from");
		player.setLastName("Client");
	sf::Packet pkt = SayPlayerInfoCommand::make(player);
	//pkt <<"Hello from client!";
	int i = 0;
	std::cout <<"======= Sending from client" << std::endl;
	for( i =0; i<5; i++){
		//std::cout <<"N°" << i+1 << " ";
		udpClient.send(pkt);
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}

	//pkt  = sf::Packet();
	//pkt <<"Hello from Server!";
	player.setFirstName("from");
	player.setLastName("Server");
	 pkt = SayPlayerInfoCommand::make(player);
	std::cout <<"======= Sending from server" << std::endl;
	for(; i<10; i++){
			//std::cout <<"N°" << i+1 << " ";
			udpServer.send(pkt);
			std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}

	//boucle qui attend 4sec
	//for (int i =0; i<4000;i++){
	std::cout << i << " packets to receive"<< std::endl;
	while(i >0){

		queueMutex.lock();
		if(packetBuf.empty() == false){
			//std::cout<< "not empty"<<std::endl;

			auto pkt_ptr = packetBuf.front();
			packetBuf.pop();
			queueMutex.unlock();

			std::cout << "Receive n° " << i << " : " << std::flush;
			cmd.interpret(*pkt_ptr);
			//string str;
			//pkt >> str;
			//std::cout << "Popped from buf :" << str << std::endl;
			i--;
		} else {
			queueMutex.unlock();
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	//*/
}


void UDPtestClass::notify(std::shared_ptr<sf::Packet> pkt){
	//std::cout << "notify appelé" << std::endl;
	/*
	std::string str;
	pkt >> str;
	std::cout << str << std::endl;
	*/
	sf::Lock lockQueue(mutex);
	//std::cout << "buf filled with one packet" << std::endl;

	packetBuf.push(pkt);
}
