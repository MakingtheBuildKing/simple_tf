#include <iostream>
#include <thread>
#include <mutex>

#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

class TFMC{

    public:

    TFMC();
    ~TFMC();

    private:

    ros::NodeHandle nh;

    std::thread thread_turtle1, thread_turtle2;
    std::mutex mutex_tf_turtle1, mutex_tf_turtle2;
    tf::StampedTransform stf_turtle1, stf_turtle2;
        
    int turtle1Task();
    int turtle2Task();
    int tfListner(tf::StampedTransform &_tf, std::string turtle_name);
    int distanceTFs();    
};

TFMC::TFMC(){

    nh = ros::NodeHandle();
    thread_turtle1 = std::thread([&]() { turtle1Task(); });
    thread_turtle2 = std::thread([&]() { turtle2Task(); });
    distanceTFs();
}

TFMC::~TFMC(){}

int TFMC::tfListner(tf::StampedTransform &_tf, std::string turtle_name){

    tf::TransformListener _tfl;

    _tfl.waitForTransform("/world", turtle_name, ros::Time(0), ros::Duration(1));

    try{

        _tfl.lookupTransform("/world", turtle_name, ros::Time(0), _tf);
    }
    catch(tf::TransformException &ex){

        ROS_ERROR("Invalid Transform : %s", ex.what());
        return -1;
    }
    return 0;
}

int TFMC::distanceTFs(){
    
    ros::Rate spinRate(60);
    tf::TransformListener turtle1_tfl;

    while(ros::ok()){

        tf::StampedTransform st1, st2;

        mutex_tf_turtle1.try_lock();
        st1 = stf_turtle1;
        mutex_tf_turtle1.unlock();

        mutex_tf_turtle2.try_lock();
        st2 = stf_turtle2;
        mutex_tf_turtle2.unlock();

        tfScalar distEuc = tf::tfDistance2(st1.getOrigin(), st2.getOrigin());

        ROS_INFO("\n"
        "   turtle1 X turtle2\n"
        "   timestamp distance\n"
        "       %d.%d\n"
        "   euclidian distance\n"
        "       %lf\n"
        "   is Captured? : %s\n",
        st1.stamp_.sec - st2.stamp_.sec, st1.stamp_.nsec - st2.stamp_.nsec,
        distEuc,
        distEuc < 1.0 ? "Yes!" : "Nope");

        ros::spinOnce();
        spinRate.sleep();
    }
    return 0;
    
}

int TFMC::turtle1Task(){

    ros::Rate spinRate(60);
    tf::TransformListener turtle1_tfl;

    while(ros::ok()){

        tfListner(stf_turtle1, "turtle1");

        ros::spinOnce();
        spinRate.sleep();
    }
    return 0;
}

int TFMC::turtle2Task(){

    ros::Rate spinRate(60);
    tf::TransformListener turtle2_tfl;

    while(ros::ok()){
        tfListner(stf_turtle2, "turtle2");

        ros::spinOnce();
        spinRate.sleep();
    }
    return 0;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "i_cant_believe_my_turtle_is_captured");

    TFMC simtf;

    ros::Rate spinRate(60);

    while(ros::ok()){

        spinRate.sleep();
        ros::spinOnce();
    }
    
    return 0;
}
    