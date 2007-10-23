#ifndef _LEVENSHTEIN_TABLE_H_
#define _LEVENSHTEIN_TABLE_H_

#include <utility>
#include <vector>
#include <list>
#include <QString>

struct range_t{
    enum range_type {
        NOCHANGE,
        INSERTION,
        DELETION,
        SUBSTITUTION
    };

    range_type type;
    bool original;
    int from;
    int length;

    bool operator==(const range_t &r) const
        { return r.type == this->type && r.original == this->original &&
                 r.from == this->from && r.length == this->length; }
    bool operator!=(const range_t &r) const { return !(r == *this); }
};

typedef std::vector<std::vector<range_t> > list_of_ranges_t;

class LevenshteinTable{
  private:
    const QString _original;
    const QString _modified;

    /**
     * Levenshtein table.
     *    O r i g i n a l S t r i n g
     *
     * M    | Insertion
     * o    v
     * d
     * i    --> Deletion
     * f
     * i    \
     * e     \
     * d      Substitution
     *
     */
    std::vector<std::vector<int> > _table;

    /**
     * List of coordinates in which can be levenshtein table traced.
     * The pair is in form (row, column).
     */
    std::list<std::pair<int, int> > _trace;

    /**
     * Allocate memory into _table.
     */
    void _allocateMemory();

    /**
     * Fill _table as levenshtein table.
     */
    void _fillTable();

    void _findTrace();
    void _minAncestor(int &row, int &column) const;

    /**
     * Helper method for fillRanges.
     */
    void _finishRange(std::vector<range_t> &ranges, range_t::range_type,
            const std::pair<int, int> &from, const std::pair<int, int> &to) const;

    /**
     * Returns minimum of numbers.
     */
    int _min(int, int, int) const;
    int _min(int, int) const;
  public:
    LevenshteinTable(const QString &orig, const QString &modif);

    /**
     * Fill ranges given in argument.
     */
    void fillRanges(std::vector<range_t> &) const;

    /**
     * Dump internal _table/_trace into given argument.
     * This method is usable for debuging or testing.
     */
    void dumpTable(std::vector<std::vector<int> > &) const;
    void dumpTrace(std::list<std::pair<int, int> > &) const;
};

#endif
