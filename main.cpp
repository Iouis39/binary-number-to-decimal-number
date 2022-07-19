
#include <iostream>
#include <vector>

using namespace std;

int calcPower(int base, int exp) {
    if (exp < 0) {
        return -1;
    }
    
    int result = 1;
    while(exp) {
        if(exp & 1) {
            result *= base;
        }
        exp >>= 1;
        base *= base;
    }
    
    return result;
}

int convertBinaryToDecimal(const vector<int>& input) {

    int result = 0;
    
    for (int i = 0; i < input.size(); i++) {
        int exp = input.size() - i - 1;        
        result += input[i] * calcPower(2, exp);
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
                vector<int> inputIntVec;
                transform(input.begin(), input.end(), std::back_inserter(inputIntVec),
                    [](unsigned char c) -> int { return c == '0' ? 0 : c == '1' ? 1 : throw invalid_argument("Invalid value in input string");});
                int resultInt = convertBinaryToDecimal(inputIntVec);
                cout << "Your value as decimal: " << resultInt << endl; 
            }
            catch(const invalid_argument& e ) {
                cout << e.what() << endl;
            }
        }
    } while (!input.empty());

    return 0;
}


