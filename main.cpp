#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

void printErrorMessage(const char* errorMessage) {
    cout << "ERROR: " << errorMessage << endl;
}

void toCharArray(string& string, char* array) {
    for (int i = 0; i < string.size(); i++) array[i] = string.at(i);
    array[string.size()] = '\0';// Terminate
}

bool isWhiteSpace(char character) { return character == ' ' || character == '\t'; }

vector<char*> parseArgs(char* line) {
    vector<char*> argsVector;

    int i = 0;
    char* token = strtok(line, " ");
    while (token != NULL) {
        argsVector.push_back(token);
        token = strtok(NULL, " ");
    }
    return argsVector;
}

void executeCommand(char* line) {
    vector<char*> argsVector = parseArgs(line);
    if (argsVector.empty()) {
        printErrorMessage("No command passed.");
    } else {
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