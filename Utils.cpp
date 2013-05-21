#include "Utils.h"

string getStuIDFromInput()
{
    cout << "Enter the student ID: ";
    string ID = "";

    while(true)
    {
        getline(cin, ID);
        if(ID.empty())
            continue;
        if(parseStuID(ID))
            break;
    }

    return ID;
}

string getCodeFromInput()
{
    cout << "Enter the course code: ";
    string code;

    while(true)
    {
        getline(cin, code);
        if(code.empty())
            continue;
        if(parseCourseCode(code))
            break;
    }

    return code;
}

string getStuNameFromInput(string _name)
{
    cout << "Enter the student name";

    if(_name != string())
        cout << " [" << _name << "]";
    cout << ": ";

    string name;

    while(true)
    {
        getline(cin, name);
        if(name.empty())
            continue;
        if(parseStuName(name))
            break;
    }

    return name;
}

unsigned int getStuYearFromInput(unsigned _year)
{
    cout << "Enter the student year ";

    if(_year == 99)
        cout << "[1-3]: ";
    else
        cout << "[" << _year << "]: ";

    unsigned int year;
    string input = "";

    while(true)
    {
        getline(cin, input);

        if(input.empty())
            continue;

        stringstream myStream(input);
        myStream >> year;

        if(parseStuYear(year))
            break;
    }

    return year;
}

char getStuGenderFromInput(char _gender)
{
    cout << "Enter the student gender ";
    if(_gender == '\0')
        cout << "[M,F]: ";
    else
        cout << "[" << _gender << "]: ";

    char gender;
    string input = "";

    while(true)
    {
        getline(cin, input);

        if(input.empty())
            continue;

        stringstream myStream(input);
        myStream >> gender;
        if(parseStuGender(gender))
            break;
    }

    gender = (gender == 'm')? 'M' : gender;
    gender = (gender == 'f')? 'F' : gender;

    return gender;
}

string getCourseNameFromInput(string _name)
{
    cout << "Enter the course name";

    if(_name != string())
        cout << " [" << _name << "]";
    cout << ": ";

    string name;

    while(true)
    {
        getline(cin, name);

        if(name.empty())
            continue;
        if(parseCourseName(name))
            break;
    }

    return name;
}

unsigned int getCourseCreditFromInput(unsigned int _credit)
{
    cout << "Enter the course credit ";

    if(_credit == 99)
        cout << "[0-5]: ";
    else
        cout << "[" << _credit << "]: ";

    unsigned int credit;
    string input = "";

    while(true)
    {
        getline(cin, input);

        if(input.empty())
            continue;

        stringstream myStream(input);
        myStream >> credit;
        if(parseCourseCredit(credit))
            break;
    }

    return credit;
}

unsigned int getExamMarkFromInput(unsigned int _mark)
{
    cout << "Enter the exam mark [";
    if( _mark == NA_EXAM_MARK)
        cout << "N/A";
    else
        cout << _mark;
    cout << "]: ";

    unsigned int mark;
    string input = "";

    while(true)
    {
        getline(cin, input);

        if(input.empty())
            continue;

        stringstream myStream(input);
        myStream >> mark;
        if(parseExamMark(mark))
            break;
    }

    return mark;
}

bool parseStuID(const string& ID)
{
    if(ID.length() > MAX_StuID_LENGTH || ID.length() < MIN_StuID_LENGTH)
    {
        cout << "Invalid input, re-enter again [student ID]: ";
        return false;
    }

    const char* c_str = ID.c_str();
    const char numMin('0'), numMax('9');

    for(unsigned int i = 0; i != ID.length(); ++i)
    {
        if(c_str[i] < numMin || c_str[i] > numMax)
        {
            cout << "Invalid input, re-enter again [student ID]: ";
            return false;
        }
    }

    return true;
}

bool parseStuName(const string& name)
{
    if(name.length() > MAX_StuName_LENGTH || name.length() == 0)
    {
        cout << "Invalid input, re-enter again [student name]: ";
        return false;
    }
    else
        return true;
}

bool parseStuYear(const unsigned int& year)
{
    if(year < MIN_StuYear || year > MAX_StuYear)
    {
        cout << "Invalid input, re-enter again [student year]: ";
        return false;
    }
    return true;
}

bool parseStuGender(const char& gender)
{
    if(gender != 'M' && gender != 'm' && gender != 'F' && gender != 'f')
    {
        cout << "Invalid input, re-enter again [M,F]: ";
        return false;
    }
    return true;
}

bool parseCourseCode(const string& code)
{
    if(code.length() > MAX_CourseCode_LENGTH || code.length() < MIN_CourseCode_LENGTH)
    {
        cout << "Invalid input, re-enter again [course code]: ";
        return false;
    }

    const char* c_str = code.c_str();
    const char upperCharMin('A'), upperCharMax('Z');

    for(unsigned int i = 0; i != CourseCodePrefix_LENGTH; ++i)
    {
        if(c_str[i] < upperCharMin || c_str[i] > upperCharMax)
        {
            cout << "Invalid input, re-enter again [course code]: ";
            return false;
        }
    }

    const char numMin('0'), numMax('9');

    for(unsigned int i = CourseCodePrefix_LENGTH; i != code.length(); ++i)
    {
        if(c_str[i] < numMin || c_str[i] > numMax)
        {
            cout << "Invalid input, re-enter again [course code]: ";
            return false;
        }
    }

    return true;
}

bool parseCourseName(const string& name)
{
    if(name.length() > MAX_CourseName_LENGTH || name.length() == 0)
    {
        cout << "Invalid input, re-enter again [course name]: ";
        return false;
    }
    else
        return true;
}

bool parseCourseCredit(const unsigned int& credit)
{
    if(credit > MAX_CREDIT)
    {
        cout << "Invalid input, re-enter again [course credit]: ";
        return false;
    }
    return true;
}

bool parseExamMark(const unsigned int& mark)
{
    if(mark > MAX_EXAM_MARK)
    {
        cout << "Invalid input, re-enter again [exam mark]: ";
        return false;
    }
    return true;
}
