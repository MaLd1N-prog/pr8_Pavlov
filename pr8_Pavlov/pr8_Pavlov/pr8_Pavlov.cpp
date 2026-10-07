// pr8_Pavlov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
/*
Вариант 10. Автомобили
Структура данных:
struct Car {
    char model[50];
    int year;
    int mileage;
};
Дополнительные операции:
1. Найти автомобиль с минимальным пробегом.
2. Удалить автомобили старше заданного года выпуска.
3. Вставить новый автомобиль перед автомобилем с указанной моделью.
*/

#include <iostream>
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

bool isEqual(const char* str1, const char* str2) {
    while (*str1 && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *str1 == *str2;
}
Car inputCar() {
    Car c;
    cout << "Введите модель: ";
    cin >> c.model;
    cout << "Введите год выпуска: ";
    cin >> c.year;
    cout << "Введите пробег: ";
    cin >> c.mileage;
    return c;
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
        cout << "Список пуст.\n";
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
    cout << "Первый элемент удален.\n";
}

void pop_back() {
    if (tail == nullptr) {
        cout << "Список пуст.\n";
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
    cout << "Последний элемент удален.\n";
}

void display_forward() {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    Node* current = head;
    cout << "\nСписок автомобилей (начало -> конец)\n";
    while (current != nullptr) {
        cout << "Модель: " << current->data.model
            << "  Год: " << current->data.year
            << "  Пробег: " << current->data.mileage << endl;
        current = current->next;
    }
 
}

void display_backward() {
    if (tail == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    Node* current = tail;
    cout << "\n Список автомобилей (конец -> начало)\n";
    while (current != nullptr) {
        cout << "Модель: " << current->data.model
            << "  Год: " << current->data.year
            << "  Пробег: " << current->data.mileage << endl;
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
    cout << "Список полностью очищен.\n";
}


void findElement() {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    char searchModel[50];
    cout << "Введите модель для поиска: ";
    cin >> searchModel;

    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (isEqual(current->data.model, searchModel)) {
            cout << "Найден: Модель " << current->data.model
                << " Год: " << current->data.year
                << " Пробег: " << current->data.mileage << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) cout << "Автомобиль с такой моделью не найден.\n";
}



// 1.
void findMinMileage() {
    if (head == nullptr) {
        cout << "Список пуст.\n";
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

    cout << "Автомобиль с минимальным пробегом: \n";
    cout << "Модель: " << minNode->data.model
        << " Год: " << minNode->data.year
        << " Пробег: " << minNode->data.mileage << endl;
}

// 2. 
void deleteOlderThan() {
    if (head == nullptr) {
        cout << "Список пуст.\n";
        return;
    }
    int thresholdYear;
    cout << "Введите год: удалить автомобили старше (меньше) этого года: ";
    cin >> thresholdYear;

    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next; 

        if (current->data.year < thresholdYear) {
         
            if (current == head) {
                head = current->next;
                if (head) head->prev = nullptr;
                else tail = nullptr;
            }
            else if (current == tail) {
                tail = current->prev;
                if (tail) tail->next = nullptr;
            }
            else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
        }
        current = nextNode;
    }
    cout << "Удаление завершено.\n";
}

// 3. 
void insertBeforeModel() {
    if (head == nullptr) {
        cout << "Список пуст. Добавьте элементы.\n";
        return;
    }
    char targetModel[50];
    cout << "Введите модель автомобиля, ПЕРЕД которым нужно вставить новый: ";
    cin >> targetModel;

    Node* current = head;
    bool found = false;
    while (current != nullptr) {
        if (isEqual(current->data.model, targetModel)) {
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Автомобиль с моделью " << targetModel << " не найден.\n";
        return;
    }

    cout << "Введите данные нового автомобиля:\n";
    Car newCar = inputCar();
    Node* newNode = new Node;
    newNode->data = newCar;

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
    cout << "Автомобиль вставлен перед " << targetModel << ".\n";
}

int main()
{
  
     setlocale(LC_ALL, "RU");

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить элемент в начало\n";
        cout << "2. Добавить элемент в конец\n";
        cout << "3. Удалить первый элемент\n";
        cout << "4. Удалить последний элемент\n";
        cout << "5. Вывести список (вперед)\n";
        cout << "6. Вывести список (назад)\n";
        cout << "7. Найти элемент по модели\n";
        cout << "8. Найти авто с мин. пробегом\n";
        cout << "9. Удалить авто старше заданного года\n";
        cout << "10. Вставить авто перед указанной моделью\n";
        cout << "11. Выход\n";
        cout << "Введите номер меню: ";

        cin >> choice;

        switch (choice)
        {
        case 1: {
            Car c = inputCar();
            push_front(c);
            break;
        }
        case 2: {
            Car c = inputCar();
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
            display_forward();
            break;
        case 6:
            display_backward();
            break;
        case 7:
            findElement();
            break;
        case 8:
            findMinMileage();
            break;
        case 9:
            deleteOlderThan();
            break;
        case 10:
            insertBeforeModel();
            break;
        case 11:
            clear(); 
            cout << "Вы вышли!\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова\n";
        }
    } while (choice != 11);

    return 0;
}