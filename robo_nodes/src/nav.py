#! /usr/bin/env python
import rospy
from robo_nodes.msg import nav2smach

while True:
	rospy.init_node('NAV')
	nav_2_smach_pub = rospy.Publisher('nav2smach', nav2smach, queue_size=10)
	rate = rospy.Rate(10)
	final_message = nav2smach()
	while not rospy.is_shutdown():
		final_message.current_yaw = 5
		final_message.current_pitch = 1.6
		final_message.current_roll = 141
		final_message.current_depth = 6162

		nav_2_smach_pub.publish(final_message)
		rate.sleep()
	else:
		exit()
