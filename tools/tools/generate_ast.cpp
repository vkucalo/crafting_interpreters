#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

struct generate_ast {

	void define_type(std::ofstream& outfile, const std::string& base_name, const std::string& class_name, const std::string& field_list) {
		outfile << " struct " + class_name + " { " << std::endl;
		std::stringstream ss(field_list);
		std::vector<std::string> fields;
		std::string field;
		while (std::getline(ss, field, ',')) {
			fields.emplace_back(field);
			outfile << "	" + field + ";" << std::endl;
		}
		outfile << "	" + class_name + "(" + field_list + ") {" << std::endl;
		for (auto& field : fields) {
			std::string rval = field.substr(field.find(' '));
			outfile << "		" + std::string("this->") + rval + " = " + rval + ";" << std::endl;
		}
		outfile << "	}" << std::endl;
		outfile << "}" << std::endl;

	}

	void define_ast(const std::string& output_dir, const std::string& base_name, std::vector<std::string>& types) {
		std::string filename = output_dir + '/' + base_name + ".h";
		std::ofstream outfile(filename);

		outfile << "#pragma once" << std::endl;
		outfile << "#include ""token.h""" << std::endl;
		outfile << "struct " + base_name + " {" << std::endl;

		for (auto& type : types) {
			std::string class_name = type.substr(0, type.find(":"));
			std::string fields = type.substr(type.find(":") + 1);
			define_type(outfile, base_name, class_name, fields);

		}
		outfile << "}";
		outfile.close();

	}
};


int main() {
	generate_ast ga;
	std::vector<std::string> types{ "binary:expr left,token oper,expr right",
									"grouping:expr expression",
									"literal:std::string value",
									"unary:token oper,expr right" };
	ga.define_ast("D:/dev/crafting_interpreters/tools", "expr", types);
	
	return 0;
}