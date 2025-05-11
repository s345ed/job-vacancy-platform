#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cstring>

using namespace std;

struct User {
    char username[30];
    char password[30];
    char name[50];
    char email[50];
    char phone[11];
    char company[50];
    char address[100];
};

bool isClickedInRect(int x1, int y1, int x2, int y2, int x, int y) {
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

void drawLoginScreen(const char* userType) {
    cleardevice();
    setbkcolor(LIGHTGRAY);
    cleardevice();
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(100, 100, 500, 400);
    floodfill(101, 101, DARKGRAY);

    settextstyle(3, 0, 2);
    char title[50];
    sprintf(title, "%s Login", userType);
    outtextxy(180, 120, title);

    settextstyle(2, 0, 1);
    setcolor(BLACK);
    outtextxy(150, 180, "Username:");
    rectangle(250, 175, 400, 200);

    outtextxy(150, 230, "Password:");
    rectangle(250, 225, 400, 250);
}

void registerUser(const char* userType) {
    User u;
    ofstream file;

    drawLoginScreen(userType);
    outtextxy(150, 280, "Registering...");

    cout << "\nRegister as " << userType << endl;
    cin.ignore();

    cout << "Full Name: ";
    cin.getline(u.name, 50);

    cout << "Email: ";
    cin.getline(u.email, 50);

    while (true) {
        cout << "Phone (10 digits): ";
        cin.getline(u.phone, 11);
        if (strlen(u.phone) == 10 && strspn(u.phone, "0123456789") == 10) break;
        cout << "Invalid phone number! Try again.\n";
    }

    if (strcmp(userType, "Employer") == 0) {
        cout << "Company Name: ";
        cin.getline(u.company, 50);
    } else {
        strcpy(u.company, "-");
    }

    cout << "Address: ";
    cin.getline(u.address, 100);

    cout << "Create Username: ";
    cin.getline(u.username, 30);

    cout << "Create Password: ";
    cin.getline(u.password, 30);

    file.open((string(userType) + "_data.txt").c_str(), ios::app | ios::binary);
    file.write((char*)&u, sizeof(u));
    file.close();

    outtextxy(150, 320, "Registration Successful!");
    delay(1500);
}

bool loginUser(const char* userType) {
    User u, temp;
    ifstream file;

    drawLoginScreen(userType);
    cout << "\nLogin as " << userType << "\nUsername: ";
    cin >> u.username;
    cout << "Password: ";
    cin >> u.password;

    file.open((string(userType) + "_data.txt").c_str(), ios::in | ios::binary);
    while (file.read((char*)&temp, sizeof(temp))) {
        if (strcmp(temp.username, u.username) == 0 && strcmp(temp.password, u.password) == 0) {
            outtextxy(150, 320, "Login Successful!");
            file.close();
            delay(1500);
            return true;
        }
    }
    file.close();
    outtextxy(150, 320, "Login Failed!");
    delay(1500);
    return false;
}

int showHomePage() {
    cleardevice();
    setbkcolor(WHITE);
    cleardevice();

    settextstyle(BOLD_FONT, 0, 3);
    setcolor(BLACK);
    outtextxy(120, 60, "WELCOME TO JOB VACANCY PLATFORM");

    settextstyle(DEFAULT_FONT, 0, 2);
    outtextxy(180, 140, "Are you an :");

    // EMPLOYER button
    setfillstyle(SOLID_FILL, GREEN);
    bar(170, 180, 370, 220);
    setcolor(RED);
    settextstyle(BOLD_FONT, 0, 2);
    outtextxy(200, 190, "EMPLOYER");

    // JOB-SEEKER button
    setfillstyle(SOLID_FILL, BLUE);
    bar(170, 240, 370, 280);
    setcolor(RED);
    outtextxy(190, 250, "JOB-SEEKER");

    // Exit text
    settextstyle(DEFAULT_FONT, 0, 2);
    outtextxy(330, 300, "exit");

    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isClickedInRect(170, 180, 370, 220, x, y)) return 1; // Employer
            if (isClickedInRect(170, 240, 370, 280, x, y)) return 2; // Job Seeker
            if (isClickedInRect(320, 300, 370, 310, x, y)) {
                closegraph();
                exit(0);
            }
        }
    }
}

int showMenu(const char* userType) {
    cleardevice();
    setbkcolor(WHITE);
    cleardevice();
    settextstyle(3, 0, 2);
    char menuTitle[50];
    sprintf(menuTitle, "%s Menu", userType);
    outtextxy(180, 100, menuTitle);

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, WHITE);

    rectangle(150, 160, 350, 200);
    floodfill(151, 161, DARKGRAY);
    outtextxy(180, 170, "Register");

    rectangle(150, 220, 350, 260);
    floodfill(151, 221, DARKGRAY);
    outtextxy(180, 230, "Login");

    rectangle(150, 280, 350, 320);
    floodfill(151, 281, DARKGRAY);
    outtextxy(180, 290, "Back");

    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isClickedInRect(150, 160, 350, 200, x, y)) return 1;
            if (isClickedInRect(150, 220, 350, 260, x, y)) return 2;
            if (isClickedInRect(150, 280, 350, 320, x, y)) return 3;
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    while (true) {
        int userType = showHomePage(); // 1 = Employer, 2 = Jobseeker
        const char* type = (userType == 1) ? "Employer" : "Jobseeker";

        while (true) {
            int action = showMenu(type);
            if (action == 1)
                registerUser(type);
            else if (action == 2)
                loginUser(type);
            else
                break;
        }
    }

    closegraph();
    return 0;
}

