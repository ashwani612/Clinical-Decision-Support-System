# Clinical Decision Support System (CDSS)

A console-based Clinical Decision Support System developed in **C++17** for a college project. It stores patient records and symptom-review history in local text files.

## Features

1. Patient registration with automatically generated patient IDs.
2. View all registered patients.
3. Create and save a symptom review.
4. View a patient's assessment history.
5. Search for a patient by ID.

## Requirements

- C++17-compatible compiler (GCC recommended)
- VS Code (optional)
- MSYS2 UCRT64 terminal (Windows setup used for development)

## Compile

Open the terminal in the project folder and run:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp CDSS.cpp -o cdss.exe
```

## Run

```bash
./cdss.exe
```

The application creates a `data` directory and the following local files on first run:

- `data/patients.txt`
- `data/assessments.txt`

These files contain local records and are intentionally excluded from Git using `.gitignore`. Do not commit real patient information.

## Data format

The files use the pipe (`|`) character as a field separator. The application removes pipe characters from entered text to preserve the format.

## Important limitation

This is an educational, rule-based demonstration. It is **not a validated medical device**, does not diagnose disease, and must not be used to make real clinical decisions. Recommendations are generic prompts to seek professional assessment.
