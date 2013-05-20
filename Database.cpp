#include "Database.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

bool Database::doInsertStudent(const Student& student)
{
    return studentRecord.insert(student);
}

bool Database::doInsertCourse(const Course& course)
{
    return courseRecord.insert(course);
}

bool Database::doInsertRegistration(const Registration& reg)
{
    if(!regRecord.insert(reg))
        return false;

    Registration* reg_ptr = regRecord.search(reg);

    StudentIdx* stu_idx_ptr = studentIndex.search(StudentIdx(reg.getID()));
    if(!stu_idx_ptr)
    {
        studentIndex.insert(StudentIdx(reg.getID()));
        stu_idx_ptr = studentIndex.search(StudentIdx(reg.getID()));
    }

    stu_idx_ptr->addReg(reg_ptr);

    CourseIdx* course_idx_ptr = courseIndex.search(CourseIdx(reg.getCode()));
    if(!course_idx_ptr)
    {
        courseIndex.insert(CourseIdx(reg.getCode()));
        course_idx_ptr = courseIndex.search(CourseIdx(reg.getCode()));
    }

    course_idx_ptr->addReg(reg_ptr);

    return true;
}


bool Database::doDeleteStudent(const string& stuID)
{
    bool ok = studentRecord.remove(Student(stuID));

    StudentIdx* idx_ptr = studentIndex.search(StudentIdx(stuID));

    if(!idx_ptr)
        return ok;

    for(list<Registration*>::iterator i = idx_ptr->reg.begin();
        i != idx_ptr->reg.end(); ++i) {

        regRecord.remove(**i);
        string courseCode = (*i)->getCode();

        CourseIdx* course_idx = courseIndex.search(CourseIdx(courseCode));
        course_idx->reg.remove(*i);

        if(course_idx->reg.empty())
            courseIndex.remove(*course_idx);

    }

    idx_ptr->reg.clear();
    studentIndex.remove(*idx_ptr);

    return true;
}

bool Database::doDeleteCourse(const string& code)
{
    bool ok = courseRecord.remove(Course(code));

    CourseIdx* idx_ptr = courseIndex.search(CourseIdx(code));

    if(!idx_ptr)
        return ok;

    for(list<Registration*>::iterator i = idx_ptr->reg.begin();
        i != idx_ptr->reg.end(); ++i) {

        regRecord.remove(**i);
        string stuID = (*i)->getID();

        StudentIdx* stu_idx = studentIndex.search(StudentIdx(stuID));
        stu_idx->reg.remove(*i);

        if(stu_idx->reg.empty())
            studentIndex.remove(*stu_idx);

    }

    idx_ptr->reg.clear();
    courseIndex.remove(*idx_ptr);

    return true;
}

bool Database::doDeleteRegistration(const string& stuID, const string& code)
{
    Registration* reg_ptr = regRecord.search(Registration(stuID, code));


    StudentIdx* stu_idx_ptr = studentIndex.search(StudentIdx(stuID));
    CourseIdx* course_idx_ptr = courseIndex.search(CourseIdx(code));

    stu_idx_ptr->reg.remove(reg_ptr);
    if(stu_idx_ptr->reg.empty())
        studentIndex.remove(*stu_idx_ptr);

    course_idx_ptr->reg.remove(reg_ptr);
    if(course_idx_ptr->reg.empty())
        courseIndex.remove(*course_idx_ptr);
}


Student Database::doQueryStudent(const string& stuID) const
{
    string studentError = "Student does not exist";

    Student* student = studentRecord.search(Student(stuID));

    if(!student) throw studentError;

    return *student;
}

Course Database::doQueryCourse(const string& code) const
{
    string courseError = "Course does not exist";

    Course* course = courseRecord.search(Course(code));

    if(!course) throw courseError;

    return *course;
}

Registration Database::doQueryRegistration(const string& stuID, const string& code) const
{
    string regError = "Registration does not exist";

    Registration* registration = regRecord.search(Registration(stuID, code));

    if(!registration) throw regError;
    return *registration;
}

bool Database::doModifyStudent(const string& stuID, const string& name,
                               const unsigned int& year, const char& gender)
{
    string studentError = "Student does not exist";

    Student* student = studentRecord.search(Student(stuID));

    if(!student) throw studentError;

    student->setName(name);
    student->setYear(year);
    student->setGender(gender);

    return true;
}

bool Database::doModifyCourse(const string& courseCode, const string& name,
                              const unsigned int& credit)
{
    string courseError = "Course does not exist";

    Course* course = courseRecord.search(Course(courseCode));

    if(!course) throw courseError;

    course->setName(name);
    course->setCredit(credit);

    return true;
}

bool Database::doModifyRegistration(const string& stuID, const string& code,
                                    const unsigned int& mark)
{
    string regError = "Registration does not exist";

    Registration* registration = regRecord.search(Registration(stuID, code));

    if(!registration) throw regError;

    registration->setMark(mark);

    return true;
}

void Database::WriteToBinary(ofstream& stream)
{
    char tag[] = "THIS IS THE BINARY FILE OF PROJECT 5: REGISTER. COPYRIGHT OF YI BAIREN";
    stream.write(tag, strlen(tag) * sizeof(char));

    list<Student> stu_list = studentRecord.items();
    unsigned int student_num = stu_list.size();

    stream.write((char*)&student_num, sizeof(unsigned int));

    for(list<Student>::iterator i = stu_list.begin();
        i != stu_list.end(); ++i)
    {
        char stuID[MAX_StuID_LENGTH];
        strcpy(stuID, i->getID().c_str());
        stream.write(stuID, sizeof(char) * MAX_StuID_LENGTH);

        char stuName[MAX_StuName_LENGTH];
        cout << i->getName();
//        strcpy(stuName, i->getName().c_str());
//        stream.write(stuName, sizeof(char) * MAX_StuName_LENGTH);

//        unsigned int year = i->getYear();
//        stream.write((char*)&year, sizeof(unsigned int));

//        char gender;
//        stream.write((char*)&gender, sizeof(char));
    }


    list<Course> course_list = courseRecord.items();
    unsigned int course_num = course_list.size();
    stream.write((char*)&course_num, sizeof(unsigned int));
    for(list<Course>::iterator i = course_list.begin();
        i != course_list.end(); ++i)
    {
        char code[MAX_CourseCode_LENGTH];
        strcpy(code, i->getCode().c_str());
        stream.write(code, sizeof(char) * MAX_CourseCode_LENGTH);

        char name[MAX_CourseName_LENGTH];
        strcpy(name, i->getName().c_str());
        stream.write(name, sizeof(char) * MAX_CourseName_LENGTH);

        unsigned int credit = i->getCredit();
        stream.write((char*)credit, sizeof(unsigned int));
    }

    list<Registration> reg_list = regRecord.items();
    unsigned int reg_num = reg_list.size();
    stream.write((char*)&reg_num, sizeof(unsigned int));
    for(list<Registration>::iterator i = reg_list.begin();
        i != reg_list.end(); ++i)
    {
        char stuID[MAX_StuID_LENGTH];
        strcpy(stuID, i->getID().c_str());
        stream.write(stuID, sizeof(char) * MAX_StuID_LENGTH);

        char code[MAX_CourseCode_LENGTH];
        strcpy(code, i->getCode().c_str());
        stream.write(code, sizeof(char) * MAX_CourseCode_LENGTH);

        unsigned int mark = i->getMark();
        stream.write((char*)mark, sizeof(unsigned int));
    }
}

void Database::ReadFromBinary(ifstream& stream)
{
    if(!stream.good())
        throw string("File not exist");

    char sample_tag[] = "THIS IS THE BINARY FILE OF PROJECT 5: REGISTER. COPYRIGHT OF YI BAIREN";
    char tag[strlen(sample_tag) + 1];
    stream.read(tag, strlen(sample_tag) * sizeof(char));
    tag[strlen(sample_tag)] = '\0';

    if(strcmp(sample_tag, tag) != 0)
        throw string("Incorrect Format");

    if(!stream.good())
        throw string("File Corrupted");
    unsigned int num_stu;
    stream.read((char*)&num_stu, sizeof(unsigned int));
    for(unsigned int i = 0; i != num_stu; ++i)
    {
        if(!stream.good())
            throw string("File Corrupted");

        char stuID[MAX_StuID_LENGTH];
        stream.read(stuID, sizeof(char) * MAX_StuID_LENGTH);
        cout << stuID;
        string id(stuID);

        char stuName[MAX_StuName_LENGTH];
        stream.read(stuName, sizeof(char) * MAX_StuName_LENGTH);
        string name(stuName);

        unsigned int year;
        stream.read((char*)&year, sizeof(unsigned int));

        char gender;
        stream.read((char*)&gender, sizeof(char));

        doInsertStudent(Student(id, name, year, gender));
    }

    if(!stream.good())
        throw string("File Corrupted");
    unsigned int num_course;
    stream.read((char*)&num_course, sizeof(unsigned int));
    for(unsigned int i = 0; i != num_course; ++i)
    {
        if(!stream.good())
            throw string("File Corrupted");

        char code[MAX_CourseCode_LENGTH];
        stream.read(code, sizeof(char) * MAX_CourseCode_LENGTH);

        char name[MAX_CourseName_LENGTH];
        stream.read(name, sizeof(char) * MAX_CourseName_LENGTH);

        unsigned int credit;
        stream.read((char*)credit, sizeof(unsigned int));

        doInsertCourse(Course(string(code), string(name), credit));
    }


    if(!stream.good())
        throw string("File Corrupted");
    unsigned int num_reg;
    stream.read((char*)&num_reg, sizeof(unsigned int));
    for(unsigned int i = 0; i != num_reg; ++i)
    {
        if(!stream.good())
            throw string("File Corrupted");

        char stuID[MAX_StuID_LENGTH];
        stream.read(stuID, sizeof(char) * MAX_StuID_LENGTH);

        char code[MAX_CourseCode_LENGTH];
        stream.read(code, sizeof(char) * MAX_CourseCode_LENGTH);

        unsigned int mark;
        stream.read((char*)mark, sizeof(unsigned int));

        doInsertRegistration(Registration(string(stuID), string(code), mark));
    }
}


void Database::Write2HTML_Student(ofstream& stream)
{
    stream << "<HTML>" << endl;
    stream << "<HEAD>" << endl;
    stream << "<TITLE>All Students List</TITLE>" << endl;
    stream << "</HEAD>" << endl;
    stream << "<BODY bgColor=#ffffcc>" << endl;
    stream << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>" << endl;
    stream << "<H2>All Students List</H2>" << endl;
    stream << "<P>" << endl;
    if(studentRecord.size())
    {
        stream << "<TABLE cellSpacing=1 cellPadding=1 border=1>" << endl;
        stream << endl;
        stream << "<TR>" << endl;
        stream << "<TD>Student ID</TD>" << endl;
        stream << "<TD>Student Name</TD>" << endl;
        stream << "<TD>Year</TD>" << endl;
        stream << "<TD>Gender</TD>" << endl;
        stream << "</TR>" << endl;
        stream << endl;

        list<Student> stuList = studentRecord.items();

        for(list<Student>::iterator i = stuList.begin();
            i != stuList.end(); ++i)
        {
            stream << "<TR>" << endl;
            stream << "<TD>" << i->getID() << "</TD>" << endl;
            stream << "<TD>" << i->getName() << "</TD>" << endl;
            stream << "<TD>" << i->getYear() << "</TD>" << endl;
            stream << "<TD>" << ((i->getGender() == 'M')? "Male" : "Female") << "</TD>" << endl;
            stream << "</TR>" << endl;
            stream << endl;
        }

        stream << "</TABLE>" << endl;
    }
    else
        stream << "No student found" << endl;

    stream << "</P>" << endl;
    stream << "</BODY>" << endl;
    stream << "</HTML>" << endl;
}

void Database::Write2HTML_Course(ofstream& stream)
{
    stream << "<HTML>" << endl;
    stream << "<HEAD>" << endl;
    stream << "<TITLE>All Course List</TITLE>" << endl;
    stream << "</HEAD>" << endl;
    stream << "<BODY bgColor=#ffffcc>" << endl;
    stream << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>" << endl;
    stream << "<H2>All Course List</H2>" << endl;
    stream << "<P>" << endl;

    if(courseRecord.size())
    {
        stream << "<TABLE cellSpacing=1 cellPadding=1 border=1>" << endl;
        stream << endl;
        stream << "<TR>" << endl;
        stream << "<TD>Course Code</TD>" << endl;
        stream << "<TD>Course Name</TD>" << endl;
        stream << "<TD>Credit</TD>" << endl;
        stream << "</TR>" << endl;
        stream << endl;

        list<Course> courseList = courseRecord.items();

        for(list<Course>::iterator i = courseList.begin();
            i != courseList.end(); ++i)
        {
            stream << "<TR>" << endl;
            stream << "<TD>" << i->getCode() << "</TD>" << endl;
            stream << "<TD>" << i->getName() << "</TD>" << endl;
            stream << "<TD>" << i->getCredit() << "</TD>" << endl;
            stream << "</TR>" << endl;
            stream << endl;
        }

        stream << "</TABLE>" << endl;
    }
    else
        stream << "No course found" << endl;

    stream << "</P>" << endl;
    stream << "</BODY>" << endl;
    stream << "</HTML>" << endl;
}

void Database::Write2HTML_CourseByStudent(ofstream&stream, const Student& student)
{
    StudentIdx* idxPtr= studentIndex.search(StudentIdx(student.getID()));

    if(!idxPtr)
    {
        cerr << "The database is inconsistent" << endl;
        return;
    }

    stream << "<HTML>" << endl;
    stream << "<HEAD>" << endl;
    stream << "<TITLE>Course Records for Student " << student.getID() << "</TITLE>" << endl;
    stream << "</HEAD>" << endl;
    stream << "<BODY bgColor=#ffffcc>" << endl;
    stream << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>" << endl;
    stream << "<H2>Course Records for Student: " << student.getName();
    stream << " (" << student.getID() << ")</H2>" << endl;
    stream << "<P>" << endl;

    list<Registration*> reg = idxPtr->getReg();
    if(!reg.empty())
    {
        stream << "<TABLE cellSpacing=1 cellPadding=1 border=1>" << endl;
        stream << endl;
        stream << "<TR>" << endl;
        stream << "<TD>Course Code</TD>" << endl;
        stream << "<TD>Course Name</TD>" << endl;
        stream << "<TD>Credit</TD>" << endl;
        stream << "<TD>Exam Mark</TD>" << endl;
        stream << "</TR>" << endl;
        stream << endl;

        for(list<Registration*>::iterator i = reg.begin();
            i != reg.end(); ++i)
        {
            Course course = doQueryCourse((*i)->getCode());

            stream << "<TR>" << endl;
            stream << "<TD>" << course.getCode() << "</TD>" << endl;
            stream << "<TD>" << course.getName() <<"</TD>" << endl;
            stream << "<TD>" << course.getCredit() << "</TD>" << endl;
            stream << "<TD>";
            if((*i)->getMark() == NA_EXAM_MARK)
                stream << "N/A";
            else
                stream << (*i)->getMark();
            stream << "</TD>" << endl;
            stream << "</TR>" << endl;
            stream << endl;
        }

        stream << "</TABLE>" << endl;
    }
    else
        stream << "No course taken" << endl;

    stream << "</P>" << endl;
    stream << "</BODY>" << endl;
    stream << "</HTML>" << endl;
}

void Database::Write2HTML_StudentByCourse(ofstream&stream, const Course& course)
{
    CourseIdx* idxPtr= courseIndex.search(CourseIdx(course.getCode()));

    if(!idxPtr)
    {
        cerr << "The database is inconsistent" << endl;
        return;
    }

    stream << "<HTML>" << endl;
    stream << "<HEAD>" << endl;
    stream << "<TITLE>Course Records for Course " << course.getCode() << "</TITLE>" << endl;
    stream << "</HEAD>" << endl;
    stream << "<BODY bgColor=#ffffcc>" << endl;
    stream << "<H1><FONT color=#6600ff>HKUST Course Registration System</FONT></H1>" << endl;
    stream << "<H2>Student Records for Course: " << course.getName();
    stream << " (" << course.getCode() << ")</H2>" << endl;
    stream << "<P>" << endl;

    list<Registration*> reg = idxPtr->getReg();
    if(!reg.empty())
    {
        stream << "<TABLE cellSpacing=1 cellPadding=1 border=1>" << endl;
        stream << endl;
        stream << "<TR>" << endl;
        stream << "<TD>Student ID</TD>" << endl;
        stream << "<TD>Student Name</TD>" << endl;
        stream << "<TD>Year</TD>" << endl;
        stream << "<TD>Gender</TD>" << endl;
        stream << "<TD>Exam Mark</TD>" << endl;
        stream << "</TR>" << endl;
        stream << endl;

        for(list<Registration*>::iterator i = reg.begin();
            i != reg.end(); ++i)
        {
            Student student = doQueryStudent((*i)->getID());

            stream << "<TR>" << endl;
            stream << "<TD>" << student.getID() << "</TD>" << endl;
            stream << "<TD>" << student.getName() << "</TD>" << endl;
            stream << "<TD>" << student.getYear() << "</TD>" << endl;
            stream << "<TD>" << ((student.getGender() == 'M')? "Male" : "Female") << "</TD>" << endl;
            if((*i)->getMark() == NA_EXAM_MARK)
                stream << "N/A";
            else
                stream << (*i)->getMark();
            stream << "</TD>" << endl;
            stream << "</TR>" << endl;
            stream << endl;
        }

        stream << "</TABLE>" << endl;
    }
    else
        stream << "No student takes this course" << endl;

    stream << "</P>" << endl;
    stream << "</BODY>" << endl;
    stream << "</HTML>" << endl;
}
