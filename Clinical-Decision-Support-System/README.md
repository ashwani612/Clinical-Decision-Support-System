# 🏥 Clinical Decision Support System (CDSS)

A simple, console-based **Clinical Decision Support System (CDSS)** developed using **C++** as a college academic project.

The system helps organize basic patient information and symptom-review records through a menu-driven interface. It demonstrates fundamental programming concepts such as object-oriented programming, file handling, input validation, and structured data management.

---

## 📌 Project Overview

The Clinical Decision Support System is designed to provide a basic and organized way to manage patient records and preliminary symptom reviews.

The application allows users to register patients, search patient information, record symptoms, and view previous assessment history.

This project is developed for educational purposes to demonstrate how a rule-based healthcare information system can be implemented using C++.

---

## ✨ Features

- **Patient Registration** — Register patients with basic personal details.
- **Automatic Patient ID** — Generate a unique patient ID for each registered patient.
- **View All Patients** — Display the list of registered patients.
- **Symptom Review** — Record patient symptoms and select a preliminary symptom category.
- **Assessment History** — View previously recorded symptom reviews for a patient.
- **Search Patient** — Find a patient using their unique patient ID.
- **Input Validation** — Validate selected inputs to reduce incorrect entries.
- **Local File Storage** — Store patient and assessment records in local text files.

---

## 🛠️ Technologies Used

- C++
- Object-Oriented Programming (OOP)
- File Handling
- Standard Template Library (STL)
- Git and GitHub
- Visual Studio Code

---

## 📂 Project Structure

```text
Clinical-Decision-Support-System/
│
├── main.cpp
├── CDSS.cpp
├── CDSS.h
├── Patient.h
├── README.md
├── .gitignore
│
└── data/
    ├── patients.txt
    └── assessments.txt
```

### File Description

| File | Description |
|---|---|
| `main.cpp` | Main program and menu |
| `CDSS.cpp` | CDSS functionality and operations |
| `CDSS.h` | CDSS class declaration |
| `Patient.h` | Patient data structure |
| `README.md` | Project documentation |
| `.gitignore` | Excludes local data and compiled files |
| `data/` | Stores local patient and assessment records |

---

## 💻 Requirements

- GCC C++ compiler
- Windows operating system
- VS Code (recommended, but optional)
- Git (optional, for version control)

---

## 🚀 How to Run the Project

### Step 1: Clone the Repository

```bash
git clone https://github.com/ashwani612/Clinical-Decision-Support-System.git
```

### Step 2: Open the Project Folder

```bash
cd Clinical-Decision-Support-System/Clinical-Decision-Support-System
```

### Step 3: Create the Data Folder

If the `data` folder does not already exist, create it:

```bash
mkdir data
```

### Step 4: Compile the Program

```bash
g++ -std=c++14 -Wall -Wextra -pedantic main.cpp CDSS.cpp -o cdss.exe
```

### Step 5: Run the Application

In Windows PowerShell:

```powershell
.\cdss.exe
```

---

## 📋 Application Menu

The application provides the following menu options:

```text
========== CLINICAL DECISION SUPPORT SYSTEM ==========

1. Register Patient
2. View All Patients
3. Create Symptom Review
4. View Patient Assessment History
5. Search Patient by ID
0. Exit
```

---

## 💾 Data Storage

Patient and assessment information is stored locally in text files:

- `data/patients.txt`
- `data/assessments.txt`

The application uses the pipe (`|`) character as a field separator.

The `data/` directory and compiled executable files are excluded from GitHub using `.gitignore`.

**Privacy Note:** Do not enter or upload real patient information. Use fictional sample data for demonstrations and academic submissions.

---

## 🎯 Project Objectives

- To understand the practical implementation of C++ programming.
- To demonstrate object-oriented programming concepts.
- To implement file handling for persistent data storage.
- To develop a basic patient information management system.
- To demonstrate a simple rule-based symptom-review workflow.
- To practice software development and version control using GitHub.

---

## ⚠️ Disclaimer

This project is an **educational prototype only**.

It is not a validated medical device and does not diagnose, treat, or prevent any disease. The symptom-review categories and recommendations are basic demonstration logic and must not be used for real clinical decisions.

Always consult a qualified healthcare professional for medical advice.

---

## 👨‍🎓 Academic Project

**Project Title:** Clinical Decision Support System  
**Project Type:** College Academic Project  
**Programming Language:** C++  
**Version:** Evolution 1

---

## 📜 License

This project is created for educational and academic purposes.
