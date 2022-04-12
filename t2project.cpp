// سیدمصطفی سجادی نسب
// 4001231060
// https://github.com/mim-s/forUniv

#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

enum os
{
    IOS = 1,
    Android,
    WindowsPhone
};
enum ram
{
    GB2 = 2,
    GB4 = 4,
    GB6 = 6,
    GB8 = 8,
    GB12 = 12,
    GB16 = 16,
    GB32 = 32,
    GB64 = 64
};
enum storage
{
    _16GB = 16,
    _32GB = 32,
    _64GB = 64,
    _128GB = 128,
    _256GB = 256,
    _512GB = 512,
    _1TB = 1,
    _2TB = 2
};
enum color
{
    black = 1,
    white,
    blue
};
struct mobile
{
    string name,
        companyName;
    long long int price;
    int numOfAvailabes,
        numOfSales;
    os os;
    ram ram;
    storage storage;
    color color;
};

void getNewPhoneInfo(mobile &);
void addPhone(mobile, mobile *&, int &);
void addPhone(string, string, int, mobile *, int);
int search(string, string, mobile *, int);
void sortByPrice(mobile *, int);
void printPhonesSortedByTheMostSold(mobile *, int);
void printPhones(mobile *, int);
void printPhoneInfo(mobile);
void sellPhone(string, string, mobile *, int);
void editPhoneInfo(string, string, mobile *, int);
void removePhone(int, mobile *&, int &);
void readFile(mobile *, int);
void writeFile(mobile *, int);
vector<string> splitString(string);
void trim(string &);
string lowerWord(string);

int main()
{
    system("cls");
    int mainMenuOption;

    cout << "Welcome";
    for (int i = 0; i < 3; i++)
    {
        Sleep(400);
        cout << '.';
    }
    Sleep(700);

    int len = 0;
    ifstream fin("t2ProjectFile.txt");
    if (fin.good())
    {
        fin >> len;
    }
    fin.close();

    mobile *mobiles = new mobile[len];
    readFile(mobiles, len);

    do
    {
        system("cls");
        cout << "Main Menu\n\n"
                "1: Add a phone\n"
                "2: Remove a phone\n"
                "3: Sort phones by price\n"
                "4: Search a phone\n"
                "5: Change mobiles info\n"
                "6: Sell a phone\n"
                "7: Print phones\n"
                "8: Print phones sorted by the most sold to the least\n"
                "0: Exit program\n"
                "\nselect an option: ";
        cin >> mainMenuOption;

        if (mainMenuOption == 1)
        {
            system("cls");
            string mobileName,
                cmpnyName;
            int mobileIndex;

            cout << "Adding Phone\n\n"
                    "Enter the phone name: ";
            cin.ignore();
            getline(cin, mobileName);
            trim(mobileName);
            cout << "Enter the phone company name: ";
            getline(cin, cmpnyName);
            trim(cmpnyName);

            mobileIndex = search(mobileName, cmpnyName, mobiles, len);

            if (mobileIndex == -1)
            {
                mobile newMobile;
                newMobile.name = mobileName;
                newMobile.companyName = cmpnyName;
                getNewPhoneInfo(newMobile);
                addPhone(newMobile, mobiles, len);
                cout << "\nThe phone was successfully added.\n\n";
            }
            else
            {
                int addedNum;
                cout << "Enter the number added to the phone inventory: ";
                cin >> addedNum;
                mobiles[mobileIndex].numOfAvailabes += addedNum;
                cout << '\n';
                if (addedNum == 1)
                {
                    cout << "A \"" << mobiles[mobileIndex].name << "\" mobile phone was successfully added.\n\n";
                }
                else
                {
                    cout << addedNum << " \"" << mobiles[mobileIndex].name << "\" phones were successfully added.\n\n";
                }
            }
            cout << "Press any key to go back to main menu.";
            getch();
        }
        else if (mainMenuOption == 2)
        {
            system("cls");
            string mobileName,
                cmpnyName;
            int mobileIndex;
            cout << "Removing Phone\n\n"
                    "Enter the phone name: ";
            cin.ignore();
            getline(cin, mobileName);
            trim(mobileName);
            cout << "Enter the phone company name: ";
            getline(cin, cmpnyName);
            trim(cmpnyName);

            mobileIndex = search(mobileName, cmpnyName, mobiles, len);
            removePhone(mobileIndex, mobiles, len);
        }
        else if (mainMenuOption == 3)
        {
            system("cls");
            sortByPrice(mobiles, len);
            cout << "The phones were successfully sorted by price.\n\n"
                    "Press any key to go back to main menu.";
            getch();
        }
        else if (mainMenuOption == 4)
        {
            system("cls");
            string mobileName,
                cmpnyName;
            int mobileIndex;
            cout << "Searching Phone\n\n"
                    "Enter the phone name: ";
            cin.ignore();
            getline(cin, mobileName);
            trim(mobileName);
            cout << "Enter the phone company name: ";
            getline(cin, cmpnyName);
            trim(cmpnyName);
            mobileIndex = search(mobileName, cmpnyName, mobiles, len);
            if (mobileIndex == -1)
            {
                cout << "\nThere is no such mobile phone!";
            }
            else
            {
                system("cls");
                printPhoneInfo(mobiles[mobileIndex]);
            }
            cout << "\nPress any key to go back to main menu.";
            getch();
        }
        else if (mainMenuOption == 5)
        {
            system("cls");
            string mobileName,
                cmpnyName;
            int mobileIndex;
            cout << "Editing Phone\n\n"
                    "Enter the phone name: ";
            cin.ignore();
            getline(cin, mobileName);
            trim(mobileName);
            cout << "Enter the phone company name: ";
            getline(cin, cmpnyName);
            trim(cmpnyName);
            editPhoneInfo(mobileName, cmpnyName, mobiles, len);
        }
        else if (mainMenuOption == 6)
        {
            system("cls");
            string mobileName,
                cmpnyName;

            cout << "Selling Phone\n\n"
                    "Enter the phone name: ";
            cin.ignore();
            getline(cin, mobileName);
            trim(mobileName);
            cout << "Enter the phone company name: ";
            getline(cin, cmpnyName);
            trim(cmpnyName);

            sellPhone(mobileName, cmpnyName, mobiles, len);
        }
        else if (mainMenuOption == 7)
        {
            printPhones(mobiles, len);
            cout << '\n';
        }
        else if (mainMenuOption == 8)
        {
            printPhonesSortedByTheMostSold(mobiles, len);
        }
        else if (mainMenuOption != 0)
        {
            cout << '\n'
                 << mainMenuOption << "?? Am I a joke to you???\n\n";
        }
    } while (mainMenuOption != 0);

    writeFile(mobiles, len);
    delete[] mobiles;

    cout << "\nGoodbye!";
    getch();
    return 0;
}
void getNewPhoneInfo(mobile &mob)
{
    int operatingS,
        mobRam,
        mobStorage,
        mobColor;
    cout << "1: IOS\n2: Android\n3: Windows Phone\nSelect the phone OS: ";
    cin >> operatingS;
    mob.os = os(operatingS);
    cout << "2: 2GB\n4: 4GB\n6: 6GB\n8: 8GB\n12: 12GB\n16: 16GB\n32: 32GB\n64: 64GB\nSelect the phone ram: ";
    cin >> mobRam;
    mob.ram = ram(mobRam);
    cout << "16: 16GB\n32: 32GB\n64: 64GB\n128: 128GB\n256: 256GB\n512: 512GB\n1: 1TB\n2: 2Tb\nSelect the phone storage: ";
    cin >> mobStorage;
    mob.storage = storage(mobStorage);
    cout << "1: Black\n2: White\n3: Blue\nSelect the phone color: ";
    cin >> mobColor;
    mob.color = color(mobColor);
    cout << "Enter the phone price: ";
    cin >> mob.price;
    cout << "Enter the number of the mobile sold: ";
    cin >> mob.numOfSales;
    cout << "Enter the number of availabe phones: ";
    cin >> mob.numOfAvailabes;
}
void addPhone(mobile mob, mobile *&mobiles, int &len)
{
    mobile *temp = new mobile[len + 1];
    for (int i = 0; i < len; i++)
    {
        temp[i] = mobiles[i];
    }
    temp[len++] = mob;
    delete[] mobiles;
    mobiles = temp;
}
void addPhone(string mob, string cmpnyName, int news, mobile *mobiles, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (lowerWord(mob) == lowerWord(mobiles[i].name) && lowerWord(cmpnyName) == lowerWord(mobiles[i].companyName))
        {
            mobiles[i].numOfAvailabes += news;
            cout << '\n';
            if (news == 1)
            {
                cout << "A \"" << mobiles[i].name << "\" mobile phone was successfully added.\n\n";
            }
            else
            {
                cout << news << " \"" << mobiles[i].name << "\" phones were successfully added.\n\n";
            }
            cout << "Press any key to go back to main menu";
            getch();
            break;
        }
    }
}
int search(string mobileName, string cmpnyName, mobile *mobiles, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (lowerWord(mobileName) == lowerWord(mobiles[i].name) && lowerWord(cmpnyName) == lowerWord(mobiles[i].companyName))
        {
            return i;
        }
    }
    return -1;
}
void sortByPrice(mobile *mobiles, int len)
{
    for (int i = (len - 1); i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (mobiles[j].price > mobiles[j + 1].price)
            {
                swap(mobiles[j], mobiles[j + 1]);
            }
        }
    }
}
void printPhonesSortedByTheMostSold(mobile *mobiles, int len)
{
    mobile *tempMobiles = new mobile[len];
    for (int i = 0; i < len; i++)
    {
        tempMobiles[i] = mobiles[i];
    }

    for (int i = (len - 1); i > 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            if (tempMobiles[j].numOfSales < tempMobiles[j + 1].numOfSales)
            {
                swap(tempMobiles[j], tempMobiles[j + 1]);
            }
        }
    }
    printPhones(tempMobiles, len);
}
void printPhones(mobile *mobiles, int len)
{
    system("cls");
    cout << "Mobile Phones List\n\n\n";
    for (int i = 0; i < len; i++)
    {
        printPhoneInfo(mobiles[i]);
    }
    cout << "\nPress any key to go back to main menu.";
    getch();
}
void printPhoneInfo(mobile mob)
{
    string r,
        s,
        os,
        c;
    r = to_string(mob.ram) + "GB";
    if (mob.storage > 2)
    {
        s = to_string(mob.storage) + "GB";
    }
    else
    {
        s = to_string(mob.storage) + "TR";
    }
    if (mob.os == 1)
    {
        os = "IOS";
    }
    else if (mob.os == 2)
    {
        os = "Android";
    }
    else
    {
        os = "Windows Phone";
    }
    if (mob.color == 1)
    {
        c = "Black";
    }
    else if (mob.color == 2)
    {
        c = "White";
    }
    else
    {
        c = "Blue";
    }

    cout << "name: " << mob.name << "\nCompany: " << mob.companyName << "\nColor: " << c << "\nOS: " << os << "\nRam: " << r << "\nStorage: " << s << "\nPrice: " << mob.price << "\nNumber of sold: " << mob.numOfSales << "\nNumber of availabes: " << mob.numOfAvailabes << "\n\n";
}
void sellPhone(string mobileName, string cmpnyName, mobile *mobiles, int len)
{
    int mobileIndex = search(mobileName, cmpnyName, mobiles, len);

    if (mobileIndex == -1)
    {
        cout << "\nThere is no such mobile phone!\n";
    }
    else if (mobiles[mobileIndex].numOfAvailabes != 0)
    {
        mobiles[mobileIndex].numOfAvailabes--;
        mobiles[mobileIndex].numOfSales++;
        cout << "\nA \"" << mobiles[mobileIndex].name << "\" mobile phone was successfully sold.\n";
    }
    else
    {
        cout << "\"" << mobiles[mobileIndex].name << "\" mobile phone is not currently available.\n";
    }
    cout << "\nPress any key to go back to main menu.";
    getch();
}
void editPhoneInfo(string mobileName, string cmpnyName, mobile *mobiles, int len)
{
    int mobileIndex = search(mobileName, cmpnyName, mobiles, len);

    if (mobileIndex == -1)
    {
        cout << "\nThere is no such mobile phone!\n"
                "\nPress any key to go back to main menu.";
        getch();
    }
    else
    {
        int opt;
        system("cls");
        cout << "Editing mobile phone \"" << mobiles[mobileIndex].companyName << ' ' << mobiles[mobileIndex].name << "\"\n\n"
                                                                                                                     "1: Name\n"
                                                                                                                     "2: Company name\n"
                                                                                                                     "3: Operating system\n"
                                                                                                                     "4: Color\n"
                                                                                                                     "5: RAM\n"
                                                                                                                     "6: Storage\n"
                                                                                                                     "7: Price\n"
                                                                                                                     "8: Number of availabes\n"
                                                                                                                     "9: Number of phones sold\n"
                                                                                                                     "0: *Go back to main menu\n"
                                                                                                                     "\nSelect what you want to edit: ";
        cin >> opt;
        if (opt == 1)
        {
            string newName;
            cout << "Enter the new name: ";
            cin >> newName;
            mobiles[mobileIndex].name = newName;
        }
        else if (opt == 2)
        {
            string newCmpName;
            cout << "Enter the new company name: ";
            cin >> newCmpName;
            mobiles[mobileIndex].companyName = newCmpName;
        }
        else if (opt == 3)
        {
            int operatingS;
            cout << "1: IOS\n2: Android\n3: Windows Phone\nSelect the phone OS: ";
            cin >> operatingS;
            mobiles[mobileIndex].os = os(operatingS);
        }
        else if (opt == 4)
        {
            int mobColor;
            cout << "1: Black\n2: White\n3: Blue\nSelect the phone color: ";
            cin >> mobColor;
            mobiles[mobileIndex].color = color(mobColor);
        }
        else if (opt == 5)
        {
            int mobRam;
            cout << "2: 2GB\n4: 4GB\n6: 6GB\n8: 8GB\n12: 12GB\n16: 16GB\n32: 32GB\n64: 64GB\nSelect the phone ram: ";
            cin >> mobRam;
            mobiles[mobileIndex].ram = ram(mobRam);
        }
        else if (opt == 6)
        {
            int mobStorage;
            cout << "16: 16GB\n32: 32GB\n64: 64GB\n128: 128GB\n256: 256GB\n512: 512GB\n1: 1TB\n2: 2Tb\nSelect the phone storage: ";
            cin >> mobStorage;
            mobiles[mobileIndex].storage = storage(mobStorage);
        }
        else if (opt == 7)
        {
            cout << "Enter the phone new price: ";
            cin >> mobiles[mobileIndex].price;
        }
        else if (opt == 8)
        {
            int newNumOfAvailabes;
            cout << "Enter the number of availabe phones: ";
            cin >> newNumOfAvailabes;
            mobiles[mobileIndex].numOfAvailabes = newNumOfAvailabes;
        }
        else if (opt == 9)
        {
            int newNumOfSold;
            cout << "Enter the number of phones sold: ";
            cin >> newNumOfSold;
            mobiles[mobileIndex].numOfAvailabes = newNumOfSold;
        }
        if (opt != 0)
        {
            cout << "\nThe info were successfully edited.\n"
                    "\nPress any key to go back to main menu.";
            getch();
        }
    }
}
void removePhone(int deletingIndex, mobile *&mobiles, int &len)
{
    if (deletingIndex == -1)
    {
        cout << "\nThere is no such mobile phone!";
    }
    else
    {
        mobile *newTemp = new mobile[--len];
        int temp = 0,
            i = 0;
        while (i < len)
        {
            if (temp != deletingIndex)
            {
                newTemp[i] = mobiles[temp];
                i++;
            }
            temp++;
        }
        delete[] mobiles;
        mobiles = newTemp;
        cout << "\nThe mobile phone was successfully removed.";
    }
    cout << "\n\nPress any key to go back to main menu.";
    getch();
}
void readFile(mobile *mobiles, int len)
{
    mobile tempMobile;
    vector<string> splittedLine;
    string tempLine;
    int i = -1;

    ifstream fin("t2ProjectFile.txt");
    while (getline(fin, tempLine))
    {
        if (i == -1)
        {
            i++;
        }
        else
        {
            splittedLine = splitString(tempLine);
            tempMobile.name = splittedLine.at(0);
            tempMobile.companyName = splittedLine.at(1);
            tempMobile.os = os(stoi(splittedLine.at(2)));
            tempMobile.ram = ram(stoi(splittedLine.at(3)));
            tempMobile.storage = storage(stoi(splittedLine.at(4)));
            tempMobile.color = color(stoi(splittedLine.at(5)));
            tempMobile.price = stoi(splittedLine.at(6));
            tempMobile.numOfAvailabes = stoi(splittedLine.at(7));
            tempMobile.numOfSales = stoi(splittedLine.at(8));
            mobiles[i++] = tempMobile;
        }
    }
    fin.close();
}
void writeFile(mobile *mobiles, int len)
{
    ofstream fout("t2ProjectFile.txt");
    fout << len << '\n';
    for (int i = 0; i < len; i++)
    {
        fout << mobiles[i].name << ',';
        fout << mobiles[i].companyName << ',';
        fout << mobiles[i].os << ',';
        fout << mobiles[i].ram << ',';
        fout << mobiles[i].storage << ',';
        fout << mobiles[i].color << ',';
        fout << mobiles[i].price << ',';
        fout << mobiles[i].numOfAvailabes << ',';
        fout << mobiles[i].numOfSales << ',';
        fout << '\n';
    }
    fout.close();
}
vector<string> splitString(string fullTeam)
{
    vector<string> splittedString;
    splittedString.push_back("");
    for (char i : fullTeam)
    {
        if (i == ',')
        {
            splittedString.push_back("");
        }
        else
        {
            splittedString[splittedString.size() - 1] += i;
        }
    }
    splittedString.pop_back();
    return splittedString;
}
void trim(string &word)
{
    while (word.at(0) == ' ')
    {
        word.erase(word.begin());
    }

    while (word.at(word.length() - 1) == ' ')
    {
        word.erase(word.end() - 1);
    }

    for (int i = 1; i < word.length(); i++)
    {
        if (word.at(i - 1) == ' ' && word.at(i) == ' ')
        {
            word.erase(word.begin() + i);
            i--;
        }
    }
}
string lowerWord(string word)
{
    for (char &i : word)
    {
        i = tolower(i);
    }
    return word;
}