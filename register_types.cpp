#include "register_types.h"

#include "command_manager.h"
#include "command_node.h"
#include "input_command_node.h"
#include "mouse_command_node.h"

void register_command_types() {
	ClassDB::register_class<CommandManager>();
	ClassDB::register_class<CommandNode>();
	ClassDB::register_class<InputCommandNode>();
	ClassDB::register_class<MouseCommandNode>();
}

void unregister_command_types() {

}

