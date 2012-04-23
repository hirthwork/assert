#ifndef __EMPTYASSERT_HPP_2012_04_23__
#define __EMPTYASSERT_HPP_2012_04_23__

#include "baseassert.hpp"

namespace assert {
    struct empty_assert: base_assert<empty_assert> {
        template <class Pred, class Message>
        static void assert(Pred, Message) throw() {
        }
    };
}

#endif

