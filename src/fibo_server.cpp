#include "ros/ros.h"
#include "ros_fibonacci/fibo_service.h"
#include <iostream>
#include <sstream>
#include "std_msgs/Int32MultiArray.h"
#include "std_msgs/Int32.h"
#include <vector>
using namespace std;

bool service_callback
(ros_fibonacci::fibo_service::Request &req, ros_fibonacci::fibo_service::Response &res) {
 
 std::vector<int> f_serie={0,1};
 int ind=req.index;
 int leng=req.length;
 
  f_serie.resize(ind+leng);
  for (int j=2; j<=ind+leng; j++)
   { f_serie[j]=f_serie[j-1]+f_serie[j-2]; }
 
  res.out.resize(ind+leng-1);
  res.out=f_serie;
  
 ROS_INFO("From Client: index is [%d], length of portion is [%d]", req.index ,req.length);

 ROS_INFO("Server says: the portion required is");
  
  for (int j=ind; j<ind+leng; j++) {
   std::cout<<" f["<<j<<"]="<< res.out[j]<<endl;
    }

 return true;
}

int main(int argc, char **argv){
 ros::init(argc, argv, "service_server");
 ros::NodeHandle n;
 ros::ServiceServer fibonacci = n.advertiseService("fibonacci", service_callback);
 ROS_INFO("Ready to receive from client.");
 ros::spin();
 return 0;
}
