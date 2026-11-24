#include "CDSS.h"

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

CDSS::CDSS() {
    // Create empty local data files if they do not already exist.
    std::ofstream patients(patientsFile, std::ios::app);
    std::ofstream assessments(assessmentsFile, std::ios::app);
}

std::string CDSS::getLine(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return cleanField(value);
}

int CDSS::getInt(const std::string& prompt, int minValue, int maxValue) {
    while (true) {
        std::string input = getLine(prompt);
        try {
            std::size_t used = 0;
            int value = std::stoi(input, &used);
            if (used == input.size() && value >= minValue && value <= maxValue) {
                return value;
            }
        } catch (...) {
            // Invalid input; show the message below.
        }
        std::cout << "Please enter a number between " << minValue
                  << " and " << maxValue << ".\n";
    }
}

std::string CDSS::cleanField(std::string value) {
    // The pipe character is the storage delimiter, so remove it from input.
    value.erase(std::remove(value.begin(), value.end(), '|'), value.end());
    std::replace(value.begin(), value.end(), '\n', ' ');
    std::replace(value.begin(), value.end(), '\r', ' ');
    return value;
}

std::vector<std::string> CDSS::split(const std::string& line, char delimiter) {
    std::vector<std::string> fields;
    std::stringstream stream(line);
    std::string field;

    while (std::getline(stream, field, delimiter)) {
        fields.push_back(field);
    }
    // Preserve a final empty field, if present.
    if (!line.empty() && line.back() == delimiter) {
        fields.emplace_back();
    }
    return fields;
}

std::string CDSS::currentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm localTime{};

#ifdef _WIN32
    localTime = *std::localtime(&now);
#else
    localtime_r(&now, &localTime);
#endif

    std::ostringstream output;
    output << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    return output.str();
}

std::vector<Patient> CDSS::loadPatients() const {
    std::vector<Patient> patients;
    std::ifstream file(patientsFile);
    std::string line;

    while (std::getline(file, line)) {
        auto fields = split(line, '|');
        if (fields.size() != 5) continue;

        try {
            Patient patient;
            patient.id = fields[0];
            patient.name = fields[1];
            patient.age = std::stoi(fields[2]);
            patient.gender = fields[3];
            patient.contact = fields[4];
            patients.push_back(patient);
        } catch (...) {
            // Ignore malformed records rather than stopping the application.
        }
    }
    return patients;
}

std::vector<Assessment> CDSS::loadAssessments() const {
    std::vector<Assessment> assessments;
    std::ifstream file(assessmentsFile);
    std::string line;

    while (std::getline(file, line)) {
        auto fields = split(line, '|');
        if (fields.size() != 5) continue;

        Assessment item;
        item.patientId = fields[0];
        item.date = fields[1];
        item.symptoms = fields[2];
        item.assessment = fields[3];
        item.recommendation = fields[4];
        assessments.push_back(item);
    }
    return assessments;
}

void CDSS::savePatient(const Patient& patient) const {
    std::ofstream file(patientsFile, std::ios::app);
    if (!file) {
        std::cout << "Error: Could not open the patient data file.\n";
        return;
    }

    file << patient.id << '|'
         << patient.name << '|'
         << patient.age << '|'
         << patient.gender << '|'
         << patient.contact << '\n';
}

void CDSS::saveAssessment(const Assessment& assessment) const {
    std::ofstream file(assessmentsFile, std::ios::app);
    if (!file) {
        std::cout << "Error: Could not open the assessment data file.\n";
        return;
    }

    file << assessment.patientId << '|'
         << assessment.date << '|'
         << assessment.symptoms << '|'
         << assessment.assessment << '|'
         << assessment.recommendation << '\n';
}

std::string CDSS::generatePatientId() const {
    int highestNumber = 0;

    for (const auto& patient : loadPatients()) {
        if (patient.id.size() > 1 && patient.id[0] == 'P') {
            try {
                highestNumber = std::max(
                    highestNumber, std::stoi(patient.id.substr(1))
                );
            } catch (...) {
                // Ignore IDs that do not follow the P<number> format.
            }
        }
    }

    std::ostringstream id;
    id << 'P' << std::setw(4) << std::setfill('0') << highestNumber + 1;
    return id.str();
}

void CDSS::printPatient(const Patient& patient) {
    std::cout << "\nPatient ID : " << patient.id
              << "\nName       : " << patient.name
              << "\nAge        : " << patient.age
              << "\nGender     : " << patient.gender
              << "\nContact    : " << patient.contact << '\n';
}

void CDSS::registerPatient() {
    std::cout << "\n--- Patient Registration ---\n";

    Patient patient;
    patient.id = generatePatientId();
    patient.name = getLine("Enter patient name: ");

    if (patient.name.empty()) {
        std::cout << "Name cannot be empty. Registration cancelled.\n";
        return;
    }

    patient.age = getInt("Enter age (0-120): ", 0, 120);
    patient.gender = getLine("Enter gender: ");
    patient.contact = getLine("Enter contact number: ");

    savePatient(patient);
    std::cout << "\nPatient registered successfully.\n";
    printPatient(patient);
}

void CDSS::viewAllPatients() const {
    std::cout << "\n--- All Registered Patients ---\n";
    const auto patients = loadPatients();

    if (patients.empty()) {
        std::cout << "No patient records found.\n";
        return;
    }

    for (const auto& patient : patients) {
        printPatient(patient);
        std::cout << "-----------------------------\n";
    }
}

void CDSS::createSymptomReview() {
    std::cout << "\n--- Create Symptom Review ---\n";
    const auto patients = loadPatients();

    if (patients.empty()) {
        std::cout << "No patients registered. Register a patient first.\n";
        return;
    }

    const std::string patientId = getLine("Enter patient ID: ");
    auto patientIt = std::find_if(
        patients.begin(), patients.end(),
        [&](const Patient& p) { return p.id == patientId; }
    );

    if (patientIt == patients.end()) {
        std::cout << "Patient ID not found.\n";
        return;
    }

    Assessment item;
    item.patientId = patientId;
    item.date = currentDateTime();
    item.symptoms = getLine("Describe symptoms: ");

    if (item.symptoms.empty()) {
        std::cout << "Symptoms cannot be empty. Review cancelled.\n";
        return;
    }

    std::cout << "\nSelect a preliminary category:\n"
              << "1. General / mild symptoms\n"
              << "2. Possible infection-related symptoms\n"
              << "3. Pain or injury\n"
              << "4. Other / uncertain\n";

    const int choice = getInt("Enter choice (1-4): ", 1, 4);

    switch (choice) {
        case 1:
            item.assessment = "General symptoms reported";
            item.recommendation =
                "Monitor symptoms and consult a qualified healthcare professional if they persist or worsen.";
            break;
        case 2:
            item.assessment = "Possible infection-related symptoms";
            item.recommendation =
                "Seek assessment from a qualified healthcare professional. Do not self-medicate.";
            break;
        case 3:
            item.assessment = "Pain or injury reported";
            item.recommendation =
                "Obtain an appropriate clinical evaluation, especially if pain is severe or worsening.";
            break;
        default:
            item.assessment = "Unclassified symptoms";
            item.recommendation =
                "A qualified healthcare professional should evaluate the reported symptoms.";
            break;
    }

    saveAssessment(item);
    std::cout << "\nSymptom review saved successfully.\n"
              << "Preliminary category: " << item.assessment << '\n'
              << "Guidance: " << item.recommendation << '\n';
}

void CDSS::viewAssessmentHistory() const {
    std::cout << "\n--- Patient Assessment History ---\n";
    const std::string patientId = getLine("Enter patient ID: ");

    const auto patients = loadPatients();
    const bool patientExists = std::any_of(
        patients.begin(), patients.end(),
        [&](const Patient& p) { return p.id == patientId; }
    );

    if (!patientExists) {
        std::cout << "Patient ID not found.\n";
        return;
    }

    const auto assessments = loadAssessments();
    bool found = false;

    for (const auto& item : assessments) {
        if (item.patientId == patientId) {
            found = true;
            std::cout << "\nDate: " << item.date
                      << "\nSymptoms: " << item.symptoms
                      << "\nAssessment: " << item.assessment
                      << "\nRecommendation: " << item.recommendation
                      << "\n-----------------------------\n";
        }
    }

    if (!found) {
        std::cout << "No assessment history found for this patient.\n";
    }
}

void CDSS::searchPatientById() const {
    std::cout << "\n--- Search Patient by ID ---\n";
    const std::string patientId = getLine("Enter patient ID (e.g. P0001): ");

    const auto patients = loadPatients();
    auto it = std::find_if(
        patients.begin(), patients.end(),
        [&](const Patient& p) { return p.id == patientId; }
    );

    if (it == patients.end()) {
        std::cout << "No patient found with ID: " << patientId << '\n';
    } else {
        std::cout << "\nPatient found:\n";
        printPatient(*it);
    }
}

void CDSS::showMenu() const {
    std::cout << "\n========== CLINICAL DECISION SUPPORT SYSTEM ==========\n"
              << "1. Register Patient\n"
              << "2. View All Patients\n"
              << "3. Create Symptom Review\n"
              << "4. View Patient Assessment History\n"
              << "5. Search Patient by ID\n"
              << "0. Exit\n"
              << "======================================================\n";
}

void CDSS::run() {
    while (true) {
        showMenu();
        const int choice = getInt("Enter your choice: ", 0, 5);

        switch (choice) {
            case 1: registerPatient(); break;
            case 2: viewAllPatients(); break;
            case 3: createSymptomReview(); break;
            case 4: viewAssessmentHistory(); break;
            case 5: searchPatientById(); break;
            case 0:
                std::cout << "Exiting CDSS. Goodbye.\n";
                return;
        }
    }
}
