#pragma once

#include <vector>
#include <initializer_list>
#include <memory>


namespace Cx
{
    template<class T>
    class VectorContainer : public std::vector<T>
    {
    public:
        /// Default constructor that creates the empty container
        VectorContainer() noexcept : std::vector<T>()
        {}


        /// Constructor with initializer list as a parameter
        VectorContainer(std::initializer_list<T> initialValues) noexcept : std::vector<T>(initialValues)
        {}
    };
}
