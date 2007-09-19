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



/**
 * Template for classes which are aggregation of other class. This template
 * provides public API and methods for manipulation with the vector which
 * contains pointers to Type (aggregated classes).
 */
template<class Type>
class VectorOfPointers{
  protected:
    typedef typename std::vector<Type *>::const_iterator list_iterator_t;
    std::vector<Type *> _list;//! list of aggregated classes

    /**
     * Do deep copy of cl.
     */
    virtual void _copy(const VectorOfPointers<Type> &cl);

    /**
     * Free all allocated memory. _list is list of pointers to allocated
     * memory, this method free all this memory.
     */
    virtual void _free();

    /**
     * Add new instance of Type into _list.
     */
    void _add(Type *t){ _list.push_back(t); }

    /**
     * Returns number of instances placed into _list.
     */
    int _size() const { return _list.size(); }

    list_iterator_t _begin() const { return _list.begin();}
    list_iterator_t _end() const { return _list.end();}

  public:
    VectorOfPointers(){}
    VectorOfPointers(const VectorOfPointers<Type> &cl){ _copy(cl); }
    virtual ~VectorOfPointers(){ _free(); }
    virtual VectorOfPointers<Type> &operator=(const VectorOfPointers<Type> &cl)
                { _free(); _copy(cl); return *this; }

    virtual bool operator==(const VectorOfPointers<Type> &cl) const;
    virtual bool operator!=(const VectorOfPointers<Type> &cl) const
        { return !(*this == cl); }
};

/* VectorOfPointers */
template<class Type>
void VectorOfPointers<Type>::_copy(const VectorOfPointers<Type> &cl)
{
    list_iterator_t it = cl._list.begin();
    list_iterator_t it_end = cl._list.end();
    for (;it != it_end; it++){
        _list.push_back(new Type(**it));
    }
}

template<class Type>
void VectorOfPointers<Type>::_free()
{
    list_iterator_t it = _list.begin();
    list_iterator_t it_end = _list.end();
    for (;it != it_end; it++){
        delete *it;
    }
    _list.clear();
}


template<class Type>
bool VectorOfPointers<Type>::operator==(const VectorOfPointers<Type> &cl) const
{
    if (_list.size() != cl._list.size())
        return false;

    // _list and t._list has same length so no t._list.end() is needed
    list_iterator_t it = _list.begin();
    list_iterator_t it_end = _list.end();
    list_iterator_t it2 = cl._list.begin();
    for (;it != it_end; it++, it2++){
        if (**it != **it2)
            return false;
    }

    return true;
}
/* VectorOfPointers END */
#endif
