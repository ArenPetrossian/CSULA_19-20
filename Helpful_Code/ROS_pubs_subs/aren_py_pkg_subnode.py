#!/usr/bin/env python                   #Tells ros to prepare the python script environment
import rospy                            #Imports commands for creating a ros node
from std_msgs.msg import String         #Let's us use Strings

def the_logger(the_string):		#This function takes an input and places it into a variable
					#named "the_string" then it does the following

   rospy.loginfo(rospy.get_caller_id() + "I swear I just heard %s", the_string.data)
					#Makes a string containing the node's full name, the quoted
					#string, and the data inputed into the function

def the_listener():			#The following defines what this function does when called

   rospy.init_node('the_subscriber', anonymous=True)
                                        #Creates a ros node with a unique name with random numbers
                                        #after it so multiple of the same publisher can be opened

   rospy.Subscriber('chatter_topic', String, the_logger)
                                        #The node will subscribe to the topic which should have
					#String data, then run the_logger when a message is received

   rospy.spin()				#Loops the code so it doesn't shut down

if __name__ == '__main__':              #If the node is run on the command line and wasn't imported

   the_listener()                       #Run the the_listener() loop that was defined above


