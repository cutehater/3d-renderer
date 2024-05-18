#include "except.h"

#include <iostream>
#include <stdexcept>

namespace Except {
void react() {
    {
        try {
            throw;
        } catch (std::exception &e) {
            std::cerr << "uncaught exception: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "uncaught unknown exception" << std::endl;
        }
    }
}
} // namespace Except
