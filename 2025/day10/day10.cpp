#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

// A simple utility function to trim leading and trailing whitespace from a string.
std::string trim(const std::string& str) {
    const std::string WHITESPACE = " \n\r\t\f\v";
    size_t first = str.find_first_not_of(WHITESPACE);
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(WHITESPACE);
    return str.substr(first, (last - first + 1));
}

std::set<int> get_target(const std::string& part1){
    std::set<int> target;
    for (size_t pos = part1.find('#', 0); pos != std::string::npos; pos = part1.find('#', pos + 1)) {
        target.insert(static_cast<int>(pos));
    }
    return target;
}

std::set<std::set<int>> get_buttons(const std::string& part2) {
    std::set<std::set<int>> buttons;
    for (size_t pos_of_open_bracket = part2.find('(', 0); pos_of_open_bracket != std::string::npos; pos_of_open_bracket = part2.find('(', pos_of_open_bracket + 1)) {

        size_t pos_of_closing_bracket = part2.find(')', pos_of_open_bracket);
        std::string button_part = part2.substr(pos_of_open_bracket + 1, pos_of_closing_bracket - pos_of_open_bracket - 1);

        std::set<int> button;
        size_t pos_of_comma = button_part.find(',', 0);
        size_t initial_pos = 0;
        for (; pos_of_comma != std::string::npos; pos_of_comma = button_part.find(',', pos_of_comma + 1)){
            button.insert(std::stoi(button_part.substr(initial_pos, pos_of_comma - initial_pos)));
            initial_pos = pos_of_comma + 1;
        }
        button.insert(std::stoi(button_part.substr(initial_pos, button_part.length() - initial_pos)));
        buttons.insert(button);
    }
    return buttons;
}


int main() {
    // The user mentioned rinput.txt, but other files use input.txt.
    // Let's stick to input.txt for consistency, but it can be changed.
    std::ifstream input_file("input.txt");
    if (!input_file) {
        std::cerr << "Unable to open file input.txt" << std::endl;
        return 1;
    }

    std::string line;
    int line_number = 0;

    // Process the file line by line
    while (std::getline(input_file, line)) {
        line_number++;
        
        // Find the positions of the delimiters
        size_t start_bracket = line.find('[');
        size_t end_bracket = line.find(']');
        size_t start_curly = line.find('{');

        // Check if all delimiters are present
        if (start_bracket == std::string::npos || end_bracket == std::string::npos || start_curly == std::string::npos) {
            std::cerr << "Warning: Malformed line " << line_number << ": " << line << std::endl;
            continue; // Skip to the next line
        }

        // Extract the part within the square brackets []
        std::string part1 = line.substr(start_bracket + 1, end_bracket - start_bracket - 1);

        // Extract the part between ']' and '{'
        std::string part2_with_whitespace = line.substr(end_bracket + 1, start_curly - end_bracket - 1);
        std::string part2 = trim(part2_with_whitespace);

        // The part inside {} is ignored as requested.

        // Output the extracted parts
        std::cout << "Line " << line_number << ":" << std::endl;
        std::cout << "  Part 1: " << part1 << std::endl;
        std::cout << "  Part 2: " << part2 << std::endl;

        std::set<int> target = get_target(part1);
        std::cout << "Target: ";
        for (auto it = target.begin(); it != target.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        std::set<std::set<int>> buttons = get_buttons(part2);
        std::cout << "Buttons: " << std::endl;
        for (auto it = buttons.begin(); it != buttons.end(); ++it) {
            std::cout << " { ";
            for (auto it2 = it->begin(); it2 != it->end(); ++it2) {
                std::cout << *it2 << " ";
            }
            std::cout << "}" << std::endl;
        }

        std::cout << "------------------------" << std::endl;
    }

    return 0;
}