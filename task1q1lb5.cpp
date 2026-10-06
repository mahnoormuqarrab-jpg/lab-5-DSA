#include <iostream>
#include <string>
using namespace std;
struct Tab {
    int id;
    string title;
    string url;
    Tab *next;
    Tab *prev;
};
Tab *current = NULL;   // the active tab
// find a tab by id returns NULL if not found
Tab *findTab(int id) {
    if (current == NULL) return NULL;
    Tab *temp = current;
    do {
        if (temp->id == id) return temp;
        temp = temp->next;
    } while (temp != current);
    return NULL;
}
void showTab(Tab *t) {
    cout << "ID: " << t->id << "  Title: " << t->title << "  URL: " << t->url << endl;
}
//1.open new tab after current
void openTab() {
    Tab *n = new Tab;
    cout << "Enter tab ID: ";
    cin >> n->id;
    if (findTab(n->id) != NULL) {
        cout << "This ID already exists!" << endl;
        delete n;
        return;
    }
    cout << "Enter title (one word): ";
    cin >> n->title;
    cout << "Enter URL: ";
    cin >> n->url;
    if (current == NULL) {
        // first tab, points to itself
        n->next = n;
        n->prev = n;
    } else {
        n->next = current->next;
        n->prev = current;
        current->next->prev = n;
        current->next = n;
    }
    current = n;   // new tab becomes active
    cout << "Tab opened." << endl;
}
//2.close current tab
void closeTab() {
    if (current == NULL) {
        cout << "No tabs open." << endl;
        return;
    }
    Tab *temp = current;
    if (current->next == current) {
        // only one tab
        current = NULL;
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        current = temp->next;   // next tab becomes current
    }
    delete temp;
    cout << "Tab closed." << endl;
}
// 3. move next
void moveNext() {
    if (current == NULL) { cout << "No tabs open." << endl; return; }
    current = current->next;
    showTab(current);
}
// 4. move previous
void movePrev() {
    if (current == NULL) { cout << "No tabs open." << endl; return; }
    current = current->prev;
    showTab(current);
}
// 5. show current tab
void displayCurrent() {
    if (current == NULL) { cout << "No tabs open." << endl; return; }
    showTab(current);
}
// 6. show all forward
void displayForward() {
    if (current == NULL) { cout << "No tabs open." << endl; return; }
    Tab *temp = current;
    do {
        showTab(temp);
        temp = temp->next;
    } while (temp != current);   // stop when we come back to start
}
// 7. show all backward
void displayBackward() {
    if (current == NULL) { cout << "No tabs open." << endl; return; }
    Tab *temp = current;
    do {
        showTab(temp);
        temp = temp->prev;
    } while (temp != current);
}
// 8. search
void searchTab() {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;
    Tab *t = findTab(id);
    if (t == NULL) cout << "Tab not found." << endl;
    else showTab(t);
}
// delete all nodes before exit
void freeAll() {
    if (current == NULL) return;
    current->prev->next = NULL;   // break the circle
    while (current != NULL) {
        Tab *temp = current;
        current = current->next;
        delete temp;
    }
}
int main() {
    int choice;
    do {
        cout << "\nBrowser Tab Manager" << endl;
        cout << "1. Open new tab" << endl;
        cout << "2. Close current tab" << endl;
        cout << "3. Move next" << endl;
        cout << "4. Move previous" << endl;
        cout << "5. Display current tab" << endl;
        cout << "6. Display all tabs forward" << endl;
        cout << "7. Display all tabs backward" << endl;
        cout << "8. Search tab" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: openTab(); break;
            case 2: closeTab(); break;
            case 3: moveNext(); break;
            case 4: movePrev(); break;
            case 5: displayCurrent(); break;
            case 6: displayForward(); break;
            case 7: displayBackward(); break;
            case 8: searchTab(); break;
            case 0: freeAll(); cout << "Bye!" << endl; break;
            default: cout << "Wrong choice." << endl;
        }
    } while (choice != 0);
    return 0;
}