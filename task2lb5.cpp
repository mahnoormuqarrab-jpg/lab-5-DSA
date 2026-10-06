#include <iostream>
#include <string>
using namespace std;
struct Photo {
    int id;
    string name;
    string date;
    string location;
    Photo *next;
    Photo *prev;
};
Photo *head = NULL;      // first photo
Photo *current = NULL;   // selected photo
int total = 0;           // number of photos
Photo *findPhoto(int id) {
    if (head == NULL) return NULL;
    Photo *temp = head;
    do {
        if (temp->id == id) return temp;
        temp = temp->next;
    } while (temp != head);
    return NULL;
}
void showPhoto(Photo *p) {
    cout << "ID: " << p->id << "  Name: " << p->name << "  Date: " << p->date
         << "  Location: " << p->location << endl;
}
// reads photo details, returns NULL if id already exists
Photo *createPhoto() {
    Photo *n = new Photo;
    cout << "Enter photo ID: ";
    cin >> n->id;
    if (findPhoto(n->id) != NULL) {
        cout << "ID already exists!" << endl;
        delete n;
        return NULL;
    }
    cout << "Enter name: ";
    cin >> n->name;
    cout << "Enter date taken: ";
    cin >> n->date;
    cout << "Enter location: ";
    cin >> n->location;
    return n;
}
// 1. add photo at the end
void addPhoto() {
    Photo *n = createPhoto();
    if (n == NULL) return;
    if (head == NULL) {
        n->next = n;
        n->prev = n;
        head = n;
        current = n;
    } else {
        Photo *tail = head->prev;
        n->next = head;
        n->prev = tail;
        tail->next = n;
        head->prev = n;
    }
    total++;
    cout << "Photo added." << endl;
}
// 2. insert after current
void insertAfterCurrent() {
    if (current == NULL) {
        addPhoto();   // album empty, so just add normally
        return;
    }
    Photo *n = createPhoto();
    if (n == NULL) return;
    n->next = current->next;
    n->prev = current;
    current->next->prev = n;
    current->next = n;
    total++;
    cout << "Photo inserted after current." << endl;
}
// deletes the given node and fixes all the links
void deletePhoto(Photo *p) {
    if (p->next == p) {
        // it was the only photo
        head = NULL;
        current = NULL;
    } else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        if (p == head) head = p->next;
        if (p == current) current = p->next;
    }
    delete p;
    total--;
}
// 3.remove by id
void removeById() {
    int id;
    cout << "Enter photo ID to remove: ";
    cin >> id;
    Photo *p = findPhoto(id);
    if (p == NULL) {
        cout << "Photo not found." << endl;
        return;
    }
    deletePhoto(p);
    cout << "Photo removed." << endl;
}
// 4.remove current photo
void removeCurrent() {
    if (current == NULL) {
        cout << "Album is empty." << endl;
        return;
    }
    deletePhoto(current);
    cout << "Current photo removed." << endl;
}
// 5.move next
void moveNext() {
    if (current == NULL) { cout << "Album is empty." << endl; return; }
    current = current->next;
    showPhoto(current);
}
// 6. move previous
void movePrev() {
    if (current == NULL) { cout << "Album is empty." << endl; return; }
    current = current->prev;
    showPhoto(current);
}

// 7. display forward
void displayForward() {
    if (current == NULL) { cout << "Album is empty." << endl; return; }
    Photo *temp = current;
    do {
        showPhoto(temp);
        temp = temp->next;
    } while (temp != current);
}
// 8. display backward
void displayBackward() {
    if (current == NULL) { cout << "Album is empty." << endl; return; }
    Photo *temp = current;
    do {
        showPhoto(temp);
        temp = temp->prev;
    } while (temp != current);
}
// 9. search
void searchPhoto() {
    int id;
    cout << "Enter photo ID to search: ";
    cin >> id;
    Photo *p = findPhoto(id);
    if (p == NULL) cout << "Photo not found." << endl;
    else showPhoto(p);
}
// 10. count
void countPhotos() {
    cout << "Total photos: " << total << endl;
}
// free everything at the end
void freeAll() {
    if (head == NULL) return;
    head->prev->next = NULL;   // break the circle
    while (head != NULL) {
        Photo *temp = head;
        head = head->next;
        delete temp;
    }
    current = NULL;
    total = 0;
}
int main() {
    int n;
    cout << "How many photos? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Photo " << i + 1 << ":" << endl;
        int before = total;
        addPhoto();
        if (total == before) i--;   // duplicate id, try again
    }
    int choice;
    do {
        cout << "\nPhoto Album" << endl;
        cout << "1. Add photo" << endl;
        cout << "2. Insert photo after current" << endl;
        cout << "3. Remove photo by ID" << endl;
        cout << "4. Remove current photo" << endl;
        cout << "5. Move next" << endl;
        cout << "6. Move previous" << endl;
        cout << "7. Display forward" << endl;
        cout << "8. Display backward" << endl;
        cout << "9. Search photo" << endl;
        cout << "10. Count photos" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addPhoto(); break;
            case 2: insertAfterCurrent(); break;
            case 3: removeById(); break;
            case 4: removeCurrent(); break;
            case 5: moveNext(); break;
            case 6: movePrev(); break;
            case 7: displayForward(); break;
            case 8: displayBackward(); break;
            case 9: searchPhoto(); break;
            case 10: countPhotos(); break;
            case 0: freeAll(); cout << "Bye!" << endl; break;
            default: cout << "Wrong choice." << endl;
        }
    } while (choice != 0);
    return 0;
}