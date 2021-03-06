#pragma once

#include <Kin/kin.h>
#include <Gui/opengl.h>

namespace rai {

struct CameraView : GLDrawer {

  /*! describes a sensor from which we can take 'images' within the simulation (e.g.: kinect, suctionRingView, etc) */
  struct Sensor {
    rai::String name;
    rai::Camera cam;     ///< this includes the transformation X
    uint width=640, height=480;
    byteA backgroundImage;
    rai::Frame *frame=0;
    Sensor(){}
    rai::Transformation& pose(){ return cam.X; }
  };

  //-- description of world configuration
  rai::KinematicWorld K;       //the configuration
  rai::Array<Sensor> sensors;  //the list of sensors

  enum RenderMode{ all, seg };
  OpenGL gl;

  //-- run parameter
  Sensor *currentSensor=0;
  bool background=true;
  int watchComputations=0;
  RenderMode renderMode=all;

  //-- evaluation outputs
  CameraView(const rai::KinematicWorld& _K, bool _background=true, int _watchComputations=0);
  ~CameraView(){}

  //-- loading the configuration: the meshes, the robot model, the tote, the sensors; all ends up in K
  Sensor& addSensor(const char* name, const char* frameAttached, uint width, uint height, double focalLength=-1., double orthoAbsHeight=-1., const arr& zRange={}, const char* backgroundImageFile=0);

  Sensor& selectSensor(const char* sensorName); //set the OpenGL sensor

  //-- compute/analyze a camera perspective (stored in classes' output fields)
  void computeImageAndDepth(byteA& image, arr& depth);
  void computeKinectDepth(uint16A& kinect_depth, const arr& depth);
  void computePointCloud(arr& pts, const arr& depth, bool globalCoordinates=true); // point cloud (rgb of every point is given in image)
  void computeSegmentation(byteA& segmentation);     // -> segmentation

  //-- displays
  void watch_PCL(const arr& pts, const byteA& rgb);

  void glDraw(OpenGL &gl);

private:
  void updateCamera();
  void done(const char* _code_);
};

}
