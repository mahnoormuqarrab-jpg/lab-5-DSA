#include <iostream>
#include <string>
using namespace std;
struct Coach {
    int number;
    string type;
    int capacity;
    int passengers;
    Coach *next;
    Coach *prev;
};
Coach *head = NULL;      // first coach
Coach *current = NULL;   // selected coach
int total = 0;           // number of coaches
Coach *findCoach(int num) {
    if (head == NULL) return NULL;
    Coach *temp = head;
    do {
        if (temp->number == num) return temp;
        temp = temp->next;
    } while (temp != head);
    return NULL;
}
void showCoach(Coach *c) {
    cout << "Coach No: " << c->number << "  Type: " << c->type
         << "Capacity: " << c->capacity << "  Passengers: " << c->passengers
         << "Empty seats: " << c->capacity - c->passengers << endl;
}
//reads coach details, returns null if input is not valid
Coach *createCoach() {
    Coach *n = new Coach;
    cout << "Enter coach number: ";
    cin >> n->number;
    if (findCoach(n->number) != NULL) {
        cout << "Coach number already exists!" << endl;
        delete n;
        return NULL;
    }
    cout << "Enter coach type: ";
    cin >> n->type;
    cout << "Enter capacity: ";
    cin >> n->capacity;
    cout << "Enter current passengers: ";
    cin >> n->passengers;
    if (n->passengers > n->capacity || n->passengers < 0) {
        cout << "Passengers cannot be more than capacity!" << endl;
        delete n;
        return NULL;
    }
    return n;
}
// 1. add coach at end
void addCoach() {
    Coach *n = createCoach();
    if (n == NULL) return;
    if (head == NULL) {
        n->next = n;
        n->prev = n;
        head = n;
        current = n;
    } else {
        Coach *tail = head->prev;
        n->next = head;
        n->prev = tail;
        tail->next = n;
        head->prev = n;
    }
    total++;
    cout << "Coach added." << endl;
}
// 2. insert after a given coach number
void insertCoach() {
    int after;
    cout << "Insert after which coach number? ";
    cin >> after;
    Coach *pos = findCoach(after);
    if (pos == NULL) {
        cout << "Coach not found." << endl;
        return;
    }
    Coach *n = createCoach();
    if (n == NULL) return;
    n->next = pos->next;
    n->prev = pos;
    pos->next->prev = n;
    pos->next = n;
    total++;
    cout << "Coach inserted." << endl;
}
// 3. remove coach by number
void removeCoach() {
    int num;
    cout << "Enter coach number to remove: ";
    cin >> num;
    Coach *c = findCoach(num);
    if (c == NULL) {
        cout << "Coach not found." << endl;
        return;
    }
    if (c->next == c) {
        // only one coach
        head = NULL;
        current = NULL;
    } else {
        c->prev->next = c->next;
        c->next->prev = c->prev;
        if (c == head) head = c->next;
        if (c == current) current = c->next;   // next coach becomes current
    }
    delete c;
    total--;
    cout << "Coach removed." << endl;
}
// 4. move forward
void moveForward() {
    if (current == NULL) { cout << "Train is empty." << endl; return; }
    current = current->next;
    showCoach(current);
}
// 5. move backward
void moveBackward() {
    if (current == NULL) { cout << "Train is empty." << endl; return; }
    current = current->prev;
    showCoach(current);
}
// 6. display clockwise
void displayClockwise() {
    if (head == NULL) { cout << "Train is empty." << endl; return; }
    Coach *temp = head;
    do {
        showCoach(temp);
        temp = temp->next;
    } while (temp != head);
}
// 7. display anti-clockwise
void displayAnticlockwise() {
    if (head == NULL) { cout << "Train is empty." << endl; return; }
    Coach *temp = head;
    do {
        showCoach(temp);
        temp = temp->prev;
    } while (temp != head);
}
// 8. search coach
void searchCoach() {
    int num;
    cout << "Enter coach number to search: ";
    cin >> num;
    Coach *c = findCoach(num);
    if (c == NULL) cout << "Coach not found." << endl;
    else showCoach(c);
}
// 9. coach with the most empty seats
void maxCapacity() {
    if (head == NULL) { cout << "Train is empty." << endl; return; }
    Coach *best = head;
    Coach *temp = head->next;
    while (temp != head) {
        if (temp->capacity - temp->passengers > best->capacity - best->passengers) {
            best = temp;
        }
        temp = temp->next;
    }
    cout << "Coach with most empty seats:" << endl;
    showCoach(best);
}
// 10. display current coach
void displayCurrent() {
    if (current == NULL) { cout << "Train is empty." << endl; return; }
    showCoach(current);
}
// 11. reverse the train by swapping next and prev of every node
void reverseTrain() {
    if (head == NULL) { cout << "Train is empty." << endl; return; }
    Coach *temp = head;
    do {
        Coach *nextNode = temp->next;   // save next before we change it
        temp->next = temp->prev;
        temp->prev = nextNode;
        temp = nextNode;
    } while (temp != head);
    head = head->next;   // old tail is now the first coach
    cout << "Train reversed." << endl;
}
// free everything at the end
void freeAll() {
    if (head == NULL) return;
    head->prev->next = NULL;   // break the circle
    while (head != NULL) {
        Coach *temp = head;
        head = head->next;
        delete temp;
    }
    current = NULL;
    total = 0;
}
int main() {
    int n;
    cout << "How many coaches? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Coach " << i + 1 << ":" << endl;
        int before = total;
        addCoach();
        if (total == before) i--;   // invalid input, try again
    }
    int choice;
    do {
        cout << "\n--- Train Coach System ---" << endl;
        cout << "1. Add coach" << endl;
        cout << "2. Insert coach after" << endl;
        cout << "3. Remove coach" << endl;
        cout << "4. Move forward" << endl;
        cout << "5. Move backward" << endl;
        cout << "6. Display train clockwise" << endl;
        cout << "7. Display train anti-clockwise" << endl;
        cout << "8. Search coach" << endl;
        cout << "9. Find max available capacity" << endl;
        cout << "10. Display current coach" << endl;
        cout << "11. Reverse train direction" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addCoach(); break;
            case 2: insertCoach(); break;
            case 3: removeCoach(); break;
            case 4: moveForward(); break;
            case 5: moveBackward(); break;
            case 6: displayClockwise(); break;
            case 7: displayAnticlockwise(); break;
            case 8: searchCoach(); break;
            case 9: maxCapacity(); break;
            case 10: displayCurrent(); break;
            case 11: reverseTrain(); break;
            case 0: freeAll(); cout << "Bye!" << endl; break;
            default: cout << "Wrong choice." << endl;
        }
    } while (choice != 0);
    return 0;
}