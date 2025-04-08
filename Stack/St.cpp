#include <iostream>

using namespace std;


class BaseStack {
protected:
    int capacity;
    
public:
    BaseStack(int size) : capacity(size) {}
    
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    
    int getCapacity() const {
        return capacity;
    }
    
    virtual ~BaseStack() {}
};

class Stack : public BaseStack {
private:
    int* elements;
    int topIndex;
    
public:
    Stack(int size = 10) : BaseStack(size) {
        elements = new int[capacity];
        topIndex = -1;
    }
    
    ~Stack() {
        delete[] elements;
    }
    
    Stack(const Stack& other) : BaseStack(other.capacity) {
        elements = new int[capacity];
        topIndex = other.topIndex;
        
        for (int i = 0; i <= topIndex; i++) {
            elements[i] = other.elements[i];
        }
    }
    
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] elements;
            
            capacity = other.capacity;
            topIndex = other.topIndex;
            elements = new int[capacity];
            
            for (int i = 0; i <= topIndex; i++) {
                elements[i] = other.elements[i];
            }
        }
        return *this;
    }
    
    bool push(int value) {
        if (isFull()) {
            return false;
        }
        
        topIndex++;
        elements[topIndex] = value;
        return true;
    }
    
    bool pop() {
        if (isEmpty()) {
            return false;
        }
        
        topIndex--;
        return true;
    }
    
    bool top(int& value) const {
        if (isEmpty()) {
            return false;
        }
        
        value = elements[topIndex];
        return true;
    }
    
    int size() const {
        return topIndex + 1;
    }
    
    bool isEmpty() const override {
        return topIndex == -1;
    }
    
    bool isFull() const override {
        return topIndex == capacity - 1;
    }
};

class IntegerStack : public Stack {
public:
    IntegerStack(int size = 10) : Stack(size) {}
    
    int sum() const {
        int total = 0;
        Stack tempStack = *this; 
        int value;
        
        while (tempStack.top(value)) {
            total += value;
            tempStack.pop();
        }
        
        return total;
    }
};

int main() {
    Stack stack(5);  
    int choice, value;
    
    while (true) {
        cout << "=== Stack Operations ===" << endl;
        cout << "1. Push an element" << endl;
        cout << "2. Pop an element" << endl;
        cout << "3. Display the top element" << endl;
        cout << "4. Check if the stack is empty" << endl;
        cout << "5. Check if the stack is full" << endl;
        cout << "6. Display stack size" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter a value to push: ";
                cin >> value;
                if (stack.push(value)) {
                    cout << "Value " << value << " pushed to stack" << endl;
                } else {
                    cout << "Stack is full! Cannot push." << endl;
                }
                break;
                
            case 2:
                if (stack.pop()) {
                    cout << "Element popped from stack" << endl;
                } else {
                    cout << "Stack is empty! Cannot pop." << endl;
                }
                break;
                
            case 3:
                if (stack.top(value)) {
                    cout << "Top element: " << value << endl;
                } else {
                    cout << "Stack is empty! No top element." << endl;
                }
                break;
                
            case 4:
                if (stack.isEmpty()) {
                    cout << "Stack is empty" << endl;
                } else {
                    cout << "Stack is not empty" << endl;
                }
                break;
                
            case 5:
                if (stack.isFull()) {
                    cout << "Stack is full" << endl;
                } else {
                    cout << "Stack is not full" << endl;
                }
                break;
                
            case 6:
                cout << "Current stack size: " << stack.size() << " out of " << stack.getCapacity() << endl;
                break;
                
            case 7:
                cout << "Exiting program..." << endl;
                return 0;
                
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    
    return 0;
}