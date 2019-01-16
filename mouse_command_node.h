#ifndef MOUSE_COMMAND_NODE
#define  MOUSE_COMMAND_NODE

#include "command_node.h"

class MouseCommandNode : public CommandNode
{
	GDCLASS(MouseCommandNode, CommandNode);

public:
	Vector2 input;

public:
	MouseCommandNode();
	
protected:
	virtual void _command_ready() override;
	void _input(Ref<InputEvent> p_event);
	static void _bind_methods();

public:
	Vector2 get_input() const;
	void consume_input();
};
#endif
