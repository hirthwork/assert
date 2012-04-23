#ifndef __NOEXCEPT_HPP_2012_04_23__
#define __NOEXCEPT_HPP_2012_04_23__

#if __cplusplus >= 201103L
#define NOEXCEPT(expr) noexcept(noexcept(expr))
#define NOEXCEPT2(expr1, expr2) noexcept(noexcept(expr1) && noexcept(expr2))
#else
#define NOEXCEPT(expr)
#define NOEXCEPT2(expr1, expr2)
#endif

#endif

