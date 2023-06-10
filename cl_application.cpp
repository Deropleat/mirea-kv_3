#include "cl_application.h"

cl_application::cl_application(cl_application* p_head_object, std::string s_object_name) : cl_base(p_head_object)
{
}

void cl_application::bild_tree_objects()
{
	int id;
	std::string head, sub;

	std::cin >> head;
	change_object_name(head);
	while (true)
	{
		std::cin >> head;
		if (head == "endtree") break;

		std::cin >> sub >> id;
		if (get_object_by_coordinate(head))
		{
			if (get_object_by_coordinate(head)->get_sub_object_by_name(sub))
			{
				std::cout << head << "     Dubbing the names of subordinate objects" << std::endl;
				continue;
			}

			if (id == 2) new cl_base_2(get_object_by_coordinate(head), sub);
			else if (id == 3) new cl_base_3(get_object_by_coordinate(head), sub);
			else if (id == 4) new cl_base_4(get_object_by_coordinate(head), sub);
			else if (id == 5) new cl_base_5(get_object_by_coordinate(head), sub);
			else if (id == 6) new cl_base_6(get_object_by_coordinate(head), sub);
		}
		else
		{
			change_object_name(get_object_name() + "_" + head + "_broken");
			return;
		}
	}
}

int cl_application::exec_app()
{
	if (get_object_name().find("_broken") != std::string::npos)
	{
		std::string origin_object_name = get_object_name().substr(0, get_object_name().find_last_of("_broken"));
		std::string error_coordinate = origin_object_name.substr(origin_object_name.find_last_of('_') + 1);
		origin_object_name = origin_object_name.substr(0, origin_object_name.find_last_of('_'));

		change_object_name(origin_object_name);
		std::cout << "Object tree";
		show_object_tree();
		std::cout << std::endl << "The head object " << error_coordinate << " is not found";
		return 1;
	}
	
	std::string command, args;
	std::vector<std::string> callback;
	cl_base* target = this, * from = nullptr;

	std::getline(std::cin, command, '\n');
	while (true)
	{
		std::getline(std::cin, command, '\n');
		
		if (command == "END")
		{
			callback.push_back("Current object hierarchy tree");
			break;
		}
		
		args = command.substr(command.find(' ') + 1);
		command = command.substr(0, command.find(' '));
		from = target->get_object_by_coordinate(args);
		if (command == "SET")
		{
			if (from)
			{
				target = from;
				callback.push_back("Object is set: " + target->get_object_name());
			}
			else callback.push_back("The object was not found at the specified coordinate: " + args);
		}
		else if (command == "FIND")
		{
			if (from) callback.push_back(args + "     Object name: " + from->get_object_name());
			else callback.push_back(args + "     Object is not found");
		}
		else if (command == "MOVE")
		{
			if (from)
			{
				if (target->get_branch_object_by_name(from->get_object_name()) && target->get_branch_object_by_name(from->get_object_name()) == from) callback.push_back(args + "     Redefining the head object failed");
				else
				{
					if (from->get_sub_object_by_name(target->get_object_name())) callback.push_back(args + "     Dubbing the names of subordinate objects");
					else if (target->change_head_object(from)) callback.push_back("New head object: " + target->get_head_object()->get_object_name());
				}
			}
			else callback.push_back(args + "     Head object is not found");
		}
		else if (command == "DELETE")
		{
			if (from)
			{
				cl_base* to = from->get_head_object();
				if (to)
				{
					std::string absolute = from->get_object_name();
					to->delete_sub_object_by_name(absolute);
					
					while (to->get_head_object())
					{
						absolute = to->get_object_name() + "/" + absolute;
						to = to->get_head_object();
					}
					callback.push_back("The object /" + absolute + " has been deleted");
				}
			}
		}
	}

	std::cout << "Object tree";
	show_object_tree();
	for (size_t i = 0; i < callback.size(); i++) std::cout << std::endl << callback.at(i);
	show_object_tree();

	return 0;
}