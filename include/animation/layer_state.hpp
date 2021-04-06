#ifndef _RIVE_LAYER_STATE_HPP_
#define _RIVE_LAYER_STATE_HPP_
#include "generated/animation/layer_state_base.hpp"
#include <stdio.h>
#include <vector>

namespace rive
{
	class StateTransition;
	class LayerStateImporter;
	class StateMachineLayerImporter;

	class LayerState : public LayerStateBase
	{
		friend class LayerStateImporter;
		friend class StateMachineLayerImporter;

	private:
		std::vector<StateTransition*> m_Transitions;
		void addTransition(StateTransition* transition);

	public:
		StatusCode onAddedDirty(CoreContext* context) override;
		StatusCode onAddedClean(CoreContext* context) override;

		StatusCode import(ImportStack& importStack) override;

#ifdef TESTING
		size_t transitionCount() const { return m_Transitions.size(); }
		StateTransition* transition(size_t index) const
		{
			if (index < m_Transitions.size())
			{
				return m_Transitions[index];
			}
			return nullptr;
		}
#endif
	};
} // namespace rive

#endif