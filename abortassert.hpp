#ifndef __ABORTASSERT_HPP_2012_04_23__
#define __ABORTASSERT_HPP_2012_04_23__

#include <cstdlib>

#include "baseassert.hpp"

namespace assert {
    struct abort_assert: base_assert<abort_assert> {
        template <class Pred, class Message>
        static void assert(Pred pred, Message) throw() {
            if (!pred()) {
                abort();
            }
        }
    };
}

#endif

