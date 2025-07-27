#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <iomanip>
using namespace std;

#define MAX_MEMBERS 100

class Person
{
public:
    string name;
    int age;
    string gender;
    virtual void inputdetails() = 0;
    virtual void displaydetails() = 0;
};

class Member : public Person
{
private:
    string memberID;
    string membershipType;
    float feePaid;
    string assignedTrainer;
    string dietPlan;
    string fingerprint;
    string faceID;
    string feedback;

    void assignTrainer(float fee)
    {
        if (fee >= 1000)
        {
            assignedTrainer = "Premium Trainer";
            dietPlan = "High Protein, Low Carb";
        }
        else if (fee >= 500)
        {
            assignedTrainer = "Basic Trainer";
            dietPlan = "Balanced Diet";
        }
        else
        {
            assignedTrainer = "No Trainer Assigned";
            dietPlan = "General Health Tips";
        }
    }

public:
    void inputdetails() override
    {
        cout << "\nEnter Member Details:\n";
        cout << "Name: ";
        cin >> ws;
        getline(cin, name);
        cout << "Age: ";
        cin >> age;

        if (age < 16)
        {
            cout << "Sorry, members below 16 years are not allowed in the gym.\n";
            return;
        }

        cout << "Gender: ";
        cin >> gender;
        cout << "Member ID: ";
        cin >> memberID;
        cout << "Membership Type (Monthly/Annual): ";
        cin >> membershipType;
        cout << "Fee Paid: ";
        cin >> feePaid;

        cout << "Set Fingerprint Code (e.g. F1234): ";
        cin >> fingerprint;
        cout << "Set Face ID Code (e.g. FACE789): ";
        cin >> faceID;

        assignTrainer(feePaid);
        cout << " Trainer Assigned: " << assignedTrainer << endl;
        cout << " Diet Plan: " << dietPlan << endl;
    }

    void displaydetails() override
    {
        cout << "\n----- Member Info -----\n";
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Member ID: " << memberID << endl;
        cout << "Membership Type: " << membershipType << endl;
        cout << "Fee Paid: " << feePaid << endl;
        cout << "Assigned Trainer: " << assignedTrainer << endl;
        cout << "Diet Plan: " << dietPlan << endl;
    }

    bool authenticate()
    {
        string enteredFP, enteredFace;
        cout << "Enter Fingerprint Code: ";
        cin >> enteredFP;
        cout << "Enter Face ID Code: ";
        cin >> enteredFace;
        return (enteredFP == fingerprint && enteredFace == faceID);
    }

    void markAttendance()
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        cout << "\n Attendance marked for " << name << " on " << dt << endl;
    }

    void updateDiet()
    {
        cout << "Enter new diet plan: ";
        cin >> ws;
        getline(cin, dietPlan);
        cout << "Diet plan updated successfully.\n";
    }

    void giveFeedback()
    {
        cout << "Enter your feedback: ";
        cin >> ws;
        getline(cin, feedback);
        cout << "Thank you for your feedback!\n";
    }

    string getID()
    {
        return memberID;
    }
};

class GymSystem : public Person
{
private:
    Member members[MAX_MEMBERS];
    int memberCount;

public:
    GymSystem()
    {
        memberCount = 0;
    }

    void inputdetails() override {}
    void displaydetails() override {}

    void registerMember()
    {
        if (memberCount < MAX_MEMBERS)
        {
            members[memberCount].inputdetails();

            if (members[memberCount].name != "")
            {
                memberCount++;
            }
        }
        else
        {
            cout << " Maximum members reached!\n";
        }
    }

    void showAllMembers()
    {
        if (memberCount == 0)
        {
            cout << "No members found.\n";
            return;
        }
        for (int i = 0; i < memberCount; i++)
        {
            members[i].displaydetails();
        }
    }

    void searchMemberByID()
    {
        string id;
        cout << "Enter Member ID to search: ";
        cin >> id;
        bool found = false;
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].getID() == id)
            {
                members[i].displaydetails();
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << " Member not found.\n";
        }
    }

    void memberLogin()
    {
        string id;
        cout << "Enter Member ID to Login: ";
        cin >> id;
        bool found = false;
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].getID() == id)
            {
                if (members[i].authenticate())
                {
                    cout << " Authentication successful.\n";
                    members[i].displaydetails();
                }
                else
                {
                    cout << " Authentication failed. Access denied.\n";
                }
                found = true;
                break;
            }
        }
        if (!found)
        {
            cout << " Member not found.\n";
        }
    }

    void markMemberAttendance()
    {
        string id;
        cout << "Enter Member ID to mark attendance: ";
        cin >> id;
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].getID() == id)
            {
                members[i].markAttendance();
                return;
            }
        }
        cout << "Member not found.\n";
    }

    void updateDietPlan()
    {
        string id;
        cout << "Enter Member ID to update diet: ";
        cin >> id;
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].getID() == id)
            {
                members[i].updateDiet();
                return;
            }
        }
        cout << " Member not found.\n";
    }

    void memberFeedback()
    {
        string id;
        cout << "Enter Member ID to give feedback: ";
        cin >> id;
        for (int i = 0; i < memberCount; i++)
        {
            if (members[i].getID() == id)
            {
                members[i].giveFeedback();
                return;
            }
        }
        cout << " Member not found.\n";
    }

    void menu()
    {
        int choice;
        do
        {
            cout << "\n====== GYM MANAGEMENT MENU ======\n";
            cout << "1. Register New Member\n";
            cout << "2. Show All Members\n";
            cout << "3. Search Member by ID\n";
            cout << "4. Member Login (Biometric)\n";
            cout << "5. Mark Attendance\n";
            cout << "6. Update Diet Plan\n";
            cout << "7. Member Feedback\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                registerMember();
                break;
            case 2:
                showAllMembers();
                break;
            case 3:
                searchMemberByID();
                break;
            case 4:
                memberLogin();
                break;
            case 5:
                markMemberAttendance();
                break;
            case 6:
                updateDietPlan();
                break;
            case 7:
                memberFeedback();
                break;
            case 0:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }

        } while (choice != 0);
    }
};

class Function
{
    int option;
    vector<int> date;

public:
    void Information()
    {
        int temp;
        int gather;
        bool alreadyBooked = false;
        cout << "Enter date (in ddmmyy): ";
        cin >> temp;

        for (int i = 0; i < date.size(); i++)
        {
            if (date[i] == temp)
            {
                alreadyBooked = true;
                break;
            }
        }

        if (alreadyBooked)
        {
            cout << "Venue already booked for this date! Please select another date to continue." << endl;
        }
        else
        {
            date.push_back(temp);
            cout << "Venue confirmed!" << endl;

            cout << "Please select the number of people attending the function: ";
            cin >> gather;

            if (gather > 0 && gather <= 250)
            {
                int price = (gather * 750) + (0.18 * gather * 750);
                cout << "Your total cost would be " << price << " inclusive of all taxes." << endl;

                cout << "Accepting payment..." << endl;
                cout << "Payment Accepted" << endl;
            }
            else if (gather > 250)
            {
                cout << "Limit exceeded. Number of people must be 250 or less." << endl;
            }
            else
            {
                cout << "Enter a valid input." << endl;
            }
        }
    }

    Function()
    {
        cout << "What kind of function are you booking the hall for?" << endl;
        cout << "Enter 1 for Casual meetup" << endl;
        cout << "Enter 2 for Birthday party" << endl;
        cout << "Enter 3 for Wedding related function" << endl;
        cin >> option;
        if (option == 1)
        {
            Information();
        }
        else if (option == 2)
        {
            Information();
            cout << "Congratulations, you have unlocked a free cake! This cake will be delivered to you on the date of the function." << endl;
        }
        else if (option == 3)
        {
            Information();
        }
        else
        {
            cout << "Invalid option selected." << endl;
        }
    }
};

class SportComplex
{
    int option;
    int temp;

public:
    SportComplex()
    {
        cout << "Sports available: \n"
             << "1. Badminton\n"
             << "2. Table Tennis\n"
             << "3. Billiards\n"
             << "4. Swimming\n"
             << "5. Net Cricket\n";
        cout << "Which sport are you willing to play (select option): ";
        cin >> option;

        if (option == 1 || option == 2 || option == 5)
        {
            cout << "Do you need equipment? If yes press 1 else press 2: ";
            cin >> temp;
            if (temp == 1)
            {
                equipment(option);
            }
            cout << "Have fun!" << endl;
        }
        else if (option == 3)
        {
            cout << "Rules for Billiards:\n"
                 << "1. No touching or bumping players.\n"
                 << "2. No distracting movements or noise.\n"
                 << "3. Handle equipment with care.\n"
                 << "4. Shake hands after match.\n"
                 << "Have fun!\n";
        }
        else if (option == 4)
        {
            cout << "Swimming Pool Rules:\n"
                 << "1. No running.\n"
                 << "2. No horseplay or fighting.\n"
                 << "3. Listen to lifeguards.\n"
                 << "4. Wear proper swimwear.\n"
                 << "5. No food or drinks in the pool.\n"
                 << "Have fun!\n";
        }
        else
        {
            cout << "Invalid option selected.\n";
        }
    }

    void equipment(int option)
    {
        if (option == 1)
        {
            cout << "Available Equipment:\n- Badminton rackets\n- Shuttles (plastic or feather)\n";
        }
        else if (option == 2)
        {
            cout << "Available Equipment:\n- Table Tennis rackets\n- Table Tennis balls\n";
        }
        else if (option == 5)
        {
            cout << "Available Equipment:\n- Bats\n- Balls\n- Guards and gloves\n";
        }
    }
};

const int DECK_SIZE = 34;
const int HAND_SIZE = 7;
const int MASTER_CARD = 11;

class GameArcade
{
private:
    int userChoice;
    int computerChoice;

public:
    GameArcade()
    {
        cout << "Welcome to the gaming arcade!" << endl;
        cout << "Rules that must be followed:" << endl
             << "1. Treat all players and staff with respect. No bullying, harassment, or bad language." << endl
             << "2. No rough handling, hitting, or damaging machines. You break it — you might be responsible!" << endl
             << "3. Play fair. Cheating ruins the fun for everyone." << endl
             << endl;

        srand(time(0));
    }

    void chooseGame()
    {
        int choice;
        cout << "\nWhich game would you like to play?\n";
        cout << "1. Rock-Paper-Scissors\n";
        cout << "2. Card Wars\n";
        cout << "Enter your choice (1 or 2): ";
        cin >> choice;

        if (choice == 1)
        {
            playRockPaperScissors();
        }
        else if (choice == 2)
        {
            playCardWars();
        }
        else
        {
            cout << "Invalid choice. Exiting.\n";
        }
    }

    void playRockPaperScissors()
    {
        char playAgain;
        do
        {
            getUserChoice();
            generateComputerChoice();
            displayChoices();
            determineWinner();
            cout << "Play again? (y/n): ";
            cin >> playAgain;
        } while (playAgain == 'y' || playAgain == 'Y');

        cout << "Thanks for playing Rock-Paper-Scissors!\n";
    }

    void playCardWars()
    {
        int deck[DECK_SIZE];
        int player_hand[HAND_SIZE] = {0};
        int computer_hand[HAND_SIZE] = {0};
        int deck_index = HAND_SIZE * 2;
        int threshold;

        for (int i = 0; i < 30; i++)
        {
            deck[i] = (i % 10) + 1;
        }
        for (int i = 30; i < DECK_SIZE; i++)
        {
            deck[i] = MASTER_CARD;
        }

        for (int i = 0; i < DECK_SIZE; i++)
        {
            int j = rand() % DECK_SIZE;
            swap(deck[i], deck[j]);
        }

        for (int i = 0; i < HAND_SIZE; i++)
        {
            player_hand[i] = deck[i];
            computer_hand[i] = deck[i + HAND_SIZE];
        }

        threshold = (rand() % 10) + 1;
        cout << "Threshold number for this round: " << threshold << endl
             << endl;

        while (true)
        {
            int has_valid_card = 0;
            int player_has_master = 0;

            cout << "\nYour cards:\n";
            for (int i = 0; i < HAND_SIZE; i++)
            {
                if (player_hand[i] == MASTER_CARD)
                {
                    cout << "Card " << i << ": Master Card\n";
                    player_has_master = 1;
                }
                else if (player_hand[i] != 0)
                {
                    cout << "Card " << i << ": " << player_hand[i] << endl;
                    if (player_hand[i] >= threshold)
                    {
                        has_valid_card = 1;
                    }
                }
            }

            if (has_valid_card)
            {
                int card_index;
                cout << "\nEnter the index of the card you want to throw (0-6): ";
                cin >> card_index;

                if (card_index < 0 || card_index >= HAND_SIZE || player_hand[card_index] == 0)
                {
                    cout << "Invalid card index or card already used.\n";
                    continue;
                }

                int chosen_card = player_hand[card_index];

                if (chosen_card == MASTER_CARD)
                {
                    threshold = 1;
                    cout << "You played a Master card! Threshold reset to 1.\n";
                }
                else if (chosen_card >= threshold)
                {
                    cout << "You played card " << chosen_card << ", meeting the threshold " << threshold << ".\n";
                    threshold = chosen_card;
                }
                else
                {
                    cout << "Card " << chosen_card << " does not meet the threshold " << threshold << ".\n";
                    continue;
                }
                player_hand[card_index] = 0;
            }
            else
            {
                cout << "\nYou have no valid cards to play. Drawing a card from the deck.\n";
                if (deck_index >= DECK_SIZE)
                {
                    cout << "The deck is empty! No more cards to draw.\n";
                    break;
                }

                int new_card = deck[deck_index++];
                cout << "You drew card: " << (new_card == MASTER_CARD ? "Master Card" : to_string(new_card)) << endl;

                if (new_card == MASTER_CARD && player_has_master)
                {
                    cout << "You already have a Master card, cannot pick another.\n";
                }
                else
                {
                    int replace_index = -1;
                    for (int i = 0; i < HAND_SIZE; i++)
                    {
                        if (player_hand[i] == 0)
                        {
                            replace_index = i;
                            break;
                        }
                    }
                    if (replace_index == -1)
                        replace_index = rand() % HAND_SIZE;
                    player_hand[replace_index] = new_card;
                    cout << "Card replaced successfully.\n";
                }
            }

            int player_cards_left = 0;
            for (int i = 0; i < HAND_SIZE; i++)
            {
                if (player_hand[i] != 0)
                    player_cards_left++;
            }
            if (player_cards_left == 0)
            {
                cout << "\nYou have no cards left! You win!\n";
                break;
            }

            cout << "\nComputer's turn...\n";
            int computer_card_played = 0;
            int computer_has_master = 0;

            for (int i = 0; i < HAND_SIZE; i++)
            {
                if (computer_hand[i] == MASTER_CARD)
                    computer_has_master = 1;

                if (computer_hand[i] >= threshold && computer_hand[i] != MASTER_CARD)
                {
                    threshold = computer_hand[i];
                    cout << "Computer played card " << computer_hand[i] << ".\n";
                    computer_hand[i] = 0;
                    computer_card_played = 1;
                    break;
                }
            }

            if (!computer_card_played)
            {
                cout << "Computer has no valid card. Drawing from the deck.\n";
                if (deck_index >= DECK_SIZE)
                {
                    cout << "The deck is empty! No more cards to draw.\n";
                    break;
                }

                int new_card = deck[deck_index++];
                cout << "Computer drew card: " << (new_card == MASTER_CARD ? "Master Card" : to_string(new_card)) << endl;

                if (new_card == MASTER_CARD && computer_has_master)
                {
                    cout << "Computer already has a Master card. Discarding the new one.\n";
                }
                else
                {
                    computer_hand[rand() % HAND_SIZE] = new_card;
                    cout << "Computer replaced a card.\n";
                }
            }

            int computer_cards_left = 0;
            for (int i = 0; i < HAND_SIZE; i++)
            {
                if (computer_hand[i] != 0)
                    computer_cards_left++;
            }
            if (computer_cards_left == 0)
            {
                cout << "\nComputer has no cards left! You win!\n";
                break;
            }
        }

        cout << "Thanks for playing Card Wars!\n";
    }

private:
    void getUserChoice()
    {
        cout << "Choose:\n0 for Rock\n1 for Paper\n2 for Scissors\nEnter your choice: ";
        cin >> userChoice;

        while (userChoice < 0 || userChoice > 2)
        {
            cout << "Invalid choice. Please choose 0, 1, or 2: ";
            cin >> userChoice;
        }
    }

    void generateComputerChoice()
    {
        computerChoice = rand() % 3;
    }

    void displayChoices()
    {
        cout << "\nYou chose: " << choiceToString(userChoice) << endl;
        cout << "Computer chose: " << choiceToString(computerChoice) << endl;
    }

    string choiceToString(int choice)
    {
        switch (choice)
        {
        case 0:
            return "Rock";
        case 1:
            return "Paper";
        case 2:
            return "Scissors";
        default:
            return "Unknown";
        }
    }

    void determineWinner()
    {
        if (userChoice == computerChoice)
        {
            cout << "It's a draw!\n";
        }
        else if ((userChoice == 0 && computerChoice == 2) ||
                 (userChoice == 1 && computerChoice == 0) ||
                 (userChoice == 2 && computerChoice == 1))
        {
            cout << "You win!\n";
        }
        else
        {
            cout << "Computer wins!\n";
        }
    }
};

class BankAccount
{
private:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    BankAccount(string name, int accNumber, double initialBalance)
    {
        accountHolderName = name;
        accountNumber = accNumber;
        balance = initialBalance;
    }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Amount deposited successfully. New Balance: " << balance << endl;
        }
        else
        {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount > balance)
        {
            cout << "Insufficient balance!" << endl;
        }
        else if (amount <= 0)
        {
            cout << "Invalid withdrawal amount." << endl;
        }
        else
        {
            balance -= amount;
            cout << "Amount withdrawn successfully. Remaining Balance: " << balance << endl;
        }
    }

    void display() const
    {
        cout << "\n=== Account Details ===\n";
        cout << "Account Holder Name : " << accountHolderName << endl;
        cout << "Account Number      : " << accountNumber << endl;
        cout << "Balance             : " << balance << endl;
        cout << "========================\n";
    }

    void changeAccountHolderName(string newName)
    {
        if (!newName.empty())
        {
            accountHolderName = newName;
            cout << "Account holder name updated successfully.\n";
        }
        else
        {
            cout << "Name cannot be empty!\n";
        }
    }

    void checkBalance() const
    {
        cout << "Your current balance is: " << balance << endl;
    }

    int getAccountNumber() const
    {
        return accountNumber;
    }

    string getAccountHolderName() const
    {
        return accountHolderName;
    }
};

void displayMenu()
{
    cout << "\n--- Bank Menu ---\n";
    cout << "1. Display Account Details\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Change Account Holder Name\n";
    cout << "5. Check Balance\n";
    cout << "6. Exit\n";
    cout << "------------------\n";
    cout << "Enter your choice: ";
}

class FoodCourt
{
private:
    string customerName;
    double totalBill;
    map<string, double> menu;
    map<string, int> order;

public:
    FoodCourt(string name)
    {
        customerName = name;
        totalBill = 0;

        // Define food menu with prices
        menu["Pizza"] = 250.0;
        menu["Burger"] = 150.0;
        menu["Fries"] = 100.0;
        menu["Drink"] = 50.0;
    }

    void showMenu() const
    {
        cout << "\n--- Food Menu ---\n";
        for (const auto &item : menu)
        {
            cout << item.first << " - Rs. " << item.second << endl;
        }
        cout << "------------------\n";
    }

    void placeOrder()
    {
        string item;
        int quantity;

        cout << "Enter the food item you want to order: ";
        cin.ignore(); // To clear any extra newline character
        getline(cin, item);

        if (menu.find(item) != menu.end())
        {
            cout << "Enter quantity for " << item << ": ";
            cin >> quantity;

            if (quantity > 0)
            {
                order[item] += quantity;
                totalBill += menu[item] * quantity;
                cout << quantity << " " << item << "(s) added to your order.\n";
            }
            else
            {
                cout << "Invalid quantity!\n";
            }
        }
        else
        {
            cout << "Item not available on the menu.\n";
        }
    }

    void cancelOrder()
    {
        string item;
        int quantity;

        cout << "Enter the food item you want to cancel: ";
        cin.ignore();
        getline(cin, item);

        if (order.find(item) != order.end())
        {
            cout << "Enter quantity to cancel for " << item << ": ";
            cin >> quantity;

            if (quantity > 0 && order[item] >= quantity)
            {
                order[item] -= quantity;
                totalBill -= menu[item] * quantity;
                cout << quantity << " " << item << "(s) removed from your order.\n";
            }
            else
            {
                cout << "Invalid quantity or insufficient quantity ordered.\n";
            }
        }
        else
        {
            cout << "You haven't ordered " << item << ".\n";
        }
    }

    void viewBill() const
    {
        cout << "\n--- Current Bill ---\n";
        if (order.empty())
        {
            cout << "No items ordered yet.\n";
        }
        else
        {
            for (const auto &item : order)
            {
                if (item.second > 0)
                {
                    cout << item.first << " x" << item.second << " = Rs. " << menu.at(item.first) * item.second << endl;
                }
            }
            cout << "---------------------\n";
            cout << "Total Bill: Rs. " << totalBill << endl;
        }
    }

    void finalizeOrder() const
    {
        cout << "\n=== Final Bill ===\n";
        viewBill();
        cout << "\nThank you for ordering, " << customerName << "!\n";
        cout << "Visit Again!\n";
    }
};

void displayFoodCourtMenu()
{
    cout << "\n--- Food Court Menu ---\n";
    cout << "1. Show Food Items\n";
    cout << "2. Place Order\n";
    cout << "3. Cancel Order\n";
    cout << "4. View Current Bill\n";
    cout << "5. Finalize Order & Exit\n";
    cout << "-------------------------\n";
    cout << "Enter your choice: ";
}

void executeBank()
{
    string name;
    int accNumber;
    double initialBalance;

    cout << "============================\n";
    cout << " Welcome to Bank Management\n";
    cout << "============================\n";

    cout << "\nEnter Account Holder Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Account Number: ";
    cin >> accNumber;

    cout << "Enter Initial Balance: ";
    cin >> initialBalance;

    BankAccount account(name, accNumber, initialBalance);

    int choice;
    double amount;
    string newName;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.display();
            break;
        case 2:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            account.deposit(amount);
            break;
        case 3:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            account.withdraw(amount);
            break;
        case 4:
            cout << "Enter new Account Holder Name: ";
            cin.ignore();
            getline(cin, newName);
            account.changeAccountHolderName(newName);
            break;
        case 5:
            account.checkBalance();
            break;
        case 6:
            cout << "\nThank you for using the Bank Management System!\n";
            cout << "Have a great day!\n";
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
            break;
        }

    } while (choice != 6);
}

void executeFoodCourt()
{
    string name;
    cout << "============================\n";
    cout << " Welcome to Food Court\n";
    cout << "============================\n";
    cout << "Enter Customer Name: ";
    getline(cin, name);

    FoodCourt order(name);

    int choice;
    do
    {
        displayFoodCourtMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            order.showMenu();
            break;
        case 2:
            order.placeOrder();
            break;
        case 3:
            order.cancelOrder();
            break;
        case 4:
            order.viewBill();
            break;
        case 5:
            order.finalizeOrder();
            break;
        default:
            cout << "Invalid choice! Try again.\n";
            break;
        }
    } while (choice != 5);
}

class Patient
{
public:
    int id;
    string name;
    int age;
    string gender;
    string disease;

    void inputDetails(int pid)
    {
        id = pid;
        cout << "\nEnter patient name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter gender: ";
        getline(cin, gender);
        cout << "Enter disease: ";
        getline(cin, disease);
    }

    void displayDetails() const
    {
        cout << left << setw(5) << id << setw(20) << name << setw(5) << age
             << setw(10) << gender << setw(20) << disease << endl;
    }
};

class Doctor
{
public:
    int id;
    string name;
    string specialty;

    void inputDetails(int did)
    {
        id = did;
        cout << "\nEnter doctor name: ";
        getline(cin, name);
        cout << "Enter specialty: ";
        getline(cin, specialty);
    }

    void displayDetails() const
    {
        cout << left << setw(5) << id << setw(20) << name << setw(20) << specialty << endl;
    }
};

class Appointment
{
public:
    int patientId;
    int doctorId;
    string date;

    void inputDetails()
    {
        cout << "\nEnter Patient ID: ";
        cin >> patientId;
        cout << "Enter Doctor ID: ";
        cin >> doctorId;
        cin.ignore();
        cout << "Enter appointment date (DD/MM/YYYY): ";
        getline(cin, date);
    }

    void displayDetails() const
    {
        cout << left << setw(12) << patientId << setw(12) << doctorId << setw(15) << date << endl;
    }
};

class Hospital
{
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    int patientCounter = 1;
    int doctorCounter = 1;

public:
    void addPatient()
    {
        Patient p;
        cin.ignore();
        p.inputDetails(patientCounter++);
        patients.push_back(p);
        cout << "Patient added successfully!\n";
    }

    void addDoctor()
    {
        Doctor d;
        cin.ignore();
        d.inputDetails(doctorCounter++);
        doctors.push_back(d);
        cout << "Doctor added successfully!\n";
    }

    void showPatients() const
    {
        if (patients.empty())
        {
            cout << "No patients available.\n";
            return;
        }
        cout << "\n--- Patient List ---\n";
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(5) << "Age"
             << setw(10) << "Gender" << setw(20) << "Disease" << endl;
        cout << string(60, '-') << endl;
        for (const auto &p : patients)
            p.displayDetails();
    }

    void showDoctors() const
    {
        if (doctors.empty())
        {
            cout << "No doctors available.\n";
            return;
        }
        cout << "\n--- Doctor List ---\n";
        cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(20) << "Specialty" << endl;
        cout << string(45, '-') << endl;
        for (const auto &d : doctors)
            d.displayDetails();
    }

    void scheduleAppointment()
    {
        if (patients.empty() || doctors.empty())
        {
            cout << "You must have at least one patient and one doctor to schedule an appointment.\n";
            return;
        }
        Appointment a;
        a.inputDetails();
        appointments.push_back(a);
        cout << "Appointment scheduled!\n";
    }

    void showAppointments() const
    {
        if (appointments.empty())
        {
            cout << "No appointments scheduled.\n";
            return;
        }
        cout << "\n--- Appointments ---\n";
        cout << left << setw(12) << "Patient ID" << setw(12) << "Doctor ID" << setw(15) << "Date" << endl;
        cout << string(40, '-') << endl;
        for (const auto &a : appointments)
            a.displayDetails();
    }

    void searchPatient() const
    {
        int id;
        cout << "Enter Patient ID to search: ";
        cin >> id;
        for (const auto &p : patients)
        {
            if (p.id == id)
            {
                cout << "Patient found:\n";
                p.displayDetails();
                return;
            }
        }
        cout << "Patient not found.\n";
    }

    void searchDoctor() const
    {
        int id;
        cout << "Enter Doctor ID to search: ";
        cin >> id;
        for (const auto &d : doctors)
        {
            if (d.id == id)
            {
                cout << "Doctor found:\n";
                d.displayDetails();
                return;
            }
        }
        cout << "Doctor not found.\n";
    }
};

void showMenu()
{
    cout << "\n--- Hospital Management System ---\n";
    cout << "1. Add Patient\n";
    cout << "2. Add Doctor\n";
    cout << "3. Show Patients\n";
    cout << "4. Show Doctors\n";
    cout << "5. Schedule Appointment\n";
    cout << "6. Show Appointments\n";
    cout << "7. Search Patient by ID\n";
    cout << "8. Search Doctor by ID\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

void executeHospitalManagement()
{
    Hospital h;
    int choice;

    do
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            h.addPatient();
            break;
        case 2:
            h.addDoctor();
            break;
        case 3:
            h.showPatients();
            break;
        case 4:
            h.showDoctors();
            break;
        case 5:
            h.scheduleAppointment();
            break;
        case 6:
            h.showAppointments();
            break;
        case 7:
            h.searchPatient();
            break;
        case 8:
            h.searchDoctor();
            break;
        case 9:
            cout << "Thank you for using the Hospital Management System.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);
}

int main()
{
    while (true)
    {
        int category, avail;

        cout << "\nWELCOME TO THE TOWN!" << endl;
        cout << "Please choose a category: " << endl;
        cout << "Enter 1 for Emergency Services" << endl;
        cout << "Enter 2 for Leisure Services" << endl;
        cout << "Your input: ";
        cin >> category;

        if (category == 1)
        {
            // Emergency Services
            cout << "\nEMERGENCY SERVICES: " << endl;
            cout << "Enter 1 to Visit Hospital" << endl;
            cout << "Enter 2 to Visit Bank" << endl;
            cout << "Your input: ";
            cin >> avail;

            if (avail == 1)
            {
                cout << "\nGoing to Hospital..." << endl;
                executeHospitalManagement();
            }
            else if (avail == 2)
            {
                cout << "\nGoing to Bank..." << endl;
                executeBank();
            }
            else
            {
                cout << "\nInvalid input, please choose a valid emergency service." << endl;
            }
        }
        else if (category == 2)
        {
            cout << "\nLeisure Services: " << endl;
            cout << "Enter 1 for GYM" << endl;
            cout << "Enter 2 for Sports Complex" << endl;
            cout << "Enter 3 for Game Arcade" << endl;
            cout << "Enter 4 for Booking Club for Functions/Gatherings" << endl;
            cout << "Enter 5 for Visiting Food Court" << endl;
            cout << "Enter 6 to Exit" << endl;
            cout << "Your input: ";
            cin >> avail;

            if (avail == 1)
            {
                GymSystem gymSystem;
                gymSystem.menu();
            }
            else if (avail == 2)
            {
                SportComplex S1;
            }
            else if (avail == 3)
            {
                GameArcade G1;
                G1.chooseGame();
            }
            else if (avail == 4)
            {
                Function F1;
            }
            else if (avail == 5)
            {
                executeFoodCourt();
            }
            else if (avail == 6)
            {
                cout << "Thank you for visiting the Town! Goodbye!" << endl;
                break;
            }
            else
            {
                cout << "\nInvalid input, please choose a valid service." << endl;
            }
        }
        else
        {
            cout << "\nInvalid input, please choose either Emergency Services or Other Services." << endl;
        }
    }

    return 0;
}