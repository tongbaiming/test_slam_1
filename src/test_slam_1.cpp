/*
 * test_slam_1.cpp
 *
 *  Created on: 2017年6月2日
 *      Author: tbm
 */

#include "../include/test_slam_1/test_slam_1.h"
#include <iostream>
#include <memory>
#include <functional>

using namespace std;
//using namespace laser_slam_ros;

int main(int argc, char** argv ){
	cout << "hello world !!!!!!!!!!!!!!!!!!!!!!" << endl;
	using namespace std::placeholders;
	ros::init(argc, argv, "LaserSlamWorker");
	//tbm:如果这个ros节点放在roslaunch文件中的嵌套的group标签之内，
	//那么这个nh本身自带了嵌套的namespace，下面的prefix就要设置为空字符串
	ros::NodeHandle nh;
	cout << "nh.namespace: "<< nh.getNamespace() << endl;
	laser_slam_ros::LaserSlamWorker worker1;
	laser_slam::LaserTrackParams laser_track_params;
	laser_slam::EstimatorParams estimator_params;
	laser_slam_ros::LaserSlamWorkerParams worker_params;
	//string prefix = "party_1/instance_1/erlecopter_2";
	string prefix = "";
	estimator_params = laser_slam_ros::getOnlineEstimatorParams(nh, prefix);
	worker_params = laser_slam_ros::getLaserSlamWorkerParams(nh, prefix);
	/*
	laser_track_params.use_odom_factors = true;
	laser_track_params.use_icp_factors = true;
	laser_track_params.force_priors = true;
	laser_track_params.save_icp_results = true;
	laser_track_params.nscan_in_sub_map = 10;
	*/
	/*
		worker_params.assembled_cloud_sub_topic = "";
		worker_params.publish_local_map = true ;
		worker_params.local_map_pub_topic = "";
		worker_params.trajectory_pub_topic = "";
		worker_params.get_laser_track_srv_topic = "";
		worker_params.voxel_size_m = 0.01;
		worker_params.world_frame = "";
		worker_params.odom_frame = "party_1/instance_1/erlecopter_2/odom_frame";
		worker_params.sensor_frame = "";
		worker_params.minimum_distance_to_add_pose = 0.01;
		worker_params.use_odometry_information = true;
		worker_params.remove_ground_from_local_map = true;
		worker_params.ground_distance_to_robot_center_m = 0.1;
		worker_params.create_filtered_map = true;
		worker_params.distance_to_consider_fixed = 30;
		*/
	cout << "I am in test_slam_1, before make estimator" << endl;
	shared_ptr<laser_slam::IncrementalEstimator> estimator = make_shared<laser_slam::IncrementalEstimator>(estimator_params, 1u);
	unsigned int worker_id = 0;
	cout << "I am in test_slam_1, before worker1.init()" << endl;
	worker1.init(nh, worker_params, estimator, worker_id);
	cout << "I am in test_slam_1, after  worker1.init()" << endl;
	ros::spin();
	return 0;
}



