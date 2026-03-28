#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
#include <string>
#include <fstream> 
using namespace std;

class Person {
protected:
	string name;
public:
	Person() {}
	Person(string n) { name = n; }
	string getName() { return name; }
};

class Student : public Person {
private:
	int id;
	double gpa;
public:
	set<string> courses;

	Student(int i, string n, double g) : Person(n), id(i), gpa(g) {}
	int getId() { return id; }
	double getGpa() { return gpa; }
	void enrollCourse(string course) { courses.insert(course); }
	void showCourses() {
		if (courses.empty()) { cout << "No courses enrolled yet.\n"; return; }
		for (auto c : courses) cout << "- " << c << endl;
	}
	void display() {
		cout << "ID: " << id << "\nName: " << name << "\nGPA: " << gpa << endl;
	}
};

vector<Student> students;

// ===== دالة لحفظ البيانات في ملف =====
void saveToFile() {
	ofstream file("students.txt");
	if (!file) { cout << "Error opening file!\n"; return; }

	for (auto& s : students) {
		file << s.getId() << "\n";
		file << s.getName() << "\n";
		file << s.getGpa() << "\n";
		file << s.courses.size() << "\n"; 
		for (auto& c : s.courses) file << c << "\n"; 
	}
	file.close();
	cout << "Data saved to students.txt\n";
}

// ===== دوال البرنامج =====
bool isIdExist(int id) {
	for (auto& s : students)
		if (s.getId() == id) return true;
	return false;
}

void addStudent() {
	int id;
	string name;
	double gpa;

	cout << "Enter ID: ";
	cin >> id;
	if (isIdExist(id)) { cout << "ID already exists! Try again.\n"; return; }

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Name: ";
	getline(cin, name);

	cout << "Enter GPA (0.0 - 4.0): ";
	cin >> gpa;
	if (gpa < 0.0 || gpa > 4.0) { cout << "Invalid GPA! Must be between 0.0 and 4.0.\n"; return; }

	students.push_back(Student(id, name, gpa));
	cout << "Student added successfully.\n";
	saveToFile();
}

void displayStudents() {
	if (students.empty()) { cout << "No students yet.\n"; return; }
	for (auto& s : students) { s.display(); cout << "-----------\n"; }
}

void searchStudent() {
	int id;
	cout << "Enter ID: ";
	cin >> id;
	for (auto& s : students) if (s.getId() == id) { s.display(); return; }
	cout << "Student not found\n";
}

void removeStudent() {
	int id;
	cout << "Enter ID: ";
	cin >> id;
	for (auto it = students.begin(); it != students.end(); it++) {
		if (it->getId() == id) { students.erase(it); cout << "Student removed\n"; saveToFile(); return; }
	}
	cout << "Student not found\n";
}

void enrollCourse() {
	int id;
	string course;
	cout << "Enter Student ID: ";
	cin >> id;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (auto& s : students) {
		if (s.getId() == id) {
			cout << "Enter Course Name: ";
			getline(cin, course);
			s.enrollCourse(course);
			cout << "Course added\n";
			saveToFile();
			return;
		}
	}
	cout << "Student not found\n";
}

void showStudentCourses() {
	int id;
	cout << "Enter Student ID: ";
	cin >> id;
	for (auto& s : students) {
		if (s.getId() == id) { s.showCourses(); return; }
	}
	cout << "Student not found\n";
}

void sortStudents() {
	sort(students.begin(), students.end(), [](Student& a, Student& b) { return a.getGpa() > b.getGpa(); });
	cout << "Students sorted by GPA\n";
}

// ===== Main Menu =====
int main() {
	int choice;
	do {
		cout << "\n1.Add Student\n2.Remove Student\n3.Search Student\n4.Display Students\n5.Enroll Course\n6.Show Student Courses\n7.Sort Students by GPA\n8.Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1: addStudent(); break;
		case 2: removeStudent(); break;
		case 3: searchStudent(); break;
		case 4: displayStudents(); break;
		case 5: enrollCourse(); break;
		case 6: showStudentCourses(); break;
		case 7: sortStudents(); break;
		case 8: cout << "Exiting...\n"; break;
		default: cout << "Invalid choice! Try again.\n";
		}
	} while (choice != 8);
}