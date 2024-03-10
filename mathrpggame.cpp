#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

class GameLoop {
private:
    string name;
    int health, strength, defense;

public:
    GameLoop(string charName = "", int charHealth = 0, int charStrength = 0, int charDefense = 0)
        : name(charName), health(charHealth), strength(charStrength), defense(charDefense)
    {};

    GameLoop()
        : name("DefaultName"), health(0), strength(0), defense(0)
    {}

    void setName(string charName) { this->name = charName; }
    void setHealth(int charHealth) { this->health = charHealth; }
    void setStrength(int charStrength) { this->strength = charStrength; }

    string getName() const { return name; }
    int getHealth() const { return health; }
    int getStrength() const { return strength; }
    int getDefense() const { return defense; }

    string Format() const {
        return "Name:" + name + " Health: " + to_string(health) + " Strength: " + to_string(strength) + " Defense: " + to_string(defense) + "\n";
    }

    void attack(GameLoop& target) {
        int damage = max(0, strength - target.getDefense());
        target.setHealth(target.getHealth() - damage);
        cout << name << " attacks " << target.getName() << " for " << damage << " damage!" << endl;
    }
};

void multiply_test(int& strength) {
    srand(time(0));
    int total = 3;
    int total_right = 0;
    int total_wrong = 0;
    int guess = 0;
    auto start_time = chrono::high_resolution_clock::now();

    while (guess < total && total_wrong < 2) {
        int a = (rand() % 21) - 10;
        int b = (rand() % 21) - 10;
        int answer;
        cout << a << " x " << b << "\n";
        cin >> answer;
        guess++;
        if (answer == (a * b)) {
            cout << "Correct! \n";
            total_right++;
        } else {
            cout << "Wrong. \n";
            total_wrong++;
        }

        cout << "\nAverage: " << static_cast<double>(total_right) / total;
        cout << "\nTotal Right: " << total_right;
        cout << "\nTotal Wrong: " << total_wrong;
        cout << "\n";
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    cout << "Time taken: " << duration.count() << " seconds" << endl;

    if (duration.count() > (total * 3)) {
        cout << "Too slow.";
    } else if (total_wrong > 0) {
        cout << "\nYou messed up " << total_wrong << " times";
    } else if (total_wrong == 0 && duration.count() <= (total * 3)) {
        cout << "Perfect! Strength boosted by!\n";
        strength = static_cast<int>(strength * 1.05);  // Boost character's strength
    } else {
        cout << "\nGood job!";
    }
}

void find_derivative(int& health) {
    int a, b, c, power;
    srand(time(0));
    a = rand() % 21 - 10;
    b = rand() % 21 - 10;
    c = rand() % 21 - 10;
    power = rand() % 10;

    int derivative_a = (power * a);
    int derivative_b = (power* b);
    int constant = c;

    int guess_a;
    int guess_b;
    int guess_c;

    cout << "Find derivatives: \n" << a << "x^" << power << "+ " << b << "x^" << power <<"+" << c;
    cout << "\n1st term: ";
    cin >> guess_a;
    if (guess_a == derivative_a) {
        cout << "Correct!";
    } else {
        cout << "Incorrect";
    }

    cout << "\n2nd term: ";
    cin >> guess_b;
    if (guess_b == derivative_b) {
        cout << "Correct!";
    } else {
        cout << "Incorrect.";
    }

    cout << "\nConstant: ";
    cin >> guess_c;
    if (guess_c == constant) {
        cout << "Correct!";
    } else {
        cout << "Incorrect.";
    }

    if (guess_a == derivative_a && guess_b == derivative_b && guess_c == constant) {
        cout << "\nAll answers correct! Health boosted!\n";
        health = static_cast<int>(health * 1.10);  // Update warrior's health
        cout << "Health Boosted by 10%";
    } else {
        cout << "\nPartial credit.\n";
    }

   
}

ostream& operator<<(ostream& os, const GameLoop& person) {
    os << person.Format();
    return os;
}

void display_data() {
    int choice;
    int special_choice;

    GameLoop warrior("Warrior", 100, 20, 10);
    GameLoop enemy("Enemy", 150, 15, 5);

    while (warrior.getHealth() > 0 && enemy.getHealth() > 0) {
        cout << warrior.Format();
        cout << enemy.Format();
        cout << "1. Normal Attack\n";
        cout << "2. Special Attack\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                warrior.attack(enemy);
                break;

            case 2:
                cout << "1. Multiple Strength \n";
                cout << "2. Derivative Health Boost \n";
                cin >> special_choice;
                switch (special_choice) {
                    case 1: {
                        int strength = warrior.getStrength();
                        multiply_test(strength);
                        warrior.setStrength(strength);
                        break;
                    }
                    case 2: {
                        int health = warrior.getHealth();
                        find_derivative(health);
                        warrior.setHealth(health);
                        break;
                    }
                }
                break;


            default:
                cout << "Invalid choice. Please choose a valid option.\n";
        }
        
    }

            if (enemy.getHealth() > 0) {
            enemy.attack(warrior);
        }

    if (warrior.getHealth() <= 0) {
        cout << "You lose. Game over.\n";
    } else {
        cout << "You win! Congratulations!\n";
    }
}

int main() {
    display_data();
    return 0;
}