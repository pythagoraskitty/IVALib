/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * This is an example explaining how to use the Camera class
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


using namespace std;
using namespace cv;

int main(int argc, char **argv){

  Mat Blank(500,500,CV_8UC3,Scalar(0,0,0)); 
  arma::cube labelMap(100,100,100);
  double x,y,z,x2,y2,z2,x3,y3,z3,dist3,dist2,dist,dist_t;
  Matx<double,3,3> R(cos(3.1416/10), 0, sin(3.1416/10), 0, 1, 0, -sin(3.1416/10), 0, cos(3.1416/10)); 
  //create the circle label map for initilization
  for(int row = 0; row < labelMap.n_rows;row++){
      for(int collum = 0; collum < labelMap.n_cols;collum++){
	  for(int slice = 0;slice< labelMap.n_slices;slice++){
	      x = (int) row - 50;
	      y = (int) collum - 50;
	      z = (int) slice - 50;
	      dist  = sqrt(pow(x,2) + pow(y,2) +pow(z,2));
	      if(dist <= 10)
		  labelMap(row,collum,slice) = 1;
	      x2 = (int) row - 20;
	      y2 = (int) collum - 20;
	      z2 = (int) slice - 50;
	      dist2 = sqrt(x2*x2 + y2*y2 + z2*z2);
	      if(dist2 <= 10)
		  labelMap(row,collum,slice) = 1;
	      x3 = (int) row - 80;
	      y3 = (int) collum - 80;
	      z3 = (int) slice - 50;
	      dist3 = sqrt(x3*x3 + y3*y3 + z3*z3);
	      if(dist3 <= 10)
		  labelMap(row,collum,slice) = 1;
	  }//end slice for loop
      }//end collum for loop
  }//end row for loop
  
  Matx<double,3,3> CamMat(200,0,250,0,200,250,0,0,1); 
  Vec3d cord(0,0,0);
  Object3D Surf(labelMap,2,cord);
  Surf.setCenter(Vec3d(0,0,200));
  cout<<"The center of Surf is : ("<<Surf.getCenter()[0]<<","<<Surf.getCenter()[1]<<","<<Surf.getCenter()[2]<<")"<<endl;
  Camera Cam1(Surf,Blank,CamMat);
  cout<<"Made it past first break"<<endl;
  Cam1.computeOcc();
  cout<<"Made it past second break"<<endl;
  Camera Cam2(Surf,Blank,CamMat);
  Camera Cam3(Surf,Blank,CamMat);
  Camera Cam4(Surf,Blank,CamMat);
  Cam2.moveCamera(Vec3d(0,1,0),-3.141592654/2,Vec3d(200,0,200));
  Cam3.moveCamera(Vec3d(0,1,0),3.141592654,Vec3d(0,0,400));
  Cam4.moveCamera(Vec3d(0,1,0),3.141592654/2,Vec3d(-200,0,200));

  Cam2.computeOcc();
  Cam3.computeOcc();
  Cam4.computeOcc();

  //Get the Surf Image
  Mat Cam1Img = Cam1.getSurfImg()*255;
  Mat Cam2Img = Cam2.getSurfImg()*255;
  Mat Cam3Img = Cam3.getSurfImg()*255;
  Mat Cam4Img = Cam4.getSurfImg()*255;



  cout<<"The value of the center of Surface 1 is : ("<<Cam1.getSurface().getCenter()[0]<<","<<Cam1.getSurface().getCenter()[1]<<","<<Cam1.getSurface().getCenter()[2]<<")"<<endl;
  cout<<"The value of the cord of Surface 1 is : ("<<Cam1.getSurface().getCord()[0]<<","<<Cam1.getSurface().getCord()[1]<<","<<Cam1.getSurface().getCord()[2]<<")"<<endl;
  
  cout<<"The value of the center of Surface 2 is : ("<<Cam2.getSurface().getCenter()[0]<<","<<Cam2.getSurface().getCenter()[1]<<","<<Cam2.getSurface().getCenter()[2]<<")"<<endl;
  cout<<"The value of the cord of Surface 2 is : ("<<Cam2.getSurface().getCord()[0]<<","<<Cam2.getSurface().getCord()[1]<<","<<Cam2.getSurface().getCord()[2]<<")"<<endl;
  
  
  cout<<"The value of the center of Surface 3 is : ("<<Cam3.getSurface().getCenter()[0]<<","<<Cam3.getSurface().getCenter()[1]<<","<<Cam3.getSurface().getCenter()[2]<<")"<<endl;
  cout<<"The value of the cord of Surface 3 is : ("<<Cam3.getSurface().getCord()[0]<<","<<Cam3.getSurface().getCord()[1]<<","<<Cam3.getSurface().getCord()[2]<<")"<<endl;


  cout<<"The value of the center of Surface 4 is : ("<<Cam4.getSurface().getCenter()[0]<<","<<Cam4.getSurface().getCenter()[1]<<","<<Cam4.getSurface().getCenter()[2]<<")"<<endl;
  cout<<"The value of the cord of Surface 4 is : ("<<Cam4.getSurface().getCord()[0]<<","<<Cam4.getSurface().getCord()[1]<<","<<Cam4.getSurface().getCord()[2]<<")"<<endl;

  Cam1Img.at<uchar>(250,250) = 127;
  Cam2Img.at<uchar>(250,250) = 127;
  Cam3Img.at<uchar>(250,250) = 127;
  Cam4Img.at<uchar>(250,250) = 127;

  

  //show the image
  namedWindow( "Camera 1 window", CV_WINDOW_AUTOSIZE );// Create a window for display.
  namedWindow( "Camera 2 window", CV_WINDOW_AUTOSIZE );// Create a window for display.
  namedWindow( "Camera 3 window", CV_WINDOW_AUTOSIZE );// Create a window for display.
  namedWindow( "Camera 4 window", CV_WINDOW_AUTOSIZE );// Create a window for display.
  imshow( "Camera 1 window", Cam1Img );
  imshow( "Camera 2 window", Cam2Img );
  imshow( "Camera 3 window", Cam3Img );
  imshow( "Camera 4 window", Cam4Img );
  waitKey(0);// Wait for a keystroke in the window

  //Obtain the occluding curve for each camera and make label map
  vector<Vec3i> Occ1 = Cam1.getOcc();
  vector<Vec3i> Occ2 = Cam2.getOcc();
  vector<Vec3i> Occ3 = Cam3.getOcc();
  vector<Vec3i> Occ4 = Cam4.getOcc();
  arma::cube Occ1label(100,100,100);
  arma::cube Occ2label(100,100,100);
  arma::cube Occ3label(100,100,100);
  arma::cube Occ4label(100,100,100);
  Occ1label.zeros();
  Occ2label.zeros();
  Occ3label.zeros();
  Occ4label.zeros();


  vector<Vec3i>::iterator i = Occ1.begin();

  for(i;i<Occ1.end();i++)
      Occ1label((*i)[0],(*i)[1],(*i)[2]) = 255;

  i = Occ2.begin();

  for(i;i<Occ2.end();i++)
      Occ2label((*i)[0],(*i)[1],(*i)[2]) = 255;

  i = Occ3.begin();

  for(i;i<Occ3.end();i++)
      Occ3label((*i)[0],(*i)[1],(*i)[2]) = 255;
  
  i = Occ4.begin();

  for(i;i<Occ4.end();i++)
      Occ4label((*i)[0],(*i)[1],(*i)[2]) = 255;

  //Show the Occluding Curves
  SurfaceWindow WOcc1(Occ1label);
  WOcc1.run();
  SurfaceWindow WOcc2(Occ2label);
  WOcc2.run();
  SurfaceWindow WOcc3(Occ3label);
  WOcc3.run();
  SurfaceWindow WOcc4(Occ4label);
  WOcc4.run();
  

}
