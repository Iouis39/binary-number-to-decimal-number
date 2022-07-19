
#include <iostream>
#include <vector>

using namespace std;

int convertBinStrToInt(const string& input) {
    int result = 0;
    int i = 0;
    char c;
    // loop through chars in the input string
    while ((c=input[i++]) != 0) {
        // move existing bits 1 to left
        result <<= 1;
        if (c == '1') {
            // if the current char is "1" make the most right bit 1
            result |= 1;
        } else if (c != '0') {
            // otherwise it has to be a "0" or return error
            throw invalid_argument("Invalid value in input string");
        }
    }
    return result;
}

int main() {    
 
    string input;
    do {
        cout << "Please enter a binary value: ";
        std::getline(cin, input);
        if (!input.empty()) {
            try {
                int resultInt = convertBinStrToInt(input);
                cout << "Your value as decimal: " << resultInt << endl; 
            }
            catch(const invalid_argument& e ) {
                cout << e.what() << endl;
            }
        }
    } while (!input.empty());

    return 0;
}
