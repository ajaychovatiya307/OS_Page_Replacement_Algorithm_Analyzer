# 🧠 Page Replacement Algorithm Analyzer

A comprehensive C++ simulation framework that analyzes and compares the performance of various page replacement algorithms across different memory configurations and page sizes.

## 📘 Project Overview

This project implements a sophisticated simulation environment for analyzing page replacement algorithms in operating systems. It provides detailed performance metrics by simulating multiple processes with varying page sizes and comparing algorithm efficiency through hit rates and miss counts.

### 🔬 Implemented Algorithms

- **FIFO (First-In-First-Out)**: Pages are replaced in the order they were loaded into memory
- **LRU (Least Recently Used)**: Replaces the page that hasn't been used for the longest time
- **MRU (Most Recently Used)**: Replaces the most recently used page (useful in certain scenarios)
- **OPT (Optimal)**: Theoretical optimal algorithm that replaces the page that will be used furthest in the future

## 🚀 Key Features

- **Multi-Algorithm Comparison**: Simultaneously runs all four algorithms on identical data sets
- **Variable Page Size Analysis**: Tests performance across different page sizes (1 to min(RAM size, process size))
- **Statistical Analysis**: Provides comprehensive hit rate calculations and tabular output
- **Object-Oriented Design**: Clean, modular architecture with singleton patterns and factory methods
- **Random Process Generation**: Creates realistic page reference strings for simulation
- **Performance Aggregation**: Combines results from multiple processes for statistical significance

## 🏗️ Architecture

The project follows object-oriented design principles with the following key components:

### Core Classes

- **`handler`**: Central controller managing simulation parameters and orchestrating analysis
- **`analyze`**: Executes simulations for specific configurations and aggregates results
- **`process`**: Represents individual processes with randomly generated page reference sequences
- **`RAM`**: Abstract base class for page replacement algorithms
- **`history`**: Singleton class maintaining simulation history and results
- **`input`/`output`**: Data management classes for user inputs and simulation results

### Algorithm Classes

- **`FIFO`**: Implements First-In-First-Out using queue data structure
- **`LRU`**: Uses set with timestamps for efficient least recently used tracking
- **`MRU`**: Similar to LRU but replaces most recently used pages
- **`OPT`**: Implements optimal replacement using future reference knowledge

## 🛠️ Technical Implementation

### Memory Simulation
- Generates 100 × number_of_pages random page references per process
- Simulates realistic memory access patterns
- Tracks page hits and misses for each algorithm

### Performance Metrics
- **Hit Rate**: (Total Accesses - Page Faults) / Total Accesses
- **Miss Count**: Number of page faults for each algorithm
- **Comparative Analysis**: Side-by-side algorithm performance

### Data Structures Used
- **FIFO**: `unordered_set` + `queue` for O(1) operations
- **LRU/MRU**: `set<pair<int,int>>` for efficient timestamp-based operations
- **OPT**: Pre-computed next occurrence array with `unordered_set` and `set`

## 📋 Prerequisites

- C++11 or later compiler (g++, clang++, MSVC)
- Standard Template Library (STL) support
- Basic understanding of operating system concepts

## 🚀 Getting Started

### Compilation

```bash
# Clone the repository
git clone <repository-url>
cd OS_Page_Replacement_Algorithm_Analyzer-main

# Navigate to the source directory
cd "Page Replacement Algorithm Analyzer"

# Compile the program
g++ -std=c++11 PageReplacementAnalyzer.cpp -o PageReplacementAnalyzer

# For optimized build
g++ -std=c++11 -O2 PageReplacementAnalyzer.cpp -o PageReplacementAnalyzer
```

### Execution

```bash
./PageReplacementAnalyzer
```

### Input Parameters

The program will prompt for three inputs:
1. **Number of Processes**: How many processes to simulate
2. **RAM Size**: Total available memory (in arbitrary units)
3. **Process Size**: Size of each process (in arbitrary units)

### Sample Execution

```
Enter the number of processes: 5
Enter the RAM size: 1024
Enter the process size: 512
```

### Output Format

The program generates a formatted table showing hit rates for each algorithm across different page sizes:

```
Results:
------------------------------------------------------------
| Page Size | OPT(Hit Rate) | FIFO(Hit Rate) | LRU(Hit Rate) | MRU(Hit Rate) |
------------------------------------------------------------
| 1         | 0.856         | 0.234          | 0.445         | 0.123         |
| 2         | 0.923         | 0.567          | 0.678         | 0.234         |
| ...       | ...           | ...            | ...           | ...           |
------------------------------------------------------------
```

## 🔍 Algorithm Analysis

### FIFO (First-In-First-Out)
- **Time Complexity**: O(1) per operation
- **Space Complexity**: O(k) where k is number of frames
- **Characteristics**: Simple but suffers from Belady's anomaly

### LRU (Least Recently Used)
- **Time Complexity**: O(log k) per operation
- **Space Complexity**: O(k)
- **Characteristics**: Good practical performance, approximates optimal behavior

### MRU (Most Recently Used)
- **Time Complexity**: O(log k) per operation
- **Space Complexity**: O(k)
- **Characteristics**: Useful for specific access patterns, generally performs poorly

### OPT (Optimal)
- **Time Complexity**: O(n) preprocessing + O(log k) per operation
- **Space Complexity**: O(n + k)
- **Characteristics**: Theoretical optimum, requires future knowledge

## 📊 Understanding Results

- **Higher hit rates** indicate better algorithm performance
- **OPT algorithm** provides the theoretical upper bound
- **Page size effects** show how memory granularity impacts performance
- **Comparative analysis** helps choose appropriate algorithms for specific scenarios

## 🔧 Customization

### Adding New Algorithms

1. Create a new class inheriting from `RAM`
2. Implement the `processRAM` method
3. Add the algorithm to the `mapping` unordered_map
4. Assign a unique algorithm ID

### Modifying Process Generation

Adjust the page reference generation in `process::createProcess()`:
- Change `noOfBlocks = 100 * noOfPages` for different reference string lengths
- Modify the random generation pattern for specific access patterns

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/new-algorithm`)
3. Commit changes (`git commit -am 'Add new page replacement algorithm'`)
4. Push to branch (`git push origin feature/new-algorithm`)
5. Create a Pull Request



**Note**: This simulator is designed for educational purposes to understand page replacement algorithm behavior and performance characteristics in controlled environments.
