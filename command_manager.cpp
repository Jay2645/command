#include "command_manager.h"
#include "core/os/input.h"

void CommandManager::_bind_methods() {
	ADD_SIGNAL(MethodInfo("execute_command"));

	ClassDB::bind_method(D_METHOD("execute_all_commands", "delta_time"), &CommandManager::execute_all_commands);
	ClassDB::bind_method(D_METHOD("set_reciever", "reciever"), &CommandManager::set_reciever);
}

void CommandManager::execute_all_commands(float delta_time) {
	if (_command_reciever == NULL) {
		print_error("Command reciever is null!");
		return;
	}

	emit_signal(EXECUTE_COMMAND_NAME, _command_reciever, delta_time);
}

void CommandManager::set_reciever(Object *reciever) {
	_command_reciever = reciever;
}

void CommandManager::add_listener(CommandNode *listener, StringName execute_command) {
	if (!is_connected(EXECUTE_COMMAND_NAME, listener, execute_command)) {
		connect(EXECUTE_COMMAND_NAME, listener, execute_command);
	}
}

void CommandManager::remove_listener(CommandNode *listener, StringName execute_command) {
	if (is_connected(EXECUTE_COMMAND_NAME, listener, execute_command)) {
		disconnect(EXECUTE_COMMAND_NAME, listener, execute_command);
	}
}
