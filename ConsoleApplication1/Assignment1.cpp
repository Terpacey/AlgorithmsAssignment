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

    Node* GetIndex(int index)
    {
        Node* first = prev;
        while (prev != nullptr)
        {
            first = first->prev;
        }
        for (int i = 0; i < index; i++)
        {
            first = first->next;
            if (first = nullptr)
            {
                return nullptr;
            }
        }
        return first;

    }

    void NodeDelete(int id)
    {
        Node* delNode;
        delNode = Search(id);
        if (delNode != nullptr)
        {
            delNode->prev->next = delNode -> next;
            delNode->next->prev = delNode -> prev;
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

    int count()
    {
        if (next == nullptr)
        {
            return 1;
        }
        else
        {
            return 1 + next->count();
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


     ProductData data;
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
     //for (int i = 0; i < start->count(); i++) 
     //{
     //    for (int j = 0; j < start->count() - i; j++)
     //    {
     //        Node* currentNode;
     //        Node* next;
     //        currentNode = start->GetIndex(j);
     //        next = start->GetIndex(j+1);
     //        data = currentNode->data;

     //        if (next != nullptr)
     //        {
     //            //return;
     //            if (currentNode->data.GetID() > next->data.GetID())
     //            {
     //                currentNode->data = next->data;
     //                next->data = data;
     //            }
     //        }
     //        
     //    }
     //    cout << "Mlem";
     //}
 }


int main()
{
    ProductData currentData;
    string line, id, price, name, category, delimiter = ", ";

    Node* head = new Node();    

    fstream datafile;
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
    else cout << "Unable to open file";

    BubbleSort(head);
    for (int i = 0; i < head->count(); i++)
    {
        cout << head->GetIndex(i)->data.GetID() << endl;
    }


}
