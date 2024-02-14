#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Node
{
    ProductData data;
    Node* next;
        
    Node()
    {
        this->next = NULL;
    }

    void InsertNode(ProductData data)
    {
        Node* newNode = new Node();
        newNode->SetData(data);
        this->next = newNode;

    }
    void SetData(ProductData data)
    {
        this->data = data;
    }

};

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
            this->productCategory = "Default Name";
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
};

int main()
{
    std::cout << "Hello World!\n";
}
