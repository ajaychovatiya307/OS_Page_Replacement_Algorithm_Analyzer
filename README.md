# 🧠 OS_Page_Replacement_Algorithm_Analyzer
 

This repository contains C++ implementations of classic **Operating System** algorithms focusing on **page replacement** and (optionally) **CPU scheduling**. It serves as an educational project to demonstrate how operating systems manage memory and schedule processes.

---

## 📘 Project Overview

This project simulates various **page replacement algorithms** to manage memory frames and (if extended) **CPU scheduling algorithms** to manage process execution. It provides insights into how operating systems make decisions regarding memory and CPU resource allocation.

### Implemented Algorithms:
- **Page Replacement Algorithms:**
  - FIFO (First-In-First-Out)
  - LRU (Least Recently Used)
  - Optimal (OPT)

- **(Optional) CPU Scheduling Algorithms:**  
  *(Add if implemented, e.g., FCFS, SJF, Round Robin)*

---

## 🚀 Features

- Simulates how pages are replaced in memory using different algorithms.
- Calculates and displays the number of page faults.
- Offers comparative performance analysis of algorithms.
- Provides a simple and interactive command-line interface.
- Written in clean, well-commented C++.

---

## 🛠️ Getting Started

### 📋 Prerequisites

- A C++ compiler (e.g., `g++`, `clang`)
- Basic understanding of Operating System concepts

## 🧪 How to Compile and Run

1. Clone the repository:

    ```bash
    git clone <repository-url>
    cd <repository-folder>
    ```

2. Compile the C++ program:

    ```bash
    g++ OS_Page_Replacement_Algo.cpp -o os_simulator
    ```

3. Run the executable:

    ```bash
    ./os_simulator
    ```

4. Follow the on-screen prompts to select algorithms and input page/reference strings or process details.

## 📁 Code Structure

- `PageReplacementAnalyzer.cpp`: Main program file implementing the algorithms.

