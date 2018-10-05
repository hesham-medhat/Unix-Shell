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
    } else if (argsVector.size() == 1) {
        if (fork() != 0) wait(nullptr);
        else execvp(argsVector.at(0), &argsVector.at(0));
    } else {
       if (argsVector.at(argsVector.size() - 1) == "&") {

       }
        // TODO: Execute the command

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