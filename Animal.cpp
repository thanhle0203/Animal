#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Animal {
private:
    int age;
public:
    Animal() : age(0) { };
    virtual ~Animal() { };
    virtual void Speak() { cout << "Growl. " << endl; };
    void Grow() { age++; };
};

class Dog : public Animal {
public:
    Dog() { };
    void Speak() { cout << "Woof!" << endl; };
};

class Cat : public Animal {
private:
    int num_lives;
    int* lives;
public:
    Cat() : num_lives(9) {
        lives = new int[num_lives];
        for (int i=0; i<num_lives; i++) {
            cout << lives[i] << endl;
        }
    };
    //When delete aptr is called, the dynamically allocated array in Cat::lives is freed
    ~Cat() {
        cout << "Cat destructor called" << endl;
        delete[] lives;
    };
    void Speak() { cout << "Meow." << endl; }
    void Print() {
        cout <<"=====PRINTING CAT =====" << endl;
        for (int i=0; i<num_lives; i++) {
            cout << lives[i] << endl;
        }
    };
};

// Take any of the above 30 animals as argument and
// make it speak using the most specific (most derived class) Speak() function.
void MakeAnimalSpeak(Animal* aptr) {
    aptr->Speak();
};

// The Separate function that recieves a vector of Animal*
// and puts all the pointers to Dogs in the dogs vectors,
// and all pointers to Cat in the cats vector.
void Separate(const vector<Animal*>& a, vector<Dog*>& d, vector<Cat*>& c) {
    for (auto aptr : a) {
        if (dynamic_cast<Dog*>(aptr) != nullptr)
            d.push_back(dynamic_cast<Dog*> (aptr));
        else if (dynamic_cast<Cat*>(aptr) != nullptr)
            c.push_back(dynamic_cast<Cat*> (aptr));
    }
};

int main() {
    Animal a_array[10];
    Dog d_array[10];
    Cat c_array[10];

    MakeAnimalSpeak(&(c_array[3]));

    Animal* aptr = new Cat;
    aptr->Grow();
    delete aptr;

    cout << "Cat" << endl;

    vector<Dog*> dogs;
    vector<Cat*> cats;
    vector<Animal*> animals;

    for (int i=0; i<20; i++) {
        int r = rand() % 3;
        if (r == 0) {
            animals.push_back(new Dog);
        } else if (r == 1) {
            animals.push_back(new Cat);
        } else if (r == 2) {
            animals.push_back(new Animal);
        }
    }

    Separate(animals, dogs, cats);
    cout << endl << endl << "Printing cats" << endl;
    for (int i=0; i<cats.size(); i++) {
        cats[i]->Speak();
    }

    return 0;
}
