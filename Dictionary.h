//
//  Dictionary.h
//  CS32 Project 4
//
//  Created by Adrian Pu on 6/6/23.
//

#ifndef Dictionary_h
#define Dictionary_h
// Dictionary class for maintaining an anagram dictionary
//     Dictionary d;         // create an empty dictionary
//     d.insert("hello");    // insert "hello" into the dictionary
//     d.lookup("idte", f);  // call the function f for every anagram of "idte"
//                           //     found in the dictionary

#include <string>

class DictionaryImpl;

class Dictionary
{
  public:
    Dictionary(int maxBuckets = 50000);
    ~Dictionary();
    void insert(std::string word);
    void lookup(std::string letters, void callback(std::string)) const;
      // We prevent Dictionary objects from being copied or assigned
    Dictionary(const Dictionary&) = delete;
    Dictionary& operator=(const Dictionary&) = delete;

  private:
    DictionaryImpl* m_impl;
};

#endif // DICTIONARY_INCLUDED



