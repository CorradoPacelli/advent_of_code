#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>

//15851356540 too low
//5361735137219

// 2 star
//1549697693318169 too much
//11685385052098 too low
//11744693538946

using namespace std;

//returns the new offset if succeed 0 uf fails
int read_one_problem(int offset, std::vector<string>& lines, std::vector<int>& operands, char& op);

int main() {
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    vector<string> lines;
    string buffer{};

    while (getline(file, buffer)) {
        lines.push_back(std::move(buffer));
    }

    long long unsigned int result{0};


    vector<int> operands;
    char op{};
    int offset = read_one_problem(0, lines, operands, op);

    while (offset) {
        long long unsigned int partial_result{0};
        // compute partial result
        for (auto o : operands){
            if (op == '+') {
                partial_result += o;
            } else if (op == '*') {
                if (partial_result == 0) {
                    partial_result = o;
                } else {
                    partial_result *= o;
                }
            } 
        }

        cout << "Patial result: " << partial_result << endl;
        result += partial_result;

        offset = read_one_problem( offset, lines, operands, op);

    }

    cout << "--The final result is: " << result << endl;
}

int read_one_problem(int offset, std::vector<string>& lines, std::vector<int>& operands, char& op){
    bool none_read_anything{true};
    operands.clear();
    int internal_operand_offselt{0};

    while (none_read_anything) {
        none_read_anything = false;
        for (int line{0}; line < lines.size(); ++line) {

            if (lines.at(0).size() <= offset) {
                if (operands.size() == 0 ) return 0;
                return offset;
            }
            
            char char_read = lines[line].at(offset);

            if (char_read != ' '){
                none_read_anything = true;

                if (char_read == '+' || char_read == '*'){
                    op = char_read;
                }

                if (isdigit(char_read)) {
                    if (operands.size() < internal_operand_offselt + 1) {
                        operands.push_back(char_read - '0');
                    } else {
                        operands[internal_operand_offselt] *= 10;
                        operands[internal_operand_offselt] += char_read - '0';
                    }
                }
            } 
        }
        ++offset;
        ++internal_operand_offselt;
    }

    return offset;
}

// first star :)
/*
int main() {
    ifstream file("input.txt");

    if (!file) {
        cout << "Unable to open file";
        return 1;
    }

    string first_line{};
    string second_line{};
    string third_line{};
    string fourth_line{};
    string operator_line{};
    long long unsigned int result{0};
    long long unsigned int partial_result{0};

    getline(file, first_line);
    getline(file, second_line);
    getline(file, third_line);
    getline(file, fourth_line);
    getline(file, operator_line);

    istringstream ss_first(std::move(first_line));
    istringstream ss_second(std::move(second_line));
    istringstream ss_third(std::move(third_line));
    istringstream ss_fourth(std::move(fourth_line));
    istringstream ss_op(std::move(operator_line));

    while (true) {

        long long unsigned int first_operand{0};
        long long unsigned int second_operand{0};
        long long unsigned int third_operand{0};
        long long unsigned int fourth_operand{0};
        string op{};

        if (!(ss_first >> first_operand)) {
            break; // Stop loop when we run out of numbers to parse
        }
        ss_second >> second_operand;
        ss_third >> third_operand;
        ss_fourth >> fourth_operand;
        ss_op >> op;

        if (op == "+") {
            partial_result = first_operand + second_operand + third_operand + fourth_operand;

        } else if (op == "*") {
            partial_result = first_operand * second_operand * third_operand * fourth_operand;
    

        } else {
            throw invalid_argument("Invalid operator");
        }
        cout << "The partial result is: " << partial_result << endl;
        result += partial_result;

    }

    cout << "--The final result is: " << result << endl;
}*/