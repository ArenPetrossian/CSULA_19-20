#! /usr/bin/env python
import rospy
from robo_nodes.msg import nav2smach
from robo_nodes.msg import cv2smach
from robo_nodes.msg import controls2smach
from robo_nodes.msg import weapons2smach
from robo_nodes.msg import smach2weapons
from robo_nodes.msg import smach2framehull

def nav_2_smach(nav_data):
	print(nav_data)

def cv_2_smach(cv_data):
        print(cv_data)

def controls_2_smach(controls_feedback):
	print(controls_feedback)

def weapons_2_smach(weapons_feedback):
	print(weapons_feedback)

while True:
	rospy.init_node('SMACH')
	smach_2_weapons_pub = rospy.Publisher('smach2weapons', smach2weapons, queue_size=10)
        smach_2_framehull_pub = rospy.Publisher('smach2framehull', smach2framehull, queue_size=10)
	rospy.Subscriber('nav2smach', nav2smach, nav_2_smach)
	rospy.Subscriber('cv2smach', cv2smach, cv_2_smach)
	rospy.Subscriber('controls2smach', controls2smach, controls_2_smach)
        rospy.Subscriber('weapons2smach', weapons2smach, weapons_2_smach)
	rate = rospy.Rate(10)
	final_message = smach2weapons()
	final_message2 = smach2framehull()
	while not rospy.is_shutdown():
		final_message.Claw = True
		final_message2.depth_input = 5
		final_message2.depth_setpoint = 7

		smach_2_weapons_pub.publish(final_message)
                smach_2_framehull_pub.publish(final_message2)
		rate.sleep()

	else:
		exit()
