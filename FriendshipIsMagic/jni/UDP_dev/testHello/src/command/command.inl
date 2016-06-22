/*
 * Command.cpp
 *
 *  Created on: 17 juin 2016
 *      Author: antony
 */


// Adds command to the interpretor
template<typename InstructionType, typename Stream>
void Command<InstructionType, Stream>::setCommand(
	InstructionType commandId,
	std::function<void(Stream&)> command
) {
	mStoredCommands[commandId] = command;
}

template<typename InstructionType, typename Stream>
void Command<InstructionType, Stream>::interpret(Stream& packet) {
	InstructionType commandId;
	packet >> commandId;
	auto command = mStoredCommands.find(commandId);
	if (command != mStoredCommands.end()){
		(command->second) (packet); // Calling the function
	}
}