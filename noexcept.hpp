#ifndef __NOEXCEPT_HPP_2012_04_23__
#define __NOEXCEPT_HPP_2012_04_23__

#if __cplusplus >= 201103L
#define NOEXCEPT(expr) noexcept(noexcept(expr))
#else
#define NOEXCEPT(expr)
#endif

#endif

