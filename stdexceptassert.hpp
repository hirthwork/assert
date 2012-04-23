#ifndef __STDEXCEPTASSERT_HPP_2012_04_23__
#define __STDEXCEPTASSERT_HPP_2012_04_23__

#include <stdexcept>

#include "baseassert.hpp"

namespace assert {
    struct stdexcept_assert: base_assert<stdexcept_assert> {
        template <class Pred, class Message>
        static void out_of_range_assert(Pred pred, Message message) {
            if (!pred()) {
                throw std::out_of_range(message);
            }
        }

        template <class Pred, class Message>
        static void assert(Pred pred, Message message) {
            if (!pred()) {
                throw std::logic_error(message);
            }
        }
    };
}

#endif

