#pragma once

#include "intercept.hpp"
#include "sys_profile\include.hpp"

namespace alive {
    namespace sys_profile {
        namespace sqf_commands {
            namespace handles {
                extern intercept::types::registered_sqf_function _startProfileSystem;
                extern intercept::types::registered_sqf_function _enableProfileSystemDebug;

                extern intercept::types::registered_sqf_function _getProfiles;
                extern intercept::types::registered_sqf_function _getProfilesBySide;

                extern intercept::types::registered_sqf_function _createProfile;
                extern intercept::types::registered_sqf_function _getProfilePosition;
                extern intercept::types::registered_sqf_function _getProfileSpeed;
            }

            void registerScriptCommands();

            // Profile System

            game_value startProfileSystem(game_value rightArg_);
            game_value enableProfileSystemDebug(game_value rightArg_);

            // Profile Handler

            game_value getProfiles();
            game_value getProfilesBySide(game_value rightArg_);

            // Profiles

            game_value createProfile(game_value profileArgs_);
            game_value getProfilePosition(game_value profileID_);
            game_value getProfileSpeed(game_value profileID_);
        }
    }
}