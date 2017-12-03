/*
==============================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IMap.h -std=c++11
Description: operates on HashMap with key being (int or char class) and value being
	      IMap data structure. Defines corresponding operations on this data structure.
Written on 10/28/2017
===============================================================================================
*/

#ifndef IMAP
#define IMAP

#include "IntMap.h" 
#include <string>
#include <algorithm> // for sorting std::vectors.
#include <unordered_map>
#include <vector>

namespace iProlog
{
  template <typename K>
  class IMap
  {
    private:
      // static const long long serialVersionUID = 1LL; (Not sure if we require this, as we are not serializing objects here.)
      std::unordered_map<K, IntMap *> map;

    public:
      // IMap(); (We don't need constructor as we do not need to create instance for map in C++ unlike Java).
      void clear()
      {
        map.clear();
      }
      bool put(const K key, const int val);
      IntMap *get(const K key);
      bool remove(const K key, const int val);
      bool remove(const K key);
      int size();
      std::string toString();
      std::vector<IMap<int> *> create(const int l);
      bool put(std::vector<IMap<int>*> imaps, const int pos, const int key, const int val);
      std::vector<int> get(std::vector<IMap<int> *> iMaps, std::vector<IntMap *> vmaps, std::vector<int> keys);
      std::string show(std::vector<int> is);
      std::string show(std::vector<IMap<int> *> imaps);	
      std::string string_or_int(std::string s);	
      std::string string_or_int(const int& s); 
  }; // End of class.

 
} // namespace close();
#endif
