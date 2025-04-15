#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

map<int, pair<string, vector<pair<double, double>>>> students; 

//Finished -- might not eliminate this func and keep it in main
int menu();
//Finished --
double gpaCalculator(vector<pair<double, double>>& grade);
//Finished --
void addStudent();
//Finished -- added verifictaion for student name and ID
void singleStudnentGPA();

void averageGPA();


int main() {
	int choice;

	cout << "------ GPA MENU ------" << endl;
	choice = menu();
	do{
		if (choice == 1) {
			addStudent();
			cout << "____________________________________________" << endl;
			choice = menu();
		}
		else if (choice == 2) {
			singleStudnentGPA();
			cout << "____________________________________________" << endl;
			choice = menu();
		}
		else if (choice == 3) {
			averageGPA();
			cout << "____________________________________________" << endl;
			choice = menu();
		}
	} while (choice != 4);
	cout << "You chose to leave this program... GOOD BYE!!!" << endl;
	return 0;
}

int menu() {
	int choice;
	do{
		cout << "1. Add a new student" << endl;
		cout << "2. Calculate Single Student GPA" << endl;
		cout << "3. Calculate the Average GPA of All Students" << endl;
		cout << "4. Exit Program" << endl;
		cout << "____________________________________________" << endl;
		cin >> choice;
	} while (choice < 1 or choice > 4);
	return choice;
}
double gpaCalculator(vector<pair<double, double>>& grades) {
	double totalGradePoints = 0;
	double totalCredits = 0;

	for (pair<double, double>& grade : grades) {
		totalCredits += grade.first;
		totalGradePoints += grade.first * grade.second;
	}

	if (totalCredits > 0) {
		return totalGradePoints / totalCredits;
	}
	else
		return 0.0;
}

void addStudent() {
	int ID, classes;
	string student;
	vector<pair<double, double>> grades;


	cout << "ID: ";
	cin >> ID;
	cin.ignore();
	cout << "Student name: ";
	getline(cin, student);
	cout << "Classes: ";
	cin >> classes;

	for (int i = 0; i < classes; ++i) {
		double credits, grade;
		cout << "For course " << i+1 << endl;
		cout << "\tEnter credits: ";
		cin >> credits;
		cout << "\tEnter Grade Points: ";
		cin >> grade;
		grades.push_back(make_pair(credits, grade));
	}
	students[ID] = make_pair(student, grades);
	cout << "Success!!! Students Information was add!" << endl;
}

void singleStudnentGPA() {
	int ID;
	string student;

	cout << "Student ID: ";
	cin >> ID;

	auto it = students.find(ID);

	if (it == students.end()) {
		cout << "Not Found" << endl;
		return;
	}

	cin.ignore();
	cout << "What is the students name ";
	getline(cin, student);

	if (it->second.first == student) {
		double gpa = gpaCalculator(it->second.second);
		cout << "The GPA for " << student << " is " << gpa << endl;
	}
	else cout << "GPA cant be calculated, ID and Name dont match..." << endl;
}

void averageGPA() {

	//base
	if (students.empty()) {
		cout << "0 Students in system" << endl;
		return;
	}

	double total = 0.0;
	for (auto& entry : students) {
		total += gpaCalculator(entry.second.second);
	}

	double avg = total / students.size();
	cout << "Average GPA is " << avg << endl;
}