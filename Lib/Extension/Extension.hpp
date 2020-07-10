#pragma once

#include "Wrapper/Container.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>


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


        void Sort()
        {
            try
            {
                std::sort( this->begin(), this->end() );
            }
            catch( const std::exception& e )
            {
                throw e;
            }
        }

        void Sort( const unsigned int positionBegin, const unsigned int positionEnd )
        {
            ExtendedVector<T> vector;
            for( unsigned int i = positionBegin; i <= positionEnd; ++i )
                vector.push_back( this->at(i) );
            try
            {
                std::sort( vector.begin(), vector.end() );
                for( unsigned int i = positionBegin, j = 0; i < positionEnd; ++i, ++j )
                    this->operator[]( i ) = vector.at(j);
                this->operator[]( positionEnd ) = vector.at( vector.size() - 1 );
            }
            catch( std::exception& e )
            {
                throw e;
            }
        }

        void Sort( std::function<bool( T, T )> comparer )
        {
            try
            {
                std::sort( this->begin(), this->end(), comparer );
            }
            catch( std::exception& e )
            {
                throw e;
            }
        }

        void Sort( const unsigned int positionBegin, const unsigned int positionEnd, std::function<bool( T, T )> comparer )
        {
            ExtendedVector<T> vector;
            for( unsigned int i = positionBegin; i <= positionEnd; ++i )
                vector.push_back( this->at( i ) );
            try
            {
                std::sort( vector.begin(), vector.end(), comparer );
                for( unsigned int i = positionBegin, j = 0; i < positionEnd; ++i, ++j )
                    this->operator[]( i ) = vector.at( j );
                this->operator[]( positionEnd ) = vector.at( vector.size() - 1 );
            }
            catch( std::exception& e )
            {
                throw e;
            }
        }


        const bool Exists( std::function<bool( T )> predicate ) const noexcept
        {
            return std::find_if( this->begin(), this->end(), predicate ) != this->end();
        }
    };
}
