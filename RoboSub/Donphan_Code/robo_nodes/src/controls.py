#! /usr/bin/env python
import rospy
from robo_nodes.msg import framehull2controls
from robo_nodes.msg import controls2smach

def framehull_2_controls(inputs_setpoints):
	print(inputs_setpoints)

while True:
	rospy.init_node('CONTROLS')
	controls_2_smach_pub = rospy.Publisher('controls2smach', controls2smach, queue_size=10)
	rospy.Subscriber('framehull2controls', framehull2controls, framehull_2_controls)
	rate = rospy.Rate(10)
	final_message = controls2smach()
	while not rospy.is_shutdown():
		final_message.stabilized = True
		controls_2_smach_pub.publish(final_message)
		rate.sleep()

	else:
		exit()
