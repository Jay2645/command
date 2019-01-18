#ifndef COMMAND_NODE_H
#define COMMAND_NODE_H

#include "scene/main/node.h"

class CommandManager;

class CommandNode : public Node {
	GDCLASS(CommandNode, Node);

protected:
	CommandManager *_manager;
	const StringName EXECUTE_COMMAND_NAME = StringName("execute_command");
	bool _executed;

public:
	bool execute_once;
	NodePath command_manager_path;

public:
	CommandNode();

protected:
	virtual void _command_ready();
	static void _bind_methods();
	virtual void _on_command_start();
	virtual void _on_command_end();
	virtual void _execute(Object *commanded_object, float delta_time);

public:
	virtual String get_configuration_warning() const override;

	void add_command();
	void remove_command();
	void execute_command(Object *commanded_object, float delta_time);

	virtual bool can_process_command() const;

	void set_command_manager_path(const NodePath& new_path);
	NodePath get_command_manager_path() const;

	void set_execute_once(const bool &can_execute_once);
	bool get_execute_once() const;
};
#endif
