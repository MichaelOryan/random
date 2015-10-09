#ifndef _ORYAN_VECTOR_H
#define _ORYAN_VECTOR_H
#include <iostream>
#include <vector>

namespace ORYAN
{

    template<class T>
    typename std::vector<T>::const_iterator offset(const std::vector<T> &source, typename std::vector<T>::difference_type offset_size, typename std::vector<T>::const_iterator start)
    {
        typename std::vector<T>::difference_type in_range_offset = ( std::distance(source.begin(), start) + offset_size) % std::distance(source.begin(), source.end());

        if(in_range_offset < 0)
        {
            return source.end() + in_range_offset;
        }

        return source.begin() + in_range_offset;

    }


    template<class T>
    typename std::vector<T>::const_iterator offset(const std::vector<T> &source, typename std::vector<T>::difference_type offset_size)
    {
        return offset(source, offset_size, source.begin());
    }

    template<class T>
    std::vector<T> cycle(const std::vector<T> &source, typename std::vector<T>::difference_type offset_size)
    {
        std::vector<T> cycled;

        typename std::vector<T>::difference_type source_size = std::distance(source.begin(), source.end());

        typename std::vector<T>::const_iterator source_iter = offset(source, offset_size);

        for(typename std::vector<T>::difference_type i = 0; i < source_size; i++)
        {
            if(source_iter == source.end())
            {
                source_iter = source.begin();
            }

            cycled.push_back(*source_iter);

            source_iter++;
        }

        return cycled;
    }

}

#endif // _ORYAN_VECTOR_H
