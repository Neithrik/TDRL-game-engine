#pragma once

#include <Python.h>

namespace tdrl {

	class Agent
	{
	public:
		Agent(int n_states, int n_actions);

		void Init();

		int GetAction(int state[], double epsilon);

		void Train(int state[], int action, int reward,
			int next_state, bool is_done);

	private:
		int n_states_;
		int n_actions_;
		PyObject* agent_;
	};

} // namespace TDRL