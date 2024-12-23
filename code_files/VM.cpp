//VM
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <stdexcept>
#include <vector>

using namespace std;

#define MEMORY_SIZE 256
#define STACK_SIZE 256

class VMachine {
private:
    double memory[MEMORY_SIZE];
    stack<double> st;

public:
    VMachine() {
        fill(begin(memory), end(memory), 0.0);
    }
    
    double getStackTop() const {
        if (st.empty()) {
            throw underflow_error("Stack is empty!");
        }
        return st.top();
    }

    void execute(const string& file_name) {
        ifstream file(file_name);

        if (!file.is_open()) {
            throw runtime_error("Failed to open file!");
        }

        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string command;
            iss >> command;

            if (command == "LOAD") {
                double value;
                iss >> value;
                LOAD(value);
            } else if (command == "WRITE") {
                int address;
                iss >> address;
                WRITE(address);
            } else if (command == "READ") {
                int address;
                iss >> address;
                READ(address);
            } else if (command == "ADD") {
                ADD();
            } else if (command == "SUB") {
                SUB();
            } else if (command == "MUL") {
                MUL();
            } else if (command == "DIV") {
                DIV();
            } else if (command == "PRINT") {
                PRINT();
            } else {
                throw runtime_error("Unknown command: " + command);
            }
        }

        file.close();
    }

    void LOAD(double value) {
        if (st.size() >= STACK_SIZE) {
            throw overflow_error("Stack overflow!");
        }
        st.push(value);
    }

    void READ(int address) {
        if (address < 0 || address >= MEMORY_SIZE) {
            throw out_of_range("Invalid memory address!");
        }
        st.push(memory[address]);
    }

    void WRITE(int address) {
        if (address < 0 || address >= MEMORY_SIZE) {
            throw out_of_range("Invalid memory address!");
        }

        if (st.empty()) {
            throw underflow_error("Stack underflow!");
        }

        memory[address] = st.top();
        st.pop();
    }

    void ADD() {
        double a, b;

        if (st.size() < 2) throw underflow_error("Not enough elements on stack for ADD");

        a = st.top();
        st.pop();
        b = st.top();
        st.pop();
        st.push(b + a);
    }

    void SUB() {
        double a, b;

        if (st.size() < 2) throw underflow_error("Not enough elements on stack for SUB");

        a = st.top();
        st.pop();
        b = st.top();
        st.pop();
        st.push(b - a);
    }

    void MUL() {
        double a, b;

        if (st.size() < 2) throw underflow_error("Not enough elements on stack for MUL");

        a = st.top();
        st.pop();
        b = st.top();
        st.pop();
        st.push(b * a);
    }

    void DIV() {
        double a, b;

        if (st.size() < 2) throw underflow_error("Not enough elements on stack for DIV");
        
        a = st.top();
        st.pop();
        b = st.top();
        st.pop();
        
        if (a == 0) {
            throw domain_error("Division by zero!");
        }
        
        st.push(b / a);
    }

    void PRINT() {
        if (st.empty()) {
            throw underflow_error("Stack is empty!");
        }
        cout << "Result: " << st.top() << endl;
    }
};

int main() {
    VMachine vm;
    
    try {
        vm.execute("program.vm");
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
