import random
import sys
if not hasattr(sys, 'argv'):
	sys.argv  = ['']

import tensorflow.compat.v1 as tf
import keras
import keras.layers as L
import numpy as np

class Agent:

	def init(self, state_dim, n_actions):
		tf.disable_v2_behavior()
		tf.reset_default_graph()
		sess = tf.InteractiveSession()
		tf.compat.v1.keras.backend.set_session(sess)

		self.state_dim = state_dim
		self.n_actions = n_actions

		self.network = keras.models.Sequential()
		self.network.add(L.InputLayer(self.state_dim))
		self.network.add(L.Dense(200, activation="relu"))
		self.network.add(L.Dense(200, activation="relu"))
		self.network.add(L.Dense(self.n_actions))

		states_ph = keras.backend.placeholder(dtype='float32', shape=[None, self.state_dim])
		actions_ph = keras.backend.placeholder(dtype='int32', shape=[None])
		rewards_ph = keras.backend.placeholder(dtype='float32', shape=[None])
		next_states_ph = keras.backend.placeholder(dtype='float32', shape=[None, self.state_dim])
		is_done_ph = keras.backend.placeholder(dtype='bool', shape=[None])

		#get q-values for all actions in current states
		predicted_qvalues = self.network(states_ph)

		#select q-values for chosen actions
		predicted_qvalues_for_actions = tf.reduce_sum(predicted_qvalues * tf.one_hot(actions_ph, self.n_actions), axis=1)

		gamma = 0.99

		# compute q-values for all actions in next states
		predicted_next_qvalues = self.network(next_states_ph)

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

	def get_action(self, state, epsilon):
		q_values = self.network.predict(np.array([state]))[0]
    
		best_action = np.argmax(q_values)
		random_action = random.randint(0, self.n_actions - 1)    

		return random_action if random.random() < epsilon else best_action

agent = Agent();
agent.init(8, 3);
for i in range(10):
	print(agent.get_action([0, 0, 1, 1, 1, 0, 0, 0], 0.25))
