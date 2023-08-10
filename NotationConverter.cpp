/* Piyush Manjhi U10602103
 */

#include <string>
#include <sstream>
#include <iostream>
#include <ios>
#include <ctype.h>
#include <stdio.h>

#include "NotationConverter.hpp"
#include "NotationConverterInterface.hpp"

// creating linked list members
LinkedList::LinkedList()
{
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

LinkedList::~LinkedList()
{
    while (!empty())
        removeFront();
    delete head;
    delete tail;
}

bool LinkedList::empty() const
{
    return (head->next == tail);
}

const Elem &LinkedList::front() const
{
    return head->next->elem;
}

const Elem &LinkedList::back() const
{
    return tail->prev->elem;
}

void LinkedList::add(Node *v, const Elem &e)
{
    Node *u = new Node;
    u->elem = e;
    u->next = v;
    u->prev = v->prev;
    v->prev->next = u;
    v->prev = u;
}

void LinkedList::addFront(const Elem &e)
{
    add(head->next, e);
}

void LinkedList::addBack(const Elem &e)
{
    add(tail, e);
}

void LinkedList::remove(Node *v)
{
    Node *u = v->prev;
    Node *w = v->next;
    u->next = w;
    w->prev = u;
    delete v;
}

void LinkedList::removeFront()
{
    remove(head->next);
}

void LinkedList::removeBack()
{
    remove(tail->prev);
}

// Deque Implementation
NotationConverter::NotationConverter() : D(), n(0) {}

bool NotationConverter::empty() const
{
    return D.empty();
}

int NotationConverter::size() const
{
    return n;
}

const Elem &NotationConverter::front() const
{
    return D.front();
}

const Elem &NotationConverter::back() const
{
    return D.back();
}

void NotationConverter::insertFront(const Elem &e)
{
    D.addFront(e);
    n++;
}

void NotationConverter::insertBack(const Elem &e)
{
    D.addBack(e);
    n++;
}

void NotationConverter::removeFront()
{
    if (empty())
        throw DequeEmpty("removeFront of empty deque");
    D.removeFront();
    n--;
}

void NotationConverter::removeBack()
{
    if (empty())
        throw DequeEmpty("removeBack of empty deque");
    D.removeBack();
    n--;
}

// This method takes in a string of postfix notation and returns a string in the infix notation
std::string NotationConverter::postfixToInfix(std::string inStr)
{
    for (unsigned int i = 0; i < inStr.length(); i++)
    { // interate throught the string
        if (inStr[i] == ' ')
        { // skipping blank spaces
            continue;
        }
        if (inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '/' || inStr[i] == '*' || isalpha(inStr[i]) || inStr[i] == '(' || inStr[i] == ')')
        { // validation
            if (!isalpha(inStr[i]))
            {                                   // checking nuberoalpha characters
                std::string oneBefore = back(); // removing last two strings from deck
                removeBack();
                std::string twoBefore = back();
                removeBack(); // adjusting two strings with non-alphabetical char by infix format
                std::string newString = "(" + twoBefore + " " + std::string(1, inStr[i]) + " " + oneBefore + ")";
                insertBack(newString); // add at the end of deck

                continue;
            }
            insertBack(std::string(1, inStr[i])); // adding char after validation
        }
        else // catch
            throw BadString("error: cannot read");
    }
    return back(); // returning from back of deck
}

// This method takes in a string of prefix notation and returns a string in the postfix notation
std::string NotationConverter::prefixToPostfix(std::string inStr)
{
    for (int i = inStr.length() - 1; i >= 0; i--)
    { // interate from back
        if (inStr[i] == ' ')
        { // space validation
            continue;
        }
        if (inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '/' || inStr[i] == '*' || isalpha(inStr[i]) || inStr[i] == '(' || inStr[i] == ')')
        { // char validaiton
            if (!isalpha(inStr[i]))
            {                                // validating non-apha
                std::string first = front(); // removing first two strng
                removeFront();
                std::string second = front(); // AB *   ( A - B ) C *
                removeFront();
                std::string newString = first + " " + second + " " + std::string(1, inStr[i]); // Concating using postifx format
                insertFront(newString);                                                        // result added at the front

                continue;
            }
            insertFront(std::string(1, inStr[i])); // char validation, adding alphabets in front
        }
        else // catch
            throw BadString("This string contains an invalid error");
    }
    return front(); // returning front
}
// This method takes in a string of infix notation and returns a string in the prefix notation
std::string NotationConverter::infixToPrefix(std::string inStr)
{
    for (unsigned int i = 0; i < inStr.length(); i++)
    { // interating thru strn
        if (inStr[i] == ' ')
        { // validating blank spaces
            continue;
        }
        if (inStr[i] == '+' || inStr[i] == '-' || inStr[i] == '/' || inStr[i] == '*' || isalpha(inStr[i]) ||
            inStr[i] == '(' || inStr[i] == ')')
        { // char validation
            if (inStr[i] == '(')
            { // parathensis validation, do not include in deck (
                continue;
            }
            else if (inStr[i] == ')')
            {                                   // for )
                std::string oneBefore = back(); // remove last three char from deck
                removeBack();
                std::string twoBefore = back(); // AB* ( A - B ) C * a * b ) * ab
                removeBack();
                std::string threeBefore = back();
                removeBack();
                std::string newString = twoBefore + " " + threeBefore + " " + oneBefore; // using concat
                insertBack(newString);                                                   // placing added value to the back
                // std::cout<<back() <<  " ";
                continue;
            }
            else
            { // parathensis validation, adding char
                insertBack(std::string(1, inStr[i]));
            }
        }
        else // catch2
            throw BadString("This string contains an invalid error");
    }
    return back();
}

// This method takes in a string of postfix notation and returns a string in the prefix notation
std::string NotationConverter::postfixToPrefix(std::string inStr)
{
    std::string toInfix = postfixToInfix(inStr); // calling postfixtoinfix
    return infixToPrefix(toInfix);               // calling infixtoprefix
}

// This method takes in a string of infix notation and returns a string in the postfix notation
std::string NotationConverter::infixToPostfix(std::string inStr)
{
    std::string toPrefix = infixToPrefix(inStr); // calling infixtoprefix
    return prefixToPostfix(toPrefix);            // calling prefixtopostfix
}

// This method takes in a string of prefix notation and returns a string in the postfix notation
std::string NotationConverter::prefixToInfix(std::string inStr)
{
    std::string toPost = prefixToPostfix(inStr); // calling prefixtopostfix
    return postfixToInfix(toPost);               // calling postfixtoinfix
}
