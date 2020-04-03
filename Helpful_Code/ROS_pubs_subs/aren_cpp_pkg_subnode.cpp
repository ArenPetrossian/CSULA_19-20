#include "ros/ros.h"				//Let's us connect to the ros system
#include "std_msgs/String.h"			//Let's us use the std_msgs::String

void chatter_topic_Callback(const std_msgs::String::ConstPtr& the_message) {
						//Function defined below, called when a new message is heard by the node

   ROS_INFO("I heard: [%s]", the_message->data.c_str());
						//Prints "the_message" for debugging with ros, publishes to terminal screen by default
}

int main(int argc, char **argv) {		//Start of all cpp node files

   ros::init(argc, argv, "listening_node");	//Contacts ros and registers node, takes args from command line

   ros::NodeHandle n;				//Used to communcicate with system

   ros::Subscriber other_cellphone = n.subscribe("chatter_topic", 1000, chatter_topic_Callback);
						//Tell ros you are going to subscribe to the topic name chatter_topic,
						//the queue size is 1000, and what to do with the message 

   ros::spin();					//This loop will continuously spin until Ctrl-C is entered or the node is shutdown

   return 0;
}
