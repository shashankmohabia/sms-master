//
// Created by Ajat Prabha on 22-11-2017.
//

#include "attendance.h"

//Initialises global value with empty data
map<string, map<string, vector<bool>>> Attendance::attendance_record = {};

void Attendance::show_attendance(const string& username)
{
    cout << "\t\tPresent\t\tAbsent\t\tTotal\t\tPercentage\n";
    for (auto& i : attendance_record[username]) {
        cout << i.first;
        int days_present = 0;
        for (auto&& j : i.second) {
            if (j==true) {
                days_present++;
            }
        }
        cout << "\t\t" << days_present << "\t\t" << i.second.size()-days_present << "\t\t" << i.second.size()
             << "\t\t" << setprecision(4) << ((float) days_present/(float) i.second.size())*100 << "\n";
    }
}
void Attendance::update_attendance(const string& username, const string& course, bool is_present)
{
    auto it = User::all().find(username);
    if (it==User::all().end()) {
        cout << "This user doesn't exist!\n";
        return;
    }
    else if (it->second.is_superuser()) {
        cout << it->second.get_fullname() << " is not a student.\n";
        return;
    }
    if (Course::all().find(course)==Course::all().end()) {
        cout << "This course doesn't exist!\n";
        return;
    }
    if (attendance_record.find(username)==attendance_record.end()) {
        map<string, vector<bool>> m1 = {};
        vector<bool> v1 = {is_present};
        m1.insert(pair<string, vector<bool>>(course, v1));
        attendance_record.insert(pair<string, map<string, vector<bool>>>(username, m1));
    }
    else {
        attendance_record.find(username)->second.find(course)->second.push_back(is_present);
    }
}
map<string, map<string, vector<bool>>>& Attendance::all()
{
    return attendance_record;
}
void Attendance::show_attendance_course(const string& course)
{
    if (Course::all().find(course)==Course::all().end()) {
        cout << "No course exists with the name " << course << endl;
        return;
    }
    cout << "The attendance of all the students in the course " << course << " is \n";
    cout << "Name\t\tPresent\t\tAbsent\t\tTotal\t\tPercentage\n";
    for (auto& i : attendance_record) {
        for (auto& j : i.second) {
            int days_present = 0;
            if (j.first==course) {
                for (auto&& k : j.second) {
                    if (k==true) {
                        days_present++;
                    }
                }
                cout << i.first << "\t\t" << days_present << "\t\t" << j.second.size()-days_present << "\t\t"
                     << j.second.size() << "\t\t" << setprecision(4)
                     << ((float) days_present/(float) j.second.size())*100 << "\n";
            }
        }
    }
}
