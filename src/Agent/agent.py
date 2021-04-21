
class Agent:
	def init(self):
		import sys
		if not hasattr(sys, 'argv'):
			sys.argv  = ['']

		import tensorflow.compat.v1 as tf
		import keras
		import keras.layers as L

		tf.disable_v2_behavior()
		tf.reset_default_graph()
		sess = tf.InteractiveSession()
		tf.compat.v1.keras.backend.set_session(sess)

		state_dim = 8
		n_actions = 3

		network = keras.models.Sequential()
		network.add(L.InputLayer(state_dim))
		network.add(L.Dense(200, activation="relu"))
		network.add(L.Dense(200, activation="relu"))
		network.add(L.Dense(n_actions))

		states_ph = keras.backend.placeholder(dtype='float32', shape=[None, state_dim])
		actions_ph = keras.backend.placeholder(dtype='int32', shape=[None])
		rewards_ph = keras.backend.placeholder(dtype='float32', shape=[None])
		next_states_ph = keras.backend.placeholder(dtype='float32', shape=[None, state_dim])
		is_done_ph = keras.backend.placeholder(dtype='bool', shape=[None])

		#get q-values for all actions in current states
		predicted_qvalues = network(states_ph)

		#select q-values for chosen actions
		predicted_qvalues_for_actions = tf.reduce_sum(predicted_qvalues * tf.one_hot(actions_ph, n_actions), axis=1)

		gamma = 0.99

		# compute q-values for all actions in next states
		predicted_next_qvalues = network(next_states_ph)

		# compute V*(next_states) using predicted next q-values
		next_state_values = tf.math.reduce_max(predicted_next_qvalues, axis = 1)

		# compute "target q-values" for loss - it's what's inside square parentheses in the above formula.
		target_qvalues_for_actions = rewards_ph + gamma * next_state_values

		# at the last state we shall use simplified formula: Q(s,a) = r(s,a) since s' doesn't exist
		target_qvalues_for_actions = tf.where(is_done_ph, rewards_ph, target_qvalues_for_actions)

		#mean squared error loss to minimize
		loss = (predicted_qvalues_for_actions - tf.stop_gradient(target_qvalues_for_actions)) ** 2
		loss = tf.reduce_mean(loss)

		# training function that resembles agent.update(state, action, reward, next_state) from tabular agent
		train_step = tf.train.AdamOptimizer(1e-4).minimize(loss)

		init = tf.global_variables_initializer()

		# tf.train.Saver.__init__ adds operations to the graph to save
		# and restore variables.
		saver_def = tf.train.Saver().as_saver_def()

		print('Agent is initialized')

		sess.run(tf.global_variables_initializer())

agent = Agent();
agent.init();