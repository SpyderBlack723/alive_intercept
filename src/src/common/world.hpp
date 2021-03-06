#pragma once

#include "intercept.hpp"


namespace alive {
    namespace common {
        namespace world {

            int getRelDir(const intercept::types::vector3& pos1_, const intercept::types::vector3& pos2_);

            intercept::types::vector3 getRelPos(const intercept::types::vector3& pos_, const float dir_, const float _dist);

        }
    }
}