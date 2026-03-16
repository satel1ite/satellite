#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <functional>
#include <limits>
#include <cstdlib>
#include <ctime>


class IAlive {
public:
    virtual int GetFood() const = 0;
    virtual ~IAlive() = default;
};


class IInventory {
public:
    virtual int GetNumber() const = 0;
    virtual ~IInventory() = default;
};

class IPlayerAnimal {
public:
    virtual bool CanInteract() const = 0;
    virtual ~IPlayerAnimal() = default;
};

class IService {
public:
    virtual ~IService() = default;
};

class Animal : public IAlive, public IInventory {
protected:
    std::string name;
    int food;
    int number;

public:
    Animal(const std::string& name, int food, int number)
        : name(name), food(food), number(number) {
    }

    int GetFood() const override { return food; }
    int GetNumber() const override { return number; }
    std::string GetName() const { return name; }

    virtual ~Animal() = default;
};

class Herbo : public Animal, public IPlayerAnimal {
private:
    int kindness;

public:
    Herbo(const std::string& name, int food, int number, int kindness)
        : Animal(name, food, number), kindness(kindness) {
    }

    bool CanInteract() const override { return kindness > 5; }
};

class Predator : public Animal {
public:
    Predator(const std::string& name, int food, int number)
        : Animal(name, food, number) {
    }
};

class Thing : public IInventory {
private:
    std::string name;
    int number;

public:
    Thing(const std::string& name, int number) : name(name), number(number) {}
    int GetNumber() const override { return number; }
    std::string GetName() const { return name; }
    virtual ~Thing() = default;
};

class IVetClinic : public IService {
public:
    virtual bool CheckHealth(Animal* animal) = 0;
};

class VetClinic : public IVetClinic {
public:
    bool CheckHealth(Animal* animal) override {
        std::cout << "[Vet] Examining " << animal->GetName() << "...\n";
        bool isHealthy = (std::rand() % 100) < 80;
        if (isHealthy) {
            std::cout << "[Vet] Verdict: Healthy!\n";
        }
        else {
            std::cout << "[Vet] Verdict: Sick. Rejected.\n";
        }
        return isHealthy;
    }
};

class Zoo : public IService {
private:
    IVetClinic* vet_clinic_;
    std::vector<std::shared_ptr<Animal>> animals_;
    std::vector<std::shared_ptr<Thing>> things_;

public:
    explicit Zoo(IVetClinic* clinic) : vet_clinic_(clinic) {}

    void AddAnimal(std::shared_ptr<Animal> animal) {
        if (vet_clinic_->CheckHealth(animal.get())) {
            animals_.push_back(animal);
            std::cout << "Animal accepted into the zoo.\n";
        }
        else {
            std::cout << "Animal rejected (quarantine).\n";
        }
    }

    void AddThing(std::shared_ptr<Thing> thing) {
        things_.push_back(thing);
        std::cout << "Item added to inventory.\n";
    }

    void PrintFoodReport() const {
        int total = 0;
        std::cout << "\n--- FOOD REPORT ---\n";
        for (const auto& a : animals_) {
            std::cout << a->GetName() << ": " << a->GetFood() << " kg/day\n";
            total += a->GetFood();
        }
        std::cout << "Total: " << total << " kg/day\n";
    }

    void PrintContactZoo() const {
        std::cout << "\n--- CONTACT ZOO ---\n";
        bool found = false;
        for (const auto& a : animals_) {
            auto* player = dynamic_cast<IPlayerAnimal*>(a.get());
            if (player && player->CanInteract()) {
                std::cout << "- " << a->GetName()
                    << " (Inv. #" << a->GetNumber() << ")\n";
                found = true;
            }
        }
        if (!found) std::cout << "No animals available for the contact zoo.\n";
    }

    void PrintInventory() const {
        std::cout << "\n--- INVENTORY ---\n";
        for (const auto& a : animals_) {
            std::cout << "[Animal] " << a->GetName()
                << " | #" << a->GetNumber() << "\n";
        }
        for (const auto& t : things_) {
            std::cout << "[Item  ] " << t->GetName()
                << " | #" << t->GetNumber() << "\n";
        }
    }
};

class DIContainer;
using FactoryFunc = std::function<IService* (DIContainer&)>;

class DIContainer {
private:
    struct ServiceEntry {
        FactoryFunc factory;
        bool is_singleton;
        IService* instance = nullptr;
    };
    std::map<std::string, ServiceEntry> registry_;
    std::vector<std::unique_ptr<IService>> storage_;

public:
    void Register(const std::string& name, FactoryFunc factory, bool singleton) {
        registry_[name] = { factory, singleton, nullptr };
    }

    IService* Resolve(const std::string& name) {
        auto it = registry_.find(name);
        if (it == registry_.end()) return nullptr;

        if (it->second.is_singleton) {
            if (!it->second.instance) {
                it->second.instance = it->second.factory(*this);
                storage_.emplace_back(it->second.instance);
            }
            return it->second.instance;
        }
        IService* fresh = it->second.factory(*this);
        storage_.emplace_back(fresh);
        return fresh;
    }
};

void SetupDI(DIContainer& container) {
    container.Register("VetClinic",
        [](DIContainer&) { return new VetClinic(); }, true);
    container.Register("Zoo",
        [](DIContainer& c) {
            auto* clinic = static_cast<IVetClinic*>(c.Resolve("VetClinic"));
            return new Zoo(clinic);
        }, true);
}

int ReadInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Error! Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string ReadString(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}


int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    DIContainer container;
    SetupDI(container);
    auto* zoo = static_cast<Zoo*>(container.Resolve("Zoo"));

    while (true) {
        std::cout << "\n1. Add animal\n"
            << "2. Add item\n"
            << "3. Food report\n"
            << "4. Contact zoo\n"
            << "5. Inventory\n"
            << "0. Exit\n";
        int choice = ReadInt("> ");

        if (choice == 1) {
            std::string name = ReadString("Name: ");
            int food = ReadInt("Food (kg/day): ");
            int num = ReadInt("Inv. number: ");
            std::cout << "Type: 1. Herbivore  2. Predator\n";
            int type = ReadInt("> ");
            if (type == 1) {
                int k = ReadInt("Kindness level (0-10): ");
                zoo->AddAnimal(std::make_shared<Herbo>(name, food, num, k));
            }
            else {
                zoo->AddAnimal(std::make_shared<Predator>(name, food, num));
            }
        }
        else if (choice == 2) {
            std::string name = ReadString("Name: ");
            int num = ReadInt("Inv. number: ");
            zoo->AddThing(std::make_shared<Thing>(name, num));
        }
        else if (choice == 3) {
            zoo->PrintFoodReport();
        }
        else if (choice == 4) {
            zoo->PrintContactZoo();
        }
        else if (choice == 5) {
            zoo->PrintInventory();
        }
        else if (choice == 0) {
            break;
        }
    }

    return 0;
}