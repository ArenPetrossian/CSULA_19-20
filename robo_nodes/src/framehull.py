#! /usr/bin/env python
import rospy
from robo_nodes.msg import smach2framehull
from robo_nodes.msg import framehull2controls

def smach_2_framehull(maneuver_data):
	print(maneuver_data)

while True:
	rospy.init_node('FRAMEHULL')
	framehull_2_controls_pub = rospy.Publisher('framehull2controls', framehull2controls, queue_size=10)
	rospy.Subscriber('smach2framehull', smach2framehull, smach_2_framehull)
	rate = rospy.Rate(10)
	final_message = framehull2controls()
	while not rospy.is_shutdown():
		final_message.distance_setpoint = 7
		framehull_2_controls_pub.publish(final_message)
		rate.sleep()

	else:
		exit()
