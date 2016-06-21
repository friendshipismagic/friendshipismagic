/*
 * Command.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: edwardvergara
 */

// #include "Command.h"

//serveur.sendCommand(Commands::connectPlayer("",""))


/*
template<typename InstructionType, typename Stream>
Command<InstructionType, Stream>::Command(std::string fileName){
	mFile.open(fileName.c_str());
	if(!mFile){
		std::cerr << "Error: can't open file";

	}
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
	bool parsingSuccessful = reader.parse( mFile, root ,false);
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n"
				   << reader.getFormattedErrorMessages();
	}

	const Json::Value list = root["CommandList"];
	for ( int index = 0; index < list.size(); ++index )  // Iterates over the sequence elements.
	   {
		this.setCommand(index,);
	   }
	
}
template<typename InstructionType, typename Stream>
Command<InstructionType, Stream>::~Command() {
	mFile.close();
}
*/



// Adds command to the interpretor
template<typename InstructionType, typename Stream>
void Command<InstructionType, Stream>::setCommand(
	int commandId,
	std::function<void(Stream&)> command
) {
	mStoredCommands[commandId] = command;
}

template<typename InstructionType, typename Stream>
void Command<InstructionType, Stream>::interpret(Stream& packet) {
	InstructionType commandId;
	packet >> commandId;
	auto command = mStoredCommands.find(commandId);
	if (command != mStoredCommands.end())
		(command->second) (packet); // Appel de la commande
}

/*
 * template<typename InstructionType, typename Stream>
Command<InstructionType, Stream>::~Command() {

}*/


