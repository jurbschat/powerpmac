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

#include "scope_exit.h"
#include "detail/wrapper.h"
#include <utility>
#include <type_traits>

namespace sr
{
    namespace detail
    {
        template<class T, class U,
                    class R = std::conditional_t<std::is_nothrow_constructible<T, U>::value, U&&, U>
                >
        constexpr R forward_if_nothrow_constructible(U&& arg)
        {
            return std::forward<U>(arg);
        }
    }


    template<class R, class D>
    class unique_resource
    {
    public:

        template<class RR, class DD,
                std::enable_if_t<(std::is_constructible<R ,RR>::value && std::is_constructible<D, DD>::value
                                && (std::is_nothrow_constructible<R, RR>::value || std::is_constructible<R, RR&>::value)
                                && (std::is_nothrow_constructible<D, DD>::value || std::is_constructible<D, DD&>::value)), int> = 0
                >
        unique_resource(RR&& r, DD&& d) noexcept((std::is_nothrow_constructible<R, RR>::value || std::is_nothrow_constructible<R, RR&>::value)
                                                    && (std::is_nothrow_constructible<D, DD> ::value|| std::is_nothrow_constructible<D, DD&>::value))
                                        : resource(detail::forward_if_nothrow_constructible<R, RR>(std::forward<RR>(r)), scope_exit{[&r, &d] { d(r); }}),
                                        deleter(detail::forward_if_nothrow_constructible<D, DD>(std::forward<DD>(d)), scope_exit{[this, &d] { d(get()); }}),
                                        execute_on_reset(true)
        {
        }

        unique_resource(unique_resource&& other) noexcept(std::is_nothrow_move_constructible<R>::value
                                                            && std::is_nothrow_move_constructible<D>::value)
                                                : resource(std::move_if_noexcept(other.resource.get()), scope_exit{[] { }}),
                                                deleter(std::move_if_noexcept(other.deleter.get()), scope_exit{[&other] {
                                                                                                            if( other.execute_on_reset == true )
                                                                                                            {
                                                                                                                other.get_deleter()(other.resource.get());
                                                                                                            }
                                                                                                            other.release(); }}),
                                                execute_on_reset(std::exchange(other.execute_on_reset, false))
        {
        }

	    unique_resource() noexcept
	        : resource(R{}, scope_exit([]{})),
	        deleter(D{}, scope_exit([]{})),
	        execute_on_reset(false)
	    {}

	    template<class DD,
			    std::enable_if_t<(std::is_constructible<D, DD>::value
			                      && (std::is_nothrow_constructible<D, DD>::value || std::is_constructible<D, DD&>::value)), int> = 0
	    >
	    unique_resource(DD&& d) noexcept(std::is_nothrow_constructible<D, DD> ::value || std::is_nothrow_constructible<D, DD&>::value)
			    : resource(R{}, scope_exit([]{})),
			      deleter(detail::forward_if_nothrow_constructible<D, DD>(std::forward<DD>(d)), scope_exit{[this, &d] { d(get()); }}),
			      execute_on_reset(true)
	    {
	    }

        unique_resource(const unique_resource&) = delete;

        ~unique_resource()
        {
            reset();
        }


        void reset() noexcept
        {
            if( execute_on_reset == true )
            {
                execute_on_reset = false;
                get_deleter()(resource.get());
            }
        }

        template <class T>
        constexpr std::add_const_t<T>& as_const(T& t) noexcept
        {
            return t;
        }

        template<class RR>
        void reset(RR&& r)
        {
            reset();

            using R1 = typename detail::Wrapper<R>::type;
            auto se = scope_exit{[this, &r] { get_deleter()(r); }};

            if constexpr( std::is_nothrow_assignable<R1&, RR>::value == true )
            {
                resource.reset(std::forward<RR>(r));
            }
            else
            {
                resource.reset(as_const(r));
            }

            execute_on_reset = true;
            se.release();
        }

        void release() noexcept
        {
            execute_on_reset = false;
        }

        const R& get() const noexcept
        {
            return resource.get();
        }

        template<class RR = R, std::enable_if_t<std::is_pointer<RR>::value, int> = 0>
        RR operator->() const noexcept
        {
            return resource.get();
        }

        template<class RR = R,
            std::enable_if_t<( std::is_pointer<RR>::value
                            && !std::is_void<std::remove_pointer_t<RR>>::value), int> = 0>
        std::add_lvalue_reference_t<std::remove_pointer_t<RR>> operator*() const noexcept
        {
            return *get();
        }

        const D& get_deleter() const noexcept
        {
            return deleter.get();
        }


        template<class RR = R, class DD = D,
            std::enable_if_t<(std::is_nothrow_move_assignable<RR>::value
                                || std::is_nothrow_copy_assignable<RR>::value)
                            && (std::is_nothrow_move_assignable<DD>::value
                                || std::is_nothrow_copy_assignable<DD>::value), int> = 0
            >
        unique_resource& operator=(unique_resource&& other) noexcept(std::is_nothrow_assignable<R&, R>::value
                                                                    && std::is_nothrow_assignable<D&, D>::value)
        {
            if( this != &other )
            {
                reset();

                if constexpr( std::is_nothrow_move_assignable<RR>::value == true )
                {
                    if constexpr( std::is_nothrow_move_assignable<DD>::value == true )
                    {
                        resource.reset(std::move(other.resource));
                        deleter.reset(std::move(other.deleter));
                    }
                    else
                    {
                        deleter.reset(other.deleter);
                        resource.reset(std::move(other.resource));
                    }
                }
                else
                {
                    if constexpr( std::is_nothrow_move_assignable<DD>::value == true )
                    {
                        resource.reset(other.resource);
                        deleter.reset(std::move(other.deleter));
                    }
                    else
                    {
                        resource.reset(other.resource);
                        deleter.reset(other.deleter);
                    }
                }

                execute_on_reset = std::exchange(other.execute_on_reset, false);
            }
            return *this;
        }

        unique_resource& operator=(const unique_resource&) = delete;


    private:

        detail::Wrapper<R> resource;
        detail::Wrapper<D> deleter;
        bool execute_on_reset;
    };


    template<class R, class D>
    unique_resource(R, D) -> unique_resource<R, D>;


    template<class R, class D, class S = std::decay_t<R>>
    unique_resource<std::decay_t<R>, std::decay_t<D>> make_unique_resource_checked(R&& r, const S& invalid, D&& d)
                                                            noexcept(std::is_nothrow_constructible<std::decay_t<R>, R>::value
                                                                    && std::is_nothrow_constructible<std::decay_t<D>, D>::value)
    {
        const bool must_release{r == invalid};
        unique_resource<std::decay_t<R>, std::decay_t<D>> ur{std::forward<R>(r), std::forward<D>(d)};

        if( must_release == true )
        {
            ur.release();
        }

        return ur;
    }

}


