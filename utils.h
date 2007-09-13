#ifndef _UTILS_H_
#define _UTILS_H_

#include <vector>

/**
 * Iterator for vectors containing pointers to Type.
 * Attention: Dereferenced iterator returns copy of the Type
 *            (not pointer to Type)!
 * For usage it should be enough to public inherit from this class and
 * declare some friend methods (functions).
 * Example:
 *
 * class Cl{
 *   public:
 *     class iterator;
 *
 *     iterator begin() const;
 *     iterator end() const;
 *
 *     class iterator : public VectorPointerIterator<QString>{
 *       public:
 *         friend iterator Cl::begin() const;
 *         friend iterator Cl::end() const;
 *     };
 * };
 *
 */
template<class Type>
class VectorPointerIterator{
  protected:
    typedef typename std::vector<Type *>::const_iterator iterator_t;
    iterator_t it;

  public:
    VectorPointerIterator(){}
    VectorPointerIterator(const VectorPointerIterator &iter) : it(iter.it){}
    virtual VectorPointerIterator
        &operator=(const VectorPointerIterator& iter)
            { it = iter.it; return *this; }
    virtual bool
        operator==(const VectorPointerIterator& iter){ return it == iter.it; }
    virtual bool
        operator!=(const VectorPointerIterator& iter){ return it != iter.it; }
    virtual VectorPointerIterator &operator++(){ it++; return *this; }
    virtual VectorPointerIterator &operator++(int){ it++; return *this; }
    virtual VectorPointerIterator &operator--(){ it--; return *this; }
    virtual VectorPointerIterator &operator--(int){ it--; return *this; }
    virtual Type operator*() const{ return **it; }
};
#endif
