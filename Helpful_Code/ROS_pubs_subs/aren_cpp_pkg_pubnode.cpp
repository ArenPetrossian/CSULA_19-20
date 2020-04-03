#include "ros/ros.h"				//Let's us connect to the ros system
#include "std_msgs/String.h"			//Let's us use the std_msgs::String
#include <sstream>				//Let's us use the stringstream

int main(int argc, char **argv) {		//Start of all cpp node files

   ros::init(argc, argv, "talking_node");	//Contacts ros and registers node, takes args from command line

   ros::NodeHandle n;				//Used to communicate with system

   ros::Publisher cellphone = n.advertise<std_msgs::String>("chatter_topic", 1000);
						//Tell ros you are going to publish to the topic name chatter_topic, 
						//the message type is std_msgs.String, and the queue size is 1000

   ros::Rate loop_rate(10);			//Works with loop_rate.sleep to loop at specifized Hertz

   int count = 0;				//Used to create a unique string each loop

   while (ros::ok()) {				//While Ctrl-C hasn't been entered, another node with the same name hasn't stopped
						//this one, terminal hasn't been closed, and ros.shutdown() isn't called later in code

     std_msgs::String the_message;		//Define "the_message" as an empty std_msgs.String

     std::stringstream cpp_serial;		//Start an empty stream named cpp_serial

     cpp_serial << "hello world" << count;	//Fill the empty stream "cpp_serial" with "hello world" followed by the count number

     the_message.data = cpp_serial.str();	//Fill the data in the empty storage of "the_message" with "cpp_serial"'s data

     ROS_INFO("%s", the_message.data.c_str());	//Prints "the_message" for debugging with ros, publishes to terminal screen by default

     cellphone.publish(the_message);		//Prints "the_message" from the publisher "cellphone" on the topic "chatter_topic"

     ros::spinOnce();				//Good practice to include this, used to process all incoming messages for the node

     loop_rate.sleep();				//Works with ros::Rate loop_rate(10) to loop this code at 10Hz

     ++count;					//Adds one to "count" to create unique message each loop

   }
   return 0;
}
