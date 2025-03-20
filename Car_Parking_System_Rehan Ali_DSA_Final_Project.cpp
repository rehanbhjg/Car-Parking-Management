#include <iostream>
#include <conio.h>
#include <fstream>
#include <queue>
using namespace std;

// UI Class
class UI
{
public:
    void header()
    {
        cout << "\t\t**" << endl;
        cout << "\t\t***                  CAR PARKING SYSTEM                    ***" << endl;
        cout << "\t\t**" << endl;
    }

    string mainMenu(string option)
    {
        header();
        cout << "\t MAIN MENU : " << endl;
        cout << "\t-----------------------------------" << endl;
        cout << "\t1). Insert the record." << endl;
        cout << "\t2). Search the record." << endl;
        cout << "\t3). Update the record." << endl;
        cout << "\t4). Delete all records." << endl;
        cout << "\t5). Show all records." << endl;
        cout << "\t6). Add to waiting queue." << endl;
        cout << "\t7). Show waiting queue." << endl;
        cout << "\t8). Exit." << endl;
        cout << "\t------------------------------------" << endl;
        cout << "\t Your Choice : ";
        cin >> option;

        return option;
    }

    void clear_screen()
    {
        cout << "\t Press any key to continue..." << endl;
        getch();
        system("CLS");
    }
};

// Doubly Linked List Node
struct Node
{
    string driverName;
    string timeSlot;
    string carNumber;
    Node *prev;
    Node *next;

    Node(string dName, string tSlot, string cNumber)
    {
        driverName = dName;
        timeSlot = tSlot;
        carNumber = cNumber;
        prev = NULL;
        next = NULL;
    }
};

// Binary Search Tree Node
struct BSTNode
{
    string driverName;
    string timeSlot;
    string carNumber;
    BSTNode *left;
    BSTNode *right;

    BSTNode(string dName, string tSlot, string cNumber)
    {
        driverName = dName;
        timeSlot = tSlot;
        carNumber = cNumber;
        left = NULL;
        right = NULL;
    }
};

// Car Class
class Car
{
private:
    Node *head, *tail;
    BSTNode *bstRoot;
    queue<string> waitingQueue;

public:
    Car()
    {
        head = NULL;
        tail = NULL;
        bstRoot = NULL;
    }

    // Doubly Linked List: Insert Record
    void insertRecord(string driverName, string timeSlot, string carNumber)
    {
        Node *newNode = new Node(driverName, timeSlot, carNumber);
        if (!head)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        bstRoot = insertToBST(bstRoot, driverName, timeSlot, carNumber);
    }

    // Doubly Linked List: Show Records
    void showRecords()
    {
        if (!head)
        {
            cout << "\tNo records available." << endl;
            return;
        }

        Node *temp = head;
        while (temp)
        {
            cout << "\t Driver Name : " << temp->driverName << endl;
            cout << "\t Time Slot : " << temp->timeSlot << endl;
            cout << "\t Car Number : " << temp->carNumber << endl;
            cout << "\t ------------------------------------" << endl;
            temp = temp->next;
        }
    }

    // Doubly Linked List: Search Record
    void searchRecord(string carNumber)
    {
        BSTNode *result = searchBST(bstRoot, carNumber);
        if (result)
        {
            cout << "\t Driver Name : " << result->driverName << endl;
            cout << "\t Time Slot : " << result->timeSlot << endl;
            cout << "\t Car Number : " << result->carNumber << endl;
        }
        else
        {
            cout << "\t Record not found." << endl;
        }
    }

    // Doubly Linked List: Update Record
    void updateRecord(string carNumber)
    {
        Node *temp = head;
        while (temp)
        {
            if (temp->carNumber == carNumber)
            {
                cout << "\t Record found. Enter new details." << endl;
                cout << "\t Enter the Driver Name : ";
                cin >> temp->driverName;
                cout << "\t Enter the Time Slot : ";
                cin >> temp->timeSlot;
                cout << "\t Record updated successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "\t Record not found." << endl;
    }

    // Doubly Linked List: Delete All Records
    void deleteAllRecords()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = NULL;

        deleteBST(bstRoot);
        bstRoot = NULL;

        while (!waitingQueue.empty())
            waitingQueue.pop();

        cout << "\t All records deleted successfully." << endl;
    }

    // Waiting Queue: Add Car
    void addToWaitingQueue(string carNumber)
    {
        waitingQueue.push(carNumber);
        cout << "\tCar added to waiting queue." << endl;
    }

    // Waiting Queue: Show Queue
    void showWaitingQueue()
    {
        if (waitingQueue.empty())
        {
            cout << "\tNo cars in the waiting queue." << endl;
            return;
        }

        queue<string> tempQueue = waitingQueue;
        while (!tempQueue.empty())
        {
            cout << "\tCar Number: " << tempQueue.front() << endl;
            tempQueue.pop();
        }
    }

private:
    // Binary Search Tree: Insert
    BSTNode *insertToBST(BSTNode *root, string driverName, string timeSlot, string carNumber)
    {
        if (!root)
            return new BSTNode(driverName, timeSlot, carNumber);

        if (carNumber < root->carNumber)
            root->left = insertToBST(root->left, driverName, timeSlot, carNumber);
        else if (carNumber > root->carNumber)
            root->right = insertToBST(root->right, driverName, timeSlot, carNumber);

        return root;
    }

    // Binary Search Tree: Search
    BSTNode *searchBST(BSTNode *root, string carNumber)
    {
        if (!root || root->carNumber == carNumber)
            return root;

        if (carNumber < root->carNumber)
            return searchBST(root->left, carNumber);

        return searchBST(root->right, carNumber);
    }

    // Binary Search Tree: Delete
    void deleteBST(BSTNode *root)
    {
        if (!root)
            return;

        deleteBST(root->left);
        deleteBST(root->right);
        delete root;
    }
};

// Main Function
int main()
{
    string option, driverName, carNumber, timeSlot;
    UI show;
    Car parkingSystem;

    while (true)
    {
        option = show.mainMenu(option);

        if (option == "1")
        {
            cout << "\t Enter the Driver Name : ";
            cin >> driverName;
            cout << "\t Enter the Time Slot : ";
            cin >> timeSlot;
            cout << "\t Enter the Car Number : ";
            cin >> carNumber;

            parkingSystem.insertRecord(driverName, timeSlot, carNumber);
            show.clear_screen();
        }
        else if (option == "2")
        {
            cout << "\t Enter the Car Number : ";
            cin >> carNumber;

            parkingSystem.searchRecord(carNumber);
            show.clear_screen();
        }
        else if (option == "3")
        {
            cout << "\t Enter the Car Number to update: ";
            cin >> carNumber;

            parkingSystem.updateRecord(carNumber);
            show.clear_screen();
        }
        else if (option == "4")
        {
            parkingSystem.deleteAllRecords();
            show.clear_screen();
        }
        else if (option == "5")
        {
            parkingSystem.showRecords();
            show.clear_screen();
        }
        else if (option == "6")
        {
            cout << "\t Enter the Car Number to add to the waiting queue: ";
            cin >> carNumber;

            parkingSystem.addToWaitingQueue(carNumber);
            show.clear_screen();
        }
        else if (option == "7")
        {
            parkingSystem.showWaitingQueue();
            show.clear_screen();
        }
        else if (option == "8")
        {
            cout << "Exit." << endl;
            show.clear_screen();
            break;
        }
        else
        {
            cout << "Invalid option." << endl;
            show.clear_screen();
        }
    }
    return 0;
}
