#pragma once

#include <Core/thread.h>

namespace mlr { struct Mesh; }
typedef mlr::Array<mlr::Mesh> MeshA;

struct ImageViewer : Thread {
  struct sImageViewer *s;
  Var<byteA> img;
  bool flipImage = false;
  ImageViewer(const char* img_name="rgb");
  ~ImageViewer();
  void open();
  void step();
  void close();
};

struct PointCloudViewer : Thread {
  struct sPointCloudViewer *s;
  Var<arr> pts;
  Var<byteA> rgb;
  PointCloudViewer(const char* pts_name="kinect_points", const char* rgb_name="kinect_rgb");
  ~PointCloudViewer();
  void open();
  void step();
  void close();
};

struct MeshAViewer : Thread {
  Var<MeshA> meshes;
  MeshA copy;
  struct OpenGL *gl;
  MeshAViewer(const char* meshes_name="visionDisplay");
  ~MeshAViewer();
  void open();
  void step();
  void close();
};