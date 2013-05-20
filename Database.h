#ifndef DATABASE_H
#define DATABASE_H

#include "Record.h"
#include "HashTable.h"
#include "DoublyLinkedList.h"
#include <string>

//====================================================
// Database object provide implementation of underlying
// manipulation of the database system.
//====================================================


class Database
{
public:
    Database() : studentRecord(HashTable<Student>(29)), courseRecord(HashTable<Course>(17)),
                 studentIndex(HashTable<StudentIdx>(29)), courseIndex(HashTable<CourseIdx>(17)) {}

    bool doInsertStudent(const Student&);
    bool doInsertCourse(const Course&);
    bool doInsertRegistration(const Registration&);

    bool doDeleteStudent(const string& stuID);
    bool doDeleteCourse(const string& code);
    bool doDeleteRegistration(const string& stuID, const string& code);

    Student doQueryStudent(const string& stuID) const;
    Course doQueryCourse(const string& code) const;
    Registration doQueryRegistration(const string& stuID, const string& code) const;

    bool doModifyStudent(const string& stuID, const string& name,
                         const unsigned int& year, const char& gender);
    bool doModifyCourse(const string& courseCode, const string& name,
                        const unsigned int& credit);
    bool doModifyRegistration(const string& stuID, const string& code,
                              const unsigned int& mark);

    void WriteToBinary(ofstream&);
    void ReadFromBinary(ifstream&);

    void Write2HTML_Student(ofstream&);
    void Write2HTML_Course(ofstream&);
    void Write2HTML_StudentByCourse(ofstream&, const Course& course);
    void Write2HTML_CourseByStudent(ofstream&, const Student& student);

private:
    HashTable<Student> studentRecord;
    HashTable<Course> courseRecord;
    HashTable<StudentIdx> studentIndex;
    HashTable<CourseIdx> courseIndex;
    DoublyLinkedList<Registration> regRecord;
};

#endif // DATABASE_H
