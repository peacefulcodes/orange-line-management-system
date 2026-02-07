#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
using namespace std;

int const arrsize = 30;
int const user_const = 1000;

// ======================= Function Prototypes =======================
void banner();
void exit_program();
string main_menue();
string admin_menu();
string manager_menu();
string user_menu();

// =======================  FOR ADMIN =======================
bool admin_login(string adminName, string adminPass);
int manager_login(string manager_names[], string manager_ids[], string manager_passwords[], string stations[], int stationCount);

bool user_sign_up(string userNames[], string userPasswords[], string userIDs[], int &user_count);
bool user_login(string userNames[], string userPasswords[], string userIDs[], int user_count, string &loggedUserID);

// ======================= FILE HANDLING PROTOTYPES =======================
void saveUserData(string name, string password, string id);
void loadUserData(string names[], string passwords[], string ids[], int &count);
string loadUserAttribute(string line, int &idx);

void update_manager(string stations[], string manager_names[], string manager_ids[], string manager_passwords[]);
void add_manager(string stations[], string manager_names[], string manager_ids[],
                 string manager_passwords[], string station_status[], int &stationCount, int &manger_count);

void remove_manger(string stations[], string manager_names[], string manager_ids[], string manager_passwords[], int &manger_count);
void update_station_status(string stations[], string station_status[]);
void admin_view_all(string stations[], string station_status[],
                    string manager_names[], string manager_ids[],
                    int stationCount);

// ======================= User Function Prototypes =======================
void viewStations(string stations[], int stationCount);
void viewStationStatus(string stations[], string station_status[], int stationCount);
void viewFares();
int calculateFare(int startStation, int endStation, int stationCount);
int findCardIndex(string cardUserIDs[], int cardCount, string userID);
void buyToken(int stationStats[][6], int stationCount);
void buyNewCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int &cardCount, int stationStats[][6], int stationCount);
void rechargeCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int cardCount, int stationStats[][6], int stationCount);
void swipeCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int cardCount, int stationStats[][6], int stationCount);

// =========================== FOR MANAGER =============================
void show_passenger_count(int user_count, string userNames[], string userPasswords[], string userIDs[]);
void Total_cards_sold(int stationIndex, int stationStats[][6], string stations[]);
void showTotalRechargedCards(int stationIndex, int stationStats[][6], string stations[]);
void showDailyEarnings(int stationIndex, int stationStats[][6], string stations[]);
void Manager_update_station(string stations[], string station_status[], int stationCount, int stationIndex);

// ======================= VALIDATION / UI HELPERS =======================
int stringToInt(string s);
bool intCheck(string s);
bool AllCapitalNoSpace(string s);
bool isValidID(string cnic);
void printHeader(string msg);

void pause_screen(); // NEW
void clear_screen(); // NOW ONLY system("cls")

void setColor(int color);
void setColor(int textColor, int bgColor);

// Table helpers
void printLine(int w, char ch = '-');
void printTableTitle(string title, int width);

// ======================= MAIN =======================
int main()
{
    string stations[arrsize] = {
        "Ali Town",
        "Thokar Niaz Baig",
        "Sabzazar",
        "Shahnoor",
        "Multan Road",
        "Chauburji",
        "GPO",
        "Lakshmi Chowk",
        "Railway Station",
        "Shalimar Gardens",
        "Baghbanpura",
        "Sultanpura",
        "UET",
        "Anarkali",
        "MAO College",
        "Canal Road",
        "Samanabad",
        "Gulshan-e-Ravi",
        "Band Road",
        "Salamatpura",
        "Mahmood Booti",
        "Pakki Thatti",
        "Islam Park",
        "Shahdara",
        "Bhagbanpura Extension",
        "Dera Gujran",
    };

    string station_status[arrsize] = {
        "Active", "Active", "Active", "Active", "Active",
        "Active", "Active", "Active", "Active", "Active",
        "Active", "Active", "Active", "Active", "Active",
        "Active", "Active", "Active", "Active", "Active",
        "Active", "Active", "Active", "Active", "Active",
        "Active"};

    string manager_names[arrsize] = {
        "Ali Ahmed", "Haida Islam", "Imran Khan", "Ahmed Raza", "Usman Ali",
        "Bilal Ahmed", "Hamza Noor", "Saad Hassan", "Adeel Khan", "Zain Abbas",
        "Fahad Ali", "Danish Ahmed", "Umar Farooq", "Kamran Shah", "Tahir Mehmood",
        "Rashid Hussain", "Noman Ali", "Faraz Ahmed", "Adnan Malik", "Saif Ullah",
        "Yasir Iqbal", "Shahzaib Khan", "Hassan Raza", "Muneeb Ahmed",
        "Abdullah Noor", "Arslan Haider"};

    string manager_ids[arrsize] = {
        "AT11", "AT22", "SB33", "SN44", "MR55",
        "CH66", "GP77", "LC88", "RS99", "SG10",
        "BA11", "SU12", "UE13", "AN14", "MA15",
        "CA16", "SA17", "GU18", "BA19", "SA20",
        "MH21", "PA22", "IS23", "SH24", "BE25",
        "DE26"};

    string manager_passwords[arrsize] = {
        "111", "222", "333", "444", "555",
        "666", "777", "888", "999", "101",
        "111", "121", "131", "141", "151",
        "161", "171", "181", "191", "110",
        "112", "113", "114", "115", "116",
        "117"};

    // ===== USER STORAGE =====
    string userNames[user_const];
    string userPasswords[user_const];
    string userIDs[user_const];
    int user_count = 0;

    loadUserData(userNames, userPasswords, userIDs, user_count);

    // ===== USER CARD STORAGE =====
    string cardUserIDs[user_const];
    int cardBalances[user_const];
    int cardCount = 0;

    int stationStats[arrsize][6] = {0};

    int stationCount = 26;
    string admin_name = "HAIDAISLAM";
    string admin_pas = "2007";
    int manager_count = 26;

    while (true)
    {
        banner();
        string role = main_menue();

        if (role == "0")
        {
            clear_screen();
            exit_program();
            break;
        }

        // ======================= ADMIN =======================
        if (role == "1")
        {
            clear_screen();
            banner();

            string role_choice = "";
            if (admin_login(admin_name, admin_pas))
            {
                clear_screen();
                banner();
                role_choice = admin_menu();
            }
            else
            {
                setColor(12, 0);
                cout << "Too many attempts!! Access denied.\n";
                setColor(7, 0);
                pause_screen();
                clear_screen();
                continue;
            }

            while (role_choice != "0")
            {
                if (role_choice == "3")
                {
                    clear_screen();
                    banner();
                    update_manager(stations, manager_names, manager_ids, manager_passwords);
                    pause_screen();
                    clear_screen();
                }
                else if (role_choice == "1")
                {
                    clear_screen();
                    banner();
                    string confirm;
                    cout << "There are currently " << stationCount << " stations. Do you want to add more?\n";
                    cout << "Press 1 to confirm: ";
                    getline(cin, confirm);

                    if (confirm == "1")
                    {
                        admin_view_all(stations, station_status, manager_names, manager_ids, stationCount);
                        pause_screen();
                        clear_screen();
                        add_manager(stations, manager_names, manager_ids, manager_passwords, station_status, stationCount, manager_count);
                    }
                    pause_screen();
                    clear_screen();
                }
                else if (role_choice == "2")
                {
                    clear_screen();
                    banner();
                    remove_manger(stations, manager_names, manager_ids, manager_passwords, manager_count);
                    pause_screen();
                    clear_screen();
                }
                else if (role_choice == "4")
                {
                    clear_screen();
                    banner();
                    update_station_status(stations, station_status);
                    pause_screen();
                    clear_screen();
                }
                else
                {
                    printHeader("Wrong choice! Please select a valid option.");
                    pause_screen();
                    clear_screen();
                }

                banner();
                role_choice = admin_menu();
            }
            clear_screen();
        }

        // ======================= MANAGER =======================
        else if (role == "2")
        {
            clear_screen();
            banner();
            int managerStationIndex = manager_login(manager_names, manager_ids, manager_passwords, stations, stationCount);

            if (managerStationIndex >= 0)
            {
                clear_screen();
                banner();
                string role_choice = manager_menu();

                while (role_choice != "0")
                {
                    if (role_choice == "1")
                    {
                        clear_screen();
                        banner();
                        show_passenger_count(user_count, userNames, userPasswords, userIDs);
                        pause_screen();
                        clear_screen();
                    }
                    else if (role_choice == "2")
                    {
                        clear_screen();
                        banner();
                        Total_cards_sold(managerStationIndex, stationStats, stations);
                        pause_screen();
                        clear_screen();
                    }
                    else if (role_choice == "3")
                    {
                        clear_screen();
                        banner();
                        showTotalRechargedCards(managerStationIndex, stationStats, stations);
                        pause_screen();
                        clear_screen();
                    }
                    else if (role_choice == "4")
                    {
                        clear_screen();
                        banner();
                        showDailyEarnings(managerStationIndex, stationStats, stations);
                        pause_screen();
                        setColor(7, 0);
                        clear_screen();
                    }
                    else if (role_choice == "5")
                    {
                        clear_screen();
                        banner();
                        Manager_update_station(stations, station_status, stationCount, managerStationIndex);
                        pause_screen();
                        clear_screen();
                    }
                    else
                    {
                        setColor(12, 0);
                        cout << "Invalid input\n";
                        setColor(7, 0);
                        pause_screen();
                        clear_screen();
                    }

                    banner();
                    role_choice = manager_menu();
                }

                clear_screen();
                setColor(12, 0);
                cout << "##########################################\n";
                cout << "#  [!] SHUTTING DOWN MANAGER SESSION...  #\n";
                cout << "##########################################\n";
                setColor(7, 0);
                pause_screen();
                clear_screen();
            }
        }

        // ======================= USER LOGIN =======================
        else if (role == "3")
        {
            clear_screen();
            banner();
            string loggedUserID = "";

            if (user_login(userNames, userPasswords, userIDs, user_count, loggedUserID))
            {
                clear_screen();
                banner();
                string choice = user_menu();

                while (choice != "0")
                {
                    if (choice == "1")
                    {
                        clear_screen();
                        banner();
                        viewStations(stations, stationCount);
                        pause_screen();
                        clear_screen();
                    }
                    else if (choice == "2")
                    {
                        clear_screen();
                        banner();
                        viewFares();
                        pause_screen();
                        clear_screen();
                    }
                    else if (choice == "3")
                    {
                        clear_screen();
                        banner();
                        buyToken(stationStats, stationCount);
                        pause_screen();
                        clear_screen();
                    }
                    else if (choice == "4")
                    {
                        clear_screen();
                        banner();
                        viewStationStatus(stations, station_status, stationCount);
                        pause_screen();
                        clear_screen();
                    }
                    else if (choice == "5")
                    {
                        clear_screen();
                        banner();
                        buyNewCard(loggedUserID, cardUserIDs, cardBalances, cardCount, stationStats, stationCount);
                        pause_screen();
                        clear_screen();
                    }
                    else if (choice == "6")
                    {
                        clear_screen();
                        banner();
                        rechargeCard(loggedUserID, cardUserIDs, cardBalances, cardCount, stationStats, stationCount);
                        pause_screen();
                        clear_screen();
                    }
                    else if (choice == "7")
                    {
                        clear_screen();
                        banner();
                        swipeCard(loggedUserID, cardUserIDs, cardBalances, cardCount, stationStats, stationCount);
                        pause_screen();
                        clear_screen();
                    }
                    else
                    {
                        printHeader("INVALID USER MENU CHOICE...");
                        pause_screen();
                        clear_screen();
                    }

                    banner();
                    choice = user_menu();
                }

                clear_screen();
                setColor(14, 0);
                printHeader("Logout successful. Returning to main menu...");
                pause_screen();
                setColor(7, 0);
                clear_screen();
            }
            else
            {
                setColor(14, 0);
                printHeader("RETURNING TO MAIN MENU");
                pause_screen();
                setColor(7, 0);
                clear_screen();
            }
        }

        // ======================= USER SIGNUP =======================
        else if (role == "4")
        {
            clear_screen();
            banner();
            bool ok = user_sign_up(userNames, userPasswords, userIDs, user_count);

            if (ok)
            {
                setColor(10, 0);
                cout << "Sign up done. Now login as user from main menu.\n";
                setColor(7, 0);
            }
            else
            {
                setColor(12, 0);
                cout << "Sign up failed. Try again.\n";
                setColor(7, 0);
            }

            pause_screen();
            clear_screen();
        }
        else
        {
            setColor(12, 0);
            cout << "+---------------------------------+\n";
            cout << "|  ERROR: Invalid Main Menu choice|\n";
            cout << "+---------------------------------+\n";
            cout << "Please try again.\n";
            setColor(7, 0);
            pause_screen();
            clear_screen();
        }
    }

    return 0;
}

// ======================= UI PRINTS =======================
void banner()
{
    setColor(14, 0);
    cout << R"(
    ____      ______       ____        __      _      _____     _____      _____          _____      __      _     _____
   / __ \    (   __ \     (    )      /  \    / )    / ___ \   / ___/     (_   _)        (_   _)    /  \    / )  / ___/
  / /  \ \    ) (__) )     / /\ \     / /\ \  / /    / /   \_) ( (__          | |          | |     / /\ \  / /  ( (__
 ( ()  () ) (    __/     ( (__) )    ) ) ) ) ) )   ( (  ____   ) __)         | |           | |     ) ) ) ) )  )   ) __)
 ( ()  () )  ) \ \  _     )    (     ( ( ( ( ( (    ( ( (__  ) ( (            | |   __     | |    ( ( ( ( (   (  ( (
  \ \__/ /  ( ( \ \_))   /  /\  \   / /  \ \/ /     \ \__/ /   \ \___      __| |___) )    _| |__  / /  \ \/ /    \ \___
   \____/    )_) \__/   /__(  )__\ (_/    \__/       \____/     \____\    \________/     /_____( (_/    \__/      \____\
    )" << endl;

    setColor(11, 0);
    cout << "  ========================================================================================= \n";
    cout << "       | fast|secure|reliable  ******* 'METRO RAIL MANAGEMENT SYSTEM ' ******               \n";
    cout << " =========================================================================================  \n";
    setColor(7, 0);
}

string main_menue()
{
    string role;
    setColor(11, 0);
    cout << "\t===========================================\n";
    setColor(14, 0);
    cout << "\t||  [1] Login as Admin                   ||\n";
    cout << "\t||  [2] Login as Manager                 ||\n";
    cout << "\t||  [3] Login as User                    ||\n";
    cout << "\t||  [4] Sign up as user                  ||\n";
    cout << "\t||  [0] Exit System                      ||\n";
    setColor(11, 0);
    cout << "\t===========================================\n";
    setColor(15, 0);
    cout << "\t  Enter choice number: ";
    setColor(7, 0);
    getline(cin, role);
    return role;
}

string admin_menu()
{
    string admin_choice;
    setColor(10, 0);
    cout << "\n\t  ___________________________________________\n";
    cout << "\t [ STATUS: AUTHORIZED SUCCESSFULLY           ]\n";
    cout << "\t [ ACCESS LEVEL: SYSTEM ADMINISTRATOR        ]\n";
    cout << "\t  -------------------------------------------\n";

    setColor(11, 0);
    cout << "\n\t/***********************************************\\\n";
    setColor(14, 0);
    cout << "\t|   [1] ADD MANAGER                             |\n";
    cout << "\t|   [2] REMOVE MANAGER                          |\n";
    cout << "\t|   [3] UPDATE MANAGER                          |\n";
    cout << "\t|   [4] UPDATE STATION STATUS                   |\n";
    cout << "\t|   [0] BACK TO MAIN MENU                       |\n";
    setColor(11, 0);
    cout << "\t\\***********************************************/\n";
    setColor(15, 0);
    cout << "\t  Admin Selection choice number> ";
    setColor(7, 0);

    getline(cin, admin_choice);
    return admin_choice;
}

string manager_menu()
{
    string manager_choice;
    setColor(13, 0);
    cout << "\n\t/===============================================\\\n";
    cout << "\t|            MANAGER CONTROL PANEL              |\n";
    setColor(11, 0);
    cout << "\t|===============================================|\n";
    setColor(14, 0);
    cout << "\t|   [1] View Daily Passenger Count              |\n";
    cout << "\t|   [2] View Total Cards Sold Today             |\n";
    cout << "\t|   [3] View Total Recharged Cards              |\n";
    cout << "\t|   [4] View Daily Total Earnings               |\n";
    cout << "\t|   [5] Update your Train Station status        |\n";
    cout << "\t|   [0] Logout & Return                         |\n";
    setColor(13, 0);
    cout << "\t\\===============================================/\n";
    setColor(15, 0);
    cout << "\t Enter Option #: ";
    setColor(7, 0);
    getline(cin, manager_choice);
    return manager_choice;
}

string user_menu()
{
    string user_choice;
    setColor(14, 0);
    cout << "\n\t/===============================================\\\n";
    cout << "\t|            ORANGE LINE METRO SYSTEM           |\n";
    cout << "\t|                USER DASHBOARD                 |\n";
    setColor(11, 0);
    cout << "\t|===============================================|\n";
    setColor(10, 0);
    cout << "\t|   [1] View Stations       [2] View Fares      |\n";
    cout << "\t|   [3] Buy Token           [4] Station Status  |\n";
    cout << "\t|   [5] Buy New Card        [6] Recharge Card   |\n";
    cout << "\t|   [7] Swipe Card          [0] Logout          |\n";
    setColor(14, 0);
    cout << "\t\\===============================================/\n";
    setColor(15, 0);
    cout << "\t Selection Choice: ";
    setColor(7, 0);
    getline(cin, user_choice);
    return user_choice;
}

// ======================= USER FUNCTIONS =======================
void viewStations(string stations[], int stationCount)
{
    cout << "\n===== ORANGE LINE STATIONS =====\n";
    for (int i = 0; i < stationCount; i++)
    {
        if (stations[i] != "")
            cout << i + 1 << ". " << stations[i] << "\n";
    }
}

void viewStationStatus(string stations[], string station_status[], int stationCount)
{
    const int W = 75;
    printTableTitle("STATION STATUS INFORMATION", W);

    setColor(11, 0);
    cout << left << setw(6) << "No."
         << setw(40) << "Station Name"
         << setw(25) << "Status" << "\n";
    setColor(7, 0);

    printLine(W);

    for (int i = 0; i < stationCount; i++)
    {
        if (stations[i] == "")
            continue;

        cout << left << setw(6) << (i + 1)
             << setw(40) << stations[i];

        if (station_status[i] == "Active")
            setColor(10, 0);
        else if (station_status[i] == "Under Maintenance")
            setColor(14, 0);
        else
            setColor(12, 0);

        cout << setw(25) << station_status[i];
        setColor(7, 0);
        cout << "\n";
    }

    printLine(W, '=');
}

void viewFares()
{
    cout << "\n===== FARES =====\n";
    cout << "Token (1 ride): 40 PKR\n";
    cout << "Card swipe (1 ride): 40 PKR\n";
    cout << "New card fee: 200 PKR\n";
}

void buyToken(int stationStats[][6], int stationCount)
{
    string Start_station, End_Station;

    cout << "Enter starting station number: ";
    getline(cin, Start_station);

    cout << "Enter destination station number: ";
    getline(cin, End_Station);

    if (!intCheck(Start_station) || !intCheck(End_Station))
    {
        setColor(12, 0);
        cout << "Invalid input. Please enter numbers only.\n";
        setColor(7, 0);
        return;
    }

    int startStation = stringToInt(Start_station);
    int endStation = stringToInt(End_Station);

    int fare = calculateFare(startStation, endStation, stationCount);

    if (fare == -1)
    {
        setColor(12, 0);
        cout << "Invalid station number.\n";
        setColor(7, 0);
        return;
    }
    if (fare == 0)
    {
        setColor(12, 0);
        cout << "Start and destination cannot be the same.\n";
        setColor(7, 0);
        return;
    }

    int stationIndex = startStation - 1;
    stationStats[stationIndex][0] += 1;
    stationStats[stationIndex][1] += fare;

    setColor(10, 0);
    cout << "Token purchased successfully.\n";
    cout << "Total Fare: " << fare << " PKR\n";
    setColor(7, 0);
}

int findCardIndex(string cardUserIDs[], int cardCount, string userID)
{
    for (int i = 0; i < cardCount; i++)
        if (cardUserIDs[i] == userID)
            return i;
    return -1;
}

void buyNewCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int &cardCount, int stationStats[][6], int stationCount)
{
    int card_index = findCardIndex(cardUserIDs, cardCount, loggedUserID);
    if (card_index != -1)
    {
        setColor(12, 0);
        cout << "You already have a card.\n";
        setColor(7, 0);
        return;
    }

    if (cardCount >= user_const)
    {
        setColor(12, 0);
        cout << "Card storage full.\n";
        setColor(7, 0);
        return;
    }

    string stationStr;
    cout << "Enter your current station number (1-" << stationCount << "): ";
    getline(cin, stationStr);

    if (!intCheck(stationStr))
    {
        setColor(12, 0);
        cout << "Invalid station number.\n";
        setColor(7, 0);
        return;
    }

    int station = stringToInt(stationStr);
    if (station < 1 || station > stationCount)
    {
        setColor(12, 0);
        cout << "Invalid station number.\n";
        setColor(7, 0);
        return;
    }

    cardUserIDs[cardCount] = loggedUserID;
    cardBalances[cardCount] = 0;
    cardCount++;

    int stationIndex = station - 1;
    stationStats[stationIndex][2] += 1;
    stationStats[stationIndex][1] += 200;

    setColor(10, 0);
    cout << "New card created successfully. Fee: 200 PKR\n";
    setColor(7, 0);
}

void rechargeCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int cardCount, int stationStats[][6], int stationCount)
{
    int card_index = findCardIndex(cardUserIDs, cardCount, loggedUserID);
    if (card_index == -1)
    {
        setColor(12, 0);
        cout << "You do not have a card. Buy a new card first.\n";
        setColor(7, 0);
        return;
    }

    string stationStr;
    cout << "Enter your current station number (1-" << stationCount << "): ";
    getline(cin, stationStr);

    if (!intCheck(stationStr))
    {
        setColor(12, 0);
        cout << "Invalid station number.\n";
        setColor(7, 0);
        return;
    }

    int station = stringToInt(stationStr);
    if (station < 1 || station > stationCount)
    {
        setColor(12, 0);
        cout << "Invalid station number.\n";
        setColor(7, 0);
        return;
    }

    string recharge_Amount;
    cout << "Enter recharge amount: ";
    getline(cin, recharge_Amount);

    if (!intCheck(recharge_Amount))
    {
        setColor(12, 0);
        cout << "Invalid amount. Please enter integer.\n";
        setColor(7, 0);
        return;
    }

    int amount_int = stringToInt(recharge_Amount);
    if (amount_int <= 0)
    {
        setColor(12, 0);
        cout << "Invalid amount.\n";
        setColor(7, 0);
        return;
    }

    cardBalances[card_index] += amount_int;

    int stationIndex = station - 1;
    stationStats[stationIndex][3] += 1;
    stationStats[stationIndex][1] += amount_int;

    setColor(10, 0);
    cout << "Recharge successful. New balance: " << cardBalances[card_index] << " PKR\n";
    setColor(7, 0);
}

void swipeCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int cardCount, int stationStats[][6], int stationCount)
{
    int card_index = findCardIndex(cardUserIDs, cardCount, loggedUserID);
    if (card_index == -1)
    {
        setColor(12, 0);
        cout << "You do not have a card. Buy a new card first.\n";
        setColor(7, 0);
        return;
    }

    string Start_station, End_Station;
    cout << "Enter starting station number: ";
    getline(cin, Start_station);
    cout << "Enter destination station number: ";
    getline(cin, End_Station);

    if (!intCheck(Start_station) || !intCheck(End_Station))
    {
        setColor(12, 0);
        cout << "Invalid input. Please enter numbers only.\n";
        setColor(7, 0);
        return;
    }

    int startStation = stringToInt(Start_station);
    int endStation = stringToInt(End_Station);

    int fare = calculateFare(startStation, endStation, stationCount);

    if (fare == -1)
    {
        setColor(12, 0);
        cout << "Invalid station number.\n";
        setColor(7, 0);
        return;
    }
    if (fare == 0)
    {
        setColor(12, 0);
        cout << "Start and destination cannot be the same.\n";
        setColor(7, 0);
        return;
    }

    if (cardBalances[card_index] >= fare)
    {
        cardBalances[card_index] -= fare;

        int stationIndex = startStation - 1;
        stationStats[stationIndex][5] += 1;
        stationStats[stationIndex][1] += fare;

        setColor(10, 0);
        cout << "Swipe successful. Fare deducted: " << fare << " PKR\n";
        cout << "Remaining balance: " << cardBalances[card_index] << " PKR\n";
        setColor(7, 0);
    }
    else
    {
        setColor(12, 0);
        cout << "Insufficient balance. Please recharge.\n";
        cout << "Your balance: " << cardBalances[card_index] << " PKR\n";
        cout << "Required fare: " << fare << " PKR\n";
        setColor(7, 0);
    }
}

// ======================= USER LOGIN/SIGNUP =======================
bool user_sign_up(string userNames[], string userPasswords[], string userIDs[], int &user_count)
{
    string user_name, user_ID, user_password;
    int user_attempts = 0;

    cout << "Enter your name: ";
    getline(cin, user_name);

    while (user_attempts < 3)
    {
        cout << "Enter your password (numbers only): ";
        getline(cin, user_password);
        if (intCheck(user_password))
            break;

        setColor(12, 0);
        cout << "Password should only contain integers!\n";
        setColor(7, 0);
        user_attempts++;
    }

    if (user_attempts >= 3 && !intCheck(user_password))
    {
        setColor(12, 0);
        cout << "Too many invalid attempts!\n";
        setColor(7, 0);
        return false;
    }

    cout << "Enter your ID: ";
    getline(cin, user_ID);

    for (int i = 0; i < user_count; i++)
        if (userIDs[i] == user_ID)
        {
            setColor(12, 0);
            cout << "User already present.\n";
            setColor(7, 0);
            return false;
        }

    if (user_count < user_const)
    {
        userNames[user_count] = user_name;
        userPasswords[user_count] = user_password;
        userIDs[user_count] = user_ID;
        user_count++;

        saveUserData(user_name, user_password, user_ID);

        setColor(10, 0);
        cout << "Sign up successful.\n";
        setColor(7, 0);
        return true;
    }

    setColor(12, 0);
    cout << "User storage full.\n";
    setColor(7, 0);
    return false;
}

bool user_login(string userNames[], string userPasswords[], string userIDs[], int user_count, string &loggedUserID)
{
    string userinput_ID, userinput_password;

    cout << "Enter your ID: ";
    getline(cin, userinput_ID);

    cout << "Enter your password: ";
    getline(cin, userinput_password);

    for (int i = 0; i < user_count; i++)
    {
        if (userIDs[i] == userinput_ID && userPasswords[i] == userinput_password)
        {
            loggedUserID = userIDs[i];
            setColor(10, 0);
            cout << "Login successful\n";
            setColor(7, 0);
            return true;
        }
    }

    setColor(12, 0);
    cout << "Login unsuccessful, ID and password don't exist.\n";
    setColor(7, 0);
    return false;
}

// ======================= VALIDATIONS =======================
bool intCheck(string s)
{
    if (s.length() == 0)
        return false;
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}

int stringToInt(string s)
{
    int num = 0;
    for (int i = 0; i < (int)s.length(); i++)
        num = num * 10 + (s[i] - '0');
    return num;
}

bool AllCapitalNoSpace(string s)
{
    if (s.length() == 0)
        return false;
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] < 'A' || s[i] > 'Z')
            return false;
    return true;
}

bool isValidID(string id)
{
    if (id.length() != 4)
        return false;
    for (int i = 0; i < 2; i++)
        if (id[i] < 'A' || id[i] > 'Z')
            return false;
    for (int i = 2; i < 4; i++)
        if (id[i] < '0' || id[i] > '9')
            return false;
    return true;
}

int calculateFare(int startStation, int endStation, int stationCount)
{
    int startIndex = startStation - 1;
    int endIndex = endStation - 1;

    if (startStation < 1 || startStation > stationCount)
        return -1;
    if (endStation < 1 || endStation > stationCount)
        return -1;
    if (startStation == endStation)
        return 0;

    int diff = endIndex - startIndex;
    if (diff < 0)
        diff = diff * -1;

    return diff * 40;
}

// ======================= COLORS =======================
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (bgColor * 16));
}

// ======================= PAUSE / CLS =======================
void pause_screen()
{
    cout << "\nPress any key to continue...";
    getch();
}

void clear_screen()
{
    system("cls");
}

// ======================= TABLE HELPERS =======================
void printLine(int w, char ch)
{
    for (int i = 0; i < w; i++)
        cout << ch;
    cout << "\n";
}

void printTableTitle(string title, int width)
{
    setColor(14, 0);
    printLine(width, '=');
    int pad = (width - (int)title.length()) / 2;
    if (pad < 0)
        pad = 0;
    cout << setw(pad) << "" << title << "\n";
    printLine(width, '=');
    setColor(7, 0);
}

// ======================= ADMIN / MANAGER FUNCTIONS =======================
void admin_view_all(string stations[], string station_status[],
                    string manager_names[], string manager_ids[],
                    int stationCount)
{
    const int W = 105;
    printTableTitle("ALL STATIONS OVERVIEW", W);

    setColor(11, 0);
    cout << left
         << setw(6) << "No."
         << setw(28) << "Station"
         << setw(18) << "Status"
         << setw(28) << "Manager"
         << setw(12) << "Manager ID"
         << "\n";
    setColor(7, 0);

    printLine(W);

    for (int i = 0; i < stationCount; i++)
    {
        if (stations[i] == "")
            continue;

        cout << left << setw(6) << (i + 1)
             << setw(28) << stations[i];

        if (station_status[i] == "Active")
            setColor(10, 0);
        else if (station_status[i] == "Under Maintenance")
            setColor(14, 0);
        else
            setColor(12, 0);

        cout << setw(18) << station_status[i];
        setColor(7, 0);

        cout << setw(28) << manager_names[i]
             << setw(12) << manager_ids[i]
             << "\n";
    }

    printLine(W, '=');
}

void update_manager(string stations[], string manager_names[], string manager_ids[], string manager_passwords[])
{
    int n;

    const int W = 95;
    printTableTitle("UPDATE MANAGER INFORMATION", W);

    setColor(11, 0);
    cout << left
         << setw(6) << "No."
         << setw(28) << "Station"
         << setw(22) << "Manager Name"
         << setw(12) << "Manager ID"
         << setw(10) << "Password"
         << "\n";
    setColor(7, 0);

    printLine(W);

    for (int i = 0; i < arrsize; i++)
    {
        if (stations[i] == "")
            continue;

        cout << left
             << setw(6) << (i + 1)
             << setw(28) << stations[i]
             << setw(22) << manager_names[i]
             << setw(12) << manager_ids[i]
             << setw(10) << manager_passwords[i]
             << "\n";
    }
    printLine(W, '=');

    cout << "\nEnter station number to update (1-" << arrsize << "), or 0 to go back: ";
    cin >> n;
    cin.ignore();

    if (n == 0)
        return;
    n = n - 1;

    if (n < 0 || n >= arrsize)
    {
        cout << "Invalid station number!\n";
        return;
    }

    cout << "Enter new name: ";
    getline(cin, manager_names[n]);

    int attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter new password (numeric only): ";
        getline(cin, manager_passwords[n]);

        if (intCheck(manager_passwords[n]))
            break;

        cout << "INVALID! Password must be numeric.\n";
        attempts++;
    }

    if (attempts >= 2)
    {
        cout << "Too many invalid attempts!\n";
        return;
    }

    attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter new manager ID (Format: 2 CAPITALS + 2 DIGITS): ";
        getline(cin, manager_ids[n]);

        if (isValidID(manager_ids[n]))
            break;

        setColor(12, 0);
        cout << "INVALID! Must be 2 capital letters + 2 digits.\n";
        setColor(7, 0);
        attempts++;
    }

    if (attempts >= 2)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts!\n";
        setColor(7, 0);
        return;
    }

    setColor(10, 0);
    cout << "Manager updated successfully!\n";
    setColor(7, 0);
}

void add_manager(string stations[], string manager_names[], string manager_ids[], string manager_passwords[], string station_status[], int &stationCount, int &manager_count)
{
    if (stationCount >= arrsize)
    {
        setColor(12, 0);
        cout << "[STATION STORAGE FULL]\n";
        setColor(7, 0);
        return;
    }

    cout << "===== ADD NEW STATION WITH MANAGER =====\n";

    cout << "Enter station name: ";
    getline(cin, stations[stationCount]);

    cout << "Enter the manager name for this station: ";
    getline(cin, manager_names[stationCount]);

    int attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter manager ID (Format: 2 CAPITALS + 2 DIGITS, e.g., AT11): ";
        getline(cin, manager_ids[stationCount]);

        if (isValidID(manager_ids[stationCount]))
            break;

        setColor(12, 0);
        cout << "INVALID! Must be 2 capital letters + 2 digits.\n";
        setColor(7, 0);
        attempts++;
    }

    if (attempts >= 2)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts! Returning to menu.\n";
        setColor(7, 0);
        return;
    }

    attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter manager password (numeric only): ";
        getline(cin, manager_passwords[stationCount]);

        if (intCheck(manager_passwords[stationCount]))
            break;

        setColor(12, 0);
        cout << "INVALID! Password must contain only numbers.\n";
        setColor(7, 0);
        attempts++;
    }

    if (attempts >= 2)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts! Returning to menu.\n";
        setColor(7, 0);
        return;
    }

    station_status[stationCount] = "Active";
    stationCount++;
    manager_count++;

    setColor(10, 0);
    cout << "\nStation and manager added successfully!\n";
    setColor(7, 0);
}

void remove_manger(string stations[], string manager_names[], string manager_ids[], string manager_passwords[], int &manager_count)
{
    string manager_ID = "";
    bool idFound = false;
    int attempt = 0;
    int deleted_index = 0;

    while (attempt < 3)
    {
        cout << "Enter manager ID to remove (2 CAPITAL + 2 DIGITS): ";
        getline(cin, manager_ID);

        if (!isValidID(manager_ID))
        {
            setColor(12, 0);
            cout << "INVALID! Manager ID must be exactly 4 characters!\n";
            setColor(7, 0);
            attempt++;
        }
        else
            break;
    }

    if (attempt >= 3)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts! Returning to menu.\n";
        setColor(7, 0);
        return;
    }

    for (int x = 0; x < arrsize; x++)
    {
        if (manager_ids[x] == manager_ID)
        {
            idFound = true;
            deleted_index = x;
            break;
        }
    }

    if (idFound)
    {
        setColor(10, 0);
        cout << "Manager removed successfully!\n";
        cout << "Station: " << stations[deleted_index] << "\n";
        cout << "Manager: " << manager_names[deleted_index] << "\n";
        cout << "ID: " << manager_ids[deleted_index] << "\n";
        setColor(7, 0);

        manager_ids[deleted_index] = "VACANT";
        manager_names[deleted_index] = "NO_MANAGER";
        manager_passwords[deleted_index] = "0000";
        manager_count--;

        cout << "\nStation '" << stations[deleted_index] << "' is now VACANT.\n";
    }
    else
    {
        setColor(12, 0);
        cout << "No such ID exists!\n";
        setColor(7, 0);
    }
}

void update_station_status(string stations[], string station_status[])
{
    int id, count = 0, loop = 0;
    cout << "How many stations to deactivate? ";
    cin >> count;

    while (loop < count)
    {
        cout << "Enter station number: ";
        cin >> id;
        id--;
        if (id >= 0 && id < arrsize)
            station_status[id] = "Not Active"; // FIXED CONSISTENCY
        loop++;
    }
    cin.ignore();

    cout << "\nUpdated station statuses:\n";
    for (int x = 0; x < arrsize; x++)
    {
        if (stations[x] == "")
            continue;
        cout << (x + 1) << ". " << stations[x] << " -> " << station_status[x] << "\n";
    }
}

int manager_login(string manager_names[], string manager_ids[], string manager_passwords[], string stations[], int stationCount)
{
    string input_id, input_pass;
    bool verified = false;
    int attempts = 0;

    while (attempts < 3 && !verified)
    {
        cout << "ENTER YOUR MANAGER ID: ";
        getline(cin, input_id);

        cout << "ENTER YOUR PASSWORD: ";
        getline(cin, input_pass);

        int index = -1;
        for (int i = 0; i < stationCount; i++)
        {
            if (manager_ids[i] == input_id)
            {
                index = i;
                break;
            }
        }

        if (index != -1 && manager_passwords[index] == input_pass)
        {
            if (manager_ids[index] == "VACANT" || manager_names[index] == "NO_MANAGER")
            {
                setColor(12, 0);
                cout << "This station currently has no active manager!\n";
                pause_screen();
                setColor(7, 0);
                return -1;
            }

            setColor(10, 0);
            cout << "LOGIN SUCCESSFUL! Welcome " << manager_names[index] << "\n";
            cout << "You are managing: " << stations[index] << " Station\n";
            pause_screen();
            setColor(7, 0);
            return index;
        }
        else
        {
            setColor(12, 0);
            cout << "Incorrect ID or password. Attempts left: " << 2 - attempts << "\n";
            setColor(7, 0);
            attempts++;
        }
    }

    setColor(12, 0);
    cout << "Too many failed attempts! Access denied.\n";
    setColor(7, 0);
    return -1;
}

bool admin_login(string adminName, string adminPass)
{
    string ad_name_input, admin_pas_input;
    int attempts = 0;

    while (attempts < 3)
    {
        cout << "ENTER YOUR NAME IN CAPITAL AND NO SPACE: ";
        getline(cin, ad_name_input);

        if (AllCapitalNoSpace(ad_name_input))
        {
            cout << "ENTER YOUR PASSWORD: ";
            getline(cin, admin_pas_input);

            if (intCheck(admin_pas_input))
            {
                if (ad_name_input == adminName && admin_pas_input == adminPass)
                {
                    setColor(10, 0);
                    cout << "IDENTIFICATION SUCCESSFUL\n";
                    setColor(7, 0);
                    return true;
                }
                else
                {
                    setColor(12, 0);
                    cout << "Wrong username or password. Attempts left: " << (2 - attempts) << "\n";
                    setColor(7, 0);
                    attempts++;
                }
            }
            else
            {
                setColor(12, 0);
                cout << "Invalid! Password must contain only integers.\n";
                setColor(7, 0);
                attempts++;
            }
        }
        else
        {
            setColor(12, 0);
            cout << "Invalid! Name must be all capital letters with no spaces.\n";
            setColor(7, 0);
            attempts++;
        }
    }
    return false;
}

// ======================= MANAGER STATS =======================
void show_passenger_count(int user_count, string userNames[], string userPasswords[], string userIDs[])
{
    cout << "Passenger count today: " << user_count << "\n\n";
    for (int i = 0; i < user_count; i++)
        cout << userNames[i] << "\t" << userPasswords[i] << "\t" << userIDs[i] << "\n";
}

void Total_cards_sold(int stationIndex, int stationStats[][6], string stations[])
{
    cout << "\n===== TOTAL CARDS SOLD TODAY =====\n";
    cout << "Station: " << stations[stationIndex] << "\n";
    cout << "Cards Sold: " << stationStats[stationIndex][2] << "\n";
    cout << "==================================\n";
}

void showTotalRechargedCards(int stationIndex, int stationStats[][6], string stations[])
{
    cout << "\n========================================\n";
    cout << "     TOTAL RECHARGED CARDS TODAY        \n";
    cout << "========================================\n";
    cout << left << setw(20) << "Station:" << stations[stationIndex] << "\n";
    cout << left << setw(20) << "Recharged Cards:" << stationStats[stationIndex][3] << "\n";
    cout << "========================================\n";
}

void Manager_update_station(string stations[], string station_status[], int stationCount, int station_index)
{
    cout << "\n===== UPDATE YOUR STATION STATUS =====\n";
    cout << "Your station: " << stations[station_index] << "\n";
    cout << "Current Status: " << station_status[station_index] << "\n";

    cout << "\n[1] Active\n[2] Not Active\n[3] Under Maintenance\n";
    cout << "\nEnter your choice (1-3): ";

    string choice;
    getline(cin, choice);

    if (choice == "1")
        station_status[station_index] = "Active";
    else if (choice == "2")
        station_status[station_index] = "Not Active";
    else if (choice == "3")
        station_status[station_index] = "Under Maintenance";
    else
    {
        setColor(12, 0);
        cout << "\nInvalid choice! Status not updated.\n";
        setColor(7, 0);
        return;
    }

    setColor(10, 0);
    cout << "\nStation status updated successfully!\n";
    cout << stations[station_index] << " is now: " << station_status[station_index] << "\n";
    setColor(7, 0);
}

void showDailyEarnings(int stationIndex, int stationStats[][6], string stations[])
{
    setColor(0, 14);
    cout << "\n===== DAILY TOTAL EARNINGS =====\n";
    cout << "Station: " << stations[stationIndex] << "\n";
    cout << "Total Earnings: " << stationStats[stationIndex][1] << " PKR\n";
    cout << "================================\n";
    setColor(0, 7);
}

// ======================= EXIT / HEADER =======================
void exit_program()
{
    setColor(0, 11);
    cout << R"(
    ==========================================
    ||                                      ||
    ||   THANK YOU FOR USING ORANGE Train   ||
    ||          HAVE A GREAT DAY!           ||
    ||                                      ||
    ==========================================
    )" << endl;
    setColor(14, 0);
    cout << R"(
          * .  * .   *
       * THANK YOU!    .    *
    .    * EXITING...    * .
          * .  * .   *
    )" << endl;
    setColor(0, 7);
}

void printHeader(string msg)
{
    int width = (int)msg.length() + 6;

    cout << "\n ";
    for (int i = 0; i < width; i++)
        cout << "=";
    cout << "\n";

    cout << " ||  " << msg << "  ||\n";

    cout << " ";
    for (int i = 0; i < width; i++)
        cout << "=";
    cout << "\n\n";
}

// ======================= FILE HANDLING =======================
string loadUserAttribute(string line, int &idx)
{
    string result = "";
    while (idx < (int)line.length() && line[idx] != ';')
    {
        result = result + line[idx];
        idx++;
    }
    idx++;
    return result;
}

void loadUserData(string names[], string passwords[], string ids[], int &count)
{
    fstream file;
    file.open("users.txt", ios::in);

    if (!file)
    {
        count = 0;
        return;
    }

    string line;
    count = 0;

    while (getline(file, line))
    {
        int idx = 0;
        names[count] = loadUserAttribute(line, idx);
        passwords[count] = loadUserAttribute(line, idx);
        ids[count] = loadUserAttribute(line, idx);
        count++;
    }

    file.close();
}

void saveUserData(string name, string password, string id)
{
    fstream file;
    file.open("users.txt", ios::app);

    if (!file)
    {
        setColor(12, 0);
        cout << "Error: Could not save user data!\n";
        setColor(7, 0);
        return;
    }

    file << name << ";" << password << ";" << id << "\n";
    file.close();
}