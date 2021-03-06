#ifndef _RECONSTRUCT3D_H_
#define _RECONSTRUCT3D_H_

/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * This file contains the header that  contains the decleration of the
 * Reconstruct3d class in IVALib.
 * Copyright (C) 2012   Matias Perez
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL
 ******************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<math.h>
#include"IVALib/ivalib.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<opencv2/highgui/highgui.hpp>
#include "IVALib/ActiveSurfaces/functor.hpp"

typedef std::vector<Camera> clist;

class Reconstruct3d : public functor<double>{
public:
  /**
   *Constructor
   *@param Cameras list of cameras that will be used to evolve the surface
   *@param labelMap labelMap of the initial surface that will be evolved
   */
  Reconstruct3d(clist const &Cameras, arma::cube const &labelMap,double dt=0.1):dt(dt){
    this->Cameras = Cameras;
    this->energy = arma::cube(labelMap.n_rows,labelMap.n_cols,labelMap.n_slices);
    this->label = new arma::cube(labelMap);
    this->Lz = new std::vector<SFM_point<double> >(Cameras.front().getSurface().getLz());
    for(clist::iterator cam = this->Cameras.begin();cam<this->Cameras.end();cam++){
      cam->getSurface().setLabelMap(this->label);
      cam->getSurface().setLz(this->Lz);
    }
  };
  /**
   *Compute method inherited from functor class. This method is used to compute the gradient of the reconstruction functional with 
   *respect to Phi. 
   *@Lz vector of points used to represent the contour
   *@Lp1 vector of points used to represent the +1 list
   *@Lp2 vector of points used to represent the +2 list
   *@Ln1 vector of points used to represent the -1 list
   *@Ln2 vector of points used to represent the -2 list
   */
  void Compute(std::vector<SFM_point<double> > const &Lz, std::vector<SFM_point<double> > const &Lp1, std::vector<SFM_point<double> > const &Lp2, std::vector<SFM_point<double> > const &Ln1,std::vector<SFM_point<double> > const &Ln2);
  /**
   *Stop method inherited from functor class. This method returns true when the stopping condition is reached. This method is used by 
   *the SFM class as a stopping condition when running Run method.
   *@param Phi Signed Distance Function representing the contour
   *@Lz vector of points used to represent the contour
   *@Lp1 vector of points used to represent the +1 list
   *@Lp2 vector of points used to represent the +2 list
   *@Ln1 vector of points used to represent the -1 list
   *@Ln2 vector of points used to represent the -2 list
   *@count int value used to keep count of number of iterations
   */
  bool Stop(std::vector<SFM_point<double> > const &Lz, std::vector<SFM_point<double> > const &Lp1, std::vector<SFM_point<double> > const &Lp2, std::vector<SFM_point<double> > const &Ln1,std::vector<SFM_point<double> > const &Ln2, int count){
    if(count<6)return false;
    else return true;
  };

  /**
   *updateCamera
   *Update all cameras in the camera list
   */
  void updateCamera(arma::cube const &Phi3D, std::vector<SFM_point<double> > const &Lz);
  
  /**
   *getCameras
   *returns list of cameras
   */
  clist & getCameras(){return Cameras;};
  
private:
  /**
   *vector of cameras that hold the 
   */
  clist Cameras;
  /**
   *arma::cube that holds the force info for each element
   */
  arma::cube energy;
  /**
   *cv::Vec3d used to describe the change of rotation for the specific camera being updated
   */
  cv::Vec3d dg;
  /**
   *cv::Vec3d used to describe the change in the translation vector for the specific camera being updated
   */
  cv::Vec3d dT;
  /**
   *double that represents delta t in the gradient descent method for optimizing the camera position
   */
  double dt;
  /**
   *arma::cube pointer that contians the label map shared by all the cameras
   */
  arma::cube *label;
  /**
   *std::vector<SFM_point<double> > that keeps the zero level set of all the cameras in the system
   */
  std::vector<SFM_point<double> > *Lz;
  /**
   *computeEnergy
   *computes the energy gradient at each point and registers in the arma::cube energy
   *@param cam camera that the gradient energe will be computed on
   */
  template<class T>
  inline void computeEnergy(Camera &cam);

  /**
   *computeCamEnergy
   *computes the energy gradient of the camera parameters and changes each camera location
   *@param cam refrence to the camera that will be changed
   *@param Phi3D arma::cube that contains the SDF at the present itteration
   */
  template<class T>
  inline void computeCamEnergy(Camera &cam, arma::cube const &Phi3D);
  
     
};

#endif
