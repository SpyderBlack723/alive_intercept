#include "core.hpp"
#include "intercept.hpp"

#include "sys_profile\sqf_commands.hpp"

#include "sys_profile\profile_system.hpp"
#include "common\include.hpp"

#include <chrono>


namespace alive {

    namespace sqf_commands {
        namespace handles {
            intercept::types::registered_sqf_function _initALiVE;
        }

        game_value initALiVE() {
            // cache SQF values
            // initialize ALiVE functions

            Core::get().initializeALiVE();

            return game_value();
        }
    }

    Core::Core() {

    }

    Core::~Core() {

    }

    void Core::registerScriptCommands() {
        sqf_commands::handles::_initALiVE = intercept::client::host::registerFunction(
            "initALiVE",
            "Initializes ALiVE base systems.",
            userFunctionWrapper<sqf_commands::initALiVE>,
            intercept::types::GameDataType::NOTHING
        );
    }

    void Core::initializeALiVE() {
        common::RV::get().initialize();
    }

    std::vector< std::shared_ptr<alive::common::Module> >& Core::getModules() {
        return _modules;
    }

    void Core::registerModule(alive::common::Module* module_) {
        _modules.push_back(std::shared_ptr<alive::common::Module>(module_));
    }

    void Core::onPreStart() {
        // register script commands
        // must be done on pre start

        Core::registerScriptCommands();
        sys_profile::sqf_commands::registerScriptCommands();

        for (auto& module : _modules)
            module->onPreStart();

        // reset frame time
        // to avoid large initial
        // simulation jumps

        _lastFrameTime = std::chrono::system_clock::now();
    }

    void Core::onPreInit() {
        for (auto& module : _modules)
            module->onPreInit();

        _missionRunning = true;
    }

    void Core::onPostInit() {
        for (auto& module : _modules)
            module->onPostInit();
    }

    void Core::onMissionStopped() {
        for (auto& module : _modules)
            module->onMissionStopped();

        _missionRunning = false;
    }

    void Core::onUnitKilled(intercept::types::object& killed_, intercept::types::object& killer_) {
        for (auto& module : _modules)
            module->onUnitKilled(killed_, killer_);
    }

    void Core::onSimulationStep() {
        // calculate elapsed time since last simulation step

        std::chrono::duration<float> diff = (std::chrono::system_clock::now()) - _lastFrameTime;

        _lastFrameTime = std::chrono::system_clock::now();

        float dt = diff.count() * intercept::sqf::acc_time();

        for (auto& module : _modules)
            module->onSimulationStep(dt);
    }

}