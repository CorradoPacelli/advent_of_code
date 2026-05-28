#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>

//15851356540 too low
//5361735137219

using namespace std;

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

    getline (file, first_line);
    getline (file, second_line);
    getline (file, third_line);
    getline (file, fourth_line);
    getline (file, operator_line);

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
}