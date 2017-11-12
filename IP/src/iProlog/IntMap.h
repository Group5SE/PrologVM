/*
=====================================================================================
Author: Karthik Venkataramana Pemmaraju.
Compilation: g++ IntMap.h -std=c++11 -c
Description: Represents the memory image of integers using HashMap implementation.
	     available at https://github.com/mikvor/hashmapTest
Written on 10/28/2017
=====================================================================================
*/

#ifndef INTMAP
#define INTMAP

#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>
#include "IntStack.h" 

namespace iProlog {
  class IntMap {
    private:
		    // static const long long serialVersionUID = 1LL; (Since we are not implementing serializable interface).
		    const int FREE_KEY = 0;
		    /** Keys and values */
		    std::vector < int > m_data;
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
		    void intersect0(const IntMap * m, const std::vector < IntMap * > maps, const std::vector < IntMap * > vmaps, IntStack * r);
		    IntStack * intersect(std::vector < IntMap * > maps, std::vector < IntMap * > vmaps);
		    int put(const int key, const int value);
		    void rehash(const int capacity);
		    int shiftKeys(int position);
		    int remove(const int key);
		    int size();
		    std::string toString(); // Printing keys and values in m_data.
  }; // End of class.

} // namespace close().
#endif