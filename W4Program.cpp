// Weekly Performance Evaluator Week 4
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    // Constants 
    const double PRO_TRAIN_HRS = 6.0;
    const double INT_TRAIN_HRS = 3.0;
    const double SLEEP_MIN_OK = 7.0;
    const double SLEEP_GOOD_MIN = 7.5;
    const double SLEEP_GOOD_MAX = 9.0;
    const double W_TRAIN = 10.0;
    const double W_SLEEP = 5.0;

    const int INPUT_FLUSH = 10000;
    const int SESSIONS_PER_WK = 3;
    const double SHIFT_MIN = 10.0;

    // ===== Banner =====
    cout << "====================================\n";
    cout << "    Weekly Performance Evaluator\n";
    cout << "====================================\n\n";

    // User Inputs 
    string player;
    int age;
    double trainingHours;
    double sleepHours;

    cout << "Enter player's full name: ";
    getline(cin, player);

    cout << "Enter player's age: ";
    while (!(cin >> age) || age <= 0) {
        cin.clear();
        cin.ignore(INPUT_FLUSH, '\n');
        cout << "Invalid age. Enter a positive integer: ";
    }

    cout << "Training hours this week: ";
    while (!(cin >> trainingHours) || trainingHours < 0.0) {
        cin.clear();
        cin.ignore(INPUT_FLUSH, '\n');
        cout << "Invalid hours. Enter a number >= 0: ";
    }

    cout << "Avg sleep hours per night: ";
    while (!(cin >> sleepHours) || sleepHours <= 0.0) {
        cin.clear();
        cin.ignore(INPUT_FLUSH, '\n');
        cout << "Invalid sleep hours. Enter a number > 0: ";
    }

	// Calculations 
    double readinessScore = (trainingHours * W_TRAIN)
        + ((sleepHours - SLEEP_MIN_OK) * W_SLEEP);

    // Determine level 
    string level;
    if (trainingHours >= PRO_TRAIN_HRS
        && (sleepHours >= SLEEP_GOOD_MIN && sleepHours <= SLEEP_GOOD_MAX)) {
        level = "Pro";
    }
    else if (trainingHours >= INT_TRAIN_HRS && sleepHours >= SLEEP_MIN_OK) {
        level = "Intermediate";
    }
    else {
        level = "Beginner";
    }

    // Advice
    string advice;
    if (sleepHours < SLEEP_MIN_OK || trainingHours < INT_TRAIN_HRS) {
        advice = "Build base: 3 focused sessions + target 8h sleep.";
    }
    else if (trainingHours >= PRO_TRAIN_HRS
        && !(sleepHours >= SLEEP_GOOD_MIN && sleepHours <= SLEEP_GOOD_MAX)) {
        advice = "Great workload; improve sleep routine for next gains.";
    }
    else {
        advice = "Solid balance; maintain consistency and recovery.";
    }

	// Variables for menu options
    string sectionTitle = "";
    string planFocus = "";
    double techMins = 0.0;
    double condMins = 0.0;
    string fatigueRisk = "Low";
    int restDays = 0;
    string recoveryTip = "";
    int choice;

    cout << fixed << showpoint << setprecision(2);

    // Menu (do-while + switch)
    do {
        cout << "\nMenu:\n";
        cout << "  1) Evaluate Level\n";
        cout << "  2) Build Training Plan\n";
        cout << "  3) Readiness & Recovery\n";
        cout << "  0) Quit\n";
        cout << "Enter choice (0-3): ";

        while (!(cin >> choice) || choice < 0 || choice > 3) {
            cin.clear();
            cin.ignore(INPUT_FLUSH, '\n');
            cout << "Invalid choice. Enter 0, 1, 2, or 3: ";
        }

        switch (choice)
        {
        case 1: {
            sectionTitle = "LEVEL";
            cout << "\n----- LEVEL -----\n";
            cout << "Player: " << player << "\n";
            cout << "Age   : " << age << "\n";
            cout << "Level : " << level << "\n";
            cout << "Readiness Score: " << readinessScore << "\n";

            ofstream out("report.txt");
            if (out) {
                out << fixed << showpoint << setprecision(2);
                out << "WEEKLY PERFORMANCE REPORT (Week 4)\n";
                out << "Section: " << sectionTitle << "\n";
                out << "----------------------------------\n";
                out << left << setw(18) << "Player:" << right << setw(20) << player << "\n";
                out << left << setw(18) << "Age:" << right << setw(20) << age << "\n";
                out << left << setw(18) << "Train hrs:" << right << setw(20) << trainingHours << "\n";
                out << left << setw(18) << "Sleep (h):" << right << setw(20) << sleepHours << "\n";
                out << left << setw(18) << "Level:" << right << setw(20) << level << "\n";
                out << left << setw(18) << "Readiness:" << right << setw(20) << readinessScore << "\n";
                out << left << setw(18) << "Advice:" << right << setw(20) << advice << "\n";
                out << "----------------------------------\n";
                out.close();
                cout << "Report saved to report.txt\n";
            }
            break;
        }

        case 2: {
            sectionTitle = "TRAINING PLAN";
            if (level == "Pro") {
                planFocus = "Advanced Finishing & High-Tempo Play";
                techMins = 50.0; condMins = 30.0;
            }
            else if (level == "Intermediate") {
                planFocus = "Passing & Finishing Basics";
                techMins = 45.0; condMins = 25.0;
            }
            else {
                planFocus = "Ball Mastery & Light Conditioning";
                techMins = 35.0; condMins = 20.0;
            }

            if (sleepHours < SLEEP_MIN_OK && condMins >= SHIFT_MIN) {
                techMins += SHIFT_MIN;
                condMins -= SHIFT_MIN;
            }

            cout << "\n------- TRAINING PLAN (3 sessions) -------\n";
            cout << left << setw(18) << "Player:" << right << setw(20) << player << "\n";
            cout << left << setw(18) << "Age:" << right << setw(20) << age << "\n";
            cout << left << setw(18) << "Level:" << right << setw(20) << level << "\n";
            cout << left << setw(18) << "Plan Focus:" << right << setw(20) << planFocus << "\n";
            cout << "----------------------------------------\n";
            cout << left << setw(10) << "Session"
                << setw(15) << "Tech (min)"
                << setw(15) << "Cond (min)" << "\n";

            double totalTech = 0.0;
            double totalCond = 0.0;
            for (int s = 1; s <= SESSIONS_PER_WK; ++s) {
                cout << left << setw(10) << s
                    << setw(15) << techMins
                    << setw(15) << condMins << "\n";
                totalTech += techMins;
                totalCond += condMins;
            }
            cout << "----------------------------------------\n";
            cout << left << setw(10) << "Total"
                << setw(15) << totalTech
                << setw(15) << totalCond << "\n";

            ofstream out("report.txt");
            if (out) {
                out << fixed << showpoint << setprecision(2);
                out << "WEEKLY PERFORMANCE REPORT (Week 4)\n";
                out << "Section: " << sectionTitle << "\n";
                out << "----------------------------------\n";
                out << left << setw(18) << "Player:" << right << setw(20) << player << "\n";
                out << left << setw(18) << "Age:" << right << setw(20) << age << "\n";
                out << left << setw(18) << "Level:" << right << setw(20) << level << "\n";
                out << left << setw(18) << "Plan Focus:" << right << setw(20) << planFocus << "\n";
                out << left << setw(18) << "Tech total:" << right << setw(20) << totalTech << "\n";
                out << left << setw(18) << "Cond total:" << right << setw(20) << totalCond << "\n";
                out << "----------------------------------\n";
                out.close();
                cout << "Report saved to report.txt\n";
            }
            break;
        }

        case 3: {
            sectionTitle = "READINESS & RECOVERY";
            cout << "\n---- READINESS & RECOVERY ----\n";

            if (sleepHours < SLEEP_MIN_OK) {
                fatigueRisk = "High";
            }
            else if ((trainingHours >= PRO_TRAIN_HRS &&
                !(sleepHours >= SLEEP_GOOD_MIN && sleepHours <= SLEEP_GOOD_MAX))
                || trainingHours < INT_TRAIN_HRS) {
                fatigueRisk = "Moderate";
            }
            else {
                fatigueRisk = "Low";
            }

            if (fatigueRisk == "High") restDays = 2;
            else if (fatigueRisk == "Moderate") restDays = 1;
            else restDays = 0;

            if (sleepHours < SLEEP_MIN_OK) recoveryTip = "Aim for 8h sleep; reduce screens.";
            else if (trainingHours >= PRO_TRAIN_HRS) recoveryTip = "Foam roll + light technical work.";
            else recoveryTip = "Stretch, hydrate, short ball session.";

            cout << left << setw(18) << "Player:" << right << setw(20) << player << "\n";
            cout << left << setw(18) << "Age:" << right << setw(20) << age << "\n";
            cout << left << setw(18) << "Fatigue Risk:" << right << setw(20) << fatigueRisk << "\n";
            cout << left << setw(18) << "Rest Days:" << right << setw(20) << restDays << "\n";
            cout << left << setw(18) << "Tip:" << right << setw(20) << recoveryTip << "\n";
            cout << "-------------------------------\n";

            ofstream out("report.txt");
            if (out) {
                out << fixed << showpoint << setprecision(2);
                out << "WEEKLY PERFORMANCE REPORT (Week 4)\n";
                out << "Section: " << sectionTitle << "\n";
                out << "----------------------------------\n";
                out << left << setw(18) << "Player:" << right << setw(20) << player << "\n";
                out << left << setw(18) << "Age:" << right << setw(20) << age << "\n";
                out << left << setw(18) << "Fatigue Risk:" << right << setw(20) << fatigueRisk << "\n";
                out << left << setw(18) << "Rest Days:" << right << setw(20) << restDays << "\n";
                out << left << setw(18) << "Tip:" << right << setw(20) << recoveryTip << "\n";
                out << "----------------------------------\n";
                out.close();
                cout << "Report saved to report.txt\n";
            }
            break;
        }

        case 0: {
            cout << "\nExiting. Goodbye!\n";
            break;
        }
        }

    } while (choice != 0);

    return 0;
}
