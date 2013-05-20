#ifndef RECORD_H
#define RECORD_H

#define MIN_StuID_LENGTH 8
#define MAX_StuID_LENGTH 8
#define MAX_StuName_LENGTH 32
#define MIN_StuYear 1
#define MAX_StuYear 3
#define MIN_CourseCode_LENGTH 7
#define MAX_CourseName_LENGTH 32
#define MAX_CourseCode_LENGTH 8
#define CourseCodePrefix_LENGTH 4
#define MAX_CREDIT 5
#define NA_EXAM_MARK 999
#define MAX_EXAM_MARK 100

#include <string>
#include <list>
using namespace std;

//=================================================================
// This is the Definition of Record Object that would be managed by
// the database system. New type of objects are welcomed; they are
// expected to provide at least several APIs. See the toy case below
// for minimal requirement.
/*
struct Char
{
    Char() : c(0) {}
    Char(char _c) : c(_c) {}
    Char(const Char& _char) : c(_char.c) {}

    bool operator==(Char _char) {return (c == _char.c);}
    bool operator<(Char _char) {return (c < _char.c);}
    char c;
    unsigned int getKey() const {return (unsigned int) c;}
};
*/
//==================================================================

inline unsigned int pow(unsigned int num, unsigned int exp)
{
    if(exp == 0) return 1;
    return num * pow(num, exp - 1);
}

class Record
{
public:
    virtual size_t getKey() const = 0;
protected:
    virtual size_t hash(string key) const
    {
        size_t sum = 0;
        for(unsigned int i = 0; i != key.length(); ++i)
        {
            sum += (key.c_str())[i];
        }
        return sum;
    }
};

class Student : public Record
{
public:
    Student() {}
    Student(string id, string n = string(), unsigned int y = 0, char g = 0) :
        ID(id), name(n), year(y), gender(g) {}
    Student(const Student& s) : ID(s.ID), name(s.name), year(s.year), gender(s.gender) {}

    size_t getKey() const {return hash(ID);}

    string getID() const {return ID;}
    string getName() const {return name;}
    unsigned int getYear() const {return year;}
    char getGender() const {return gender;}

    void setName(string n) {name = n;}
    void setYear(unsigned int y) {year = y;}
    void setGender(char g) {gender = g;}

    Student& operator=(const Student& s) {
        ID = s.ID; name = s.name; year = s.year; gender = s.gender; return *this;
    }

    bool operator==(Student s) {return ID.compare(s.ID) == 0;}
    bool operator!=(Student s) {return !((*this) == s);}
    bool operator<(Student s) {return ID.compare(s.ID) == -1;}

protected:
    virtual size_t hash(string key) const
    {
        size_t sum = 0;
        for(unsigned int i = 0; i != key.length(); ++i)
        {
            unsigned int temp = (key.c_str())[i] - '0';
            sum += pow(10, i) * temp;
        }
        return sum;
    }

private:
    string ID;
    string name;
    unsigned int year;
    char gender;
};

class Course : public Record
{
public:
    Course() {}
    Course(string c, string n = string(), unsigned int cd = 0) :
        code(c), name(n), credit(cd) {}
    Course(const Course& c) : code(c.code), name(c.name), credit(c.credit) {}

    size_t getKey() const {return hash(code);}
    string getCode() const {return code;}
    string getName() const {return name;}
    unsigned int getCredit() const {return credit;}

    void setCode(string c) {code = c;}
    void setName(string n) {name = n;}
    void setCredit(unsigned int c) {credit = c;}

    Course& operator=(const Course& c) {
        code = c.code; name = c.name; credit = c.credit; return *this;
    }

    bool operator==(Course c) {return code.compare(c.code) == 0;}
    bool operator!=(Course c) {return !((*this) == c);}
    bool operator<(Course c) {return code.compare(c.code) == -1;}

protected:
    virtual size_t hash(string key) const
    {
        size_t sum = 0;
        for(unsigned int i = 0; i != CourseCodePrefix_LENGTH; ++i)
        {
            unsigned int temp = (key.c_str())[i] - 'A' + 10;
            sum += pow(36, i) * temp;
        }
        for(unsigned int i = CourseCodePrefix_LENGTH; i != MAX_CourseCode_LENGTH; ++i)
        {
            unsigned int temp = (key.c_str())[i] - '0';
            sum += pow(36, i) * temp;
        }
        return sum;
    }
private:
    string code;
    string name;
    unsigned int credit;
};

class Registration
{
public:
    Registration() {}
    Registration(string id, string c, unsigned int m = NA_EXAM_MARK) :
        ID(id), code(c), mark(m) {}
    Registration(const Registration& r) : ID(r.ID), code(r.code), mark(r.mark) {}

    string getID() const {return ID;}
    string getCode() const {return code;}
    unsigned int getMark() const {return mark;}

    void setMark(unsigned int m) {mark = m;}

    Registration& operator=(const Registration& r) {
        ID = r.ID; code = r.code; mark = r.mark; return *this;
    }

    bool operator==(Registration r) {return ID.compare(r.ID) == 0 && code.compare(r.code) == 0;}
    bool operator!=(Registration r) {return !((*this) == r);}
    bool operator<(Registration r) {
        if(ID.compare(r.ID) == -1) return true;
        else if(ID.compare(r.ID) == 0 && code.compare(r.code) == -1) return true;
        else return false;
    }

private:
    string ID;
    string code;
    unsigned int mark;
};

struct RegRecordIdx : public Record
{
    RegRecordIdx() {}
    RegRecordIdx(const RegRecordIdx& r) : reg(r.reg) {}

    virtual size_t getKey() const = 0;
    list<Registration*> getReg() const {return reg;}
    void addReg(Registration* r) {reg.push_back(r);}
    list<Registration*> reg;
};

struct StudentIdx : public RegRecordIdx
{
    StudentIdx() {}
    StudentIdx(string id) : ID(id) {}
    StudentIdx(const StudentIdx& s) : RegRecordIdx(), ID(s.ID) {}

    size_t getKey() const {return hash(ID);}

    StudentIdx& operator=(const StudentIdx idx) {
        reg = idx.reg; ID = idx.ID; return *this;
    }

    bool operator==(StudentIdx idx) {return ID.compare(idx.ID) == 0;}
    bool operator!=(StudentIdx idx) {return !((*this) == idx);}
    bool operator<(StudentIdx idx) {return ID.compare(idx.ID) == -1;}

protected:
    virtual size_t hash(string key) const
    {
        size_t sum = 0;
        for(unsigned int i = 0; i != key.length(); ++i)
        {
            unsigned int temp = (key.c_str())[i] - '0';
            sum += pow(10, i) * temp;
        }
        return sum;
    }
private:
    string ID;
};

struct CourseIdx : public RegRecordIdx
{
    CourseIdx() {}
    CourseIdx(string c) : code(c) {}
    CourseIdx(const CourseIdx& c) : RegRecordIdx(), code(c.code) {}

    size_t getKey() const {return hash(code);}

    CourseIdx& operator=(const CourseIdx idx) {
        reg = idx.reg; code = idx.code; return *this;
    }

    bool operator==(CourseIdx idx) {return code.compare(idx.code) == 0;}
    bool operator!=(CourseIdx idx) {return !((*this) == idx);}
    bool operator<(CourseIdx idx) {return code.compare(idx.code) == -1;}

protected:
    virtual size_t hash(string key) const
    {
        size_t sum = 0;
        for(unsigned int i = 0; i != CourseCodePrefix_LENGTH; ++i)
        {
            unsigned int temp = (key.c_str())[i] - 'A' + 10;
            sum += pow(36, i) * temp;
        }
        for(unsigned int i = CourseCodePrefix_LENGTH; i != MAX_CourseCode_LENGTH; ++i)
        {
            unsigned int temp = (key.c_str())[i] - '0';
            sum += pow(36, i) * temp;
        }
        return sum;
    }

private:
    string code;
};

#endif // RECORD_H
