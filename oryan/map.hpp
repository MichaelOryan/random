/*
 *
 * c++98 (QQ) compliant functions dealing with maps
 *
 */


#ifndef _ORYAN_MAP_H
#define _ORYAN_MAP_H

#include <vector>
#include <map>
#include <iostream>

namespace ORYAN
{

    template<class SourceT, class DestinationT>
    std::vector<DestinationT> convert(std::vector<SourceT> source, const std::map<SourceT, DestinationT> codex)
    {
        std::vector<DestinationT> converted;


        typedef typename std::vector<SourceT>::iterator Source_IT;
        typedef typename std::map<SourceT, DestinationT>::const_iterator Codex_IT;

        for(Source_IT iter = source.begin(); iter != source.end(); iter++)
        {
            Codex_IT index = codex.find(*iter);
            if(index != codex.end())
            {
                converted.push_back((*index).second);
            }
        }

        return converted;
    }

    template<class SourceKeyT, class DestinationKeyT, class DataT>
    std::map<DestinationKeyT, DataT> convert_map(std::map<SourceKeyT, DataT> source, std::map<SourceKeyT, DestinationKeyT> codex)
    {
        std::map<DestinationKeyT, DataT> converted_map;

        typedef typename std::map<SourceKeyT, DataT>::iterator Source_IT;
        typedef typename std::map<SourceKeyT, DestinationKeyT>::iterator Codex_IT;

        for(Source_IT source_iter = source.begin(); source_iter != source.end(); source_iter++)
        {
            Codex_IT codex_index = codex.find((*source_iter).first);
            if(codex_index != codex.end())
            {
                converted_map[(*codex_index).second] = (*source_iter).second;
            }
        }

        return converted_map;
    }

    template<class T, class U>
    bool isBijective(std::map<T, U> theMap)
    {
        std::map<U, int> testMap;

        bool isBijective = true;

        typedef typename std::map<T, U>::iterator TheMap_IT;
        typedef typename std::map<U, int>::iterator TestMap_IT;

        for(TheMap_IT iter = theMap.begin(); isBijective && iter != theMap.end(); iter++)
        {
            U nextU = (*iter).second;
            TestMap_IT testMapIndex = testMap.find(nextU);
            isBijective = testMapIndex == testMap.end();
            if(isBijective)
            {
                testMap[nextU] = 1;
            }
        }

        return isBijective;
    }


    template<class T, class U, class V>
    bool isKeyInjective(std::map<T, U> source, std::map<T, V> target)
    {
        bool isInjective = true;

        typedef typename std::map<T, U>::iterator Source_IT;
        typedef typename std::map<T, V>::iterator Target_IT;

        for(Source_IT source_iter = source.begin(); isInjective == true && source_iter != source.end(); source_iter++)
        {
            T next_key = (*source_iter).first;
            Target_IT target_index = target.find(next_key);
            isInjective = (target_index != target.end());
        }

        return isInjective;
    }

    template<class T, class U, class V>
    bool isKeyBijective (std::map<T, U> first_map, std::map<T, V> second_map)
    {
        return isKeyInjective(first_map, second_map) && isKeyInjective(second_map, first_map);
    }

    template<class T, class U>
    std::map<U, T> inverseMap(std::map<T, U> source)
    {

        std::map<U, T> inverse_map;

        typedef typename std::map<T, U>::iterator Source_IT;

        for(Source_IT source_iter = source.begin(); source_iter != source.end(); source_iter++)
        {
            inverse_map[(*source_iter).second] = (*source_iter).first;
        }

        return inverse_map;
    }

    template<class T, class U>
    std::map<T, U> cycle(std::map<T, U> source, std::vector<T> cycle)
    {
        std::map<T, U> cycled_map;

        typedef typename std::vector<T>::iterator Cycle_IT;


        for(Cycle_IT cycle_iter = cycle.begin(); cycle_iter != cycle.end(); cycle_iter++)
        {
            Cycle_IT next_iter = cycle_iter + 1;
            if(next_iter == cycle.end())
            {
                next_iter = cycle.begin();
            }

            cycled_map[*cycle_iter] = source[(*next_iter)];
        }

        return cycled_map;
    }

    template<class T, class U>
    std::vector<T> getKeys(std::map<T, U> source)
    {
        std::vector<T> keys;

        for(typename std::map<T, U>::iterator source_iter = source.begin(); source_iter != source.end(); source_iter++)
        {
            keys.push_back((*source_iter).first);
        }

    }

    template<class T, class U>
    std::vector<U> getValues(std::map<T, U> source)
    {
        std::vector<U> keys;

        for(typename std::map<T, U>::iterator source_iter = source.begin(); source_iter != source.end(); source_iter++)
        {
            keys.push_back((*source_iter).second);
        }

    }

}

#endif // _ORYAN_MAP_H
