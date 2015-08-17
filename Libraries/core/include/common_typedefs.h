#ifndef COMMON_TYPEDEFS_H
#define COMMON_TYPEDEFS_H

#include <core_types.h>

/**
 * @macro DEPRECATED
 *
 * @brief Denotes a deprecated method or variable.
 */
#define DEPRECATED


/**
 * @macro FIXME
 *
 * @brief Denotes a portion of code that has a known problem to be fixed.
 */
#define FIXME


/**
 * @macro UNREF
 *
 * Macro to be used around the unused arguments of the functions to prevent
 * tedious compilation warnings.
 */
#define UNREF(a)


/******************************************************************************/
/* Basic typedefs. */

//#ifndef uint
//typedef unsigned int    uint;
//#endif

//#ifndef UCHAR
//typedef uint8_t         UCHAR;
//#endif

/******************************************************************************/
/* Union types. */

union char_uchar
{
    uint8_t     m_ucData;
    char        m_cData;
};

union ValueDouble
{
    uint8_t     m_aucData[8];
    double      m_dValue;
}; // end union ValueDouble.

union ValueFloat
{
    uint8_t     m_aucData[4];
    float       m_fValue;
}; // end union ValueFloat.

union ValueInt8
{
    uint8_t     m_aucData[1];
    int8_t      m_cValue;
}; // end union ValueInt8.

union ValueInt16
{
    uint8_t   m_aucData[2];
    int16_t   m_sValue;
}; // end union ValueInt16.

union ValueInt32
{
    uint8_t   m_aucData[4];
    int32_t   m_iValue;
}; // end union ValueInt32.

union ValueInt64
{
    uint8_t   m_aucData[8];
    int64_t   m_iValue;
}; // end union ValueInt32.

union ValueUint8
{
    uint8_t   m_aucData[8];
    uint8_t   m_ucValue;
}; // end union ValueUint8.

union ValueUint16
{
    uint8_t   m_aucData[2];
    uint16_t  m_usValue;
}; // end union ValueUint16.

union ValueUint32
{
    uint8_t   m_aucData[4];
    uint32_t  m_uiValue;
}; // end union ValueUint16.

union ValueUint64
{
    uint8_t   m_aucData[8];
    uint64_t  m_uiValue;
}; // end union ValueUint64.

/******************************************************************************/
/* Pointers */

#ifndef SHARED_PTR
#  define SHARED_PTR        std::tr1::shared_ptr
#  define GET_PTR(s)        s.get()
#  define RELEASE_PTR(s)    s.reset();
#  define DYNAMIC_PTR_CAST  std::dynamic_pointer_cast
#endif // SHARED_PTR

#ifndef DEF_PTR
#define DEF_PTR(type)       typedef SHARED_PTR<type>  type##Ptr
#endif


/******************************************************************************/
/* Numerical typedefs. */

#define DEG_TO_RAD(x)       (x * M_PI / 180.0)
#define RAD_TO_DEG(x)       (x * 180.0 / M_PI)

#define MM_TO_INCHES(x)     (x / 25.4)
#define INCHES_TO_MM(m)     (x * 25.4)

#ifndef INFINITY
#define INFINITY    std::numeric_limits<double>::infinity()
#endif

inline bool FuzzyCompare(double p1, double p2)
{
    return (std::abs(p1 - p2) * 1000000000000. <= std::min(std::abs(p1),
                                                           std::abs(p2)));
}

inline bool FuzzyCompare(float p1, float p2)
{
    return (std::abs(p1 - p2) * 100000.f <= std::min(std::abs(p1),
                                                     std::abs(p2)));
}

inline bool FuzzyIsNull(double d)
{
    return std::abs(d) <= 0.000000000001;
}

inline bool FuzzyIsNull(float d)
{
    return std::abs(d) <= 0.00001f;
}

/******************************************************************************/
/* STD library extension. */

/* Definition of isnan. */
#ifndef isnan
#define isnan(x) (x != x)
#endif // isnan

/* Shortcuts to access the key and the value of a std::map<>::iterator. */
#define MAP_KEY(iterator)   (iterator->first)
#define MAP_VALUE(iterator) (iterator->second)

#ifdef __unix
#ifndef __ANDROID__
/* Definition of std::next and std::prev functions is not defined. */
namespace std
{
template <typename ForwardIt>
ForwardIt next(const ForwardIt it,
               typename std::iterator_traits<ForwardIt>::difference_type n = 1)
{
    ForwardIt   nit;
    nit = it;
    std::advance(nit, n);
    return nit;
}
template <typename ForwardIt>
ForwardIt prev(const ForwardIt it,
               typename std::iterator_traits<ForwardIt>::difference_type n = 1)
{
    ForwardIt   nit;
    nit = it;
    std::advance(nit, -n);
    return nit;
}
} // end namespace std.
#endif // __ANDROID__
#endif // __unix

#define FORALL(container, it) \
    for (it = container.begin(); it != container.end(); it++)

#define FORALL_REV(container, it) \
    for (it = container.rbegin(); it != container.rend(); it++)

#define LIST_AT(list, index)    (*std::next(list.begin(), index))

#define LIST_CONTAINS(list, item) \
    (std::find(list.begin(), list.end(), item) != list.end())

#define LIST_REMOVE(list, item) \
    (list.remove(item))

#define MAP_CONTAINS(map, item) \
    (map.find(item) != map.end())

#endif // COMMON_TYPEDEFS_H
