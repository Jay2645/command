#include "command_node.h"
#include "command_manager.h"

CommandNode::CommandNode() {
	connect("ready", this, "_command_ready");
	execute_once = false;
}

void CommandNode::_command_ready() {
	if (has_node(command_manager_path)) {
		_manager = cast_to<CommandManager>(get_node(command_manager_path));
	}
}

void CommandNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_command_ready"), &CommandNode::_command_ready);

	ClassDB::bind_method(D_METHOD("execute_command", "commanded_object", "delta_time"), &CommandNode::execute_command);
	ClassDB::bind_method(D_METHOD("_execute", "commanded_object", "delta_time"), &CommandNode::_execute);
	ClassDB::bind_method(D_METHOD("_on_command_start"), &CommandNode::_on_command_start);
	ClassDB::bind_method(D_METHOD("_on_command_end"), &CommandNode::_on_command_end);

	ClassDB::bind_method(D_METHOD("add_command"), &CommandNode::add_command);
	ClassDB::bind_method(D_METHOD("remove_command"), &CommandNode::remove_command);

	ClassDB::bind_method(D_METHOD("can_process_command"), &CommandNode::can_process_command);

	ClassDB::bind_method(D_METHOD("set_command_manager_path", "command_paths"), &CommandNode::set_command_manager_path);
	ClassDB::bind_method(D_METHOD("get_command_manager_path"), &CommandNode::get_command_manager_path);
	ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "command_manager_path", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "CommandManager"), "set_command_manager_path", "get_command_manager_path");

	ClassDB::bind_method(D_METHOD("set_execute_once", "execute_once"), &CommandNode::set_execute_once);
	ClassDB::bind_method(D_METHOD("get_execute_once"), &CommandNode::get_execute_once);
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "execute_once"), "set_execute_once", "get_execute_once");
}

void CommandNode::_on_command_start() {
}

void CommandNode::_on_command_end() {
}

void CommandNode::_execute(Object *commanded_object, float delta_time) {
}

String CommandNode::get_configuration_warning() const {
	if (_manager == NULL) {
		return String("No Command Manager found!");
	}

	return Node::get_configuration_warning();
}

void CommandNode::add_command() {
	_executed = false;
	call_multilevel("_on_command_start");
	if (_manager != NULL) {
		_manager->add_listener(this, EXECUTE_COMMAND_NAME);
	} else {
		print_error("Tried to add to a command manager which doesn't exist!");
	}
}

void CommandNode::remove_command() {
	if (_manager != NULL) {
		_manager->remove_listener(this, EXECUTE_COMMAND_NAME);
	} else {
		print_error("Tried to add to a command manager which doesn't exist!");
	}
	call_multilevel("_on_command_end");
}

void CommandNode::execute_command(Object *commanded_object, float delta_time) {
	if (execute_once && _executed) {
		return;
	}
	call_multilevel("_execute", commanded_object, delta_time);
	_executed = true;
	if (execute_once) {
		remove_command();
	}
}

bool CommandNode::can_process_command() const {
	return true;
}

void CommandNode::set_command_manager_path(const NodePath &new_path) {
	command_manager_path = new_path;
	if (has_node(command_manager_path)) {
		_manager = cast_to<CommandManager>(get_node(command_manager_path));
	}
}

NodePath CommandNode::get_command_manager_path() const {
	return command_manager_path;
}

void CommandNode::set_execute_once(const bool &can_execute_once) {
	execute_once = can_execute_once;
}

bool CommandNode::get_execute_once() const {
	return execute_once;
}
