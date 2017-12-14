/*
=====================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IntMap.cpp -std=c++11 -c
Description: Implements the memory image of integers using HashMap implementation.
	     available at https://github.com/mikvor/hashmapTest
Written on 10/28/2017
=====================================================================================
*/

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

#include "IntMap.h"
#include "IntStack.h" 

using namespace std;
namespace iProlog {
  /**
   * Setting inital size to 2
   */
  IntMap::IntMap(): IntMap(1 << 2) { // Calling constructor inside constructor (Available from c++11)
  }

  /**
   * Setting inital fillfactor to 0.75
   */
  IntMap::IntMap(const int size): IntMap(size, 0.75f) {}

  IntMap::IntMap(const int size,
    const float fillFactor): m_fillFactor(fillFactor) { // Initializing constant parameters.
    if (fillFactor <= 0 || fillFactor >= 1) {
      throw std::invalid_argument("FillFactor must be in (0, 1)");
    }
    if (size <= 0) {
      throw invalid_argument("Size must be positive!");
    }
    const int capacity = IntMap::arraySize(size, fillFactor);
    m_mask = capacity - 1;
    m_mask2 = capacity * 2 - 1;
    m_data = std::vector < int > (capacity * 2);
    m_threshold = static_cast < int > (capacity * fillFactor);
  }

  /** Returns the least power of two smaller than or equal to 2 ^ 30.
   *and larger than or equal to  Math.ceil( expected / f ).
   *
   * @param expected the expected number of elements in a hash table.
   * @param f the load factor.
   * @return the minimum possible size for a backing array.
   * @throws IllegalArgumentException if the necessary size is larger than 2<sup>30</sup>.
   */
  int IntMap::arraySize(const int expected,
    const float f) {
    const long long s = std::max(static_cast < long long > (2), IntMap::nextPowerOfTwo(static_cast < long long > (std::ceil(expected / f))));
    if (s > 1 << 30) {
      throw invalid_argument("Too large (" + to_string(expected) + " expected elements with load factor " + to_string(f) + ")");
    }
    return static_cast < int > (s);
  }

  /** Taken from FastUtil implementation */
  /** Return the least power of two greater than or equal to the specified value.
   *
   * <p>Note that this function will return 1 when the argument is 0.
   *
   * @param x a long integer smaller than or equal to 2<sup>62</sup>.
   * @return the least power of two greater than or equal to the specified value.
   */
  long long IntMap::nextPowerOfTwo(long long x) { // Long in java is 8 bytes whereas in C++ is only 4. Hence, using long long.
    if (x == 0) {
      return 1;
    }
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return (x | x >> 32) + 1;
  }

  int IntMap::get(const int key) const {
    int ptr = (IntMap::phiMix(key) & m_mask) << 1;
    if (key == FREE_KEY)
      return m_hasFreeKey ? m_freeValue : NO_VALUE;
    int k = m_data[ptr];
    if (k == FREE_KEY)
      return NO_VALUE; //end of chain already
    if (k == key) //we check FREE prior to this call
      return m_data[ptr + 1];
    while (true) {
      ptr = ptr + 2 & m_mask2; //that's next index
      k = m_data[ptr];
      if (k == FREE_KEY) {
        return NO_VALUE;
      }
      if (k == key)
        return m_data[ptr + 1];
    }
  }

  int IntMap::phiMix(const int x) { // For static functions, no need of writing static again during definition.
    const int h = x * INT_PHI;
    return h ^ h >> 16;
  }

  // for use as IntSet - Paul Tarau - Edited by Karthik.

  bool IntMap::contains(const int key) {
    return NO_VALUE != get(key);
  }

  bool IntMap::add(const int key) {
    return NO_VALUE != put(key, 666);
  }

  bool IntMap::deleteKey(const int key) {
    return NO_VALUE != remove(key);
  }

  bool IntMap::isEmpty() {
    return 0 == m_size;
  }

  void IntMap::intersect0(const IntMap * m, vector < IntMap * > maps, vector < IntMap * > vmaps, IntStack * r) {
      const vector < int > data = m -> m_data;
      for (int k = 0; k < data.size(); k += 2) {
        bool found = true;
        const int key = data[k];
        if (FREE_KEY == key)
          continue;
        for (int i = 1; i < maps.size(); i++) {
          const IntMap * map = maps[i];
          const int val = map -> get(key);
          if (NO_VALUE == val) {
            const IntMap * vmap = vmaps[i];
            const int vval = vmap -> get(key);
            if (NO_VALUE == vval) {
              found = false;
              break;
            }
          }
        }
        if (found)
          r -> push(key);
      }
    } // End of intersect0() function.

  IntStack* IntMap::intersect(vector <IntMap *> maps, vector < IntMap *> vmaps) {
    IntStack *ptr = new IntStack();
    if(maps.size() > 0 && vmaps.size() > 0){
      intersect0(maps[0], maps, vmaps, ptr);
      intersect0(vmaps[0], maps, vmaps, ptr);
    }
    return ptr;
  }

  int IntMap::put(const int key,
      const int value) {
      if (key == FREE_KEY) {
        const int ret = m_freeValue;
        if (!m_hasFreeKey)
          ++m_size;
        m_hasFreeKey = true;
        m_freeValue = value;
        return ret;
      }
      int ptr = (IntMap::phiMix(key) & m_mask) << 1;
      int k = m_data[ptr];
      if (k == FREE_KEY) { //end of chain already
        m_data[ptr] = key;
        m_data[ptr + 1] = value;
        if (m_size >= m_threshold)
          rehash(m_data.size() * 2); //size is set inside
        else
          ++m_size;
        return NO_VALUE;
      } else if (k == key) { //we check FREE prior to this call
        const int ret = m_data[ptr + 1];
        m_data[ptr + 1] = value;
        return ret;
      }
      while (true) {
        ptr = ptr + 2 & m_mask2; //that's next index calculation
        k = m_data[ptr];
        if (k == FREE_KEY) {
          m_data[ptr] = key;
          m_data[ptr + 1] = value;
          if (m_size >= m_threshold)
            rehash(m_data.size() * 2); //size is set inside
          else
            ++m_size;
          return NO_VALUE;
        } else if (k == key) {
          const int ret = m_data[ptr + 1];
          m_data[ptr + 1] = value;
          return ret;
        }
      }
    } // End of put() function.

  int IntMap::remove(const int key) {
  
    if (key == FREE_KEY) {
      if (!m_hasFreeKey)
        return NO_VALUE;
      m_hasFreeKey = false;
      --m_size; 
      return m_freeValue; //value is not cleaned
    }
    int ptr = (phiMix(key) & m_mask) << 1;
    int k = m_data[ptr];
    if (k == key) { //we check FREE prior to this call
      const int res = m_data[ptr + 1]; 
      shiftKeys(ptr);  
      --m_size; 
      return res;
    } else if (k == FREE_KEY)
      return NO_VALUE; //end of chain already
    while (true) {
      ptr = ptr + 2 & m_mask2; //that's next index calculation
      k = m_data[ptr];
      if (k == key) {
        const int res = m_data[ptr + 1];
        shiftKeys(ptr);
        --m_size;
        return res;
      } else if (k == FREE_KEY)
        return NO_VALUE;
    }
  }

  /**
   *  Shift entries with the same hash.
   */
  int IntMap::shiftKeys(int pos) {
    int last, slot;
    int k; 
    while (true) {
      pos = (last = pos) + 2 & m_mask2;
      while (true) {
        if ((k = m_data[pos]) == FREE_KEY) {
          m_data[last] = FREE_KEY;
          return last;
        }
        slot = (IntMap::phiMix(k) & m_mask) << 1; //calculate the starting slot for the current key
        if (last <= pos ? last >= slot || slot > pos : last >= slot && slot > pos){
          break;
        }
        pos = pos + 2 & m_mask2; //go to the next entry
      }
      m_data[last] = k;
      m_data[last + 1] = m_data[pos + 1];
    }
  }

  int IntMap::size() {
    return m_size;
  }

  /**
   * Rehashing with a new specified capacity.
   */
  void IntMap::rehash(const int newCapacity) {
      m_threshold = static_cast < int > (newCapacity / 2 * m_fillFactor);
      m_mask = newCapacity / 2 - 1;
      m_mask2 = newCapacity - 1;
      const int oldCapacity = m_data.size();
      const vector < int > oldData = m_data;
      m_data = vector < int > (newCapacity);
      m_size = m_hasFreeKey ? 1 : 0;
      for (int i = 0; i < oldCapacity; i += 2) {
        const int oldKey = oldData[i];
        if (oldKey != FREE_KEY)
          IntMap::put(oldKey, oldData[i + 1]);
      }
    }
  /**
  	* Used for testing purposes, adapted accordingly.
  */
  string IntMap::toString() {
	    string b = "{";
	    const int l = m_data.size(); 
	    bool first = true;
	    for (int i = 0; i < l; i += 2) {
        const int v = m_data[i]; 
	      if (v != FREE_KEY) {
	        if (!first)
	          b += ",";
          first = false; 
	        b += to_string(v - 1);
	      }
	    }
	    b += "}";
	    return b;
  }

  template<typename T>
  void IntMap::printVector(vector<T> x){
      cout << " [";
      for(auto t = x.begin(); t != x.end(); ++t){
        cout << *t << " ";
      }
      cout << "]";
    }
}

// int main(){

// 	  iProlog::IntMap noarg();
// 	  iProlog::IntMap sizeargobj(10);
// 	  iProlog::IntMap sizefillargobj(10, 0.5f);
	  
// 	  sizefillargobj.put(20, 1);
// 	  sizefillargobj.put(21, 2);
// 	  sizefillargobj.put(51, 4);
// 	  //IntMap wrongfillobj = new IntMap(10, 2f);// Uncomment this to test error for wrong fill factor  
// 	  //IntMap wrongsizeobj = new IntMap(-10);//Uncomment this to test error for wrong size( To Test this comment previous statement)
// 	  cout << "Is map empty: "<<  sizeargobj.isEmpty() << endl;
// 	  sizeargobj.put(50, 1);
// 	  sizeargobj.put(51, 2);
// 	  cout << "can we put keys with negative values: "<<  sizeargobj.put(-1,3) << endl;
// 	  cout << "Is map empty: "<<  sizeargobj.isEmpty() << endl;
// 	  cout << "IntMap after adding key value pairs(which shows (key-1) only): " <<  sizeargobj.toString() << endl;
// 	  cout << "Value for given key in IntMap: " <<  sizeargobj.get(51) << endl;
// 	  sizeargobj.put(51, 3);
// 	  cout << "value for given key after modifying its value: " <<  sizeargobj.get(51) << endl;
// 	  cout << "Check if a key is present in map: " <<  sizeargobj.contains(52)<< endl;
// 	  cout << "Accessing key which is not present in map: " <<  sizeargobj.get(52) << endl;
// 	  cout << "Check if a key is present in map: " <<  sizeargobj.contains(51) << endl;
// 	  cout << "Can we add already existing key:" <<  sizeargobj.add(51) << endl;
// 	  sizeargobj.add(52);
// 	  cout << "IntMap after adding key without any value: " <<  sizeargobj.toString() <<  " and its value is: "<< sizeargobj.get(52) << endl;
// 	  cout << "Deleting the key which is not present in map: "<<   sizeargobj.deleteKey(0) << endl;
//     cout << sizeargobj.size() << endl; 
//     cout << "Deleting the key which is not present in map: "<<   sizeargobj.deleteKey(50);
//     cout << "; Current Map: " <<  sizeargobj.toString() << endl;
//     cout << "size of current map:" <<  sizeargobj.size() << endl;
//     iProlog::IntStack* list = sizeargobj.intersect(vector<iProlog::IntMap*> {&sizeargobj}, vector<iProlog::IntMap*> {&sizefillargobj} ); 
// 	  cout << "Intersect two maps: "<< list -> toString();

//   return 0;
// }

/*
  JAVA OUTPUT:
  Is map empty: true
  can we put keys with negative values: 0
  Is map empty: false
  IntMap after adding key value pairs(which shows (key-1) only): {50,49,-2}
  Value for given key in IntMap: 2
  value for given key after modifying its value: 3
  Check if a key is present in map: false
  Accessing key which is not present in map: 0
  Check if a key is present in map: true
  Can we add already existing key:true
  IntMap after adding key without any value: {51,50,49,-2} and its value is: 666
  Deleting the key which is not present in map: false
  Deleting the key which is not present in map: true; Current Map: {51,50,-2}
  size of current map:3
  Intersect two maps: [52, 51, -1, 20, 21, 51]

  C++ OUTPUT:
  E:\Software Engineering\Term Project Clone\IP\src\iProlog>g++ IntMap.cpp IntStack.cpp -std=c++11

  E:\Software Engineering\Term Project Clone\IP\src\iProlog>a.exe
  Is map empty: 1
  can we put keys with negative values: 0
  Is map empty: 0
  IntMap after adding key value pairs(which shows (key-1) only): {50,49,-2}
  Value for given key in IntMap: 2
  value for given key after modifying its value: 3
  Check if a key is present in map: 0
  Accessing key which is not present in map: 0
  Check if a key is present in map: 1
  Can we add already existing key:1
  IntMap after adding key without any value: {51,50,49,-2} and its value is: 666
  Deleting the key which is not present in map: 0
  4
  Deleting the key which is not present in map: 1; Current Map: {51,50,-2}
  size of current map:3
  Intersect two maps: 52,51,-1,20,21,51
*/