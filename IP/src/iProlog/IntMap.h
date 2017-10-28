/*
=====================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IntMap.h -std=c++11 -c
Description: Represents the memory image of integers using HashMap implementation.
	     available at https://github.com/mikvor/hashmapTest
Written on 10/28/2017
=====================================================================================
*/

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "IntStack.h"
using namespace std;

namespace iProlog {
  class IntMap {
    private:
		    // static const long long serialVersionUID = 1LL; (Since we are not implementing serializable interface).
		    const int FREE_KEY = 0;
		    /** Keys and values */
		    vector < int > m_data;
		    /** Do we have 'free' key in the map? */
		    bool m_hasFreeKey = false;
		    /** Value of 'free' key */
		    int m_freeValue = 0;
		    /** Fill factor, must be between (0 and 1) */
		    const float m_fillFactor;
		    /** We will resize a map once it reaches this size */
		    int m_threshold = 0;
		    /** Current map size */
		    int m_size = 0;
		    /** Mask to calculate the original position */
		    int m_mask = 0;
		    int m_mask2 = 0;
    public:
      	const int NO_VALUE = 0;
		    IntMap();
		    IntMap(const int size);
		    IntMap(const int size, const float fillFactor);
		    int arraySize(const int expected, const float f);
		    long long nextPowerOfTwo(long long x);
		    int get(const int size) const;
		    static const int INT_PHI = 0x9E3779B9;
		    static int phiMix(const int x);
		    bool contains(const int key);
		    bool add(const int key);
		    bool deleteKey(const int key);
		    bool isEmpty();
		    void intersect0(const IntMap * m, const vector < IntMap * > maps, const vector < IntMap * > vmaps, IntStack * r);
		    IntStack * intersect(vector < IntMap * > maps, vector < IntMap * > vmaps);
		    int put(const int key, const int value);
		    void rehash(const int capacity);
		    int shiftKeys(int position);
		    int remove(const int key);
		    int size();
		    string toString(); // Printing keys and values in m_data.
  }; // End of class.

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
    int ptr = (phiMix(key) & m_mask) << 1;
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

  IntStack * IntMap::intersect(vector < IntMap * > maps, vector < IntMap * > vmaps) {
    IntStack r; // Call constructor
    IntStack * ptr = & r;
    intersect0(maps[0], maps, vmaps, ptr);
    intersect0(vmaps[0], maps, vmaps, ptr);
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
      int ptr = (phiMix(key) & m_mask) << 1;
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
      IntMap::shiftKeys(ptr);
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
    vector < int > data = m_data;
    while (true) {
      pos = (last = pos) + 2 & m_mask2;
      while (true) {
        if ((k = data[pos]) == FREE_KEY) {
          data[last] = FREE_KEY;
          return last;
        }
        slot = (phiMix(k) & m_mask) << 1; //calculate the starting slot for the current key
        if (last <= pos ? last >= slot || slot > pos : last >= slot && slot > pos)
          break;
        pos = pos + 2 & m_mask2; //go to the next entry
      }
      data[last] = k;
      data[last + 1] = data[pos + 1];
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

} // namespace close().
