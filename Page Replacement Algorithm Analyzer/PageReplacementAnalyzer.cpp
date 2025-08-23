/**********************************************************************************
 * Project Name : Page Replacement Algorithm Analyzer
 * Author       : Ajay Chovatiya
 * Description  : This project simulates various page replacement algorithms 
                  including FIFO, LRU, MRU, and OPT to analyze their performance
                  based on hit and miss rates. The simulator runs across multiple
                  page sizes and process configurations, then aggregates and
                  displays performance metrics in a tabular format.
   
                  Core components include:
                  - Input/Output Management
                  - Process Simulation
                  - Algorithm Execution Logic
                  - Statistical History Tracking
 
                 Designed using OOP principles to ensure modularity and clarity.
 **********************************************************************************/

#include <bits/stdc++.h>
using namespace std;

// Constants to represent types of statistics
const int MISS = 0;
const int TOTAL = 1;

// Forward Declarations
class history;
class handler;
class input;
class output;
class analyze;
class Process;
class RAM;
class algoData;
class FIFO;
class LRU;
class MRU;

// Singleton class to maintain history of input-output pairs
class history {
private:
    static history *currentInstance;                               // Singleton instance
    vector<pair<input *, output *>> hist;                          // List of input-output history

public:
    static history *getInstance();                                 // Accessor for singleton instance
    history(){};                                                   // Default constructor

    void updateHistory(input *in, output *out);                    // Append new input-output entry
    pair<input *, output *> getLastElement();                      // Retrieve most recent entry
    void printCurrentStats();                                      // Display statistics from last entry
};

// Central controller class to manage simulation parameters
class handler {
    int RAMSize;                                                   // Size of RAM
    int noOfProcess;                                               // Total number of processes
    int processSize;                                               // Size of each process

    handler(int RAMSize, int noOfProcess, int processSize);        // Private constructor

public:
    static handler *createHandler();                               // Factory method to instantiate handler
    void analyzeOnAllPageSize();                                   // Run analysis for varying page sizes
    void printAnalyzedData();                                      // Output the analyzed data
};

// Class to execute simulation and aggregate performance metrics
class analyze {
    int noOfProcess;                                               // Number of processes to simulate
    int noOfPages;                                                 // Total pages in a process
    int noOfRAMPages;                                              // Pages that can fit in RAM
    vector<vector<int>> curOutput;                                 // Temporary output holder

    analyze(int noOfProcess, int RAMSize, int processSize);        // Private constructor

public:
    static analyze *createAnalyze(int noOfProcess, int RAMSize, int processSize, int pageSize); // Factory method
    void runProcesses();                                           // Initiate execution of processes

private:
    void mergeOutput(vector<vector<int>> curOutput);               // Combine individual results
};

// Class representing a simulated process with generated page references
class process {
    int noOfRAMPages;                                              // RAM size in pages
    int noOfPages;                                                 // Total number of page references
    vector<int> pageID;                                            // Generated page reference string

    process(int noOfPages, int noOfRAMPages, vector<int> pageID); // Private constructor

public:
    static process *createProcess(int noOfPages, int noOfRAMPages); // Factory method
    vector<vector<int>> runProcess();                              // Execute simulation with current algorithm
};

// Abstract base class for RAM behavior simulation
class RAM {
protected:
    int noOfRAMPages;                                              // Available RAM pages
    int noOfPages;                                                 // Total process pages
    vector<int> pageID;                                            // Page reference sequence

public:
    RAM(int noOfRAMPages, int noOfPages, vector<int> pageID);      // Constructor

    virtual vector<int> processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) = 0; // Pure virtual method
};

// Data structure to encapsulate algorithm creation function and identifier
class algoData {
public:
    function<RAM *(int, int, vector<int>)> createFunction;         // Function to instantiate algorithm class
    int algoID;                                                    // Unique identifier for algorithm

    algoData(function<RAM *(int, int, vector<int>)> createFunction, int algoID); // Constructor
};

// Class to hold user inputs (singleton-like)
class input {
    int RAMSize;                                                   // Total RAM size
    int noOfProcess;                                               // Number of processes
    int processSize;                                               // Size of each process

    input(int RAMSize, int noOfProcess, int processSize);          // Private constructor

private:
    static input *getInput();                                      // Singleton accessor

public:
    static void createHistory();                                   // Trigger history creation
    int getRAMSize();                                              // Getter for RAM size
    int getNoOfProcess();                                          // Getter for number of processes
    int getProcessSize();                                          // Getter for process size
};

// Class to accumulate and merge output from simulations
class output {
    output();                                                      // Private constructor

public:
    vector<vector<vector<int>>> mainOutput;                        // Aggregated simulation results

    void mergeOutput(vector<vector<int>> curOutput);               // Merge result into main output
    static output *getOutput();                                    // Singleton accessor
};

// FIFO (First-In-First-Out) page replacement algorithm
class FIFO : public RAM {
public:
    FIFO(int noOfRAMPages, int noOfPages, vector<int> pageID) : RAM(noOfRAMPages, noOfPages, pageID) {}

    vector<int> processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) override; // FIFO logic
};

// LRU (Least Recently Used) page replacement algorithm
class LRU : public RAM {
public:
    LRU(int noOfRAMPages, int noOfPages, vector<int> pageID) : RAM(noOfRAMPages, noOfPages, pageID) {}

    vector<int> processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) override; // LRU logic
};

// MRU (Most Recently Used) page replacement algorithm
class MRU : public RAM {
public:
    MRU(int noOfRAMPages, int noOfPages, vector<int> pageID) : RAM(noOfRAMPages, noOfPages, pageID) {}

    vector<int> processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) override; // MRU logic
};

// OPT (Optimal) page replacement algorithm (requires future knowledge)
class OPT : public RAM {
public:
    OPT(int noOfRAMPages, int noOfPages, vector<int> pageID) : RAM(noOfRAMPages, noOfPages, pageID) {}

    vector<int> processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) override; // Optimal logic
};

// Mapping algorithm names to their corresponding factory functions and unique identifiers
unordered_map<string, algoData *> mapping = {
    {"OPT", new algoData([](int noOfRAMPages, int noOfPages, vector<int> pageID)
                         { return new OPT(noOfRAMPages, noOfPages, pageID); }, 1)},
    {"FIFO", new algoData([](int noOfRAMPages, int noOfPages, vector<int> pageID)
                          { return new FIFO(noOfRAMPages, noOfPages, pageID); }, 2)},
    {"LRU", new algoData([](int noOfRAMPages, int noOfPages, vector<int> pageID)
                         { return new LRU(noOfRAMPages, noOfPages, pageID); }, 3)},
    {"MRU", new algoData([](int noOfRAMPages, int noOfPages, vector<int> pageID)
                         { return new MRU(noOfRAMPages, noOfPages, pageID); }, 4)}};

// ------------------------------
// Definition: history class
// ------------------------------
history *history::currentInstance = NULL;

void history::printCurrentStats() {
    input *currInput = hist.back().first;
    output *currOutput = hist.back().second;

    int noOfRows = currOutput->mainOutput.size();
    int noOfColumns = mapping.size() + 1;

    vector<vector<string>> table(noOfRows, vector<string>(noOfColumns));
    cout << "Results:" << endl;

    table[0][0] = "Page Size";
    for (int i = 1; i < noOfRows; i++) {
        table[i][0] = to_string(i);
    }

    for (auto it : mapping) {
        table[0][it.second->algoID] = it.first + "(Hit Rate)";
        for (int i = 1; i < noOfRows; i++) {
            int total = currOutput->mainOutput[i][it.second->algoID][TOTAL];
            int miss = currOutput->mainOutput[i][it.second->algoID][MISS];
            table[i][it.second->algoID] = to_string(1.0 * (total - miss) / total);
        }
    }

    // Padding cells for alignment
    for (int j = 0; j < noOfColumns; j++) {
        int mxLen = 0;
        for (int i = 0; i < noOfRows; i++) {
            mxLen = max(mxLen, (int)table[i][j].size());
        }
        for (int i = 0; i < noOfRows; i++) {
            while ((int)table[i][j].size() != mxLen) {
                table[i][j] += ' ';
            }
        }
    }

    // Construct visual table
    vector<string> rowString(noOfRows + 2);
    for (int i = 0; i < noOfRows; i++) {
        rowString[i + 1] += "| ";
        for (int j = 0; j < noOfColumns; j++) {
            rowString[i + 1] += table[i][j] + " | ";
        }
    }

    // Top and bottom borders
    while (rowString[0].size() != rowString[1].size()) {
        rowString[0] += "-";
        rowString[noOfRows + 1] += "-";
    }

    for (auto it : rowString) {
        cout << it << endl;
    }
}

history *history::getInstance() {
    if (currentInstance == NULL)
        currentInstance = new history();
    return currentInstance;
}

void history::updateHistory(input *in, output *out) {
    hist.push_back({in, out});
}

pair<input *, output *> history::getLastElement() {
    return hist.back();
}

// ------------------------------
// Definition: output class
// ------------------------------
output::output() {}

output *output::getOutput() {
    return new output();
}

void output::mergeOutput(vector<vector<int>> curOutput) {
    this->mainOutput.push_back(curOutput);
}

// ------------------------------
// Definition: input class
// ------------------------------
input::input(int RAMSize, int noOfProcess, int processSize) {
    this->RAMSize = RAMSize;
    this->noOfProcess = noOfProcess;
    this->processSize = processSize;
}

input *input::getInput() {
    int RAMSize, noOfProcess, processSize;

    cout << "Enter the number of processes: ";
    cin >> noOfProcess;
    cout << "Enter the RAM size: ";
    cin >> RAMSize;
    cout << "Enter the process size: ";
    cin >> processSize;

    return new input(RAMSize, noOfProcess, processSize);
}

void input::createHistory() {
    input *in = input::getInput();
    output *out = output::getOutput();
    history::getInstance()->updateHistory(in, out);
}

int input::getRAMSize() { return RAMSize; }
int input::getNoOfProcess() { return noOfProcess; }
int input::getProcessSize() { return processSize; }

// ------------------------------
// Definition: handler class
// ------------------------------
handler::handler(int RAMSize, int noOfProcess, int processSize) {
    this->RAMSize = RAMSize;
    this->noOfProcess = noOfProcess;
    this->processSize = processSize;
}

handler *handler::createHandler() {
    history *instance = history::getInstance();
    input::createHistory();
    input *curInput = instance->getLastElement().first;
    return new handler(curInput->getRAMSize(), curInput->getNoOfProcess(), curInput->getProcessSize());
}

void handler::analyzeOnAllPageSize() {
    for (int curPageSize = 0; curPageSize <= min(RAMSize, processSize); curPageSize++) {
        analyze *curAnalyze = analyze::createAnalyze(noOfProcess, RAMSize, processSize, curPageSize);
        curAnalyze->runProcesses();
    }
}

void handler::printAnalyzedData() {
    history::getInstance()->printCurrentStats();
}

// ------------------------------
// Definition: analyze class
// ------------------------------
analyze::analyze(int noOfProcess, int noOfPages, int noOfRAMPages) {
    this->noOfProcess = noOfProcess;
    this->noOfPages = noOfPages;
    this->noOfRAMPages = noOfRAMPages;
}

analyze *analyze::createAnalyze(int noOfProcess, int RAMSize, int processSize, int pageSize) {
    int noOfPages = (pageSize == 0) ? -1 : ((processSize + pageSize - 1) / pageSize);
    int noOfRAMPages = (pageSize == 0) ? -1 : (RAMSize / pageSize);
    return new analyze(noOfProcess, noOfPages, noOfRAMPages);
}

void analyze::runProcesses() {
    for (int i = 0; i < noOfProcess; i++) {
        process *curProcess = process::createProcess(noOfPages, noOfRAMPages);
        vector<vector<int>> curOutput = curProcess->runProcess();
        mergeOutput(curOutput);
    }

    output *mainOutput = history::getInstance()->getLastElement().second;
    mainOutput->mergeOutput(this->curOutput);
}

void analyze::mergeOutput(vector<vector<int>> curOutput) {
    for (int i = 0; i < curOutput.size(); i++) {
        if (this->curOutput.size() > i) {
            this->curOutput[i][TOTAL] += curOutput[i][TOTAL];
            this->curOutput[i][MISS] += curOutput[i][MISS];
        } else {
            this->curOutput.push_back(curOutput[i]);
        }
    }
}

// ------------------------------
// Definition: process class
// ------------------------------
process::process(int noOfPages, int noOfRAMPages, vector<int> pageID) {
    this->noOfPages = noOfPages;
    this->noOfRAMPages = noOfRAMPages;
    this->pageID = pageID;
}

process *process::createProcess(int noOfPages, int noOfRAMPages) {
    vector<int> pageID;
    int noOfBlocks = 100 * noOfPages;

    for (int i = 0; i < noOfBlocks; i++) {
        int pid = (rand() % noOfPages) + 1;
        pageID.push_back(pid);
    }

    return new process(noOfPages, noOfRAMPages, pageID);
}

vector<vector<int>> process::runProcess() {
    vector<vector<int>> processOutput(mapping.size() + 1, vector<int>(2, -1));
    for (auto it : mapping) {
        if (noOfPages == -1) {
            processOutput[it.second->algoID] = {-1, -1};
            continue;
        }
        RAM *algoInstance = it.second->createFunction(noOfPages, noOfRAMPages, pageID);
        processOutput[it.second->algoID] = algoInstance->processRAM(noOfPages, noOfRAMPages, pageID);
    }
    return processOutput;
}

// ------------------------------
// Definition: RAM class
// ------------------------------
RAM::RAM(int noOfRAMPages, int noOfPages, vector<int> pageID) {
    this->noOfPages = noOfPages;
    this->noOfRAMPages = noOfRAMPages;
    this->pageID = pageID;
}

// ------------------------------
// Definition: algoData class
// ------------------------------
algoData::algoData(function<RAM *(int, int, vector<int>)> createFunction, int algoID) {
    this->algoID = algoID;
    this->createFunction = createFunction;
}

// ------------------------------
// Algorithm Implementations
// ------------------------------
vector<int> FIFO::processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) {
    int missCount = 0, total = pageID.size();
    unordered_set<int> cache;
    queue<int> order;

    for (int id : pageID) {
        if (!cache.count(id)) {
            missCount++;
            if (cache.size() == noOfRAMPages) {
                cache.erase(order.front());
                order.pop();
            }
            cache.insert(id);
            order.push(id);
        }
    }
    return {missCount, total};
}

vector<int> LRU::processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) {
    int missCount = 0, total = pageID.size();
    unordered_set<int> cache;
    unordered_map<int, int> lastUsed;

    for (int i = 0; i < total; i++) {
        if (!cache.count(pageID[i])) {
            missCount++;
            if (cache.size() == noOfRAMPages) {
                int lru = INT_MAX, val;
                for (int p : cache)
                    if (lastUsed[p] < lru)
                        lru = lastUsed[p], val = p;
                cache.erase(val);
            }
            cache.insert(pageID[i]);
        }
        lastUsed[pageID[i]] = i;
    }
    return {missCount, total};
}

vector<int> MRU::processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) {
    int missCount = 0, total = pageID.size();
    unordered_set<int> cache;
    unordered_map<int, int> lastUsed;

    for (int i = 0; i < total; i++) {
        if (!cache.count(pageID[i])) {
            missCount++;
            if (cache.size() == noOfRAMPages) {
                int mru = -1, val;
                for (int p : cache)
                    if (lastUsed[p] > mru)
                        mru = lastUsed[p], val = p;
                cache.erase(val);
            }
            cache.insert(pageID[i]);
        }
        lastUsed[pageID[i]] = i;
    }
    return {missCount, total};
}

vector<int> OPT::processRAM(int noOfPages, int noOfRAMPages, vector<int> pageID) {
    int missCount = 0, total = pageID.size();

    vector<int> next(total, total);
    map<int, int> futureIndex;
    for (int i = total - 1; i >= 0; i--) {
        if (futureIndex.count(pageID[i]))
            next[i] = futureIndex[pageID[i]];
        futureIndex[pageID[i]] = i;
    }

    unordered_set<int> cache;
    set<int> occSet;

    for (int i = 0; i < total; i++) {
        if (!cache.count(pageID[i])) {
            if (cache.size() == noOfRAMPages) {
                int removeAt = *occSet.rbegin();
                occSet.erase(removeAt);
                cache.erase(pageID[removeAt]);
            }
            cache.insert(pageID[i]);
            occSet.insert(next[i]);
            missCount++;
        } else {
            occSet.erase(i);
            occSet.insert(next[i]);
        }
    }
    return {missCount, total};
}

// ------------------------------
// Entry Point
// ------------------------------
int main() {
    handler *run = handler::createHandler();
    run->analyzeOnAllPageSize();
    run->printAnalyzedData();
    return 0;
}
