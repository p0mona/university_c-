//Compiler
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <regex>

using namespace std;

class Compiler {
private:
    unordered_map<string, int> variables;
    int memory_address = 0;
    int temp_var_count = 0;

    void emit(vector<string>& instructions, const string& command) {
        instructions.push_back(command);
    }

    vector<string> tokenize(const string& expr) {
        vector<string> tokens;
        regex token_regex("([0-9]+(?:\\.[0-9]+)?)|([a-zA-Z_][a-zA-Z0-9_]*)|([+\\-*/()])");
        auto begin = sregex_iterator(expr.begin(), expr.end(), token_regex);
        auto end = sregex_iterator();

        for (auto it = begin; it != end; ++it) {
            if ((*it)[1].length() > 0) {
                tokens.push_back((*it)[1]);
            } else if ((*it)[2].length() > 0) {
                tokens.push_back((*it)[2]);
            } else if ((*it)[3].length() > 0) {
                tokens.push_back((*it)[3]);
            }
        }

        return tokens;
    }

    string generate_temp_var() {
        return "_temp" + to_string(temp_var_count++);
    }

    void process_expression(const string& expr, vector<string>& instructions) {
        regex number_regex("(-?\\d*\\.?\\d+)");
        regex variable_regex("[a-zA-Z_][a-zA-Z0-9_]*");
        regex operator_regex("[+\\-*/()]");

        istringstream iss(expr);
        string token;
        stack<string> operators;
        vector<string> output;

        auto precedence = [](const string& op) {
            if (op == "+" || op == "-") return 1;
            if (op == "*" || op == "/") return 2;
            return 0;
        };

        vector<string> tokens = tokenize(expr);
        
        for (const auto& token : tokens) {
            if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                output.push_back(token);
            }
            else if (variables.find(token) != variables.end()) {
                output.push_back("READ " + to_string(variables[token]));
            }
            else if (token == "(") {
                operators.push(token);
            }
            else if (token == ")") {
                while (!operators.empty() && operators.top() != "(") {
                    output.push_back(operators.top());
                    operators.pop();
                }
                if (!operators.empty() && operators.top() == "(") {
                    operators.pop();
                } else {
                    throw runtime_error("Mismatched parentheses");
                }
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/") {
                while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                    output.push_back(operators.top());
                    operators.pop();
                }
                operators.push(token);
            }
            else {
                throw runtime_error("Unknown token in expression: " + token);
            }
        }

        while (!operators.empty()) {
            output.push_back(operators.top());
            operators.pop();
        }

        for (const auto& item : output) {
            if (item.find("READ") == 0) {
                emit(instructions, item);
            } else if (isdigit(item[0]) || (item[0] == '-' && isdigit(item[1]))) {
                emit(instructions, "LOAD " + item);
            } else if (item == "+") {
                emit(instructions, "ADD");
            } else if (item == "-") {
                emit(instructions, "SUB");
            } else if (item == "*") {
                emit(instructions, "MUL");
            } else if (item == "/") {
                emit(instructions, "DIV");
            }
        }
    }

public:
    void compile(const string& input_file, const string& output_file) {
        ifstream input(input_file);

        if (!input.is_open()) {
            throw runtime_error("Failed to open input file!");
        }

        vector<string> instructions;
        string line;
        string last_variable;

        while (getline(input, line)) {
            size_t equal_pos = line.find('=');

            if (equal_pos == string::npos) {
                string temp_var = generate_temp_var();
                string expr = line;
                expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
                process_expression(expr, instructions);
                emit(instructions, "WRITE " + to_string(memory_address));
                variables[temp_var] = memory_address++;
                last_variable = temp_var;
            } else {
                string var = line.substr(0, equal_pos);
                string expr = line.substr(equal_pos + 1);
                var.erase(remove(var.begin(), var.end(), ' '), var.end());
                expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
                
                if (variables.find(var) == variables.end()) {
                    variables[var] = memory_address++;
                }
                process_expression(expr, instructions);

                emit(instructions, "WRITE " + to_string(variables[var]));
                last_variable = var;
            }
        }

        emit(instructions, "READ " + to_string(variables[last_variable]));
        emit(instructions, "PRINT");

        input.close();

        ofstream output(output_file);
        if (!output.is_open()) {
            throw runtime_error("Failed to open output file!");
        }

        for (const auto& instr : instructions) {
            output << instr << endl;
        }

        output.close();
    }
};

int main() {
    Compiler compiler;
    try {
        compiler.compile("program.txt", "program.vm");
        cout << "Compilation successful. Generated program.vm" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
