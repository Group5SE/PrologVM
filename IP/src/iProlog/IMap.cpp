/*
==============================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IMap.cpp -std=c++11 -c
Description: operates on HashMap with key being (int or char class) and value being
	      IMap data structure. Defines corresponding operations on this data structure.
Written on 10/28/2017
===============================================================================================
*/


#include "IntMap.h"
#include "IMap.h"
#include <string>
#include <typeinfo>
#include <algorithm> // for sorting vectors.
#include <unordered_map>
#include <vector>
using namespace std;

namespace iProlog{

  /**
  * Given a key and value, puts it into our hash map;
  */
  template <typename K>
  bool IMap<K>::put(const K key, const int val)
  {
    IntMap *vals;
    try{
      vals = map.at(key);
    }
    catch(out_of_range e){
      vals = nullptr;
    }
    if (nullptr == vals)
    {
      vals = new IntMap();
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
      s = new IntMap();
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
    return map.erase(key);
  }

  /**
     * returns size of our data structure(sum of all sizes of IntMaps in IMap);
     */
  template <typename K>
  int IMap<K>::size(){
    int s = 0;
    for (auto it = map.begin(); it != map.end(); ++it){// For each pair in the Hash Map.
      const K key = it->first; // Get Key
      IntMap *vals = get(key);
      s += vals->size();
    }
    return s;
  }

  template <typename K>
  string IMap<K>::toString(){// Get an iterator pointing to begining of map
    typename std::unordered_map<K, IntMap *>::iterator it = map.begin(); // Need typename because iterator is in dependent scope.
    string s = " {";
    // Iterate over the map using iterator
    while (it != map.end()){
      s += string_or_int(it->first);
      s += " = "; // Printing only keys for now, Unsure of iterating over IntMap and is it required in general.
      s += (it -> second -> toString());
      s += ",";
      it++;
    }
    s+= "}";
    return s;
  }
  template <typename K>
  string IMap<K>::string_or_int(string s){
    return s;
  }
  
  template <typename K>
  string IMap<K>::string_or_int(const int& s){
    return to_string(s);
  }
  
  /**
     *	creates an array of int Maps of size l (Requires attention!).
    */
  template <typename K>
  vector<IMap<int> *> IMap<K>::create(const int l)
  {
    IMap<int> *first = new IMap<int>;
    //vector<IMap<int>*> imaps = static_cast<std::vector<IMap<int>*>>(java::lang::reflect::Array::newInstance(first->getClass(), l));
    vector<IMap<int> *> imaps(l); // create a vector of size l.
    imaps[0] = first;
    for (int i = 1; i < l; i++)
    {
      IMap<int> *temp = new IMap<int>; // create a new pointer to IMap.
      imaps[i] = temp;
    }
    return imaps;
  }

  template <typename K>
  bool IMap<K>::put(vector<IMap<int>*> imaps, const int pos, const int key, const int val)
  { 
    return imaps[pos] -> put(key, val);
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
    vector<IntMap *> ims;
    vector<IntMap *> vims;
    for (int i = 0; i < ims.size(); i++)
    {
      IntMap *im = ms[i];
      ims[i] = im;
      IntMap *vim = vms[i];
      vims[i] = vim;
    }
    IntMap m;
    IntStack *cs = m.intersect(ims, vims); // $$$ add vmaps here
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
    for (auto it = begin(imaps); it != end(imaps); ++it){
      s += (*it) -> toString(); 
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
  template class IMap<int>;
}

// int main(){
//   iProlog::IMap<int> x;
//   vector<iProlog::IMap<int> *> imaps = x. create(3);
//   x.put(imaps, 0, 10, 100);
//   x.put(imaps, 1, 20, 200);
//   x.put(imaps, 2, 30, 777);
//   cout << x.show(imaps) << endl;

//   iProlog::IMap<string> obj;
//   obj.put("first", 10);
//   obj.put("second", 11);
//   obj.put("third", 12);

//   cout << "Current IMap object: " <<  obj.toString() << endl;
//   cout << "Size of IMap Object: " <<  obj.size() << endl ;
//   cout << "Remove element from IMap object by passing only key: " <<  obj.remove("first") << endl;
//   cout << "current IMap object: " <<  obj.toString()<< endl;
//   cout << "Can we remove element from IMap object by passing wrong key and value: "<< obj.remove("second",10) << endl;
//   cout << "current IMap object: "<< obj.toString() << endl;
//   cout << "Can we remove element from IMap object by passing correct key and value: "<< obj.remove("second",11) << endl;
//   cout << "Current IMap object: "<< obj.toString() << endl;
//   cout << "Value of given key which doesn't exists in IMap : " << obj.get("second") -> toString()<< endl;
//   cout << "Value of given key which exists in IMap: "<< obj.get("third") -> toString() << endl;
//   obj.clear();
//   cout << "Size of IMap after clearing it:" << obj.size() << endl;
//   return 0;
// }

/*
JAVA OUTPUT:
E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>javac -d . IMap.java

E:\Software Engineering\Term Project Clone\IP\src\IProlog_Java>java iProlog/IMap
[{10={99}}, {20={199}}, {30={776}}]
Set of keys in current IMap object: [third, first, second]
Current IMap object: {third={11}, first={9}, second={10}}
Iterate through current IMap object using 'Iterator' and showing one of key: third
Size of IMap Object: 3
Remove element from IMap object by passing only key: true
current IMap object: {third={11}, second={10}}
Can we remove element from IMap object by passing wrong key and value: false
current IMap object: {third={11}, second={10}}
Can we remove element from IMap object by passing correct key and value: true
Current IMap object: {third={11}}
Value of given key which doesn't exists in IMap : {}
Value of given key which exists in IMap: {11}
Size of IMap after clearing it:0

C++ OUTPUT:

E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ IMap.cpp IntMap.cpp  IntStack.cpp -std=c++11

E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
 {10 = {99},} {20 = {199},} {30 = {776},}
Current IMap object:  {third = {11},second = {10},first = {9},}
Size of IMap Object: 3
Remove element from IMap object by passing only key: 1
current IMap object:  {third = {11},second = {10},}
Can we remove element from IMap object by passing wrong key and value: 0
current IMap object:  {third = {11},second = {10},}
Can we remove element from IMap object by passing correct key and value: 1
Current IMap object:  {third = {11},}
Value of given key which doesn't exists in IMap : {}
Value of given key which exists in IMap: {11}
Size of IMap after clearing it:0
*/