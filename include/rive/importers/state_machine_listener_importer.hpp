#ifndef _RIVE_STATE_MACHINE_LISTENER_IMPORTER_HPP_
#define _RIVE_STATE_MACHINE_LISTENER_IMPORTER_HPP_

#include "rive/importers/import_stack.hpp"

namespace rive {
    class StateMachineListener;
    class StateMachine;
    class ListenerInputChange;
    class StateMachineListenerImporter : public ImportStackObject {
    private:
        StateMachineListener* m_StateMachineListener;

    public:
        StateMachineListenerImporter(StateMachineListener* listener);
        const StateMachineListener* stateMachineListener() const { return m_StateMachineListener; }
        void addInputChange(ListenerInputChange* change);
        StatusCode resolve() override;
    };
} // namespace rive
#endif