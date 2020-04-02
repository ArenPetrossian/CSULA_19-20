#! /usr/bin/env python
import rospy
from robo_nodes.msg import cv2smach

while True:
	rospy.init_node('CV')
	cv_2_smach_pub = rospy.Publisher('cv2smach', cv2smach, queue_size=10)
	rate = rospy.Rate(10)
	final_message = cv2smach()
	while not rospy.is_shutdown():
		final_message.Gate = True
		cv_2_smach_pub.publish(final_message)
		rate.sleep()

	else:
		exit()
