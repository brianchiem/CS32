// Brian Chiem
// 705973390

// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <vector> // for our hashtable implementation
#include <algorithm> // for sort
#include <functional> // for hashing
#include <cctype>
#include <utility>  // for swap
using namespace std;

struct Entry;
void removeNonLetters(string& s);
// void generateNextPermutation(string& permutation); // don't need this 

  // This class does the real work of the implementation.
class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl() {}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
    int getHash(const string& someString) const; // hasher
  private:
    vector<list<Entry>> m_hashTable; // a vector that stores a list of entries
    int m_maxBuckets;
};

struct Entry  // for our hash table. It is a vector that stores a list of these Entries
{
    string baseString; // we will store a sorted string that corresponds to anagrams for every combination of this string
    vector<string> anagrams; // this is where we store the actual unsorted word
};

DictionaryImpl::DictionaryImpl(int maxBuckets)
{
    m_maxBuckets = maxBuckets;
    m_hashTable.resize(m_maxBuckets); // resize our vector to have our amount of buckets
}

int DictionaryImpl::getHash(const string& someString) const
{
    hash<string> stringHasher;
    return stringHasher(someString) % m_maxBuckets; // % ensures that we are within range of our buckets
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word); 
    string unsortedWord = word; // store our unsorted word
    sort(word.begin(), word.end()); // we sort the word so that we can store matching words together. just sorts the string by least to greatest
    // ... this makes it so that every anagramable(?) variant is the same string, because it is just sorted
    if ( ! word.empty()) 
    {
        int bucket = getHash(word); // the hash should also be the same 
        list<Entry>& bucketList = m_hashTable[bucket]; // go into the bucket

        for (list<Entry>::iterator entry = bucketList.begin(); entry != bucketList.end(); entry++)
        { // loop through the list of entries for this bucket
            if (entry->baseString == word) // if it is a match, it is an anagram
            {
                entry->anagrams.push_back(unsortedWord); // put our unsorted word into the vector of anagrams
                return;
            }
        } 
        // else the string is a new entry
        Entry newEntry;
        newEntry.baseString = word;
        newEntry.anagrams.push_back(unsortedWord);
        m_hashTable[bucket].push_back(newEntry);
    }
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    sort(letters.begin(), letters.end()); // again, sort the string. it is like a key to the anagrams for the word
  
    int bucket = getHash(letters); // grab the hash
    const list<Entry>& bucketList = m_hashTable[bucket]; // grab our bucket

    for (list<Entry>::const_iterator entry = bucketList.begin(); entry != bucketList.end(); entry++) // loop through entries in bucket
    {   
        if (letters == entry->baseString) // if there is a match
        {
            for (int i = 0; i < entry->anagrams.size(); i++) // call callback for each anagram in the vector
            {
                callback(entry->anagrams[i]);
            }
        }
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 

  // Each successive call to this function generates the next permutation of the
  // characters in the parameter.  For example,
  //    string s = "eel";
  //    generateNextPermutation(s);  // now s == "ele"
  //    generateNextPermutation(s);  // now s == "lee"
  //    generateNextPermutation(s);  // now s == "eel"
  // You don't have to understand this function's implementation.
// void generateNextPermutation(string& permutation)
// {
//     string::iterator last = permutation.end() - 1;
//     string::iterator p;

//     for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
//         ;
//     if (p != permutation.begin())
//     {
//         string::iterator q;
//         for (q = p+1; q <= last  &&  *q > *(p-1); q++)
//             ;
//         swap(*(p-1), *(q-1));
//     }
//     for ( ; p < last; p++, last--)
//         swap(*p, *last);
// }

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

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
