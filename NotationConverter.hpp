#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include <iostream>
#include <string>

#include "NotationConverterInterface.hpp"

typedef std::string Elem;

// linked liist node
class Node
{
private:
    Elem elem;
    Node *prev;
    Node *next;
    friend class LinkedList;
};

// linked list class
class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    bool empty() const;
    const Elem &front() const;
    const Elem &back() const;
    void addFront(const Elem &e);
    void addBack(const Elem &e);
    void removeFront();
    void removeBack();

private:
    Node *head;
    Node *tail;

protected:
    void add(Node *v, const Elem &e);
    void remove(Node *v);
};

// CalcList Linked List class, extends the CalcListInterface class
class NotationConverter : public NotationConverterInterface
{
    LinkedList D;
    int n; // Number of elements, used in size
public:
    // Default Functions
    NotationConverter();
    bool empty() const;
    int size() const;
    const Elem &front() const;
    const Elem &back() const;
    void insertFront(const Elem &e);
    void insertBack(const Elem &e);
    void removeFront();
    void removeBack();

    // Required Functions
    std::string postfixToInfix(std::string inStr);
    std::string postfixToPrefix(std::string inStr);
    std::string infixToPostfix(std::string inStr);
    std::string infixToPrefix(std::string inStr);
    std::string prefixToInfix(std::string inStr);
    std::string prefixToPostfix(std::string inStr);
};

// exception classes
class Exception
{
public:
    Exception(const std::string &err) : errMsg(err) {}
    std::string getError() { return errMsg; }

private:
    std::string errMsg;
};

class DequeEmpty : public Exception
{
public:
    DequeEmpty(const std::string &err) : Exception(err) {}
};

class BadString : public Exception
{
public:
    BadString(const std::string &err) : Exception(err) {}
};

#endif