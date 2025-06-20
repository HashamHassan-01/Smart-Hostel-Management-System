
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Student {
    string name;
    int rollNo;
    string dept;
    float cgpa;
    bool isScholarship;
};

Student* hostel[3][5][2] = { nullptr };

bool rollExists(int roll) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 5; ++j)
            for (int k = 0; k < 2; ++k)
                if (hostel[i][j][k] && hostel[i][j][k]->rollNo == roll)
                    return true;
    return false;
}

void allocateStudent() {
    Student* p = new Student();
    cout << "Enter the Name of the Student:" << endl;
    cin >> p->name;
    cout << "Enter the Roll No of the Student:" << endl;
    cin >> p->rollNo;
    cout << "Enter the Department of the Student:" << endl;
    cin >> p->dept;
    cout << "Enter the CGPA of the Student:" << endl;
    cin >> p->cgpa;
    cout << "Has the Student received Scholarship? (1 = Yes, 0 = No):" << endl;
    cin >> p->isScholarship;

    if (rollExists(p->rollNo)) {
        cout << "Error: Roll exists in the system." << endl;
        delete p;
        return;
    }

    int h, r;
    cout << "Enter Hostel (0-2) and Room (0-4):" << endl;
    cin >> h >> r;
    if (h < 0 || h > 2 || r < 0 || r > 4) {
        cout << "Invalid hostel or room numbers." << endl;
        delete p;
        return;
    }
    if (p->isScholarship && r > 2) {
        cout << "Scholarship students can only be in rooms 0 to 2." << endl;
        delete p;
        return;
    }

    for (int s = 0; s < 2; ++s) {
        if (hostel[h][r][s] == nullptr) {
            hostel[h][r][s] = p;
            cout << "Student added to Hostel " << h
                 << ", Room " << r << ", Slot " << s << "." << endl;
            return;
        }
    }

    cout << "That room is already full." << endl;
    delete p;
}

void displayAll() {
    cout << "---- Room Status ----" << endl;
    for (int h = 0; h < 3; ++h) {
        cout << "Hostel " << h << ":" << endl;
        for (int r = 0; r < 5; ++r) {
            int cnt = 0;
            for (int s = 0; s < 2; ++s)
                if (hostel[h][r][s]) cnt++;
            cout << " Room " << r << ": "
                 << (cnt == 0 ? "Empty" : cnt == 2 ? "Full" : "Partial")
                 << endl;
            for (int s = 0; s < 2; ++s) {
                if (hostel[h][r][s]) {
                    Student* st = hostel[h][r][s];
                    cout << "  - " << st->name
                         << " R" << st->rollNo
                         << " CGPA:" << fixed << setprecision(2)
                         << st->cgpa
                         << (st->isScholarship ? " [Scholar]" : "")
                         << endl;
                }
            }
        }
    }
}

Student* findStudent(int roll, int& h, int& r, int& s) {
    for (h = 0; h < 3; ++h)
        for (r = 0; r < 5; ++r)
            for (s = 0; s < 2; ++s)
                if (hostel[h][r][s] && hostel[h][r][s]->rollNo == roll)
                    return hostel[h][r][s];
    return nullptr;
}

void transferStudent() {
    cout << "Enter Roll of Student to Transfer:" << endl;
    int roll; cin >> roll;
    int h, r, s;
    Student* st = findStudent(roll, h, r, s);
    if (!st) {
        cout << "Student not found." << endl;
        return;
    }

    int nh, nr;
    cout << "Enter New Hostel (0-2) and New Room (0-4):" << endl;
    cin >> nh >> nr;
    if (nh < 0 || nh > 2 || nr < 0 || nr > 4) {
        cout << "Invalid location." << endl;
        return;
    }
    if (st->isScholarship && nr > 2) {
        cout << "Scholarship students can only be in rooms 0 to 2." << endl;
        return;
    }

    for (int ns = 0; ns < 2; ++ns) {
        if (!hostel[nh][nr][ns]) {
            hostel[h][r][s] = nullptr;
            hostel[nh][nr][ns] = st;
            cout << "Student moved to Hostel " << nh
                 << ", Room " << nr
                 << ", Slot " << ns << "." << endl;
            return;
        }
    }
    cout << "New room is full." << endl;
}

void showSummary() {
    int total = 0, scholarCount = 0, above3[3] = {0};
    double sum = 0.0;
    for (int h = 0; h < 3; ++h)
        for (int r = 0; r < 5; ++r)
            for (int s = 0; s < 2; ++s)
                if (hostel[h][r][s]) {
                    ++total;
                    sum += hostel[h][r][s]->cgpa;
                    if (hostel[h][r][s]->isScholarship) ++scholarCount;
                    if (hostel[h][r][s]->cgpa > 3.0) ++above3[h];
                }

    cout << "Total students: " << total<<endl;
      cout   << " | Avg CGPA: "<< (total ? sum / total : 0.0)<<endl;
         cout<< " | Scholarships: " << scholarCount << endl;
    for (int h = 0; h < 3; ++h)
        cout << "Hostel " << h << " CGPA > 3.0 count: " << above3[h] << endl;
}

int main() {
    while (true) {
    	cout<<"__________WELCOME TO HOSTEL MANAGEMENT SYSTEM__________"<<endl;
        cout << "\nMenu Options:\n"<<endl;
         cout    << "^^^^^ 1 = Add Student^^^^"<<endl;
          cout   << "****  2 = Show Rooms*****"<<endl;
           cout  << "_____ 3 = Transfer Student________"<<endl;
           cout  << "~~~~~  4 = Show Summary~~~~~"<<endl;
           cout  << "0 = Exit\n"<<endl;
           cout  << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 0) break;
        else if (choice == 1) allocateStudent();
        else if (choice == 2) displayAll();
        else if (choice == 3) transferStudent();
        else if (choice == 4) showSummary();
        else cout << "Invalid choice. Please try again." << endl;
    }

    for (int h = 0; h < 3; ++h)
        for (int r = 0; r < 5; ++r)
            for (int s = 0; s < 2; ++s)
                delete hostel[h][r][s];

    cout << "Goodbye!" << endl;
    return 0;
}

