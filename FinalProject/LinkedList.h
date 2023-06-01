#pragma once
#include <iostream>

class Node
{
    std::string Data;
    Node* Next;

public:
    Node(std::string a = 0, Node* ptr = NULL)
    {
        Data = a;
        Next = ptr;
    }

    void SetData(std::string a)
    {
        Data = a;
    }

    void SetNext(Node* ptr)
    {
        Next = ptr;
    }


    std::string getData() const { return Data; }
    Node* getNext() const { return Next; }
};

class LinkedList
{
    Node* Head;
    int Count;

public:
    LinkedList()
    {
        Head = NULL;
        Count = 0;
    }

    int GetCount()
    {
        return Count;
    }

    Node* GetHead()
    {
        return Head;
    }

    void EndInsert(std::string Data)
    {
        Count++;
        Node* NewNode = new Node;
        Node* ptr = Head;
        if (IsEmpty())
        {
            HeadInsert(Data);
            return;
        }

        while (ptr->getNext() != NULL)
        {
            ptr = ptr->getNext();
        }
        ptr->SetNext(NewNode);
        NewNode->SetData(Data);
    }

    void HeadInsert(std::string Data)
    {
        Count++;
        Node* NewNode = new Node;
        if (Head == NULL)
        {
            Head = NewNode;
            NewNode->SetNext(NULL);
            NewNode->SetData(Data);

            return;
        }
        NewNode->SetNext(Head);
        NewNode->SetData(Data);
        Head = NewNode;
    }

    bool IsEmpty()
    {
        return (Head == NULL);
    }

    Node* Search(std::string data)
    {
        Node* ptr = Head;
        Node* ExistPtr = NULL;

        while (ptr->getNext() != NULL)
        {
            if (ptr->getData() == data)
            {
                ExistPtr = ptr;
                break;
            }
        }
        return ExistPtr;
    }

    bool Update(std::string Check, std::string Replace)
    {
        Node* UpdatePtr = Search(Check);
        if (UpdatePtr != NULL)
        {
            UpdatePtr->SetData(Replace);
            return true;
        }

        else
            return  false;
    }

    bool UpdateIndex(int Index, std::string Replace)
    {
        Node* ptr = Head;
        for (int i = 1; i < Index || ptr != NULL; i++)
        {
            ptr = ptr->getNext();
        }

        if (ptr != NULL)
        {
            ptr->SetData(Replace);
            return true;
        }

        else
            return  false;
    }

    void IndexInsert(int Index, std::string Data)
    {

        if (Index == 0)
        {
            HeadInsert(Data);
            return;
        }

        Node* NewNode = new Node;
        Node* ptr = Head;

        for (int i = 1; i < Index || ptr == NULL; i++)
        {
            ptr = ptr->getNext();
        }
        if (ptr != NULL)
        {
            NewNode->SetNext(ptr->getNext());
            ptr->SetNext(NewNode);
            NewNode->SetData(Data);
        }
    }

    bool Delete(std::string Data)
    {
        if (IsEmpty())
        {
            return false;
        }

        Node* ptr = Head;
        if (Head->getData() == Data)
        {
            Head = Head->getNext();
            delete ptr;
            return true;
        }

        while (ptr->getNext()->getData() != Data || ptr == NULL)
        {
            ptr = ptr->getNext();
        }

        if (ptr != NULL)
        {
            ptr->SetNext(ptr->getNext()->getNext());
            return true;
        }

        else
            return false;
    }


    void Print()
    {
        if (!IsEmpty())
        {
            Node* ptr = Head;
            while (ptr != NULL)
            {
                std::cout << ptr->getData() << '\n';
                ptr = ptr->getNext();
            }
            std::cout << "List End\n";
        }

    }
};
