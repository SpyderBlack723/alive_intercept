#pragma once

#include "intercept.hpp"
#include "helpers.hpp"

#include <string>


namespace alive {
    namespace sys_profile {


        class Profile {

            friend class ProfileHandler;

            public:


                Profile();
                Profile(const intercept::types::side& side_, const std::string& faction_, const intercept::types::vector3& pos_);
                virtual ~Profile();

                // getters
            
                const std::string& getID() const                { return _id; }
                const std::string& getFaction() const           { return _faction; }
                bool debugEnabled() const                       { return _debugEnabled; }
                bool isActive() const                           { return _active; }
                int getSpeed() const                            { return _speed; }
                const intercept::types::side& getSide()         { return _side; }
                const intercept::types::vector3& getPosition()  { return _pos; }

                // setters

                void enableDebug(bool enabled_);
                virtual void setPosition(const intercept::types::vector3& newPos_) { _pos = newPos_; }

                // functional

                virtual void spawn() = 0;
                virtual void despawn() = 0;
                virtual void update(const float dt_) = 0;


            protected:


                std::string _id;
                std::string _faction;

                bool _debugEnabled;
                bool _active;

                int _speed;

                intercept::types::side      _side;
                intercept::types::vector3   _pos;
                intercept::types::marker    _debugMarker;

                // functions

                virtual void _calculateSpeed() = 0;
                virtual void _createDebugMarker() = 0;

        };


    }
}