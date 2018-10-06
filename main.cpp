#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>
#include <a.out.h>

using namespace std;

void printErrorMessage(const char* errorMessage) {
    cout << "ERROR: " << errorMessage << endl;
}

void toCharArray(string& string, char* array) {
    for (unsigned i = 0; i < string.size(); i++) array[i] = string.at(i);
    array[string.size()] = '\0';// Terminate
}

vector<char*> parseArgs(char* line) {
    vector<char*> argsVector;

    char* token = strtok(line, " ");
    while (token != nullptr) {
        argsVector.push_back(token);
        token = strtok(nullptr, " ");
    }
    return argsVector;
}

void executeCommand(char* line) {
    vector<char*> argsVector = parseArgs(line);
    if (argsVector.empty()) {
        printErrorMessage("No command passed.");
    } else {
        if (strcmp(argsVector.at(argsVector.size() - 1), "&") == 0) {
            /* Prepare arguments */
            argsVector.at(argsVector.size() - 1) = nullptr;
            char* args[argsVector.size()];
            for (int i = 0; i < argsVector.size(); i++) args[i] = argsVector[i];

            if (fork() != 0) { // Parent process continues
                cout << "Running in background" << endl;
            } else {
                if (fork() != 0) { // Process termination handler
                    wait(0);
                    cout << "Process terminated" << endl; // TODO: Log in file
                    exit(-1);
                } else {
                    execvp(args[0], args);
                    // Only returns on failure
                    printErrorMessage("Failed to execute command.");
                    exit(-1);
                }
            }
        } else {
            /* Prepare arguments */
            argsVector.push_back(nullptr);
            char* args[argsVector.size()];
            for (int i = 0; i < argsVector.size(); i++) args[i] = argsVector[i];

            if (fork() != 0) wait(0);
            else {
                execvp(args[0], args);
                // Only returns on failure
                printErrorMessage("Failed to execute command.");
                exit(-1);
            }
        }
    }
}

int main() {

    bool exited = false;
    string line;
    while (!exited) {
        printf("H Shell: Enter command: ");
        getline(cin, line);

        if (line == "exit") {
            exited = true;
        } else {
            char lineArray[line.size() + 1];
            toCharArray(line, lineArray);
            executeCommand(lineArray);
        }
    }

    exit(0);
}