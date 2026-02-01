#include <iostream>  //for input output
#include <conio.h>   //for getch
#include <windows.h> //for coloring
#include <stdlib.h>  //for system cls
#include <iomanip>   //for setw formatted output
#include <fstream>   //for file handling
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

// =======================  FOR ADMIN =======================//
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
//===========================FOR MANAGER=============================================
void show_passenger_count(int user_count, string userNames[], string userPasswords[], string userIDs[]);
void Total_cards_sold(int stationIndex, int stationStats[][6], string stations[]);
void showTotalRechargedCards(int stationIndex, int stationStats[][6], string stations[]);
void showDailyEarnings(int stationIndex, int stationStats[][6], string stations[]);
void Manager_update_station(string stations[], string station_status[], int stationCount, int stationIndex);
// ======================= VALIDATION FUNCTIONS =======================//
int stringToInt(string s);
bool intCheck(string s);
bool AllCapitalNoSpace(string s);
bool isValidID(string cnic);
void printHeader(string msg);
void clear_screen();
void setColor(int color);
void setColor(int textColor, int bgColor);

// ======================= MAIN =======================//
int main()
{
    // ===== LOCAL ARRAYS =====
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

    // arrsize for future slots
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

    // ===== LOAD USERS FROM FILE =====
    loadUserData(userNames, userPasswords, userIDs, user_count);

    // ===== USER CARD STORAGE (one card per user ID) =====
    string cardUserIDs[user_const];
    int cardBalances[user_const];
    int cardCount = 0;
    int stationStats[arrsize][6] = {0};
    // all columns represent stats and rows are the stations

    int stationCount = 26; // starts with 26 predefined stations
    string admin_name = "HAIDAISLAM";
    string admin_pas = "2007";
    int manager_count = 26;

    // ======================= FLOW LOOP (MAIN MENU REPEATS) =======================
    while (true)
    {
        banner();
        string role = main_menue();

        // EXIT
        if (role == "0")
        {
            exit_program();
            break;
        }

        // ADMIN
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
                getch();
                clear_screen();
                continue;
            }

            while (role_choice != "0")
            {
                if (role_choice == "3")
                {
                    update_manager(stations, manager_names, manager_ids, manager_passwords);
                    clear_screen();
                }

                else if (role_choice == "1")
                {
                    string confirm;
                    cout << "            There are currently " << stationCount << " stations. Do you want to add more?                   " << endl;
                    cout << "Press 1 to confirm: ";
                    getline(cin, confirm);

                    if (confirm == "1")
                    {
                        admin_view_all(stations, station_status, manager_names, manager_ids, stationCount);
                        add_manager(stations, manager_names, manager_ids, manager_passwords, station_status, stationCount, manager_count);
                    }
                    clear_screen();
                }

                else if (role_choice == "2")
                {
                    remove_manger(stations, manager_names, manager_ids, manager_passwords, manager_count);
                    clear_screen();
                }

                else if (role_choice == "4")
                {
                    update_station_status(stations, station_status);
                    clear_screen();
                }
                else
                {
                    printHeader("Wrong choice! Please select a valid option.");
                    getch();
                    clear_screen();
                }

                // Re-display admin menu for next operation
                banner();
                role_choice = admin_menu();
            }
            clear_screen();
        }

        // MANAGER
        else if (role == "2")
        {
            clear_screen();
            banner();
            int managerStationIndex = manager_login(manager_names, manager_ids, manager_passwords, stations, stationCount);

            // If login successful (index >= 0), show manager menu

            if (managerStationIndex >= 0)

            {
                clear_screen();
                banner();
                string role_choice = manager_menu();
                while (role_choice != "0")
                {

                    if (role_choice == "1")
                    {
                        show_passenger_count(user_count, userNames, userPasswords, userIDs);
                        clear_screen();
                    }
                    else if (role_choice == "2")
                    {

                        Total_cards_sold(managerStationIndex, stationStats, stations);
                        clear_screen();
                    }
                    else if (role_choice == "3")
                    {

                        showTotalRechargedCards(managerStationIndex, stationStats, stations);
                        clear_screen();
                    }

                    else if (role_choice == "4")
                    {

                        showDailyEarnings(managerStationIndex, stationStats, stations);
                        clear_screen();
                    }
                    else if (role_choice == "5")
                    {
                        Manager_update_station(stations, station_status, stationCount, managerStationIndex);
                        clear_screen();
                    }
                    else
                    {
                        setColor(12, 0);
                        cout << " invalid input" << endl;
                        setColor(7, 0);
                        getch();
                        clear_screen();
                    }
                    banner();
                    role_choice = manager_menu();
                }
                clear_screen();
                setColor(12, 0);
                cout << "##########################################" << endl;
                cout << "#                                        #" << endl;
                cout << "#  [!] SHUTTING DOWN MANAGER SESSION...  #" << endl;
                cout << "#                                        #" << endl;
                cout << "##########################################" << endl;
                setColor(7, 0);
                getch();
                clear_screen();
            }
        }
        // ======================= USER FLOW =======================
        // USER LOGIN
        else if (role == "3")
        {
            clear_screen();
            banner();
            string loggedUserID = "";

            if (user_login(userNames, userPasswords, userIDs, user_count, loggedUserID))
            {
                clear_screen();
                banner();                    // show banner again
                string choice = user_menu(); // show user menu and take input
                while (choice != "0")
                {
                    if (choice == "1")
                    {
                        viewStations(stations, stationCount);
                        clear_screen();
                    }
                    else if (choice == "2")
                    {
                        viewFares();
                        clear_screen();
                    }
                    else if (choice == "3")
                    {
                        buyToken(stationStats, stationCount);
                        clear_screen();
                    }
                    else if (choice == "4")
                    {
                        viewStationStatus(stations, station_status, stationCount);
                        clear_screen();
                    }
                    else if (choice == "5")
                    {
                        buyNewCard(loggedUserID, cardUserIDs, cardBalances, cardCount, stationStats, stationCount);
                        clear_screen();
                    }
                    else if (choice == "6")
                    {
                        rechargeCard(loggedUserID, cardUserIDs, cardBalances, cardCount, stationStats, stationCount);
                        clear_screen();
                    }
                    else if (choice == "7")
                    {
                        swipeCard(loggedUserID, cardUserIDs, cardBalances, cardCount, stationStats, stationCount);
                        clear_screen();
                    }
                    else
                    {
                        printHeader("INVALID USER MENUE CHOICE PLZ ENTER VALID CHOICE NUMBER...");
                        getch();
                        clear_screen();
                    }
                    banner();
                    choice = user_menu();
                }
                clear_screen();
                printHeader("Logout successful. Returning to main menu...");
                getch();
                clear_screen();
            }
            else
            {
                printHeader(" RETURNING TO MAIN MENUE ");
                getch();
                clear_screen();
            }
        } // USER SIGNUP
        else if (role == "4")
        {
            clear_screen();
            banner();
            bool ok = user_sign_up(userNames, userPasswords, userIDs, user_count);
            if (ok)
            {
                setColor(10, 0);
                cout << "Sign up done. Now login as user from main menu." << endl;
                setColor(7, 0);
            }
            else
            {
                setColor(12, 0);
                cout << "Sign up failed. Try again." << endl;
                setColor(7, 0);
            }
            getch();
            clear_screen();
        }

        else
        {
            setColor(12, 0);
            cout << "\n";
            cout << "+---------------------------------+" << endl;
            cout << "|  ERROR: Invalid Main Menu choice|" << endl;
            cout << "+---------------------------------+" << endl;
            cout << "   Please try again.enter any choice number from 1 to 0\n"
                 << endl;
            setColor(7, 0);
            getch();
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
    cout << "  ========================================================================================= " << endl;
    cout << "       | fast|secure|reliable  ******* 'METRO RAIL MANAGEMENT SYSTEM ' ******               " << endl;
    cout << " =========================================================================================  " << endl;
    setColor(7, 0);
}

string main_menue()
{
    string role;
    setColor(11, 0);
    cout << "\t===========================================" << endl;
    setColor(14, 0);
    cout << "\t||  [1] Login as Admin                   ||" << endl;
    cout << "\t||  [2] Login as Manager                 ||" << endl;
    cout << "\t||  [3] Login as User                    ||" << endl;
    cout << "\t||  [4] sigin up as user                 ||" << endl;
    cout << "\t||  [0] Exit System                      ||" << endl;
    setColor(11, 0);
    cout << "\t===========================================" << endl;
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
    cout << "\n\t  ___________________________________________" << endl;
    cout << "\t [ STATUS: AUTHORIZED SUCCESSFULLY           ]" << endl;
    cout << "\t [ ACCESS LEVEL: SYSTEM ADMINISTRATOR        ]" << endl;
    cout << "\t  -------------------------------------------" << endl;

    setColor(11, 0);
    cout << "\n\t/***********************************************\\" << endl;
    setColor(14, 0);
    cout << "\t|   [1] ADD MANAGER                             |" << endl;
    cout << "\t|   [2] REMOVE MANAGER                          |" << endl;
    cout << "\t|   [3] UPDATE MANAGER                          |" << endl;
    cout << "\t|   [4] UPDATE STATION STATUS                   |" << endl;
    cout << "\t|   [0] BACK TO MAIN MENU                       |" << endl;
    setColor(11, 0);
    cout << "\t\\***********************************************/" << endl;
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
    cout << "\n\t/===============================================\\" << endl;
    cout << "\t|            MANAGER CONTROL PANEL              |" << endl;
    setColor(11, 0);
    cout << "\t|===============================================|" << endl;
    setColor(14, 0);
    cout << "\t|   [1] View Daily Passenger Count              |" << endl;
    cout << "\t|   [2] View Total Cards Sold Today             |" << endl;
    cout << "\t|   [3] View Total Recharged Cards              |" << endl;
    cout << "\t|   [4] View Daily Total Earnings               |" << endl;
    cout << "\t|   [5] Update ur Train Station status          |" << endl;
    cout << "\t|   [0] Logout & Return                         |" << endl;
    setColor(13, 0);
    cout << "\t\\===============================================/" << endl;
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
    cout << "\n\t/===============================================\\" << endl;
    cout << "\t|            ORANGE LINE METRO SYSTEM           |" << endl;
    cout << "\t|                USER DASHBOARD                 |" << endl;
    setColor(11, 0);
    cout << "\t|===============================================|" << endl;
    setColor(10, 0);
    cout << "\t|   [1] View Stations       [2] View Fares      |" << endl;
    cout << "\t|   [3] Buy Token           [4] Station Status  |" << endl;
    cout << "\t|   [5] Buy New Card        [6] Recharge Card   |" << endl;
    cout << "\t|   [7] Swipe Card          [0] Logout          |" << endl;
    setColor(14, 0);
    cout << "\t\\===============================================/" << endl;
    setColor(15, 0);
    cout << "\t number of Selection Choice: ";
    setColor(7, 0);
    getline(cin, user_choice);
    return user_choice;
}

// ======================= USER  FUNCTIONS =======================

void viewStations(string stations[], int stationCount)
{
    cout << "\n===== ORANGE LINE STATIONS =====\n";
    for (int i = 0; i < stationCount; i++)
    {
        if (stations[i] != "")
            cout << i + 1 << ". " << stations[i] << endl;
    }
}

void viewStationStatus(string stations[], string station_status[], int stationCount)
{
    setColor(14, 0);
    cout << "\n========================================================================" << endl;
    cout << "                   STATION STATUS INFORMATION                           " << endl;
    cout << "========================================================================" << endl;
    setColor(11, 0);
    cout << left << setw(8) << "No."
         << setw(35) << "Station Name"
         << setw(20) << "Status" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    setColor(7, 0);

    for (int i = 0; i < stationCount; i++)
    {
        if (stations[i] != "")
        {
            cout << left << setw(8) << (i + 1)
                 << setw(35) << stations[i];

            // Color code the status
            if (station_status[i] == "Active")
            {
                setColor(10, 0); // Green for active
                cout << setw(20) << station_status[i];
                setColor(7, 0);
            }
            else if (station_status[i] == "Under Maintenance")
            {
                setColor(14, 0); // Yellow for maintenance
                cout << setw(20) << station_status[i];
                setColor(7, 0);
            }
            else
            {
                setColor(12, 0); // Red for not active
                cout << setw(20) << station_status[i];
                setColor(7, 0);
            }

            cout << endl;
        }
    }

    setColor(11, 0);
    cout << "========================================================================" << endl;
    setColor(7, 0);
}

void viewFares()
{
    cout << "\n===== FARES =====\n";
    cout << "Token (1 ride): 40 PKR" << endl;
    cout << "Card swipe (1 ride): 40 PKR" << endl;
    cout << "New card fee: 200 PKR" << endl;
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
        cout << "Invalid input. Please enter numbers only." << endl;
        setColor(7, 0);
        return;
    }

    int startStation = stringToInt(Start_station);
    int endStation = stringToInt(End_Station);

    int fare = calculateFare(startStation, endStation, stationCount);

    if (fare == -1)
    {
        setColor(12, 0);
        cout << "Invalid station number." << endl;
        setColor(7, 0);
        return;
    }
    if (fare == 0)
    {
        setColor(12, 0);
        cout << "Start and destination cannot be the same." << endl;
        setColor(7, 0);
        return;
    }

    // Update stats for the STARTING station
    int stationIndex = startStation - 1;                                  // Convert 1-based to 0-based index
    stationStats[stationIndex][0] = stationStats[stationIndex][0] + 1;    // Increment tokensSold (column 0)
    stationStats[stationIndex][1] = stationStats[stationIndex][1] + fare; // Add to totalEarning (column 1)

    setColor(10, 0); // Green for success
    cout << "Token purchased successfully." << endl;
    cout << "Total Fare: " << fare << " PKR" << endl;
    setColor(7, 0);
}

int findCardIndex(string cardUserIDs[], int cardCount, string userID)
{
    for (int i = 0; i < cardCount; i++)
    {
        if (cardUserIDs[i] == userID)
            return i;
    }
    return -1;
}

void buyNewCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int &cardCount, int stationStats[][6], int stationCount)
{
    int card_index = findCardIndex(cardUserIDs, cardCount, loggedUserID);
    if (card_index != -1)
    {
        setColor(12, 0);
        cout << "You already have a card." << endl;
        setColor(7, 0);
        return;
    }

    if (cardCount >= user_const)
    {
        setColor(12, 0);
        cout << "Card storage full." << endl;
        setColor(7, 0);
        return;
    }

    // Ask user which station they're buying from
    string stationStr;
    cout << "Enter your current station number (1-" << stationCount << "): ";
    getline(cin, stationStr);

    if (!intCheck(stationStr))
    {
        setColor(12, 0);
        cout << "Invalid station number." << endl;
        setColor(7, 0);
        return;
    }

    int station = stringToInt(stationStr);
    if (station < 1 || station > stationCount)
    {
        setColor(12, 0);
        cout << "Invalid station number." << endl;
        setColor(7, 0);
        return;
    }

    cardUserIDs[cardCount] = loggedUserID;
    cardBalances[cardCount] = 0;
    cardCount++;

    // Update stats for this station
    int stationIndex = station - 1;
    stationStats[stationIndex][2] = stationStats[stationIndex][2] + 1;   // Increment cardsSold (column 2)
    stationStats[stationIndex][1] = stationStats[stationIndex][1] + 200; // Add 200 to earnings (column 1)

    setColor(10, 0); // Green for success
    cout << "New card created successfully. Fee: 200 PKR" << endl;
    setColor(7, 0);
}

void rechargeCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int cardCount, int stationStats[][6], int stationCount)
{
    int card_index = findCardIndex(cardUserIDs, cardCount, loggedUserID);
    if (card_index == -1)
    {
        setColor(12, 0);
        cout << "You do not have a card. Buy a new card first." << endl;
        setColor(7, 0);
        return;
    }

    // Ask user which station they're recharging at
    string stationStr;
    cout << "Enter your current station number (1-" << stationCount << "): ";
    getline(cin, stationStr);

    if (!intCheck(stationStr))
    {
        setColor(12, 0);
        cout << "Invalid station number." << endl;
        setColor(7, 0);
        return;
    }

    int station = stringToInt(stationStr);
    if (station < 1 || station > stationCount)
    {
        setColor(12, 0);
        cout << "Invalid station number." << endl;
        setColor(7, 0);
        return;
    }

    string recharge_Amount;
    cout << "Enter recharge amount: ";
    getline(cin, recharge_Amount);

    if (!intCheck(recharge_Amount))
    {
        setColor(12, 0);
        cout << "Invalid amount. plz enter integer" << endl;
        setColor(7, 0);
        return;
    }

    int amount_int = stringToInt(recharge_Amount);
    if (amount_int <= 0)
    {
        setColor(12, 0);
        cout << "Invalid amount." << endl;
        setColor(7, 0);
        return;
    }

    cardBalances[card_index] = cardBalances[card_index] + amount_int;

    // Update stats for this station
    int stationIndex = station - 1;
    stationStats[stationIndex][3] = stationStats[stationIndex][3] + 1;          // Increment rechargeCount (column 3)
    stationStats[stationIndex][1] = stationStats[stationIndex][1] + amount_int; // Add amount to earnings (column 1)

    setColor(10, 0); // Green for success
    cout << "Recharge successful. New balance: " << cardBalances[card_index] << " PKR" << endl;
    setColor(7, 0);
}

void swipeCard(string loggedUserID, string cardUserIDs[], int cardBalances[], int cardCount, int stationStats[][6], int stationCount)
{
    int card_index = findCardIndex(cardUserIDs, cardCount, loggedUserID);
    if (card_index == -1)
    {
        setColor(12, 0);
        cout << "You do not have a card. Buy a new card first." << endl;
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
        cout << "Invalid input. Please enter numbers only." << endl;
        setColor(7, 0);
        return;
    }

    int startStation = stringToInt(Start_station);
    int endStation = stringToInt(End_Station);

    int fare = calculateFare(startStation, endStation, stationCount);

    if (fare == -1)
    {
        setColor(12, 0);
        cout << "Invalid station number." << endl;
        setColor(7, 0);
        return;
    }
    if (fare == 0)
    {
        setColor(12, 0);
        cout << "Start and destination cannot be the same." << endl;
        setColor(7, 0);
        return;
    }

    if (cardBalances[card_index] >= fare)
    {
        cardBalances[card_index] = cardBalances[card_index] - fare;

        // Update stats for the STARTING station
        int stationIndex = startStation - 1;
        stationStats[stationIndex][5] = stationStats[stationIndex][5] + 1;    // Increment swipeCount (column 5)
        stationStats[stationIndex][1] = stationStats[stationIndex][1] + fare; // Add fare to earnings (column 1)

        setColor(10, 0); // Green for success
        cout << "Swipe successful. Fare deducted: " << fare << " PKR" << endl;
        cout << "Remaining balance: " << cardBalances[card_index] << " PKR" << endl;
        setColor(7, 0);
    }
    else
    {
        setColor(12, 0);
        cout << "Insufficient balance. Please recharge." << endl;
        cout << "Your balance: " << cardBalances[card_index] << " PKR" << endl;
        cout << "Required fare: " << fare << " PKR" << endl;
        setColor(7, 0);
    }
}

// ======================= USER LOGIN/SIGNUP =======================
bool user_sign_up(string userNames[], string userPasswords[], string userIDs[], int &user_count)
{
    string user_name, user_ID, user_password;
    int user_attempts = 0;
    cout << "enter your name: ";
    getline(cin, user_name);
    while (user_attempts < 3)
    {
        cout << "enter your password: ";
        getline(cin, user_password);
        if (intCheck(user_password))
        {
            break; // Valid password
        }
        setColor(12, 0);
        cout << "Password should only contain integers!!!!!!" << endl;
        setColor(7, 0);
        user_attempts++;
    }
    if (user_attempts >= 3 && !intCheck(user_password))
    {
        setColor(12, 0);
        cout << "Too many invalid attempts!" << endl;
        setColor(7, 0);
        return false;
    }

    setColor(10, 0); // Green for success
    cout << "correct password" << endl;
    setColor(7, 0);
    cout << "enter your ID: ";
    getline(cin, user_ID);

    for (int i = 0; i < user_count; i++)
    {
        if (userIDs[i] == user_ID)
        {
            setColor(12, 0);
            cout << "User Already Present" << endl;
            setColor(7, 0);
            return false;
        }
    }

    if (user_count < user_const)
    {
        userNames[user_count] = user_name;
        userPasswords[user_count] = user_password;
        userIDs[user_count] = user_ID;
        user_count++;

        // Save user to file
        saveUserData(user_name, user_password, user_ID);

        setColor(10, 0); // Green for success
        cout << "Sign up successful." << endl;
        setColor(7, 0);
        return true;
    }

    setColor(12, 0);
    cout << "User storage full." << endl;
    setColor(7, 0);
    return false;
}

bool user_login(string userNames[], string userPasswords[], string userIDs[], int user_count, string &loggedUserID)
{
    string userinput_ID, userinput_password;

    cout << "enter your ID: ";
    getline(cin, userinput_ID);

    cout << "enter your password: ";
    getline(cin, userinput_password);

    for (int i = 0; i < user_count; i++)
    {
        if (userIDs[i] == userinput_ID && userPasswords[i] == userinput_password)
        {
            loggedUserID = userIDs[i];
            setColor(10, 0); // Green for success
            cout << "login successful" << endl;
            setColor(7, 0);
            return true;
        }
    }

    setColor(12, 0);
    cout << "login unsuccesful, id and password dont exist" << endl;
    setColor(7, 0);
    return false;
}

// =======================  HELPERS AND VALIDATIONS (getline numbers) =======================
bool intCheck(string s)
{
    if (s.length() == 0)
        return false;
    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
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
        return false; // Empty string is not all capital

    for (int i = 0; i < (int)s.length(); i++)
    {
        if (s[i] < 'A' || s[i] > 'Z')
            return false; // Not a capital letter
    }
    return true;
}
bool isValidID(string id)
{
    // Check length is exactly 4
    if (id.length() != 4)
        return false;

    // Check first 2 characters are capital letters (A-Z)
    for (int i = 0; i < 2; i++)
    {
        if (id[i] < 'A' || id[i] > 'Z') // Check if NOT capital letter
            return false;
    }

    // Check last 2 characters are digits (0-9)
    for (int i = 2; i < 4; i++)
    {
        if (id[i] < '0' || id[i] > '9') // Check if NOT digit
            return false;
    }

    return true;
}
int calculateFare(int startStation, int endStation, int stationCount)
{
    int startIndex = startStation - 1;
    int endIndex = endStation - 1;

    // validation
    if (startStation < 1 || startStation > stationCount)
        return -1;
    if (endStation < 1 || endStation > stationCount)
        return -1;
    if (startStation == endStation)
        return 0;

    int diff = endIndex - startIndex;
    if (diff < 0)
        diff = diff * -1; // always positive

    return diff * 40;
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (bgColor * 16));
}

// =======================  ORIGINAL ADMIN/MANAGER FUNCTIONS =======================
void admin_view_all(string stations[], string station_status[],
                    string manager_names[], string manager_ids[],
                    int stationCount)
{
    cout << left
         << setw(8) << "INDEX"
         << setw(25) << "STATION"
         << setw(15) << "STATUS"
         << setw(20) << "MANAGER"
         << setw(12) << "MANAGER ID" << endl;
    cout << "-----------------------------------------------------------------------------------------\n";
    for (int i = 0; i < stationCount; i++)
    {
        cout << left
             << setw(8) << (i + 1)
             << setw(25) << stations[i]
             << setw(15) << station_status[i]
             << setw(20) << manager_names[i]
             << setw(12) << manager_ids[i]
             << endl;
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}
void update_manager(string stations[], string manager_names[], string manager_ids[], string manager_passwords[])
{
    int n;

    // Display header
    setColor(14, 0);
    cout << "\n============================================================================" << endl;
    cout << "                        UPDATE MANAGER INFORMATION                          " << endl;
    cout << "============================================================================" << endl;
    setColor(11, 0);
    cout << left << setw(8) << "No."
         << setw(30) << "Station"
         << setw(20) << "Manager Name"
         << setw(12) << "Manager ID"
         << setw(10) << "Password" << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    setColor(7, 0);

    // Display all managers
    for (int i = 0; i < arrsize; i++)
    {
        cout << left << setw(8) << i
             << setw(30) << stations[i]
             << setw(20) << manager_names[i]
             << setw(12) << manager_ids[i]
             << setw(10) << manager_passwords[i] << endl;
    }

    setColor(11, 0);
    cout << "============================================================================" << endl;
    setColor(7, 0);

    cout << "\nEnter station number to update" << endl;
    cout << "or enter -1 to go back" << endl;
    cout << "Your choice: ";
    cin >> n;
    cin.ignore();

    if (n == -1)
    {
        return;
    }

    if (n < 0 || n >= arrsize)
    {
        cout << "Invalid station number!" << endl;
        return;
    }

    cout << "Enter new name" << endl;
    getline(cin, manager_names[n]);

    // Validate new password with 2 attempts
    int attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter new password (numeric only): ";
        getline(cin, manager_passwords[n]);

        if (intCheck(manager_passwords[n]))
        {
            break;
        }

        cout << "INVALID! Password must be numeric." << endl;
        attempts++;
        if (attempts < 2)
        {
            cout << "Attempts left: " << (2 - attempts) << endl;
        }
    }

    if (attempts >= 2)
    {
        cout << "Too many invalid attempts!" << endl;
        return;
    }

    // Validate new manager ID with 2 attempts
    attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter new manager ID (Format: 2 CAPITALS + 2 DIGITS): ";
        getline(cin, manager_ids[n]);

        if (isValidID(manager_ids[n]))
        {
            break;
        }

        setColor(12, 0);
        cout << "INVALID! Must be 2 capital letters + 2 digits." << endl;
        setColor(7, 0);
        attempts++;
        if (attempts < 2)
        {
            cout << "Attempts left: " << (2 - attempts) << endl;
        }
    }

    if (attempts >= 2)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts!" << endl;
        setColor(7, 0);
        return;
    }

    setColor(10, 0);
    cout << "Manager updated successfully!" << endl;
    setColor(7, 0);
}

void add_manager(string stations[], string manager_names[], string manager_ids[], string manager_passwords[], string station_status[], int &stationCount, int &manager_count)
{
    if (stationCount >= arrsize)
    {
        setColor(12, 0);
        cout << "[STATION STORAGE FULL]" << endl;
        setColor(7, 0);
        return;
    }

    cout << "===== ADD NEW STATION WITH MANAGER =====" << endl;

    cout << "Enter station name: ";
    getline(cin, stations[stationCount]);

    cout << "Enter the manager name for this station: ";
    getline(cin, manager_names[stationCount]);

    // Validate manager ID with 2 attempts
    int attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter manager ID (Format: 2 CAPITALS + 2 DIGITS, e.g., AT11): ";
        getline(cin, manager_ids[stationCount]);

        if (isValidID(manager_ids[stationCount]))
        {
            break;
        }

        setColor(12, 0);
        cout << "INVALID! Must be 2 capital letters + 2 digits." << endl;
        setColor(7, 0);
        attempts++;
        if (attempts < 2)
        {
            cout << "Attempts left: " << (2 - attempts) << endl;
        }
    }

    if (attempts >= 2)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts! Returning to menu." << endl;
        setColor(7, 0);
        return;
    }

    attempts = 0;
    while (attempts < 2)
    {
        cout << "Enter manager password (numeric only): ";
        getline(cin, manager_passwords[stationCount]);

        if (intCheck(manager_passwords[stationCount]))
        {
            break;
        }

        setColor(12, 0);
        cout << "INVALID! Password must contain only numbers." << endl;
        setColor(7, 0);
        attempts++;
        if (attempts < 2)
        {
            cout << "Attempts left: " << (2 - attempts) << endl;
        }
    }

    if (attempts >= 2)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts! Returning to menu." << endl;
        setColor(7, 0);
        return;
    }

    station_status[stationCount] = "Active";

    stationCount++;
    manager_count++;

    setColor(10, 0);
    cout << "\n========================================" << endl;
    cout << "Station and manager added successfully!" << endl;
    cout << "========================================" << endl;
    setColor(7, 0);

    int lastIndex = stationCount - 1;
    cout << "Station: " << stations[lastIndex] << endl;
    cout << "Manager: " << manager_names[lastIndex] << endl;
    cout << "ID: " << manager_ids[lastIndex] << endl;
    cout << "Status: " << station_status[lastIndex] << endl;
    cout << "========================================" << endl;
}

void remove_manger(string stations[], string manager_names[], string manager_ids[], string manager_passwords[], int &manager_count)
{
    string manager_ID = "";
    bool idFound = false;
    int attempt = 0;
    int deleted_index = 0;

    while (attempt < 3)
    {
        cout << "Enter manager ID to remove: " << endl;
        cout << "FORMAT MUST BE 2 CAPITAL ALPHABETS AND LAST 2 DIGITS TOTAL LENGTH 4" << endl;
        getline(cin, manager_ID);

        if (!isValidID(manager_ID))
        {
            setColor(12, 0);
            cout << "INVALID! Manager ID must be exactly 4 characters!" << endl;
            setColor(7, 0);
            cout << "Attempts left: " << (2 - attempt) << endl;
            attempt++;
        }
        else
        {
            break;
        }
    }

    if (attempt >= 3)
    {
        setColor(12, 0);
        cout << "Too many invalid attempts! Returning to menu." << endl;
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
        cout << "========================================" << endl;
        cout << "Manager removed successfully!" << endl;
        cout << "Station: " << stations[deleted_index] << endl;
        cout << "Manager: " << manager_names[deleted_index] << endl;
        cout << "ID: " << manager_ids[deleted_index] << endl;
        cout << "========================================" << endl;
        setColor(7, 0);

        manager_ids[deleted_index] = "VACANT";
        manager_names[deleted_index] = "NO_MANAGER";
        manager_passwords[deleted_index] = "0000";
        manager_count--;

        cout << "\nStation '" << stations[deleted_index] << "' is now VACANT." << endl;
        cout << "Use 'UPDATE MANAGER' option to assign a new manager to this station." << endl;
    }
    else
    {
        setColor(12, 0);
        cout << "NO such ID exists!" << endl;
        setColor(7, 0);
    }
}

void update_station_status(string stations[], string station_status[])
{
    int id, count = 0, loop = 0;
    cout << "how many stations to deactivate? ";
    cin >> count;

    while (loop < count)
    {
        cout << "enter station number: ";
        cin >> id;
        id--;
        if (id >= 0 && id < arrsize)
            station_status[id] = "NOT ACTIVE";
        loop++;
    }
    cin.ignore();

    for (int x = 0; x < arrsize; x++)
        cout << stations[x] << "\t" << station_status[x] << endl;
}

int manager_login(string manager_names[], string manager_ids[], string manager_passwords[], string stations[], int stationCount)
{
    // Returns the station index (0-29) if login successful, -1 if failed
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
                cout << "This station currently has no active manager!" << endl;
                cout << "Contact admin to be assigned to this station." << endl;
                setColor(7, 0);
                return -1;
            }

            setColor(10, 0);
            cout << "LOGIN SUCCESSFUL! Welcome " << manager_names[index] << endl;
            cout << "You are managing: " << stations[index] << " Station" << endl;
            setColor(7, 0);
            return index;
        }
        else
        {
            setColor(12, 0);
            cout << "Incorrect ID or password. Attempts left: " << 2 - attempts << endl;
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
                    cout << "Wrong username or password. Attempts left: " << (2 - attempts) << endl;
                    setColor(7, 0);
                    attempts++;
                }
            }
            else
            {
                setColor(12, 0);
                cout << "Invalid! Password must contain only integers." << endl;
                setColor(7, 0);
                cout << "Attempts left: " << (2 - attempts) << endl;
                attempts++;
            }
        }
        else
        {
            setColor(12, 0);
            cout << "Invalid! Name must be all capital letters with no spaces." << endl;
            setColor(7, 0);
            cout << "Attempts left: " << (2 - attempts) << endl;
            attempts++;
        }
    }
    return false;
}
// manager functions definitiom
void show_passenger_count(int user_count, string userNames[], string userPasswords[], string userIDs[])
{
    cout << "the passenger count of today is:............" << user_count << endl;
    for (int i = 0; i < user_count; i++)
    {
        cout << userNames[i] << "\t" << userPasswords[i] << "\t" << userIDs[i] << endl;
    }
}
void Total_cards_sold(int stationIndex, int stationStats[][6], string stations[])
{
    // stationStats[stationIndex][2] = cardsSold column for this station
    cout << "\n===== TOTAL CARDS SOLD TODAY =====\n";
    cout << "Station: " << stations[stationIndex] << endl;
    cout << "Cards Sold: " << stationStats[stationIndex][2] << endl;
    cout << "==================================\n";
}
void showTotalRechargedCards(int stationIndex, int stationStats[][6], string stations[])
{
    // Display recharge count at THIS manager's station only
    // stationStats[stationIndex][3] = rechargeCount column for this station
    cout << "\n========================================\n";
    cout << "     TOTAL RECHARGED CARDS TODAY        \n";
    cout << "========================================\n";

    cout << left << setw(20) << "Station:"
         << stations[stationIndex] << endl;

    cout << left << setw(20) << "Recharged Cards:"
         << stationStats[stationIndex][3] << endl;

    cout << "========================================\n";
}
void Manager_update_station(string stations[], string station_status[], int stationCount, int station_index)
{
    cout << "\n===== UPDATE YOUR STATION STATUS =====\n";
    cout << "Your station: " << stations[station_index] << endl;
    cout << "Current Status: " << station_status[station_index] << endl;

    cout << "\n[1] Active\n";
    cout << "[2] Not Active\n";
    cout << "[3] Under Maintenance\n";
    cout << "\nEnter your choice (1-3): ";

    string choice;
    getline(cin, choice);

    if (choice == "1")
    {
        station_status[station_index] = "Active";
    }
    else if (choice == "2")
    {
        station_status[station_index] = "Not Active";
    }
    else if (choice == "3")
    {
        station_status[station_index] = "Under Maintenance";
    }
    else
    {
        setColor(12, 0);
        cout << "\nInvalid choice! Status not updated." << endl;
        setColor(7, 0);
        return;
    }

    setColor(10, 0);
    cout << "\nStation status updated successfully!" << endl;
    cout << stations[station_index] << " is now: "
         << station_status[station_index] << endl;
    setColor(7, 0);
}
void showDailyEarnings(int stationIndex, int stationStats[][6], string stations[])
{
    // Display earnings at THIS manager's station only
    // stationStats[stationIndex][1] = totalEarning column for this station
    setColor(0, 14);
    cout << "\n===== DAILY TOTAL EARNINGS =====\n";
    cout << "Station:" << setw(10) << stations[stationIndex] << endl;
    cout << "Total Earnings:" << setw(10) << stationStats[stationIndex][1] << " PKR" << endl;
    cout << "================================\n";
    setColor(0, 7);
}
void exit_program()
{
    setColor(0, 11);
    cout << R"(
    ==========================================
    ||                                      ||
    ||   THANK YOU FOR USING ORANGE Train   ||
    ||          HAVE A GREAT DAY!           ||
    ||                                      ||
    ||                                      ||
    =========================================
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

void clear_screen()
{
    cout << "press any key to continue" << endl;
    getch();
    system("cls");
}
void printHeader(string msg)
{

    int width = msg.length() + 6;

    cout << "\n ";
    for (int i = 0; i < width; i++)
        cout << "=";
    cout << endl;

    cout << " ||  " << msg << "  ||" << endl;

    cout << " ";
    for (int i = 0; i < width; i++)
        cout << "=";
    cout << "\n"
         << endl;
}

// ======================= FILE HANDLING FUNCTIONS =======================

string loadUserAttribute(string line, int &idx)
{
    string result = "";

    // Read characters until we hit a semicolon or end of line
    while (idx < line.length() && line[idx] != ';')
    {
        result = result + line[idx];
        idx++;
    }

    idx++; // Skip the semicolon
    return result;
}

// Load all users from file when program starts
void loadUserData(string names[], string passwords[], string ids[], int &count)
{
    fstream file;
    file.open("users.txt", ios::in); // Open for READING

    // Check if file exists
    if (!file)
    {
        // File doesn't exist yet (first time running program)
        count = 0;
        return;
    }

    string line;
    count = 0;

    // Read each line from the file
    while (getline(file, line))
    {
        int idx = 0;

        // Parse the line: name;password;id
        names[count] = loadUserAttribute(line, idx);
        passwords[count] = loadUserAttribute(line, idx);
        ids[count] = loadUserAttribute(line, idx);

        count++;
    }

    file.close();
}

// Save one new user to file when they sign up
void saveUserData(string name, string password, string id)
{
    fstream file;
    file.open("users.txt", ios::app); // Open for APPENDING

    // Check if file opened successfully
    if (!file)
    {
        setColor(12, 0);
        cout << "Error: Could not save user data!" << endl;
        setColor(7, 0);
        return;
    }

    // Write one line: name;password;id
    file << name << ";" << password << ";" << id << endl;

    file.close();
}