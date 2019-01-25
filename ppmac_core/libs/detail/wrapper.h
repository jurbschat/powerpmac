// MIT License
//
// Copyright (c) 2017-2019 offa
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <functional>
#include <type_traits>

namespace sr::detail
{

   template<class T>
   class Wrapper
   {
   public:

        template<class TT, class G, std::enable_if_t<std::is_constructible<T, TT>::value, int> = 0>
        Wrapper(TT&& v, G&& g) noexcept(std::is_nothrow_constructible<T, TT>::value) : value(std::forward<TT>(v))
        {
            g.release();
        }


        T& get() noexcept
        {
            return value;
        }

        const T& get() const noexcept
        {
            return value;
        }

        void reset(Wrapper<T>&& other) noexcept
        {
            value = std::move(other.value);
        }

        void reset(T&& newValue) noexcept(std::is_nothrow_assignable<T, decltype(std::move_if_noexcept(newValue))>::value)
        {
            value = std::forward<T>(newValue);
        }

        void reset(const T& newValue) noexcept(std::is_nothrow_assignable<T, const T&>::value)
        {
            value = newValue;
        }


        using type = T;


    private:

        T value;
    };


   template<class T>
   class Wrapper<T&>
   {
   public:

        template<class TT, class G, std::enable_if_t<std::is_convertible<TT, T&>::value, int> = 0>
        Wrapper(TT&& v, G&& g) noexcept(std::is_nothrow_constructible<TT, T&>::value) : value(static_cast<T&>(v))
        {
            g.release();
        }


        T& get() noexcept
        {
            return value.get();
        }

        const T& get() const noexcept
        {
            return value.get();
        }

        void reset(Wrapper<T>&& other) noexcept
        {
            value = std::move(other.value);
        }

        void reset(T& newValue) noexcept
        {
            value = std::ref(newValue);
        }


        using type = std::reference_wrapper<std::remove_reference_t<T>>;


    private:

        type value;
   };

}
