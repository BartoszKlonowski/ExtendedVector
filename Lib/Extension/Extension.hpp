#pragma once

#include "Wrapper/Container.hpp"
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <exception>


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


        void CopyTo( const unsigned int index, T* array, const unsigned int arrayIndex, const unsigned int count ) const
        {
            if( array == nullptr )
                throw std::invalid_argument( "array is nullptr" );
            else if( index >= this->size() || (this->size() - index) > (count - arrayIndex) )
                throw std::out_of_range( "index exceeds the size of Vector" );
            for( unsigned int copiedElements = 0; copiedElements < count; ++copiedElements )
                array[arrayIndex + copiedElements] = this->operator[]( index + copiedElements );
        }

        void CopyTo( T* array, const unsigned int size )
        {
            if( array == nullptr )
                throw std::invalid_argument( "array is nullptr" );
            else if( size < this->size() )
                throw std::invalid_argument( "destination smaller than source" );
            for( unsigned int i = 0; i < this->size(); ++i )
            {
                array[i] = this->at( i );
            }
        }

        void CopyTo( T* array, const unsigned int size, unsigned int arrayIndex )
        {
            if( array == nullptr )
                throw std::invalid_argument( "array is nullptr" );
            else if( size - arrayIndex < this->size() )
                throw std::invalid_argument( "destination smaller than source" );
            for( unsigned int i = 0; i < this->size(); ++i, ++arrayIndex )
            {
                array[arrayIndex] = this->at( i );
            }
        }


        T Find( std::function<bool( T )> predicate )
        {
            if( predicate == nullptr )
                throw std::invalid_argument( "predicate is nullptr" );

            for( auto it = this->begin(); it != this->end(); ++it )
                if( predicate( *it ) == true )
                    return it.operator*();
            return T();
        }
    };
}
