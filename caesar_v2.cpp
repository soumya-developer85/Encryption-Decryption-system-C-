#include <iostream>
#include <string>
#include <limits>
using namespace std;

int safeMod(int value, int mod) {
    return ((value % mod) + mod) % mod;
}

int getValidShift() {
    int shift;
    while (true) {
        cout << "Enter shift value (integer): ";
        if (cin >> shift) {
            int effective = safeMod(shift, 26);
            if (effective == 0) {
                cout << "  Warning: Shift of " << shift
                     << " is equivalent to 0. No encryption will be applied.\n";
            } else if (shift != effective) {
                cout << "  Note: Shift " << shift
                     << " is equivalent to shift " << effective << ".\n";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return shift;
        } else {
            cout << "  Invalid input. Please enter a whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string getValidMode() {
    string mode;
    while (true) {
        cout << "Mode (e = encrypt, d = decrypt, ex = exit): ";
        cin >> mode;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (mode == "e" || mode == "E")  return "e";
        if (mode == "d" || mode == "D")  return "d";
        if (mode == "ex" || mode == "EX" || mode == "Ex") return "ex";

        cout << "  Invalid mode. Please enter 'e', 'd', or 'ex'.\n";
    }
}

string applyCipher(const string& text, int shift) {
    string result = text;
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = safeMod(result[i] - 'A' + shift, 26) + 'A';
        else if (result[i] >= 'a' && result[i] <= 'z')
            result[i] = safeMod(result[i] - 'a' + shift, 26) + 'a';
        // spaces, digits, punctuation unchanged
    }
    return result;
}

int main() {
    cout << "=============================\n";
    cout << "      Caesar Cipher Tool     \n";
    cout << "=============================\n\n";

    while (true) {
        string mode = getValidMode();

        // --- EXIT ---
        if (mode == "ex") {
            cout << "\nExit Successful!\n";
            break;
        }

        int shift = getValidShift();

        cout << "Enter text: ";
        string text;
        getline(cin, text);

        int effectiveShift = safeMod(shift, 26);

        // --- DECRYPT --- reverse the shift
        if (mode == "d")
            effectiveShift = safeMod(26 - effectiveShift, 26);

        string result = applyCipher(text, effectiveShift);

        cout << "\nResult: " << result << "\n";
        cout << "-----------------------------\n\n";
        // loops back so user can encrypt/decrypt again or exit
    }

    return 0;
}
