#pragma once

#include <vector>
#include <Python.h>

namespace tdrl {

	class Agent
	{
	public:
		Agent(int n_states, int n_actions);

		void Init();

		int GetAction(std::vector<int> state, double epsilon);

		void Train(std::vector<int> state, int action, int reward,
				   std::vector<int> new_state, bool is_done);

	private:
		int n_states_;
		int n_actions_;
		PyObject* agent_;
	};

} // namespace TDRL