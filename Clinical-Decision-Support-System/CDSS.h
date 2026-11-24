#ifndef CDSS_H
#define CDSS_H

#include "Patient.h"
#include <string>
#include <vector>

struct Assessment {
    std::string patientId;
    std::string date;
    std::string symptoms;
    std::string assessment;
    std::string recommendation;
};

class CDSS {
public:
    CDSS();

    void run();

private:
    const std::string patientsFile = "data/patients.txt";
    const std::string assessmentsFile = "data/assessments.txt";

    void showMenu() const;
    void registerPatient();
    void viewAllPatients() const;
    void createSymptomReview();
    void viewAssessmentHistory() const;
    void searchPatientById() const;

    std::vector<Patient> loadPatients() const;
    std::vector<Assessment> loadAssessments() const;
    void savePatient(const Patient& patient) const;
    void saveAssessment(const Assessment& assessment) const;
    std::string generatePatientId() const;

    static std::string getLine(const std::string& prompt);
    static int getInt(const std::string& prompt, int minValue, int maxValue);
    static std::string currentDateTime();
    static std::string cleanField(std::string value);
    static std::vector<std::string> split(const std::string& line, char delimiter);
    static void printPatient(const Patient& patient);
};

#endif
