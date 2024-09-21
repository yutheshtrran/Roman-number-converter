#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <map>

using namespace std;

// Function to validate the Roman numeral
bool Validate(string str)
{
    const regex shape("^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");

    return regex_match(str, shape);
}

// Function to convert Roman numeral to integer
int convertRoman(string& str) {
    if (!Validate(str)) {
        return -1; // Invalid Roman numeral
    }

    map<char, int> romanValues;
    romanValues['I'] = 1;
    romanValues['V'] = 5;
    romanValues['X'] = 10;
    romanValues['L'] = 50;
    romanValues['C'] = 100;
    romanValues['D'] = 500;
    romanValues['M'] = 1000;

    int result = 0;
    int prevValue = 0;

    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == ' ') {
            continue; // Ignore spaces
        }

        int currentVal = romanValues[str[i]];

        if (currentVal < prevValue) {
            result -= currentVal;
        }
        else {
            result += currentVal;
        }

        prevValue = currentVal;
    }

    return result;
}

int main() {
    ifstream inputfl("roman_numbers.txt");

    if (!inputfl.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    string st1;
    ofstream outputfl("converted_numbers.txt"); // Create an output file stream

    while (getline(inputfl, st1)) {
        // Remove spaces from the input string
        st1.erase(remove_if(st1.begin(), st1.end(), ::isspace), st1.end());

        cout << st1 << " = ";
        transform(st1.begin(), st1.end(), st1.begin(), ::toupper); // Changing the string to uppercase

        int convertedValue = convertRoman(st1);

        if (convertedValue > 0) {
            if (convertedValue <= 200) {
                cout << convertedValue << "\n";
                // Write the converted value to the output file
                outputfl << st1 << " = " << convertedValue << "\n";
            }
            else {
                cout << "Higher Than 200\n";
                // Write a message to the output file
                outputfl << st1 << " = Higher Than 200\n";
            }
        }
        else {
            cout << "Error! [it is invalid Roman]\n";
            // Write an error message to the output file
            outputfl << st1 << " = Error! [it is invalid Roman]\n";
        }
    }

    inputfl.close();
    outputfl.close(); // Close the output file stream

    // Check if the output file is empty and delete it if there are no valid Roman numerals
    ifstream outputFileCheck("converted_numbers.txt");
    outputFileCheck.seekg(0, ios::end);
    if (outputFileCheck.tellg() == 0) {
        outputFileCheck.close();
        remove("converted_numbers.txt");
    }

    return 0;
}
