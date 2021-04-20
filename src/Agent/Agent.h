#pragma once

namespace tdrl {

	class Agent
	{
	public:
		Agent(int n_states, int n_actions);

		int GetAction(int state[]);

		void Train(int state[], int action, int reward,
			int next_state, bool is_done);
	};

} // namespace TDRL