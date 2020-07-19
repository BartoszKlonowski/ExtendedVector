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


        void RemoveAll( std::function<bool( T )> predicate ) noexcept
        {
            this->erase( std::remove_if( this->begin(), this->end(), predicate ) );
        }


        const bool TrueForAll( std::function<bool( T )> predicate )
        {
            if( predicate == nullptr )
                throw std::invalid_argument( "predicate is null" );
            for( auto it = this->cbegin(); it != this->cend(); ++it )
                if( predicate( *it ) == false )
                    return false;
            return true;
        }


        const int BinarySearch( T item ) noexcept
        {
            return BinarySearchGenericImplementation( item, [&]( T element )->bool { return element == item; }, 0, this->size() - 1 );
        }

        const bool BinarySearch( T item, std::function<bool( T )> predicate ) noexcept
        {
            return BinarySearchGenericImplementation( item, predicate, 0, this->size() - 1 );
        }

        const bool BinarySearch( T item, const unsigned int start, const unsigned int count, std::function<bool( T )> predicate )
        {
            return BinarySearchGenericImplementation( item, predicate, start, count );
        }


        void Remove( T item ) noexcept
        {
            auto it = std::find( this->cbegin(), this->cend(), item );
            this->erase( it );
        }


        T FindLast( std::function<bool( T )> predicate ) const noexcept
        {
            auto resultInstance = T();
            for( auto it = this->cbegin(); it != this->cend(); ++it )
                if( predicate( *it ) )
                    resultInstance = *it;
            return resultInstance;
        }


    private:
        const int BinarySearchGenericImplementation( T item, std::function<bool( T )> predicate, const unsigned int start, const unsigned int count )
        {
            constexpr int notFoundResult = -1;
            unsigned int leftIndex = start;
            unsigned int rightIndex = start + count >= this->size() ? this->size() - 1 : start + count;

            while( leftIndex <= rightIndex )
            {
                auto middle = (rightIndex - leftIndex) / 2 + leftIndex;
                if( predicate( this->at( middle ) ) )
                    return middle;
                else if( item < this->at( middle ) )
                    rightIndex = middle - 1;
                else if( item > this->at( middle ) )
                    leftIndex = middle + 1;
            }
            return notFoundResult;
        }
    };
}
