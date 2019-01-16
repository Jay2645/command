#include "mouse_command_node.h"
#include "core/os/input.h"
#include "core/os/input_event.h"
#include "scene/main/scene_tree.h"
#include "core/os/os.h"

MouseCommandNode::MouseCommandNode() {
	set_process_input(true);
}

void MouseCommandNode::_command_ready() {
	CommandNode::_command_ready();
	add_command();
}

void MouseCommandNode::_input(Ref<InputEvent> p_event) {
	if (!can_process_command()) {
		return;
	}
	Ref<InputEventMouseMotion> _mouse_event = p_event;
	if (_mouse_event.is_null()) {
		return;
	}
	input = _mouse_event->get_relative();
	SceneTree::get_singleton()->set_input_as_handled();
}

void MouseCommandNode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_input"), &MouseCommandNode::_input);
	ClassDB::bind_method(D_METHOD("get_input"), &MouseCommandNode::get_input);
	ClassDB::bind_method(D_METHOD("consume_input"), &MouseCommandNode::consume_input);
}

Vector2 MouseCommandNode::get_input() const {
	return input;
}

void MouseCommandNode::consume_input() {
	input.x = 0.0f;
	input.y = 0.0f;
}
