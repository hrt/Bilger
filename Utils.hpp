#ifndef UTILS_HPP
#define UTILS_HPP

#define swap(x, y) {\
                     x ^= y; \
                     y ^= x; \
                     x ^= y; \
                   }

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))

#endif
