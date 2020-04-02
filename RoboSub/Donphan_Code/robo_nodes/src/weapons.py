#! /usr/bin/env python
import rospy
from robo_nodes.msg import smach2weapons
from robo_nodes.msg import weapons2smach

def smach_2_weapons(weapons_data):
	print(weapons_data)

while True:
	rospy.init_node('WEAPONS')
	weapons_2_smach_pub = rospy.Publisher('weapons2smach', weapons2smach, queue_size=10)
	rospy.Subscriber('smach2weapons', smach2weapons, smach_2_weapons)
	rate = rospy.Rate(10)
	final_message = weapons2smach()
	while not rospy.is_shutdown():
		final_message.Torpedo_done = True
		weapons_2_smach_pub.publish(final_message)
		rate.sleep()

	else:
		exit()
