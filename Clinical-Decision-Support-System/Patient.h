#ifndef PATIENT_H
#define PATIENT_H

#include <string>

struct Patient {
    std::string id;
    std::string name;
    int age{};
    std::string gender;
    std::string contact;
};

#endif
