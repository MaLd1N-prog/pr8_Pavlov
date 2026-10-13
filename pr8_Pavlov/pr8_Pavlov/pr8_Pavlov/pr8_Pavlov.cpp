// pr8_Pavlov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Вариант 10. Автомобили
struct Car {
    char model[50];
    int year;
    int mileage;
};
1. Найти автомобиль с минимальным пробегом.
2. Удалить автомобили старше заданного года выпуска.
3. Вставить новый автомобиль перед автомобилем с указанной моделью.
*/

#include <iostream>
#include <fstream>
using namespace std;

struct Car {
    char model[50];
    int year;
    int mileage;
};

struct Node {
    Car data;
    Node* next;
    Node* prev;
};

Node* head = nullptr;
Node* tail = nullptr;


bool isEqual(const char* a, const char* b) {
    int i = 0;
    while (a[i] == b[i] && a[i] != '\0') {
        i++;
    }
    return a[i] == b[i];
}

void push_front(Car c) {
    Node* newNode = new Node;
    newNode->data = c;
    newNode->prev = nullptr;
    newNode->next = head;

    if (head != nullptr) {
        head->prev = newNode;
    }
    else {
        tail = newNode;
    }
    head = newNode;
}

void push_back(Car c) {
    Node* newNode = new Node;
    newNode->data = c;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    }
    else {
        head = newNode;
    }
    tail = newNode;
}

void pop_front() {
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete temp;
    cout << "Удалили первый\n";
}

void pop_back() {
    if (tail == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    Node* temp = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete temp;
    cout << "Удалили последний\n";
}

void showForward() {
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    Node* current = head;
    cout << "\nСписок (от начала к концу):\n";
    while (current != nullptr) {
        cout << "Модель: " << current->data.model
            << " Год: " << current->data.year
            << " Пробег: " << current->data.mileage << endl;
        current = current->next;
    }
}

void showBackward() {
    if (tail == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    Node* current = tail;
    cout << "\nСписок (от конца к началу):\n";
    while (current != nullptr) {
        cout << "Модель: " << current->data.model
            << " Год: " << current->data.year
            << " Пробег: " << current->data.mileage << endl;
        current = current->prev;
    }
}

void clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;
    cout << "Список очищен\n";
}

void findElement() {
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    char searchModel[50];
    cout << "Введите модель: ";
    cin >> searchModel;

    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (isEqual(current->data.model, searchModel)) {
            cout << "Найдено: " << current->data.model<< " " << current->data.year<< " " << current->data.mileage << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "Ничего не найдено\n";
    }
}

// 1. мин пробег
void minMileage() {
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    Node* current = head;
    Node* minNode = head;
    while (current != nullptr) {
        if (current->data.mileage < minNode->data.mileage) {
            minNode = current;
        }
        current = current->next;
    }
    cout << "Минимальный пробег у: " << minNode->data.model << " " << minNode->data.year<< " " << minNode->data.mileage << endl;
}

// 2. удалить старше года
void deleteOld() {
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    int y;
    cout << "Введите год, старше которого удалить: ";
    cin >> y;

    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        if (current->data.year < y) {
            
            if (current == head) {
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
                else {
                    tail = nullptr;
                }
            }
            else if (current == tail) {
                tail = current->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                }
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
        }
        current = nextNode;
    }
    cout << "Готово\n";
}

// 3. вставить перед моделью
void insertBefore() {
    if (head == nullptr) {
        cout << "Список пуст\n";
        return;
    }
    char target[50];
    cout << "Введите модель, перед которой вставить: ";
    cin >> target;

    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (isEqual(current->data.model, target)) {
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Модель не найдена\n";
        return;
    }

    Car c;
    cout << "Введите модель новой машины: ";
    cin >> c.model;
    cout << "Введите год: ";
    cin >> c.year;
    cout << "Введите пробег: ";
    cin >> c.mileage;

    Node* newNode = new Node;
    newNode->data = c;

    if (current == head) {
        newNode->next = head;
        newNode->prev = nullptr;
        head->prev = newNode;
        head = newNode;
    }
    else {
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    cout << "Вставили\n";
}


void saveToFile(const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Файл не открылся\n";
        return;
    }

    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

   
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));

   
    current = head;
    while (current != nullptr) {
        file.write(reinterpret_cast<const char*>(&current->data), sizeof(Car));
        current = current->next;
    }

    file.close();
    cout << "Сохранили " << count << " записей\n";
}


void loadFromFile(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        cout << "Файл не открылся\n";
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
    tail = nullptr;

    int count = 0;
    file.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (int i = 0; i < count; i++) {
        Car c;
        file.read(reinterpret_cast<char*>(&c), sizeof(Car));
        push_back(c);
    }

    file.close();
    cout << "Загрузили " << count << " записей\n";
}

int main()
{
    setlocale(LC_ALL, "RU");
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить в начало\n";
        cout << "2. Добавить в конец\n";
        cout << "3. Удалить первый\n";
        cout << "4. Удалить последний\n";
        cout << "5. Вывести (вперед)\n";
        cout << "6. Вывести (назад)\n";
        cout << "7. Найти по модели\n";
        cout << "8. Найти с мин пробегом\n";
        cout << "9. Удалить старше года\n";
        cout << "10. Вставить перед моделью\n";
        cout << "11. Сохранить в файл\n";
        cout << "12. Загрузить из файла\n";
        cout << "13. Выход\n";
        cout << "Выбор: ";
        cin >> choice;

        switch (choice)
        {
        case 1: {
            Car c;
            cout << "Модель: "; cin >> c.model;
            cout << "Год: "; cin >> c.year;
            cout << "Пробег: "; cin >> c.mileage;
            push_front(c);
            break;
        }
        case 2: {
            Car c;
            cout << "Модель: "; cin >> c.model;
            cout << "Год: "; cin >> c.year;
            cout << "Пробег: "; cin >> c.mileage;
            push_back(c);
            break;
        }
        case 3:
            pop_front();
            break;
        case 4:
            pop_back();
            break;
        case 5:
            showForward();
            break;
        case 6:
            showBackward();
            break;
        case 7:
            findElement();
            break;
        case 8:
            minMileage();
            break;
        case 9:
            deleteOld();
            break;
        case 10:
            insertBefore();
            break;
        case 11:
            saveToFile("cars.bin");
            break;
        case 12:
            loadFromFile("cars.bin");
            break;
        case 13:
            clear();
            cout << "Выход\n";
            break;
        default:
            cout << "Нет такого пункта\n";
        }
    } while (choice != 13);

    return 0;
}