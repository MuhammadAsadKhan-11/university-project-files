#include <iostream>
using namespace std;

struct Person {
    string name;
    int age;
    string contact;
};

class Event {
public:
    string name;
    string date;
    string time;
    string location;
    int capacity;
    Person organizer;
    Event* prev;
    Event* next;

    Event() {
        prev = next = NULL;
        capacity = 0;
    }
};

class EventPlanner {
private:
    Event* head;
    Event* tail;

public:
	//constructor to initialize the head and tail of pointer
    EventPlanner() {
        head = NULL;
        tail = NULL;
    }
// adding new event to the list
    void addEvent(string name, string date, string time, string location, int capacity, string organizerName, string organizerContact) {
        Event* newEvent = new Event;
        newEvent->name = name;
        newEvent->date = date;
        newEvent->time = time;
        newEvent->location = location;
        newEvent->capacity = capacity;
        newEvent->organizer.name = organizerName;
        newEvent->organizer.contact = organizerContact;

        if (head == NULL) {
            head = newEvent;
            tail = newEvent;
        }
        else {
            tail->next = newEvent;
            newEvent->prev = tail;
            tail = newEvent;
        }

        cout << "Event added successfully!" << endl << endl;
    }
// removing event from the list
    bool deleteEvent(string eventName) {
        if (isEmpty()) {
            cout << "Event List is Empty" << endl;
        }
        else {
            Event* temp = head;
            while (temp != NULL) {
                if (temp->name == eventName) {
                    if (temp->prev != NULL) {
                        temp->prev->next = temp->next;
                    }
                    else {
                        head = temp->next;
                    }

                    if (temp->next != NULL) {
                        temp->next->prev = temp->prev;
                    }
                    else {
                        tail = temp->prev;
                    }

                    delete temp;
                    cout << "Event Deleted: " << eventName << endl;
                    return true;
                }
                temp = temp->next;
            }
            cout << "Event Not Found" << endl;
        }
        return false;
    }

// to check if the event list is empty 
    bool isEmpty() {
        return (head == NULL);
    }

    // Function to search for an event by name
    bool searchEvent(string eventName) {
        Event* temp = head;
        while (temp != NULL) {
            if (temp->name == eventName) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    // displaying event of the list
    void displayEvents() {
        if (isEmpty()) {
            cout << "Event List is Empty" << endl;
        }
        else {
            Event* temp = head;
            cout << "Events:" << endl;
            while (temp != NULL) {
                cout << "Name: " << temp->name << ", Date: " << temp->date << ", Time: " << temp->time
                    << ", Location: " << temp->location << ", Capacity: " << temp->capacity << endl;
                cout << "Organizer: " << temp->organizer.name << " (" << temp->organizer.contact << ")" << endl;
                cout << endl;
                temp = temp->next;
            }
        }
    }
};
//represents a participants who can join events and i inherited it from person structure
class Participant : public Person {
public:
    string participatingEvent;// to store the event the particcipant wants to join
    int rear, front;
    int size = 5;
    Person* arr;// to store info of participant

    Participant() {
        arr = new Person[size];
        rear = front = -1;
    }

    bool isFull() {
        return rear == size - 1;
    }

    bool isEmpty() {
        return front == -1 && rear == -1;
    }
// to add participant to an event
    void participate(EventPlanner& planner) {
        char choice;
        cout << "Enter Event name to Participate: ";
        cin.ignore();
        getline(cin, participatingEvent);

        if (planner.isEmpty()) {
            cout << "Event List is Empty" << endl;
            return;
        }

        if (planner.searchEvent(participatingEvent)) {
            cout << "Event Found" << endl;
            do {
                if (isFull()) {
                    cout << "Maximum Participants Reached" << endl;
                    break;
                }
                cout << "Enter Name: ";
                getline(cin, arr[++rear].name);
                cout << "Enter Age: ";
                cin >> arr[rear].age;
                cin.ignore();
                cout << "Enter Contact: ";
                getline(cin, arr[rear].contact);

                cout << "Add another participant? (Y/y): ";
                cin >> choice;
            } while (choice=='Y'||choice=='y');
        }
        else {
            cout << "Event Not Found" << endl;
        }
    }
};

int main() {
	// planner object
    EventPlanner planner;
    //participants object
    Participant participants;
    int choice;
    string name, date, time, location, organizerName, organizerContact;
    int capacity;

    do {
        cout << "|| MENU ||" << endl;
        cout << "1. Add Event" << endl;
        cout << "2. Delete Event" << endl;
        cout << "3. Display Events" << endl;
        cout << "4. Participate" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            // Adding an event
            cout << "Enter details for the event:" << endl;
            cout << "Event Name: ";
            getline(cin, name);
            cout << "Date: ";
            getline(cin, date);
            cout << "Time: ";
            getline(cin, time);
            cout << "Location: ";
            getline(cin, location);
            cout << "Capacity: ";
            cin >> capacity;
            cin.ignore();
            cout << "Organizer Name: ";
            getline(cin, organizerName);
            cout << "Organizer Contact: ";
            getline(cin, organizerContact);
            planner.addEvent(name, date, time, location, capacity, organizerName, organizerContact);
            break;

        case 2:
            // Deleting an event
            cout << "Enter the name of the event to delete: ";
            getline(cin, name);
            if (!planner.deleteEvent(name))
                cout << "Event Not Found" << endl;
            break;

        case 3:
            // Displaying events
            planner.displayEvents();
            break;

        case 4:
            // Participate in an event
            participants.participate(planner);
            break;

        case 5:
            cout << "Program Ended Successfully" << endl;
            break;

        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}
