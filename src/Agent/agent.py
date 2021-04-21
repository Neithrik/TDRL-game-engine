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
		self.sess = tf.InteractiveSession()
		tf.compat.v1.keras.backend.set_session(self.sess)

		self.state_dim = state_dim
		self.n_actions = n_actions

		self.network = keras.models.Sequential()
		self.network.add(L.InputLayer(self.state_dim))
		self.network.add(L.Dense(200, activation="relu"))
		self.network.add(L.Dense(200, activation="relu"))
		self.network.add(L.Dense(self.n_actions))

		self.state_ph = keras.backend.placeholder(dtype='float32', shape=[None, self.state_dim])
		self.actions_ph = keras.backend.placeholder(dtype='int32', shape=[None])
		self.rewards_ph = keras.backend.placeholder(dtype='float32', shape=[None])
		self.next_state_ph = keras.backend.placeholder(dtype='float32', shape=[None, self.state_dim])
		self.is_done_ph = keras.backend.placeholder(dtype='bool', shape=[None])

		#get q-values for all actions in current states
		predicted_qvalues = self.network(self.state_ph)

		#select q-values for chosen actions
		predicted_qvalues_for_actions = tf.reduce_sum(predicted_qvalues * tf.one_hot(self.actions_ph, self.n_actions), axis=1)

		gamma = 0.99

		# compute q-values for all actions in next states
		predicted_next_qvalues = self.network(self.next_state_ph)

		# compute V*(next_states) using predicted next q-values
		next_state_values = tf.math.reduce_max(predicted_next_qvalues, axis = 1)

		# compute "target q-values" for loss - it's what's inside square parentheses in the above formula.
		target_qvalues_for_actions = self.rewards_ph + gamma * next_state_values

		# at the last state we shall use simplified formula: Q(s,a) = r(s,a) since s' doesn't exist
		target_qvalues_for_actions = tf.where(self.is_done_ph, self.rewards_ph, target_qvalues_for_actions)

		#mean squared error loss to minimize
		loss = (predicted_qvalues_for_actions - tf.stop_gradient(target_qvalues_for_actions)) ** 2
		loss = tf.reduce_mean(loss)

		# training function that resembles agent.update(state, action, reward, next_state) from tabular agent
		self.train_step = tf.train.AdamOptimizer(1e-4).minimize(loss)

		init = tf.global_variables_initializer()

		# tf.train.Saver.__init__ adds operations to the graph to save
		# and restore variables.
		saver_def = tf.train.Saver().as_saver_def()

		print('Agent is initialized')

		self.sess.run(tf.global_variables_initializer())

	def get_action(self, state, epsilon):
		q_values = self.network.predict(np.array([state]))[0]
    
		best_action = np.argmax(q_values)
		random_action = random.randint(0, self.n_actions - 1)    

		return random_action if random.random() < epsilon else best_action

	def train(self, state, action, reward, next_state, done):
		self.sess.run(self.train_step, {
					self.state_ph: [state], self.actions_ph: [action], self.rewards_ph: [reward], 
					self.next_state_ph: [next_state], self.is_done_ph: [done]
				})

agent = Agent();
agent.init(8, 3);
for i in range(10):
	action = agent.get_action([0, 0, 1, 1, 1, 0, 0, 0], 0.25)
	print(action)
	agent.train([0, 0, 1, 1, 1, 0, 0, 0], action, 0, [0, 0, 1, 1, 1, 0, 0, 0], False)
