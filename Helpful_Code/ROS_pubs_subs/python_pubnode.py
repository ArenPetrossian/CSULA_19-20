#!/usr/bin/env python			#Tells ros to prepare the python script environment
import rospy				#Imports commands for creating a ros node
from std_msgs.msg import String		#Let's us use Strings

def the_talker():			#The following defines what this function does when called

   rospy.init_node('the_publisher', anonymous=True)
                                        #Creates a ros node with a unique name with random numbers
                                        #after it so multiple of the same publisher can be opened

   the_pub = rospy.Publisher('chatter_topic', String, queue_size=10)
					#The node will publish a "std_msgs.msg.String" on the
					#chatter_topic with a queue size of 10

   the_rate = rospy.Rate(10)		#Works with "the_rate.sleep()" to cycle loop at 10Hz

   while not rospy.is_shutdown():	#While Ctrl-C hasn't been entered and the terminal hasn't
					#been closed, run this loop

     the_string = "yo dude %s" % rospy.get_time()
					#Makes a string containing "yo dude" followed by the node's
					#run time

     rospy.loginfo(the_string)		#Prints messages to the terminal and to ros for debugging

     the_pub.publish(the_string)	#Publishes the_string to chatter_topic

     the_rate.sleep()			#Works with "rospy.Rate()" to cycle loop at 10Hz

if __name__ == '__main__':		#If the node is run on the command line and wasn't imported

   try: 				#Do the following when the exception is not met

     the_talker()			#Run the the_talker() loop that was defined above

   except rospy.ROSInterruptException:	#Do the following when Ctrl-C is pressed or the window is
					#closed

     pass				#Don't do anything (null statement)
