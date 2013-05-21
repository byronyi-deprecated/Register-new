#ifndef MENU_H
#define MENU_H

#include "Database.h"
#include "Utils.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

//========================================================================
// Remarkable design of Command Line Menus using OOP. Inspired by
// http://stackoverflow.com/questions/4688055/create-menus-in-command-line
//=========================================================================

struct MenuItem
{
    virtual void go() = 0;
};

struct Menu : public MenuItem
{
    virtual void go() = 0;
    void addItem(MenuItem* item) {subItem.push_back(item);}
protected:
    vector<MenuItem*> subItem;
};

struct MainMenu : public Menu
{
    MainMenu();
    ~MainMenu() {delete db;}
    void go();
private:
    Database* db;
};

static struct StudentMenu : public Menu
{
    void go();
} *studentMenu;

static struct CourseMenu : public Menu
{
    void go();
} *courseMenu;

static struct RegistrationMenu : public Menu
{
    void go();
} *registrationMenu;

static struct ReportMenu : public Menu
{
    void go();
} *reportMenu;

static struct FileMenu : public Menu
{
    void go();
} *fileMenu;

static struct Quit : public MenuItem
{
    void go();
} quit;

static struct InsertStudent : public MenuItem
{
    void go();
} insertStudent;

static struct InsertCourse : public MenuItem
{
    void go();
} insertCourse;

static struct InsertRegistration : public MenuItem
{
    void go();
} insertRegistration;

static struct ModifyStudent : public MenuItem
{
    void go();
} modifyStudent;

static struct ModifyCourse : public MenuItem
{
    void go();
} modifyCourse;

static struct ModifyRegistration : public MenuItem
{
    void go();
} modifyRegistration;

static struct DeleteStudent : public MenuItem
{
    void go();
} deleteStudent;

static struct DeleteCourse : public MenuItem
{
    void go();
} deleteCourse;

static struct DeleteRegistration : public MenuItem
{
    void go();
} deleteRegistration;

static struct QueryStudent : public MenuItem
{
    void go();
} queryStudent;

static struct QueryCourse : public MenuItem
{
    void go();
} queryCourse;

static struct QueryRegistration : public MenuItem
{
    void go();
} queryRegistration;

static struct ReportStudent : public MenuItem
{
    void go();
} reportStudent;

static struct ReportCourse : public MenuItem
{
    void go();
} reportCourse;

static struct ReportCourseByStudent : public MenuItem
{
    void go();
} reportCourseByStudent;

static struct ReportStudentByCourse : public MenuItem
{
    void go();
} reportStudentByCourse;

static struct SaveDatabase : public MenuItem
{
    void go();
} saveDatabase;

static struct LoadDatabase : public MenuItem
{
    void go();
} loadDatabase;

#endif // MENU_H
