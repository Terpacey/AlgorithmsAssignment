#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class ProductData
{
public:
    int productID;
    float productPrice;
    string productName, productCategory;

    ProductData()
    {
        this->productID = 0;
        this->productPrice = 0.00f;
        this->productName = "Default Name";
        this->productCategory = "Default Category";
    }

    void SetID(int id)
    {
        this->productID = id;
    }
    void SetPrice(float price)
    {
        this->productPrice = price;
    }
    void SetName(string name)
    {
        this->productName = name;
    }
    void SetCategory(string category)
    {
        this->productCategory = category;
    }

    int GetID()
    {
        return this->productID;
    }
    float GetPrice()
    {
        return this->productPrice;
    }
    string GetName()
    {
        return this->productName;
    }
    string GetCategory()
    {
        return this->productCategory;
    }
    void InsertProductData(int id, float price, string name, string category)
    {
        SetID(id);
        SetPrice(price);
        SetName(name);
        SetCategory(category);
    }
};

class Node
{
public: 
    ProductData data;
    Node* next;
    Node* prev;
        
    Node()
    {
        this->next = nullptr;
        this->prev = nullptr;
    }

    void InsertNode(ProductData data)
    {
        if (this->data.productName == "Default Name")
        {
            SetData(data);
            return;
        }

        if (next != nullptr)
        {
            next->InsertNode(data);
        }
        else
        {
            Node* newNode = new Node();
            newNode->SetData(data);
            this->next = newNode;
            newNode->prev = this;
        }

    }
    void SetData(ProductData data)
    {
        this->data = data;
    }

    Node* Search(int id)
    {
        if (this->data.productID == id)
        {
            return this;
        }
        else if(next == nullptr)
        {
            return nullptr;
        }
        else
        {
            return next->Search(id);
        }
    }

    void NodeDelete(int id)
    {
        Node* delNode;
        delNode = Search(id);
        if (delNode != nullptr)
        {
            if (delNode->next != nullptr)
            {
                delNode->next->prev = delNode->prev;
            }
            if (delNode->prev != nullptr)
            {
                delNode->prev->next = delNode->next;
            }
            
            delete(delNode);
        }
        else
        {
            cout << "\nSpecified Product ID not found in index\n";
        }
    }

    void Update(int id, ProductData data)
    {
        Node* updateNode;
        updateNode = Search(id);
        if(updateNode != nullptr)
        {
            updateNode->SetData(data);
        }
        else
        {
            cout << "\nSpecified Product ID not found in index\n";
        }

    }
};


 vector<string> split(string s, string delimiter) { // Citation for code: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

 void BubbleSort(Node* start)
 {
     Node* first = start;
     while (first != nullptr) {
         Node* second = start;
             while (second != nullptr) {
                 if (first != second) {
                     if (first->data.GetID() < second->data.GetID())
                     {
                         ProductData temp = second->data;
                         second->data = first->data;
                         first->data = temp;
                     }
                 }
                 second = second->next;
             }
         first = first->next;
     }
 }


int main()
{
    ProductData currentData;
    string line, id, price, name, category, delimiter = ", ";

    Node* head = new Node();    

    ifstream datafile;
    datafile.open("product_data.txt");
    
    if (datafile.is_open())
    {
        while (getline(datafile, line))
        {
            vector<string> v = split(line, delimiter);
            currentData.InsertProductData(stoi(v[0]), stof(v[2]), v[1], v[3]);
            head->InsertNode(currentData);
        }
        datafile.close();
    }
    else cout << "Unable to open file\n";

    int choice;
    Node* first;
    Node* search = head;
    do {
        cout << "\nEnter 1 to display the current state of the Linked List, 2 to insert a value, 3 to delete a value, 4 to search for a value and 5 to sort using Bubble sort. Enter 0 to exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1: 
            first = head;
            cout << "\nCurrent list: \n";
            while (first != nullptr)
            {
                cout << "ProductID: "<< first->data.GetID() << "Product Name: " << first->data.GetName() << "Product Price: " << first->data.GetPrice() << "Product Category: " << first->data.GetCategory() << endl;
                first = first->next;
            }
            break;
        case 2:
            cout << "\nEnter ProductID, Price, Name and Category in order\n";
            cin >> id >> price;
            getline(cin, name);
            getline(cin, category);
            currentData.InsertProductData(stoi(id), stof(price), name, category);
            break;
        case 3:
            cout << "\nEnter ProductID to delete\n";
            cin >> id;
            head->NodeDelete(stoi(id));
            break;
        case 4:
            cout << "\nEnter ProductID to search\n";
            cin >> id;
            search->Search(stoi(id));
            cout << "ProductID: " << search->data.GetID() << "Product Name: " << search->data.GetName() << "Product Price: " << search->data.GetPrice() << "Product Category: " << search->data.GetCategory() << endl;
            break;
        case 5:
            BubbleSort(head);
            break;
        case 0: 
            exit;
        default:
            cout << "\nPlease enter a valid choice\n";
            break;

        }
    } while (choice != 0);
    

    

}
