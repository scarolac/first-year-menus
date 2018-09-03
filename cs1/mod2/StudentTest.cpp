// Section CSC160 - Computer Science I: C++
// File Name: StudentTest.cpp
// Student: Chris Scarola
// Homework Number: 8
// Description: Exception handling testing for students classes
// Last Changed: 10/17/2016

#include "Student.h"
#include "StudentException.h"

namespace lesson8_students {

void run()
{
    clear_screen();

    try
    {
        Student testStudent1("S0203478");
        Student testStudent2("S0000002");
        Student testStudent3("S0000003");
                //testStudent4,
                //testStudent5;
        testStudent1.enroll("CSC-160-500");
        testStudent2.enroll("CSC-161-500");
        testStudent3.enroll("PHI-112-500");
    }
    catch(StudentException& s)
    {
        std::cout << s.errorMessage() << std::endl;
    }
    catch(...)
    {
        std::cout << "Unknown Exception\n";
    }

    std::cout << std::endl << "End of program" << std::endl;
    
    keep_window_open("~~");
}

}
