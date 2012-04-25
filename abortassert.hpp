#ifndef __ABORTASSERT_HPP_2012_04_23__
#define __ABORTASSERT_HPP_2012_04_23__

#include <cstdlib>

#include "noexcept.hpp"

namespace assert {
    struct abort_assert {
        template <class Pred, class Message>
        static void assert(Pred pred, Message) NOEXCEPT(pred()) {
            if (!pred()) {
                abort();
            }
        }

        template <class Pred, class Message>
        static void out_of_range_assert(Pred pred, Message message)
            NOEXCEPT(assert(pred, message))
        {
            assert(pred, message);
        }
    };
}

#endif

