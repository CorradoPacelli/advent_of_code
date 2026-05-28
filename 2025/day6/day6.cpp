#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>

//15851356540 too low
//5361735137219

// 2 star
//1549697693318169 too much
//11685385052098 too low

using namespace std;

// return 0 if succeed, 1 if it fails
int read_right_to_left_om_colums( istringstream& s1,  istringstream& s2,  istringstream& s3,  istringstream& s4, long long unsigned int* operand);

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
        ss_op >> op;

        if ((op != "+") && (op != "*")) {
            throw invalid_argument("Invalid operator");
        }

        if(read_right_to_left_om_colums(ss_first, ss_second, ss_third, ss_fourth, &first_operand) == 1){
            break;
        }
        cout << "first operand " << first_operand << endl;
        partial_result = first_operand;

        int result_function = read_right_to_left_om_colums(ss_first, ss_second, ss_third, ss_fourth, &second_operand);
        if(result_function == 1){
            break;
        } else if (result_function == 0){
            if (op == "+") {
                partial_result += second_operand;
            } else{
                partial_result *= second_operand;
            }
        } else {
            cout << "The partial result is: " << partial_result << endl;
            result += partial_result;
            cout << "--The final result is: " << result << endl;
            partial_result = 0;
            continue;
        }
        cout << "second operand " << second_operand << endl;

        result_function = read_right_to_left_om_colums(ss_first, ss_second, ss_third, ss_fourth, &third_operand);
        if(result_function == 1){
            break;
        } else if (result_function == 0){
            if (op == "+") {
                partial_result += third_operand;
            } else{
                partial_result *= third_operand;
            }
        } else {
            cout << "The partial result is: " << partial_result << endl;
            result += partial_result;
            cout << "--The final result is: " << result << endl;
            partial_result = 0;
            continue;
        }
        cout << "third operand " << third_operand << endl;

        result_function = read_right_to_left_om_colums(ss_first, ss_second, ss_third, ss_fourth, &fourth_operand);
        if(result_function == 1){
            break;
        } else if (result_function == 0){
            if (op == "+") {
                partial_result += fourth_operand;
            } else{
                partial_result *= fourth_operand;
            }
        } else {
            cout << "The partial result is: " << partial_result << endl;
            result += partial_result;
            cout << "--The final result is: " << result << endl;
            partial_result = 0;
            continue;
        }
        cout << "forth operand " << fourth_operand << endl;

        ss_first.get();
        ss_second.get();
        ss_third.get();
        ss_fourth.get();

        cout << "The partial result is: " << partial_result << endl;
        result += partial_result;
        cout << "--The final result is: " << result << endl;
        partial_result = 0;
    }

    cout << "--The final result is: " << result << endl;
}

int read_right_to_left_om_colums(istringstream& s1, istringstream& s2, istringstream& s3, istringstream& s4, long long unsigned int* operand){

    bool changed = false;
    char first_char = s1.get();
    if (first_char == EOF) {
        return 1;
    } else if (first_char != ' ') {
        changed = true;
        *operand = first_char - '0';
    }

    char second_char = s2.get();
    if (second_char == EOF) {
        return 1;
    } else if (second_char != ' ') {
        changed = true;
        *operand *= 10;
        *operand += (second_char - '0');
    }

    char third_char = s3.get();
    if (third_char == EOF) {
        return 1;
    } else if (third_char != ' ') {
        changed = true;
        *operand *= 10;
        *operand += (third_char - '0');
    }

    char forth_char = s4.get();
    if (forth_char == EOF) {
        return 1;
    } else if (forth_char != ' ') {
        changed = true;
        *operand *= 10;
        *operand += (forth_char - '0');
    }

    if (!changed){
        return -1;
    }

    return 0;
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