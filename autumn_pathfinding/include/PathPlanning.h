#ifndef PathPlaning_H
#define PathPlaning_H

#include "Point3D.h"

class PathPlaning
{
public:
  //Consturctor
  PathPlaning(ros::NodeHandle n, int rMin, int rMax);

  //Helper Methodes
  bool isInitialized();

  //PathPlaning Methods
  void getPath(nav_msgs::OccupancyGrid g, geometry_msgs::Pose p, geometry_msgs::Point goal, pcl::PointCloud<pcl::PointXYZ> c, int nodeSpacing, int iteratons);

private:
  nav_msgs::OccupancyGrid Grid;
  geometry_msgs::Pose Pose;
  Point3D goal;
  pcl::PointCloud<pcl::PointXYZ> cloud;
  std::map<long, long> Tree;
  std::pair<int, int> centerDelta;
  int radiusCollisionMin;
  int radiusCollisionMax;
  const int pairingAdditiv = 10000;
  //ROS Publisher
  ros::Publisher pubNewNode;
  ros::Publisher pubRandNode;
  ros::Publisher pubPath;
  Point3D generateXrand(double goalDistance);
  bool cellIsFree(int x, int y);
  bool pathIsFree(Point3D node1, Point3D node2, int radius);
  Point3D getNearestNode(Point3D startNode, Point3D goalNode);
  Point3D generateNewNode(Point3D nearest, Point3D random, int d);
  double getPathLength(Point3D node);
  std::vector<Point3D> getNearestNeighbors(Point3D node, Point3D goalNode, double range);
  bool prevPathValid(Point3D newPosNode, Point3D goalNode, int nodeSpacing);

  //Helper Methodes
  geometry_msgs::PointStamped generatePoint(Point3D node);
  geometry_msgs::PoseStamped generatePose(Point3D node);
  nav_msgs::Path generatePath(Point3D goalNode);
  int gridIndex(int x, int y);
  void setCenterDelta();
  long pairing(int x, int y);
  double nodeDistance(Point3D node1, Point3D node2);
  std::pair<int, int> depairing(long z);
  //Mathemetical
  int gschSum(int w);
  int triangularRoot(int z);
};

#endif
