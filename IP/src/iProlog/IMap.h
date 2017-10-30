/*
==============================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IMap.h -std=c++11 -c
Description: operates on HashMap with key being (int or char class) and value being
	      IMap data structure. Defines corresponding operations on this data structure.
Written on 10/28/2017
===============================================================================================
*/

#include <string>
#include <algorithm> // for sorting vectors.
#include <unordered_map>
#include <vector>
#include "IntMap.h"
using namespace std;

namespace iProlog
{
  template <typename K>
  class IMap
  {
    private:
      // static const long long serialVersionUID = 1LL; (Not sure if we require this, as we are not serializing objects here.)
      const unordered_map<K, IntMap *> map;

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
      string toString();
      vector<IMap<int> *> create(const int l);
      bool put(vector<IMap<int>> imaps, const int pos, const int key, const int val);
      vector<int> get(vector<IMap<int> *> iMaps, vector<IntMap *> vmaps, vector<int> keys);
      string show(vector<int> is);
      string show(vector<IMap<int> *> imaps);
  }; // End of class.

  /**
     * Given a key and value, puts it into our hash map;
    */
  template <typename K>
  bool IMap<K>::put(const K key, const int val)
  {
    IntMap *vals = map[key];
    if (nullptr == vals)
    {
      IntMap val; // Create a new IntMap (requires ATTENTION!).
      vals = &val;
      map.emplace(key, vals);
    }
    return vals->add(val);
  }

  /**
      * returns the value (IntMap) given a key.
    */
  template <typename K>
  IntMap *IMap<K>::get(const K key)
  {
    IntMap *s = map[key];
    if (nullptr == s)
    {
      // If Map is empty, create new Map (requires ATTENTION!).
      IntMap t;
      s = &t;
    }
    return s;
  }

  /**
    * Given a key and value, removes it from IMap;
    */
  template <typename K>
  bool IMap<K>::remove(const K key, const int val)
  {
    IntMap *vals = get(key);
    bool ok = vals->deleteKey(val);
    if (vals->isEmpty())
      map.erase(key);
    return ok;
  }

  template <typename K>
  bool IMap<K>::remove(const K key)
  {
    return nullptr != map.erase(key);
  }

  /**
     * returns size of our data structure(sum of all sizes of IntMaps in IMap);
     */
  template <typename K>
  int IMap<K>::size()
  {
    int s = 0;
    for (auto it = map.begin(); it != map.end(); ++it)
    {                          // For each pair in the Hash Map.
      const K key = it->first; // Get Key
      IntMap *vals = get(key);
      s += vals->size();
    }
    return s;
  }

  template <typename K>
  string IMap<K>::toString()
  {                                                                      // Get an iterator pointing to begining of map
    typename std::unordered_map<K, IntMap *>::iterator it = map.begin(); // Need typename because iterator is in dependent scope.
    string s = "";
    // Iterate over the map using iterator
    while (it != map.end())
    {
      s += "K: " + it->first + ", "; // Printing only keys for now, I am unsure of iterating over IntMap and is it rquired in general.
      it++;
    }
  }

  /**
     *	creates an array of int Maps of size l (Requires attention!).
    */
  vector<IMap<int> *> create(const int l)
  {
    IMap<int> *first;
    //vector<IMap<int>*> imaps = static_cast<std::vector<IMap<int>*>>(java::lang::reflect::Array::newInstance(first->getClass(), l));
    vector<IMap<int> *> imaps(l); // create a vector of size l.
    imaps[0] = first;
    for (int i = 1; i < l; i++)
    {
      IMap<int> *temp; // create a new pointer to IMap.
      imaps[i] = temp;
    }
    return imaps;
  }

  template <typename K>
  bool IMap<K>::put(vector<IMap<int>> imaps, const int pos, const int key, const int val)
  {
    return imaps[pos].put(key, val);
  }

  template <typename K>
  vector<int> IMap<K>::get(vector<IMap<int> *> iMaps, vector<IntMap *> vmaps, vector<int> keys)
  {
    const int l = iMaps.size();
    vector<IntMap *> ms;
    vector<IntMap *> vms;
    for (int i = 0; i < l; i++)
    {
      const int key = keys[i];
      if (0 == key)
        continue;
      IntMap *m = iMaps[i]->get(key);
      // //Main.pp("m=" + m);
      ms.push_back(m);
      vms.push_back(vmaps[i]);
    }
    vector<IntMap *> ims(ms.size());
    vector<IntMap *> vims(vms.size());
    for (int i = 0; i < ims.size(); i++)
    {
      const IntMap *im = ms[i];
      ims[i] = im;
      const IntMap *vim = vms[i];
      vims[i] = vim;
    }
    IntStack *cs = IntMap::intersect(ims, vims); // $$$ add vmaps here
    vector<int> is = cs->toArray();
    for (int i = 0; i < is.size(); i++)
    {
      is[i] = is[i] - 1;
    }
    sort(is.begin(), is.end());
    return is;
  }

  template <typename K>
  string IMap<K>::show(vector<IMap<int> *> imaps)
  {
    string s = "";
    for (auto it = begin(imaps); it != end(imaps); ++it)
    {
      cout << *it; // TO - DO (Not sure if this is necessary).
    }
    return s;
  }

  template <typename K>
  string IMap<K>::show(vector<int> is)
  {
    string s = "";
    for (vector<int>::iterator it = is.begin(); it != is.end(); ++it)
      s += " " + *it;
    return s;
  }
} // namespace close();
