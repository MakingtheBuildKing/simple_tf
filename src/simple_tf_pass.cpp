#include <iostream>
#include <thread>

#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

class TFM{

    public:

    TFM();
    ~TFM();

    private:

    ros::NodeHandle nh;    
    int task();
};

TFM::TFM(){

    nh = ros::NodeHandle();
    task();
}

TFM::~TFM(){}

int TFM::task(){

    ros::Rate spinRate(60);
    tf::TransformListener tfl_turtle;
    tf::TransformBroadcaster tf_bcast;

    while(ros::ok()){

        tfl_turtle.waitForTransform("/world", "/turtle1", ros::Time(0), ros::Duration(1));
        tf::StampedTransform stf_turtle;

        try{

            tfl_turtle.lookupTransform("/world", "/turtle1", ros::Time(0), stf_turtle);
            tf_bcast.sendTransform(tf::StampedTransform(stf_turtle, ros::Time::now(), "base", "turtle1"));
        }
        catch(tf::TransformException &ex){
            ROS_ERROR("Invalid Transform : %s", ex.what());
        }

        ros::spinOnce();
        spinRate.sleep();
    }
    return 0;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "tf_pass");

    TFM simtf;

    ros::Rate spinRate(60);

    while(ros::ok()){

        spinRate.sleep();
        ros::spinOnce();
    }
}
    