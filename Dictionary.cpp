//
//  Dictionary.cpp
//  CS32 Project 4
//
//  Created by Adrian Pu UID 805958884.
//

#include "Dictionary.h"
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>

class DictionaryImpl
{
public:
    DictionaryImpl(int MAXNUMBERS = 50000) :m_max(MAXNUMBERS)
    {
        m_HashTable.resize(MAXNUMBERS); //sets amount of buckets in hash table
    }
    ~DictionaryImpl()
    {
        
    }
    void insert(std::string s);
    void lookup(std::string s, void callback(std::string));
private:
    std::vector<std::list<std::string>> m_HashTable;
    int m_max;
};


void removeNonLetters(std::string& s)
{
    std::string::iterator to = s.begin();
    for (std::string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

void DictionaryImpl::insert(std::string s)
{
    removeNonLetters(s);
    std::string temp = s; //sort the string and then hash so every anagram goes in the same bucket
    std::sort(temp.begin(), temp.end());
    unsigned long x = std::hash<std::string>()(temp);
    x = x % m_max;
    (m_HashTable.at(x)).push_back(s);
}

void DictionaryImpl::lookup(std::string s, void callback(std::string))
{
    removeNonLetters(s);
    std::sort(s.begin(), s.end()); //hash the sorted string
    unsigned long x = std::hash<std::string>()(s);
    x = x % m_max;

    for(std::list<std::string>::iterator p = (m_HashTable.at(x)).begin(); p!= m_HashTable.at(x).end(); p++) //search through that bucket
    {
        if(s.size() == (*p).size()) //checking if the word is an anagram
        {
            std::string temp = *p;
            sort(temp.begin(), temp.end());
            if(temp == s)
                callback(*p);
        }
    }
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(std::string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(std::string letters, void callback(std::string)) const
{
    m_impl->lookup(letters,callback);
}

