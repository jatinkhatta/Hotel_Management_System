#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Room class
class Room {
public:
    int roomNumber;
    string roomType;
    bool isAvailable;

    Room(int number, const string& type) 
        : roomNumber(number), roomType(type), isAvailable(true) {}

    void display() const {
        cout << "Room Number: " << roomNumber
             << ", Type: " << roomType
             << ", Status: " << (isAvailable ? "Available" : "Booked") << endl;
    }
};

// Guest class
class Guest {
public:
    string name;
    int age;
    string phoneNumber;

    Guest(const string& guestName, int guestAge, const string& phone) 
        : name(guestName), age(guestAge), phoneNumber(phone) {}

    void display() const {
        cout << "Guest Name: " << name 
             << ", Age: " << age 
             << ", Phone: " << phoneNumber << endl;
    }
};

// Booking class
class Booking {
public:
    Room* room;
    Guest* guest;

    Booking(Room* r, Guest* g) : room(r), guest(g) {
        room->isAvailable = false;
    }

    void display() const {
        cout << "Booking Details:" << endl;
        room->display();
        guest->display();
    }
};

// Hotel class
class Hotel {
private:
    vector<Room> rooms;
    vector<Booking> bookings;

public:
    void addRoom(int roomNumber, const string& roomType) {
        rooms.emplace_back(roomNumber, roomType);
    }

    void bookRoom(int roomNumber, const string& guestName, int age, const string& phoneNumber) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber && room.isAvailable) {
                Guest* guest = new Guest(guestName, age, phoneNumber);
                bookings.emplace_back(&room, guest);
                cout << "Room " << roomNumber << " successfully booked!" << endl;
                return;
            }
        }
        cout << "Room " << roomNumber << " is not available!" << endl;
    }

    void showAvailableRooms() const {
        cout << "Available Rooms:" << endl;
        for (const auto& room : rooms) {
            if (room.isAvailable) {
                room.display();
            }
        }
    }

    void showBookedRooms() const {
        cout << "Booked Rooms:" << endl;
        for (const auto& booking : bookings) {
            booking.display();
        }
    }
};

// Main function
int main() {
    Hotel hotel;

    // Adding rooms to the hotel
    hotel.addRoom(101, "Single");
    hotel.addRoom(102, "Double");
    hotel.addRoom(103, "Suite");

    int choice;
    do {
        cout << "\nHotel Management System\n";
        cout << "1. Show Available Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Show Booked Rooms\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.showAvailableRooms();
                break;
            case 2: {
                int roomNumber;
                string guestName;
                int age;
                string phoneNumber;
                
                cout << "Enter Room Number: ";
                cin >> roomNumber;
                cout << "Enter Guest Name: ";
                cin.ignore();
                getline(cin, guestName);
                cout << "Enter Age: ";
                cin >> age;
                cout << "Enter Phone Number: ";
                cin >> phoneNumber;
                
                hotel.bookRoom(roomNumber, guestName, age, phoneNumber);
                break;
            }
            case 3:
                hotel.showBookedRooms();
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
