#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cstring>
#define MAX_WIDTH 1250
#define MAX_HEIGHT 700

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

bool isClickedInRect(int x1, int y1, int x2, int y2, int x, int y)
{
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}


void drawRegisterPage(const char* userType) {
    cleardevice();
    setbkcolor(LIGHTGRAY);
    cleardevice();

    // Box dimensions
    int formWidth = 600;
    int formHeight = (strcmp(userType, "Employer") == 0) ? 400 : 350;
    int formX = (MAX_WIDTH - formWidth) / 2;
    int formY = (MAX_HEIGHT - formHeight) / 2;

    // Outer form box
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(formX, formY, formX + formWidth, formY + formHeight);
    floodfill(formX + 1, formY + 1, DARKGRAY);

    // Title
    setcolor(BLACK);
    settextstyle(3, 0, 2);
    char title[100];
    sprintf(title, "%s Registration", userType);
    int titleX = (MAX_WIDTH - textwidth(title)) / 2;
    outtextxy(titleX, formY + 20, title);

    // Input fields
    settextstyle(2, 0, 1);
    int labelX = formX + 50;
    int inputX1 = formX + 200;
    int inputX2 = formX + formWidth - 50;
    int y = formY + 70;

    outtextxy(labelX, y, "Full Name:");
    rectangle(inputX1, y - 5, inputX2, y + 15);

    y += 30;
    outtextxy(labelX, y, "Email:");
    rectangle(inputX1, y - 5, inputX2, y + 15);

    y += 30;
    outtextxy(labelX, y, "Phone (10 digits):");
    rectangle(inputX1, y - 5, inputX2, y + 15);

    y += 30;
    if (strcmp(userType, "Employer") == 0) {
        outtextxy(labelX, y, "Company Name:");
        rectangle(inputX1, y - 5, inputX2, y + 15);
        y += 30;

        outtextxy(labelX, y, "Company Address:");
        rectangle(inputX1, y - 5, inputX2, y + 15);
        y += 30;
    }

    outtextxy(labelX, y, "Create Username:");
    rectangle(inputX1, y - 5, inputX2, y + 15);
    y += 30;

    outtextxy(labelX, y, "Create Password:");
    rectangle(inputX1, y - 5, inputX2, y + 15);

    // Submit button
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(formX + 200, y + 40, formX + 350, y + 70);
    floodfill(formX + 201, y + 41, WHITE);
    setcolor(BLACK);
    outtextxy(formX + 235, y + 50, "Submit");
}




void registerUser(const char* userType) {
    User u;
    ofstream file;

    drawRegisterPage(userType);  // Assume this draws a graphical form

    // Console input
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
        cout << "Company Address: ";
        cin.getline(u.address, 100);
    } else {
        strcpy(u.company, "-");
        strcpy(u.address, "-");
    }

    cout << "Create Username: ";
    cin.getline(u.username, 30);

    cout << "Create Password: ";
    cin.getline(u.password, 30);

    file.open((string(userType) + "_data.txt").c_str(), ios::app | ios::binary);
    file.write((char*)&u, sizeof(u));
    file.close();

    // Centered message using MAX_WIDTH and MAX_HEIGHT
    settextstyle(10, 0, 2);
    setcolor(GREEN);
    const char* message = "Registration Successful!";
    int text_x = (MAX_WIDTH - textwidth("message")) / 2;
    int text_y = MAX_HEIGHT - 100;
    outtextxy(text_x, text_y, "message");
    delay(1500);
}


void drawLoginScreen(const char* userType) {
    cleardevice();
    setbkcolor(LIGHTGRAY);
    cleardevice();

    // Outer box for login area
    int box_width = 500, box_height = 300;
    int box_x = (MAX_WIDTH - box_width) / 2;
    int box_y = (MAX_HEIGHT - box_height) / 2;

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(box_x, box_y, box_x + box_width, box_y + box_height);
    floodfill(box_x + 1, box_y + 1, DARKGRAY);

    // Title
    settextstyle(3, 0, 2);
    char title[50];
    sprintf(title, "%s Login", userType);
    int title_x = (MAX_WIDTH - textwidth(title)) / 2;
    outtextxy(title_x, box_y + 20, title);

    // Labels and input boxes
    settextstyle(2, 0, 1);
    setcolor(BLACK);
    
    // Username
    int label_x = box_x + 50;
    int input_x1 = box_x + 150;
    int input_x2 = box_x + box_width - 50;
    int username_y = box_y + 80;
    outtextxy(label_x, username_y, "Username:");
    rectangle(input_x1, username_y - 5, input_x2, username_y + 20);

    // Password
    int password_y = username_y + 60;
    outtextxy(label_x, password_y, "Password:");
    rectangle(input_x1, password_y - 5, input_x2, password_y + 20);
}



bool loginUser(const char* userType) {
    User temp;
    User input;
    ifstream file;

    drawLoginScreen(userType);  // Assumes this function draws the login form

    // Console Input
    cout << "\nLogin as " << userType << "\nUsername: ";
    cin >> input.username;
    cout << "Password: ";
    cin >> input.password;

    file.open((string(userType) + "_data.txt").c_str(), ios::in | ios::binary);
    bool success = false;

    while (file.read((char*)&temp, sizeof(temp))) {
        if (strcmp(temp.username, input.username) == 0 &&
            strcmp(temp.password, input.password) == 0) {
            success = true;
            break;
        }
    }
    file.close();

    // Result message
    settextstyle(10, 0, 2);
    setcolor(success ? GREEN : RED);
    const char* message = success ? "Login Successful!" : "Login Failed!";
    int text_x = (MAX_WIDTH - textwidth("message")) / 2;
    int text_y = MAX_HEIGHT - 100;
    outtextxy(text_x, text_y, "message");
    delay(1500);

    return success;
}


int showMenu(const char* userType) {
    cleardevice();
    setbkcolor(LIGHTGRAY);
    cleardevice();

    // Title
    settextstyle(10, 0, 3);
    setcolor(BLACK);
    char menuTitle[50];
    sprintf(menuTitle, "%s MENU", userType);
    outtextxy((MAX_WIDTH - textwidth(menuTitle)) / 2, MAX_HEIGHT / 6, menuTitle);

    // Button dimensions
    int btn_width = 300, btn_height = 50;
    int btn_x = (MAX_WIDTH - btn_width) / 2;
    int top_y = MAX_HEIGHT / 3;

    // Register Button
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(DARKGRAY);
    bar(btn_x, top_y, btn_x + btn_width, top_y + btn_height);
    setcolor(BLACK);
    settextstyle(10, 0, 2);
    outtextxy(btn_x + 100, top_y + 15, "Register");

    // Login Button
    int login_y = top_y + btn_height + 30;
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(DARKGRAY);
    bar(btn_x, login_y, btn_x + btn_width, login_y + btn_height);
    setcolor(BLACK);
    outtextxy(btn_x + 110, login_y + 15, "Login");

    // Back Button
    int back_y = login_y + btn_height + 30;
    setfillstyle(SOLID_FILL, WHITE);
    setcolor(DARKGRAY);
    bar(btn_x, back_y, btn_x + btn_width, back_y + btn_height);
    setcolor(BLACK);
    outtextxy(btn_x + 110, back_y + 15, "Back");

    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (x >= btn_x && x <= btn_x + btn_width && y >= top_y && y <= top_y + btn_height) return 1;
            if (x >= btn_x && x <= btn_x + btn_width && y >= login_y && y <= login_y + btn_height) return 2;
            if (x >= btn_x && x <= btn_x + btn_width && y >= back_y && y <= back_y + btn_height) return 3;
        }
    }
}

int showHomePage() {
    cleardevice();
    setbkcolor(WHITE);
    cleardevice();

    settextstyle(10, 0, 4);
    setcolor(BLACK);
    outtextxy((MAX_WIDTH/2)-320,MAX_HEIGHT/10, "Welcome to Job Vacancy Platform");

    settextstyle(10, 0, 3);
    outtextxy((MAX_WIDTH/2)-150, MAX_HEIGHT/3-50, "Choose your role:");
    
    // Outer black box
    int box_width = 400, box_height = 300;
    int box_left = (MAX_WIDTH - box_width) / 2;
    int box_top = MAX_HEIGHT / 2 - 100;
    int box_right = box_left + box_width;
    int box_bottom = box_top + box_height;

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(box_left - 5, box_top - 5, box_right + 5, box_bottom + 5); // outer black border

    // Inner gray box
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(box_left, box_top, box_right, box_bottom);

    // Common X for both buttons
    int center_x = (MAX_WIDTH/2)-125;
    // jobseeker
	setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(((MAX_WIDTH/2)-150)+25,MAX_HEIGHT/3+10,((MAX_WIDTH/2)+150)-25,MAX_HEIGHT/3+50);
    floodfill((((MAX_WIDTH/2)-150)+25)+ 1,(MAX_HEIGHT/3+10 )+ 1, DARKGRAY);
    outtextxy((((MAX_WIDTH/2)-150)+25)+ 50,(MAX_HEIGHT/3+10 ) + 10, "Job Seeker");

    // Employer button (below Job Seeker)
    int emp_top = (MAX_HEIGHT/3)+130;
    int emp_left = center_x;
    int emp_right = emp_left + 240;
    int emp_bottom = emp_top + 40;

    rectangle(emp_left, emp_top, emp_right, emp_bottom);
    floodfill(emp_left + 1, emp_top + 1, DARKGRAY);
    outtextxy(emp_left + 60, emp_top + 10, "Employer");

    // Exit button
    settextstyle(DEFAULT_FONT, 0, 2);
    outtextxy((MAX_WIDTH / 2) - 30, emp_bottom + 40, "Exit");

    int x, y;
    while (true) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, x, y);
            if (isClickedInRect(((MAX_WIDTH/2)-150)+25,MAX_HEIGHT/3+10,((MAX_WIDTH/2)+150)-25,(MAX_WIDTH/3)+125, x, y)) return 1;
            if (isClickedInRect(emp_left, emp_top, emp_right, emp_bottom, x, y)) return 2;
            if (isClickedInRect((MAX_WIDTH / 2) - 30, emp_bottom + 40, (MAX_WIDTH / 2) + 40, emp_bottom + 60, x, y)) exit(0);
        }
    }
}

int main() {
    int gd = DETECT, gm;
   initgraph(&gd, &gm, "");
    initwindow(MAX_WIDTH, MAX_HEIGHT, "Jobify");  // Initialize graphics window
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
