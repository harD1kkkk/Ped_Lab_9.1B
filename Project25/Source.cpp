#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

struct Student {
    string surname;
    int course;
    string specialty;
    union {
        struct {
            double physics;
            double math;
            double informatics;
        };
    } o;
};

void inputStudents(Student* s, const int N) {
    for (int i = 0; i < N; i++) {
        cout << "Student #" << i + 1 << ":" << endl;
        cout << " Surname: ";
        getline(cin, s[i].surname);
        cout << " Course: ";
        cin >> s[i].course;
        cin.ignore();
        cout << " Specialty: ";
        getline(cin, s[i].specialty);
        cout << " Physics grade: ";
        cin >> s[i].o.physics;
        cout << " Math grade: ";
        cin >> s[i].o.math;
        cout << " Informatics grade: ";
        cin >> s[i].o.informatics;
        cin.ignore();
        cout << endl;
    }
}

void printStudents(Student* s, const int N) {
    cout << "======================================================================================" << endl;
    cout << "| No. | Surname        | Course | Specialty          | Physics |  Math | Informatics |" << endl;
    cout << "--------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(2) << right << i + 1 << "  ";
        cout << "| " << setw(13) << left << s[i].surname;
        cout << "  | " << setw(6) << right << s[i].course;
        cout << " | " << setw(18) << left << s[i].specialty;
        cout << " | " << setw(7) << right << fixed << setprecision(2) << s[i].o.physics;
        cout << " | " << setw(5) << right << fixed << setprecision(2) << s[i].o.math;
        cout << " | " << setw(10) << right << fixed << setprecision(2) << s[i].o.informatics;
        cout << "  |" << endl;
    }
    cout << "======================================================================================" << endl;
}

double studentAverage(const Student& s) {
    return (s.o.physics + s.o.math + s.o.informatics) / 3.0;
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
    double& avgPhysics, double& avgMath, double& avgInformatics) {
    avgPhysics = avgMath = avgInformatics = 0.0;
    for (int i = 0; i < N; i++) {
        avgPhysics += s[i].o.physics;
        avgMath += s[i].o.math;
        avgInformatics += s[i].o.informatics;
    }
    avgPhysics /= N;
    avgMath /= N;
    avgInformatics /= N;
}

void subjectWithHighestAverage(double avgPhysics, double avgMath, double avgInformatics) {
    string subject;
    double maxAvg = avgPhysics;
    subject = "Physics";
    if (avgMath > maxAvg) {
        maxAvg = avgMath;
        subject = "Math";
    }
    if (avgInformatics > maxAvg) {
        maxAvg = avgInformatics;
        subject = "Informatics";
    }
    cout << "Subject with highest average grade: " << subject
        << " (average: " << fixed << setprecision(2) << maxAvg << ")" << endl;
}

int main() {
    int N;
    cout << "Enter number of students: ";
    cin >> N;
    cin.ignore();

    int menuItem;
    Student* s = new Student[N];

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
        case 1: {
            inputStudents(s, N);
            break;
        }
        case 2: {
            printStudents(s, N);
            break;
        }
        case 3: {
            int highAvgCount = countHighAverage(s, N, 4.5);
            cout << "Number of students whose average grade is greater than 4.5: " << highAvgCount << endl;
            break;
        }
        case 4: {
            double avgPhysics, avgMath, avgInformatics;
            computeSubjectAverages(s, N, avgPhysics, avgMath, avgInformatics);
            cout << "Average grade in Physics: " << fixed << setprecision(2) << avgPhysics << endl;
            cout << "Average grade in Math: " << fixed << setprecision(2) << avgMath << endl;
            cout << "Average grade in Informatics: " << fixed << setprecision(2) << avgInformatics << endl;
            subjectWithHighestAverage(avgPhysics, avgMath, avgInformatics);
            break;
        }
        case 0:
            cout << "Goodbye" << endl;
            break;
        default: {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }
    } while (menuItem != 0);

    delete[] s;
    return 0;
}
