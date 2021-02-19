#pragma once

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
    class Vector : public std::vector<T>
    {
    public:
        Vector() noexcept : std::vector<T>()
        {}

        Vector( std::initializer_list<T> initialValues ) noexcept : std::vector<T>( initialValues )
        {}

#pragma region AddRange
        /// <summary>
        /// Adds the element of the specified collection to the end of the Vector
        /// </summary>
        /// <param name="list">The collection whose elements should be added to the end of the Vector.</param>
        void AddRange( const std::initializer_list<T>& list ) noexcept
        {
            for( auto element : list )
                this->push_back( element );
        }

        /// <summary>
        /// Adds the element of the specified collection to the end of the Vector
        /// </summary>
        /// <param name="range">The collection whose elements should be added to the end of the Vector.</param>
        /// <param name="size">Number of elements in the range which should be added</param>
        void AddRange( const T* const range, const unsigned int size ) noexcept
        {
            if( range != nullptr )
                for( unsigned int i = 0; i < size; ++i )
                    this->push_back( range[i] );
        }

        /// <summary>
        /// Adds the element of the specified collection to the end of the Vector
        /// </summary>
        /// <param name="vector">The collection given as another Vector, whose elements should be copied to the end of current Vector</param>
        void AddRange( const Vector<T>& vector ) noexcept
        {
            for( auto element : vector )
                this->push_back( element );
        }

        /// <summary>
        /// Adds the element of the specified collection to the end of the Vector
        /// </summary>
        /// <param name="vector">The collection given as another Vector, whose elements should be moved to the end of current Vector</param>
        void AddRange( Vector<T>&& vector ) noexcept
        {
            for( auto element : vector )
                this->push_back( element );
        }
#pragma endregion

#pragma region Contains
        /// <summary>
        /// Determines whether an element is in the Vector
        /// </summary>
        /// <param name="item">The object to locate in the Vector</param>
        /// <returns>true if item is found in the Vector, false otherwise</returns>
        bool Contains( T item ) const noexcept
        {
            for( auto it = this->begin(); it != this->end(); ++it )
                if( *it == item )
                    return true;
            return false;
        }
#pragma endregion

#pragma region Sort
        /// <summary>
        /// Sorts the elements in the Vector using the default std::sort
        /// </summary>
        void Sort()
        {
            try
            {
                std::sort( this->begin(), this->end() );
            }
            catch( const std::exception& e ) { throw e; }
        }

        /// <summary>
        /// Sorts a portion of the elements in the Vector using the default std::sort
        /// </summary>
        /// <param name="positionBegin">Index of the first element of the portion to sort</param>
        /// <param name="positionEnd">Index of the last element of the portion to sort</param>
        void Sort( const unsigned int positionBegin, const unsigned int positionEnd )
        {
            Vector<T> vector;
            for( unsigned int i = positionBegin; i <= positionEnd; ++i )
                vector.push_back( this->at( i ) );
            try
            {
                std::sort( vector.begin(), vector.end() );
                for( unsigned int i = positionBegin, j = 0; i < positionEnd; ++i, ++j )
                    this->operator[]( i ) = vector.at( j );
                this->operator[]( positionEnd ) = vector.at( vector.size() - 1 );
            }
            catch( std::exception& e ) { throw e; }
        }

        /// <summary>
        /// Sorts the elements in the Vector using the specified comparer
        /// </summary>
        /// <param name="comparer">Function determining the sort order</param>
        void Sort( std::function<bool( T, T )> comparer )
        {
            try
            {
                std::sort( this->begin(), this->end(), comparer );
            }
            catch( std::exception& e ) { throw e; }
        }

        /// <summary>
        /// Sorts a portion of the elements in the Vector using the specified comparer
        /// </summary>
        /// <param name="positionBegin">Index of the first element of the portion to sort</param>
        /// <param name="positionEnd">Index of the last element of the portion to sort</param>
        /// <param name="comparer">Function determining the sort order</param>
        void Sort( const unsigned int positionBegin, const unsigned int positionEnd, std::function<bool( T, T )> comparer )
        {
            Vector<T> vector;
            for( unsigned int i = positionBegin; i <= positionEnd; ++i )
                vector.push_back( this->at( i ) );
            try
            {
                std::sort( vector.begin(), vector.end(), comparer );
                for( unsigned int i = positionBegin, j = 0; i < positionEnd; ++i, ++j )
                    this->operator[]( i ) = vector.at( j );
                this->operator[]( positionEnd ) = vector.at( vector.size() - 1 );
            }
            catch( std::exception& e ) { throw e; }
        }
#pragma endregion

#pragma region Exists
        /// <summary>
        /// Determines whether the Vector contains elements that match the conditions defined by the specified predicate
        /// </summary>
        /// <param name="predicate">The predicate std::function delegate that defines the conditions of the elements to search for</param>
        /// <returns>true if the Vector contains one or more elements that match the conditions defined by the specified predicate; false otherwise</returns>
        const bool Exists( std::function<bool( T )> predicate ) const noexcept
        {
            return std::find_if( this->begin(), this->end(), predicate ) != this->end();
        }
#pragma endregion

#pragma region CopyTo
        /// <summary>
        /// Copies a range of elements from the Vector to a compatible one-dimensional array starting at the specified index of the target
        /// </summary>
        /// <param name="index">The zero-based index in the source Vector at which copying begins</param>
        /// <param name="array">The one-dimensional array that is the destination of the elements copied from from Vector. The array must have zero-based indexing</param>
        /// <param name="arrayIndex">The zero-based index in array at which copying begins</param>
        /// <param name="count">The number of elements to copy</param>
        void CopyTo( const unsigned int index, T* array, const unsigned int arrayIndex, const unsigned int count ) const
        {
            if( array == nullptr )
                throw std::invalid_argument( "array is nullptr" );
            else if( index >= this->size() || (this->size() - index) > (count - arrayIndex) )
                throw std::out_of_range( "index exceeds the size of Vector" );
            for( unsigned int copiedElements = 0; copiedElements < count; ++copiedElements )
                array[arrayIndex + copiedElements] = this->operator[]( index + copiedElements );
        }

        /// <summary>
        /// Copies the entire Vector to a compatible one-dimensional array, starting at the beginning of the target array
        /// </summary>
        /// <param name="array">The one-dimensional array that is the destination of the elements copied from Vector</param>
        /// <param name="size">Size of target array which the Vector's elements are copied to</param>
        void CopyTo( T* array, const unsigned int size )
        {
            if( array == nullptr )
                throw std::invalid_argument( "array is nullptr" );
            else if( size < this->size() )
                throw std::invalid_argument( "destination smaller than source" );
            for( unsigned int i = 0; i < this->size(); ++i )
                array[i] = this->at( i );
        }

        /// <summary>
        /// Copies the entire Vector to a compatible one-dimensional array, starting at the specified index of the target array
        /// </summary>
        /// <param name="array">The one-dimensional array that is the destination of the elements copied from Vector</param>
        /// <param name="size">Size of target array which the Vector's elements are copied to</param>
        /// <param name="arrayIndex">The zero-based index in the array at which copying begins</param>
        void CopyTo( T* array, const unsigned int size, unsigned int arrayIndex )
        {
            if( array == nullptr )
                throw std::invalid_argument( "array is nullptr" );
            else if( size - arrayIndex < this->size() )
                throw std::invalid_argument( "destination smaller than source" );
            for( unsigned int i = 0; i < this->size(); ++i, ++arrayIndex )
                array[arrayIndex] = this->at( i );
        }
#pragma endregion


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
            this->erase( std::remove_if( this->begin(), this->end(), predicate ), this->end() );
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


        void RemoveRange( const unsigned int start, const unsigned int count )
        {
            if( start + count > this->size() )
                throw std::invalid_argument( "range exceeds the container size" );
            this->erase( this->cbegin() + start, this->cbegin() + start + count );
        }


        const int IndexOf( T element ) const
        {
            try
            {
                return IndexOfGenericImplementation( element, 0, this->size() );
            }
            catch( const std::invalid_argument& e ) { throw e; }
        }

        const int IndexOf( T element, const unsigned int start ) const
        {
            try
            {
                return IndexOfGenericImplementation( element, start, this->size() - start );
            }
            catch( const std::invalid_argument& e ) { throw e; }
        }

        const int IndexOf( T element, const unsigned int start, const unsigned int count ) const
        {
            try
            {
                return IndexOfGenericImplementation( element, start, count );
            }
            catch( const std::invalid_argument& e ) { throw e; }
        }


        const int FindIndex( std::function<bool( T )> predicate ) const
        {
            try
            {
                return FindIndexGenericImplementation( predicate, 0, this->size() );
            }
            catch( const std::invalid_argument& e ) { throw e; }
        }

        const int FindIndex( std::function<bool( T )> predicate, const unsigned int start ) const
        {
            try
            {
                return FindIndexGenericImplementation( predicate, start, this->size() - start );
            }
            catch( const std::invalid_argument& e ) { throw e; }
        }

        const int FindIndex( std::function<bool( T )> predicate, const unsigned int start, const unsigned int count ) const
        {
            try
            {
                return FindIndexGenericImplementation( predicate, start, count );
            }
            catch( const std::invalid_argument& e ) { throw e; }
        }


        void Reverse() noexcept
        {
            const auto swapRange = static_cast<int>(this->size() / 2);
            for( auto swappedIndex = 0; swappedIndex < swapRange; ++swappedIndex )
                std::swap( this->operator[]( swappedIndex ), this->operator[]( this->size() - 1 - swappedIndex ) );
        }

        void Reverse( const unsigned int start, const unsigned int count )
        {
            if( start + count >= this->size() )
                throw std::invalid_argument( "reverse range exceeds container size" );
            for( unsigned int swappedIndex = 0; swappedIndex < count / 2; ++swappedIndex )
                std::swap( this->operator[]( swappedIndex + start ), this->operator[]( start + count - swappedIndex - 1 ) );
        }


        const int FindLastIndex( std::function<bool( T )> predicate ) const noexcept
        {
            int index = 0;
            int lastIndex = -1;
            for( auto it = this->cbegin(); it != this->cend(); ++it, ++index )
                if( predicate( *it ) )
                    lastIndex = index;
            return lastIndex;
        }

        const int FindLastIndex( const unsigned int end, std::function<bool( T )> predicate ) const
        {
            if( end >= this->size() )
                throw std::invalid_argument( "Ending index exceeds container size" );
            int lastIndex = -1;
            int index = 0;
            for( auto it = this->cbegin(); it != this->cbegin() + end; ++it, ++index )
                if( predicate( *it ) )
                    lastIndex = index;
            return lastIndex;
        }

        const int FindLastIndex( const unsigned int start, const unsigned int end, std::function<bool( T )> predicate ) const
        {
            if( start > end )
                throw std::invalid_argument( "starting index bigger than ending index of search range" );
            else if( end >= this->size() )
                throw std::invalid_argument( "ending index exceeds container size" );
            else if( start >= this->size() )
                throw std::invalid_argument( "starting index is beyond the container size" );
            int lastIndex = -1;
            int index = 0;
            for( auto it = this->cbegin() + start; it != this->cbegin() + end; ++it, ++index )
                if( predicate( *it ) )
                    lastIndex = index;
            return lastIndex;
        }


        void InsertRange( const unsigned int index, const T* const range, const unsigned int n )
        {
            if( range == nullptr )
                throw std::invalid_argument( "range is nullptr" );
            else if( index > this->size() )
                throw std::invalid_argument( "insertion index beyond container size" );
            for( auto i = 0u; i < n; ++i )
                this->insert( this->cbegin() + index + i, range[i] );
        }

        void InsertRange( const unsigned int index, const std::vector<T>& range )
        {
            try
            {
                InsertRange( index, range.data(), range.size() );
            }
            catch( std::invalid_argument& e ) { throw e; }
        }

        void InsertRange( const unsigned int index, std::vector<T>&& range )
        {
            try
            {
                InsertRange( index, range.data(), range.size() );
            }
            catch( std::invalid_argument& e ) { throw e; }
        }

        void InsertRange( const unsigned int index, const Vector<T>& range )
        {
            try
            {
                InsertRange( index, range.data(), range.size() );
            }
            catch( std::invalid_argument& e ) { throw e; }
        }

        void InsertRange( const unsigned int index, Vector<T>&& range )
        {
            try
            {
                InsertRange( index, range.data(), range.size() );
            }
            catch( std::invalid_argument& e ) { throw e; }
        }


        Vector<T> GetRange( const unsigned int start, const unsigned int end ) const
        {
            if( start >= this->size() || end >= this->size() || start >= end )
                throw std::invalid_argument( "Incorrect range tresholds were given" );
            Vector<T> newVector;
            for( auto it = this->cbegin() + start; it != this->cbegin() + end; ++it )
                newVector.push_back( *it );
            return newVector;
        }


        const int LastIndexOf( T item ) const noexcept
        {
            return LastIndexOfGenericImplementation( item, 0, this->size() );
        }

        const int LastIndexOf( T item, const unsigned int index )
        {
            return LastIndexOfGenericImplementation( item, 0, index );
        }

        const int LastIndexOf( T item, const unsigned int index, const unsigned int count )
        {
            return LastIndexOfGenericImplementation( item, index, count );
        }


        template<class Tout> Vector<Tout> ConvertAll( std::function<Tout( T )> converter ) const noexcept
        {
            Vector<Tout> convertedContainer;
            for( auto it = this->cbegin(); it != this->cend(); ++it )
                convertedContainer.push_back( converter( *it ) );
            return convertedContainer;
        }


        void RemoveAt( const unsigned int index )
        {
            if( index >= this->size() )
                throw std::invalid_argument( "index to remove exceeds the container size" );
            this->erase( this->cbegin() + index );
        }


        void ForEach( std::function<void( T& )> action ) noexcept
        {
            for( T& element : *this )
                action( element );
        }


        Vector<T> FindAll( std::function<bool( T )> predicate ) const noexcept
        {
            Vector<T> results;
            for( auto element : *this )
                if( predicate( element ) )
                    results.push_back( element );
            return results;
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


        const int IndexOfGenericImplementation( T item, const unsigned int start, const unsigned int count ) const
        {
            if( start + count > this->size() )
                throw std::invalid_argument( "search range exceeds containers size" );
            constexpr int result = -1;
            for( unsigned int index = start; index < start + count; ++index )
                if( this->operator[]( index ) == item )
                    return index;
            return result;
        }


        const int LastIndexOfGenericImplementation( T item, const unsigned int start, const unsigned int count ) const
        {
            if( start + count > this->size() )
                throw std::invalid_argument( "search range exceeds containers size" );
            int lastIndex = -1;
            int index = 0;
            for( auto it = this->cbegin() + start; it != this->cbegin() + (start + count); ++it, ++index )
                if( *it == item )
                    lastIndex = index;
            return lastIndex;
        }


        const int FindIndexGenericImplementation( std::function<bool( T )> predicate, const unsigned int start, const unsigned int count ) const
        {
            if( start + count > this->size() )
                throw std::invalid_argument( "search range exceeds containers size" );
            constexpr int result = -1;
            for( unsigned int index = start; index < start + count; ++index )
                if( predicate( this->operator[]( index ) ) )
                    return index;
            return result;
        }
    };
}
