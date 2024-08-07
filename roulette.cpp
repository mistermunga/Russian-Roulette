#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits.h>

using namespace std;

int roulette(int chambers) {
    srand(time(0));
    return rand() % chambers + 1;
}

void shutdown() {
#ifdef _WIN32
    system("shutdown /s /t 0");
#elif __unix__
    system("sudo shutdown -h now");
#else
    cout << "You're running this on an alien device" << endl;
#endif
}

bool validator(int input_value, int upper_bound) {
    if (input_value <= 0) {
        cout << "Input must be at least 1." << endl;
        return false;
    }
    if (input_value > upper_bound) {
        cout << "Input must be less than or equal to the upper bound." << endl;
        return false;
    }
    return true;
}

void game_mode(int chambers) {
    int result = roulette(chambers);
    while (true) {
        cout << "Take a guess between 1 and " << chambers << ": ";
        string input;
        cin >> input;
        int guess;
        try {
            guess = stoi(input);
        } catch (invalid_argument&) {
            cout << "Please enter a numeric value." << endl;
            continue;
        }
        if (guess == result) {
            cout << "BANG! You're dead." << endl;
            shutdown();
        } else {
            cout << "Nothing happens...this time. Try again." << endl;
            cout << "Enter 'r' to redo this mode or 'm' to return to the main menu: ";
            cin >> input;
            if (input == "r") {
                result = roulette(chambers);
            } else if (input == "m") {
                return;
            } else {
                cout << "Invalid choice! Returning to the main menu." << endl;
                return;
            }
        }
    }
}

int main() {
    const int modes[] = {6, 38, 100, 2};
    while (true) {
        cout << "\nWelcome to roulette!" << endl;
        cout << "The rules are simple: pick a number in the given range. If nothing happens, you get to try again." << endl;
        cout << "Trust me, you'll know when you lose.\n" << endl;
        cout << "Choose a mode:" << endl;
        cout << "a) Russian roulette (6 slots | 16.67% chance of death)" << endl;
        cout << "b) Casino roulette (38 slots | 2.63% chance of death)" << endl;
        cout << "c) Percenter (100 slots | 1% chance of death)" << endl;
        cout << "d) Coin (2 slots | 50% chance of death)" << endl;
        cout << "e) Custom\n" << endl;
        cout << "q) Quit" << endl;

        string mode;
        cin >> mode;
        if (mode == "q") {
            cout << "You'll be back. I know it." << endl;
            break;
        }

        int chambers;
        if (mode == "e") {
            cout << "Enter number of chambers: ";
            cin >> chambers;
            if (validator(chambers, INT_MAX)) {
                game_mode(chambers);
            } else {
                cout << "That's not a valid choice!" << endl;
            }
        } else if (mode == "a" || mode == "b" || mode == "c" || mode == "d") {
            int index = mode[0] - 'a';
            chambers = modes[index];
            game_mode(chambers);
        } else {
            cout << "That's not a valid choice!" << endl;
        }
    }
    return 0;
}
