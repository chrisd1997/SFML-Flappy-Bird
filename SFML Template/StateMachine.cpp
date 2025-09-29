#include "StateMachine.hpp"

namespace PixelPanic
{
	void StateMachine::AddState(StateRef newState, bool isReplacing)
	{
		this->_isAdding = true;
		this->_isReplacing = isReplacing;

		this->_newState = std::move(newState);
	}

	void StateMachine::RemoveState()
	{
		this->_isRemoving = true;
	}

	void StateMachine::ProcessStateChanges()
	{
		if (this->_isRemoving && !this->_states.empty())
		{
			// Remove the current state
			this->_states.pop();

			if (!this->_states.empty())
			{
				// Start the new first state
				this->_states.top()->Resume();
			}

			// Reset the _isRemoving variable
			this->_isRemoving = false;
		}

		if (this->_isAdding)
		{
			if (!this->_states.empty())
			{
				if (this->_isReplacing)
				{
					// Get rid of the current state
					this->_states.pop();
				}
				else
				{
					// Pause the current state
					this->_states.top()->Pause();
				}
			}

			// Add the new state to the stack
			this->_states.push(std::move(this->_newState));
			// Initialize the new state
			this->_states.top()->Init();
			// Reset the _isAdding variable
			this->_isAdding = false;
		}
	}

	StateRef& StateMachine::GetActiveState()
	{
		return this->_states.top();
	}
}