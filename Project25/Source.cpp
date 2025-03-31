#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

enum specialty { IT, CS, Math, Physics, Pe };

struct Student {
    string surname;
    int course;
    specialty spec;
    double physics;
    double math;
    union {
        double programming;  // для IT, CS
        double numerics;     // для Math, Physics
        double pedagogy;     // для Pe
    };
};

void inputStudents(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Student #" << i + 1 << ":" << endl;
        cout << " Surname: ";
        cin.ignore();
        getline(cin, s[i].surname);
        cout << " Course: ";
        cin >> s[i].course;

        cout << " Specialty (0 - IT, 1 - CS, 2 - Math, 3 - Physics, 4 - Pe): ";
        int specInput;
        cin >> specInput;
        s[i].spec = static_cast<specialty>(specInput);

        cout << " Physics grade: ";
        cin >> s[i].physics;
        cout << " Math grade: ";
        cin >> s[i].math;

        switch (s[i].spec) {
        case IT:
        case CS:
            cout << " Programming grade: ";
            cin >> s[i].programming;
            break;
        case Math:
        case Physics:
            cout << " Numerics grade: ";
            cin >> s[i].numerics;
            break;
        case Pe:
            cout << " Pedagogy grade: ";
            cin >> s[i].pedagogy;
            break;
        }
    }
}

void printStudents(Student* s, const int N) {
    cout << "=====================================================================================================" << endl;
    cout << "| No. | Surname        | Course | Specialty   | Physics |  Math | Programming | Numerics | Pedagogy |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << "  ";
        cout << "| " << setw(13) << left << s[i].surname;
        cout << "  | " << setw(6) << right << s[i].course;
        cout << " | ";

        string specName;
        switch (s[i].spec) {
        case IT: specName = "IT"; break;
        case CS: specName = "CS"; break;
        case Math: specName = "Math"; break;
        case Physics: specName = "Physics"; break;
        case Pe: specName = "Pe"; break;
        }
        cout << setw(11) << left << specName;

        cout << " | " << setw(7) << right << fixed << setprecision(2) << s[i].physics;
        cout << " | " << setw(5) << right << fixed << setprecision(2) << s[i].math;

        if (s[i].spec == IT || s[i].spec == CS) {
            cout << " | " << setw(9) << right << fixed << setprecision(2) << s[i].programming;
            cout << " |              |      ";
        }
        else if (s[i].spec == Math || s[i].spec == Physics) {
            cout << " |         | " << setw(10) << right << fixed << setprecision(2) << s[i].numerics;
            cout << " |         |";
        }
        else if (s[i].spec == Pe) {
            cout << " |              |              |      " << setw(10) << right << fixed << setprecision(2) << s[i].pedagogy;
        }

        cout << "       |   " << endl;
    }
    cout << "=====================================================================================================" << endl;
}

double studentAverage(const Student& s) {
    double total = s.physics + s.math;
    int count = 2;

    switch (s.spec) {
    case IT:
    case CS:
        total += s.programming;
        count++;
        break;
    case Math:
    case Physics:
        total += s.numerics;
        count++;
        break;
    case Pe:
        total += s.pedagogy;
        count++;
        break;
    }

    return total / count;
}

int countHighAverage(Student* s, const int N, double threshold = 4.5) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (studentAverage(s[i]) > threshold) {
            count++;
        }
    }
    return count;
}

void computeSubjectAverages(Student* s, const int N,
    double& avgPhysics, double& avgMath, double& avgAdditional) {
    avgPhysics = avgMath = avgAdditional = 0.0;
    int count = 0;

    for (int i = 0; i < N; i++) {
        avgPhysics += s[i].physics;
        avgMath += s[i].math;

        switch (s[i].spec) {
        case IT:
        case CS:
            avgAdditional += s[i].programming;
            count++;
            break;
        case Math:
        case Physics:
            avgAdditional += s[i].numerics;
            count++;
            break;
        case Pe:
            avgAdditional += s[i].pedagogy;
            count++;
            break;
        }
    }

    avgPhysics /= N;
    avgMath /= N;
    avgAdditional /= count;
}

void subjectWithHighestAverage(double avgPhysics, double avgMath, double avgAdditional) {
    string subject;
    double maxAvg = avgPhysics;
    subject = "Physics";

    if (avgMath > maxAvg) {
        maxAvg = avgMath;
        subject = "Math";
    }
    if (avgAdditional > maxAvg) {
        maxAvg = avgAdditional;
        subject = "Additional Subject";
    }

    cout << "Subject with highest average grade: " << subject
        << " (average: " << fixed << setprecision(2) << maxAvg << ")" << endl;
}

int main() {
    int N;
    cout << "Enter number of students: ";
    cin >> N;
    cin.ignore();

    Student* s = new Student[N];

    int menuItem;
    do {
        cout << "\n\n================ MENU ==================" << endl;
        cout << "1 - Create students" << endl;
        cout << "2 - Print students" << endl;
        cout << "3 - Count number of students whose average grade is greater than 4.5" << endl;
        cout << "4 - Subject with highest average grade" << endl;
        cout << "0 - Exit" << endl;
        cout << "========================================" << endl;
        cout << "Choose an option: ";
        cin >> menuItem;
        cin.ignore();

        switch (menuItem) {
        case 1:
            inputStudents(s, N);
            break;
        case 2:
            printStudents(s, N);
            break;
        case 3:
            cout << "Number of students with average > 4.5: " << countHighAverage(s, N, 4.5) << endl;
            break;
        case 4: {
            double avgPhysics, avgMath, avgAdditional;
            computeSubjectAverages(s, N, avgPhysics, avgMath, avgAdditional);
            subjectWithHighestAverage(avgPhysics, avgMath, avgAdditional);
            break;
        }
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}
