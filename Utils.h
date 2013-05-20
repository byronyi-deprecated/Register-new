#ifndef UTILS_H
#define UTILS_H

#include "Record.h"
#include <fstream>
using namespace std;

string getStuIDFromInput();
string getCodeFromInput();
string getStuNameFromInput(string _name = string());
unsigned int getStuYearFromInput(unsigned _year = 99);
char getStuGenderFromInput(char _gender = '\0');
string getCourseNameFromInput(string _name = string());
unsigned int getCourseCreditFromInput(unsigned int credit = 99);
unsigned int getExamMarkFromInput(unsigned int _mark = NA_EXAM_MARK);

void outputHTMLByStudent(ofstream stream, string _ID);
void outputHTMLByCourse(ofstream stream, string _code);
void outputHTMLStudent(ofstream stream);
void outputHTMLCourse(ofstream stream);

bool parseStuID(const string&);
bool parseStuName(const string&);
bool parseStuYear(const unsigned int&);
bool parseStuGender(const char&);
bool parseCourseCode(const string&);
bool parseCourseName(const string&);
bool parseCourseCredit(const unsigned int&);
bool parseExamMark(const unsigned int&);

#endif // UTILS_H
