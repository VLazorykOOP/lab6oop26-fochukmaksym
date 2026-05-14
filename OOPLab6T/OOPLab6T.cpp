#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

//  завдання 1


class A {
protected:
    int a;

public:
    A() {
        a = 10;
        cout << "Constructor A\n";
    }

    ~A() {
        cout << "Destructor A\n";
    }
};

class B : public A {
protected:
    int b;

public:
    B() {
        b = 20;
        cout << "Constructor B\n";
    }

    ~B() {
        cout << "Destructor B\n";
    }
};

class C : public A {
protected:
    int c;

public:
    C() {
        c = 30;
        cout << "Constructor C\n";
    }

    ~C() {
        cout << "Destructor C\n";
    }
};

class D : public B, public C {
private:
    int d;

public:
    D() {
        d = 40;
        cout << "Constructor D\n";
    }

    ~D() {
        cout << "Destructor D\n";
    }
};


class AV {
protected:
    int a;

public:
    AV() {
        a = 100;
        cout << "Constructor AV\n";
    }

    virtual ~AV() {
        cout << "Destructor AV\n";
    }
};

class BV : virtual public AV {
protected:
    int b;

public:
    BV() {
        b = 200;
        cout << "Constructor BV\n";
    }

    virtual ~BV() {
        cout << "Destructor BV\n";
    }
};

class CV : virtual public AV {
protected:
    int c;

public:
    CV() {
        c = 300;
        cout << "Constructor CV\n";
    }

    virtual ~CV() {
        cout << "Destructor CV\n";
    }
};

class DV : public BV, public CV {
private:
    int d;

public:
    DV() {
        d = 400;
        cout << "Constructor DV\n";
    }

    ~DV() {
        cout << "Destructor DV\n";
    }
};

// завдання 2


class Human {
protected:
    string name;

public:
    Human(string n) {
        name = n;
        cout << "Human created: " << name << endl;
    }

    virtual ~Human() {
        cout << "Human deleted: " << name << endl;
    }

    virtual void reaction(Human* other) = 0;
};

class Girl : public Human {
public:
    Girl(string n) : Human(n) {}

    void reaction(Human* other) override {
        cout << "Girl " << name
            << " smiles at another person.\n";
    }
};

class Boy : public Human {
public:
    Boy(string n) : Human(n) {}

    void reaction(Human* other) override {
        cout << "Boy " << name
            << " says hello to another person.\n";
    }
};

// завдання 3


class Machine {
protected:
    string brand;
    int speed;

public:
    Machine(string b = "Unknown", int s = 0) {
        brand = b;
        speed = s;
        cout << "Machine constructor\n";
    }

    Machine(const Machine& obj) {
        brand = obj.brand;
        speed = obj.speed;
        cout << "Machine copy constructor\n";
    }

    virtual ~Machine() {
        cout << "Machine destructor\n";
    }

    friend ostream& operator<<(ostream& out, const Machine& m) {
        out << "Brand: " << m.brand
            << ", Speed: " << m.speed;
        return out;
    }

    friend istream& operator>>(istream& in, Machine& m) {
        cout << "Enter brand: ";
        in >> m.brand;

        cout << "Enter speed: ";
        in >> m.speed;

        return in;
    }
};

class PassengerTransport {
protected:
    int passengers;

public:
    PassengerTransport(int p = 0) {
        passengers = p;
        cout << "PassengerTransport constructor\n";
    }

    PassengerTransport(const PassengerTransport& obj) {
        passengers = obj.passengers;
        cout << "PassengerTransport copy constructor\n";
    }

    virtual ~PassengerTransport() {
        cout << "PassengerTransport destructor\n";
    }

    friend ostream& operator<<(ostream& out,
        const PassengerTransport& p) {
        out << "Passengers: " << p.passengers;
        return out;
    }

    friend istream& operator>>(istream& in,
        PassengerTransport& p) {
        cout << "Enter passengers: ";
        in >> p.passengers;
        return in;
    }
};

class Bus : public Machine, public PassengerTransport {
private:
    int routeNumber;

public:
    Bus(string b = "Bus",
        int s = 50,
        int p = 20,
        int r = 1)
        : Machine(b, s), PassengerTransport(p) {

        routeNumber = r;
        cout << "Bus constructor\n";
    }

    Bus(const Bus& obj)
        : Machine(obj), PassengerTransport(obj) {

        routeNumber = obj.routeNumber;
        cout << "Bus copy constructor\n";
    }

    ~Bus() {
        cout << "Bus destructor\n";
    }

    friend ostream& operator<<(ostream& out, const Bus& b) {
        out << "===== BUS INFO =====\n";
        out << "Brand: " << b.brand << endl;
        out << "Speed: " << b.speed << endl;
        out << "Passengers: " << b.passengers << endl;
        out << "Route number: " << b.routeNumber << endl;
        return out;
    }

    friend istream& operator>>(istream& in, Bus& b) {
        cout << "Enter brand: ";
        in >> b.brand;

        cout << "Enter speed: ";
        in >> b.speed;

        cout << "Enter passengers: ";
        in >> b.passengers;

        cout << "Enter route number: ";
        in >> b.routeNumber;

        return in;
    }
};


void testTask1() {

    cout << "\n===== TASK 1 =====\n";

    cout << "\nWITHOUT virtual inheritance:\n";
    D obj1;

    cout << "Size of A: " << sizeof(A) << endl;
    cout << "Size of B: " << sizeof(B) << endl;
    cout << "Size of C: " << sizeof(C) << endl;
    cout << "Size of D: " << sizeof(D) << endl;

    cout << "\nWITH virtual inheritance:\n";
    DV obj2;

    cout << "Size of AV: " << sizeof(AV) << endl;
    cout << "Size of BV: " << sizeof(BV) << endl;
    cout << "Size of CV: " << sizeof(CV) << endl;
    cout << "Size of DV: " << sizeof(DV) << endl;
}

void testTask2() {

    cout << "\n===== TASK 2 =====\n";

    Human* g = new Girl("Anna");
    Human* b = new Boy("Ivan");

    g->reaction(b);
    b->reaction(g);

    delete g;
    delete b;
}

void keyboardInput() {

    cout << "\nInput from keyboard\n";

    Bus b;
    cin >> b;

    cout << b;
}

void fileInput() {

    cout << "\nInput from file\n";

    ifstream file("bus.txt");

    if (!file) {
        cout << "File not found!\n";
        return;
    }

    string brand;
    int speed;
    int passengers;
    int route;

    file >> brand;
    file >> speed;
    file >> passengers;
    file >> route;

    cout << "===== BUS INFO =====\n";
    cout << "Brand: " << brand << endl;
    cout << "Speed: " << speed << endl;
    cout << "Passengers: " << passengers << endl;
    cout << "Route number: " << route << endl;

    file.close();
}

void randomInput() {

    cout << "\nRandom generated object\n";

    srand(time(0));

    Bus b(
        "RandomBus",
        rand() % 120,
        rand() % 60,
        rand() % 100
    );

    cout << b;
}

void testTask3() {

    cout << "\n===== TASK 3 =====\n";

    Bus b1;

    cout << "\nEnter bus information:\n";
    cin >> b1;

    cout << "\nBus object:\n";
    cout << b1;

    cout << "\nTesting copy constructor:\n";
    Bus b2 = b1;

    cout << b2;

    keyboardInput();
    fileInput();
    randomInput();
}


int main() {

    int choice;

    do {

        cout << "\n=============================\n";
        cout << "LABORATORY WORK MENU\n";
        cout << "=============================\n";

        cout << "1 - Task 1\n";
        cout << "2 - Task 2\n";
        cout << "3 - Task 3\n";
        cout << "4 - Run all tests\n";
        cout << "0 - Exit\n";

        cout << "Choose: ";
        cin >> choice;

        switch (choice) {

        case 1:
            testTask1();
            break;

        case 2:
            testTask2();
            break;

        case 3:
            testTask3();
            break;

        case 4:
            testTask1();
            testTask2();
            testTask3();
            break;

        case 0:
            cout << "Program finished.\n";
            break;

        default:
            cout << "Wrong choice!\n";
        }

    } while (choice != 0);

    return 0;
}
