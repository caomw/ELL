// IIterator.h

#pragma once

/// stl
#include <vector>
using std::vector;

namespace utilities
{
    template <typename T>
    class IIterator
    {
    public:
        /// \returns True if the iterator is currently pointing to a valid iterate
        ///
        virtual bool IsValid() const = 0;

        /// Proceeds to the Next row
        ///
        virtual void Next() = 0;

        /// \returns The weight of the current example
        ///
        virtual T Get() = 0;
    };

    template <typename T, typename IteratorType>
    class IteratorAdapter : public IIterator<T>
    {
    public:
        IteratorAdapter(IteratorType begin, IteratorType end) : _current(begin), _end(end)
        {
        }

        virtual bool IsValid() const override { return _current != _end; }
        virtual void Next() override { if (IsValid()) _current++; }
        virtual T Get() override { return *_current; }

    private:
        IteratorType _current;
        IteratorType _end;
    };

    template <typename IteratorType>
    auto MakeIterator(IteratorType begin, IteratorType end) -> IteratorAdapter<decltype(*begin), IteratorType>
    {
        return IteratorAdapter<decltype(*begin), IteratorType>(begin, end);
    }

}
