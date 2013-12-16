///
/// file: Type.h
///

#ifndef __CONDUIT_TYPE_H
#define __CONDUIT_TYPE_H

#include "Core.h"
#include "Endianness.h"

#include <vector>
#include <string>
#include <sstream>

namespace conduit
{

class Node;
///============================================
/// DataType
///============================================
class DataType
{
public:
    typedef enum
    {
        EMPTY_T = 0, // default
        NODE_T,      // node
        LIST_T,      // list
        BOOL_T,      // boolean
        INT8_T,      // int8 and  int8_array
        INT16_T,     // int16 and int16_array
        INT32_T,     // int32 and int32_array
        INT64_T,     // int64 and int64_array
        UINT8_T,     // int8 and  int8_array
        UINT16_T,    // uint16 and uint16_array
        UINT32_T,    // uint32 and uint32_array
        UINT64_T,    // uint64 and uint64_array
        FLOAT32_T,   // float32 and float32_array
        FLOAT64_T,   // float64 and float64_array
        BYTESTR_T,   // bytestr (incore c-string)
    } TypeEnum;
    
    class Objects
    {
    public:
        static const DataType &empty() {return m_empty;}
        static const DataType &node()  {return m_node;}
        static const DataType &list()  {return m_list;}
    private:
        /// TODO: const ref access via function
        static DataType m_empty;
        static DataType m_node;
        static DataType m_list;
    };
    
    class Scalars
    {    
    public:
        static const DataType &boolean() {return m_boolean;}
        /* int scalars */
        static const DataType &int8()  {return m_int8;}
        static const DataType &int16() {return m_int16;}
        static const DataType &int32() {return m_int32;}
        static const DataType &int64() {return m_int64;}
        /* uint scalars */
        static const DataType &uint8()  {return m_uint8;}
        static const DataType &uint16() {return m_uint16;}
        static const DataType &uint32() {return m_uint32;}
        static const DataType &uint64() {return m_int64;}
        /* float scalars */
        static const DataType &float32() {return m_float32;}
        static const DataType &float64() {return m_int64;}

    private:
        static DataType m_boolean;
        /* int scalars */
        static DataType m_int8;
        static DataType m_int16;
        static DataType m_int32;
        static DataType m_int64;
        /* uint scalars */
        static DataType m_uint8;
        static DataType m_uint16;
        static DataType m_uint32;
        static DataType m_uint64;
        /* float scalars */
        static DataType m_float32;
        static DataType m_float64;
    };

             DataType();
             explicit DataType(index_t id);

             DataType(const DataType& type);

             DataType(const std::string &dtype_name,
                      index_t num_elements,
                      index_t offset,
                      index_t stride,
                      index_t element_bytes,
                      index_t endianness);

             DataType(index_t dtype_id,
                      index_t num_elements,
                      index_t offset,
                      index_t stride,
                      index_t element_bytes,
                      index_t endianness);

    virtual ~DataType();

    void       reset(const DataType& type);
    void       reset(index_t dtype_id);
    void       reset(index_t dtype_id,
                     index_t num_elements,
                     index_t offset,
                     index_t stride,
                     index_t element_bytes,
                     index_t endianness);

    static index_t          name_to_id(const std::string &name);
    static std::string      id_to_name(index_t dtype);
    

    static DataType const  &default_dtype(index_t dtype_id);
    static DataType const  &default_dtype(const std::string &name);
       
    std::string         schema() const;
    void                schema(std::ostringstream &oss) const;
    
    index_t     id()    const { return m_id;}    
    index_t     total_bytes()   const;
    index_t     total_bytes_compact() const;
    bool        is_compatible(const DataType& type) const;

    index_t    number_of_elements()  const { return m_num_ele;}
    index_t    offset()              const { return m_offset;}
    index_t    stride()              const { return m_stride;}
    index_t    element_bytes()       const { return m_ele_bytes;}
    index_t    endianness()          const { return m_endianness;}
    index_t    element_index(index_t idx) const;

    template<typename T>
    struct Traits { };

private:

    index_t   m_id;         // for dtype enum value
    index_t   m_num_ele;    // number of entries
    index_t   m_offset;     // bytes to start of array
    index_t   m_stride;     // bytes between start of current and start of next
    index_t   m_ele_bytes;  // bytes per element
    index_t   m_endianness;  // endianness of elements

};



template<>
struct DataType::Traits<conduit::uint32>
{
   static const DataType::TypeEnum data_type = UINT32_T;
};

template<>
struct DataType::Traits<conduit::float64>
{
   static const DataType::TypeEnum data_type = FLOAT64_T;
};



};


#endif
