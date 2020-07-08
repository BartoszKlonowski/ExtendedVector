#pragma once

#include "Wrapper/Container.hpp"
#include <memory>
#include <vector>
#include <iostream>


namespace Cx
{
    template<class T>
    class ExtendedVector : public VectorContainer<T>
    {
    public:
        ExtendedVector() = default;

        void AddRange(const std::initializer_list<T>& list) noexcept
        {
            for(auto element : list)
                this->push_back(element);
        }

        void AddRange(const T* const range, const unsigned int size) noexcept
        {
            if(range != nullptr)
                for(unsigned int i = 0; i < size; ++i)
                    this->push_back(range[i]);
        }

        void AddRange(const ExtendedVector<T>& vector) noexcept
        {
            for(auto element : vector)
                this->push_back(element);
        }

        void AddRange(ExtendedVector<T>&& vector) noexcept
        {
            for(auto element : vector)
                this->push_back(element);
        }


        bool Contains( T item ) const noexcept
        {
            for( auto it = this->begin(); it != this->end(); ++it )
                if( *it == item )
                    return true;
            return false;
        }

    private:
    };
}
