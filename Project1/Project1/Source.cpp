#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Team {
    string name;
    int points;
    Team* next;
    Team* prev;
};

void insertTeam(Team*& first, Team*& last, const string& name, int points) {
    Team* newTeam = new Team;
    newTeam->name = name;
    newTeam->points = points;
    newTeam->next = nullptr;
    newTeam->prev = last;

    if (last != nullptr) {
        last->next = newTeam;
    }

    if (first == nullptr) {
        first = newTeam;
    }

    last = newTeam;
}

void printTeams(Team* first) {
    while (first != nullptr) {
        cout << "Team: " << first->name << ", Points: " << first->points << endl;
        first = first->next;
    }
}

void deleteHalfTeams(Team*& first, Team*& last) {
    
    int count = 0;
    Team* current = first;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    int teamsToDelete = count / 2;

   
    for (int i = 0; i < teamsToDelete; i++) {
 
        Team* minNode = first;
        current = first->next;
        while (current != nullptr) {
            if (current->points < minNode->points) {
                minNode = current;
            }
            current = current->next;
        }
        Team* prevNode = minNode->prev;
        Team* nextNode = minNode->next;
        if (prevNode != nullptr) {
            prevNode->next = nextNode;
        }
        else {
            first = nextNode;
        }
        if (nextNode != nullptr) {
            nextNode->prev = prevNode;
        }
        else {
            last = prevNode;
        }
        cout << "Eliminated team: " << minNode->name << endl;
        delete minNode;
    }
}


int main() {
    Team* first = nullptr;
    Team* last = nullptr;

    ifstream inputFile("teams.txt");
    if (!inputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string name;
    int points;
    while (inputFile >> name >> points) {
        insertTeam(first, last, name, points);
    }
    inputFile.close();

    cout << "Initial teams:" << endl;
    printTeams(first);

    int rounds = 0;
    while (first != nullptr && first->next != nullptr) {
        rounds++;
        cout << "\nRound " << rounds << ":" << endl;
        deleteHalfTeams(first, last);
        cout << "\nRemaining teams after round " << rounds << ":" << endl;
        printTeams(first);
    }

    cout << "\nTotal rounds: " << rounds << endl;

    while (first != nullptr) {
        Team* temp = first;
        first = first->next;
        delete temp;
    }

    return 0;
}
