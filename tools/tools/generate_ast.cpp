#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

struct generate_ast {

	void define_type(std::ofstream& outfile, const std::string& base_name, const std::string& class_name, const std::string& field_list) {
		outfile << "template <typename R>" << std::endl;
		outfile << " struct " + class_name + " : expr<R> { " << std::endl;
		std::stringstream ss(field_list);
		std::vector<std::string> fields;
		std::string field;
		while (std::getline(ss, field, ',')) {
			fields.emplace_back(field);
			outfile << "	" + field + ";" << std::endl;
		}
		outfile << "\n\t" + class_name + "(" + field_list + ") {" << std::endl;
		for (auto& field : fields) {
			std::string rval = field.substr(field.find(' '));
			outfile << "		" + std::string("this->") + rval + " = " + rval + ";" << std::endl;
		}
		outfile << "	} \n" << std::endl;
		outfile << "	virtual R accept(expr_visitor& visitor) {" << std::endl;
		outfile << "		return visitor.visit(this);" << std::endl;
		outfile << "	}" << std::endl;
		outfile << "};\n" << std::endl;

	}

	void define_ast(const std::string& output_dir, const std::string& base_name, std::vector<std::string>& types) {
		std::string filename = output_dir + '/' + base_name + ".h";
		std::ofstream outfile(filename);

		outfile << "#pragma once" << std::endl;
		outfile << "#include \"token.h\" \n" << std::endl;
		outfile << "template <typename R>" << std::endl;
		outfile << "struct " + base_name + " {" << std::endl;
		outfile << "	virtual R accept();" << std::endl;
		outfile << "};" << std::endl;
		
		for (auto& type : types) {
			std::string class_name = type.substr(0, type.find(":"));
			std::string fields = type.substr(type.find(":") + 1);
			define_type(outfile, base_name, class_name, fields);

		}
		outfile.close();

	}
};

int main() {
	generate_ast ga;
	std::vector<std::string> types{ "binary:expr<R> left,token oper,expr<R> right",
									"grouping:expr<R> expression",
									"literal:std::string value",
									"unary:token oper,expr<R> right" };
	ga.define_ast("D:/dev/crafting_interpreters", "expr", types);
	
	return 0;
}