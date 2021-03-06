/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * This file contains the cpp that  contains the methods of the Camera 
 * class in IVALib.
 * Copyright (C) 2012   Matias Perez
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL
 ******************************************************************************/

#include"IVALib/ThreeD/Object3D.hpp"

Object3D::Object3D(arma::cube const &labelMap){
    this->labelMap = new arma::cube(labelMap);
    Phi = NULL;
    scale = 1;
    cord = cv::Vec3d(0,0,0);    
    SFM_point<double> point(labelMap.n_rows,labelMap.n_cols,labelMap.n_slices);
    this->rot = cv::Matx<double,3,3>::eye();
    this->Center = this->cord +this->rot*cv::Vec3d(this->labelMap->n_cols/2.0,this->labelMap->n_rows/2.0,this->labelMap->n_slices/2.0)*scale;
    this->Lz = new std::vector<SFM_point<double> >;

    //initializes the zero-level set
    for(int slice = 0; slice < this->labelMap->n_slices;slice++){
	//run through rows
	for(int row = 0; row < this->labelMap->n_rows; row++){
	    //next run through collums 
	    for(int collum =0; collum < this->labelMap->n_cols;collum++){
		//check to see if the point is in the zero levelset
		point.set(row,collum,slice);           
		if((*this->labelMap)(row,collum,slice) == 1){
		    if(point.checkForward() && (*this->labelMap)(point[0] +1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBackward() && (*this->labelMap)(point[0] -1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkUp() && (*this->labelMap)(point[0],point[1]+1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkDown() && (*this->labelMap)(point[0],point[1]-1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkFSlice() && (*this->labelMap)(point[0],point[1],point[2]+1) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBSlice() && (*this->labelMap)(point[0],point[1],point[2]-1) == 0)
			this->Lz->push_back(point);
		}//end if checking labelMap(row,collum)
	    }//end collum for loop
	}//end row for loop
    }//end slice for loop
    
};

Object3D::Object3D(arma::cube const &labelMap, arma::cube const &Phi, double const &scale){
    this->labelMap = new arma::cube(labelMap);
    this->Phi = new arma::cube(Phi);
    this->scale = scale;
    cord = cv::Vec3d(0,0,0);
    SFM_point<double> point(labelMap.n_rows,labelMap.n_cols,labelMap.n_slices);
    this->rot = cv::Matx<double,3,3>::eye();
    this->Center = this->cord +this->rot*cv::Vec3d(this->labelMap->n_cols/2.0,this->labelMap->n_rows/2.0,this->labelMap->n_slices/2.0)*scale;
    this->Lz = new std::vector<SFM_point<double> >;
    
    //initializes the zero-level set
    for(int slice = 0; slice < this->labelMap->n_slices;slice++){
	//run through rows
	for(int row = 0; row < this->labelMap->n_rows; row++){
	    //next run through collums 
	    for(int collum =0; collum < this->labelMap->n_cols;collum++){
		//check to see if the point is in the zero levelset
		point.set(row,collum,slice);           
		if((*this->labelMap)(row,collum,slice) == 1){
		    if(point.checkForward() && (*this->labelMap)(point[0] +1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBackward() && (*this->labelMap)(point[0] -1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkUp() && (*this->labelMap)(point[0],point[1]+1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkDown() && (*this->labelMap)(point[0],point[1]-1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkFSlice() && (*this->labelMap)(point[0],point[1],point[2]+1) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBSlice() && (*this->labelMap)(point[0],point[1],point[2]-1) == 0)
			this->Lz->push_back(point);
		}//end if checking labelMap(row,collum)
	    }//end collum for loop
	}//end row for loop
    }//end slice for loop
};

Object3D::Object3D(arma::cube  const &labelMap, arma::cube const &Phi, double const &scale, cv::Vec3d const &cord){
    this->labelMap = new arma::cube(labelMap);
    this->Phi = new arma::cube(Phi);
    this->scale = scale;
    this->cord = cord;
    SFM_point<double> point(labelMap.n_rows,labelMap.n_cols,labelMap.n_slices);
    this->rot = cv::Matx<double,3,3>::eye();
    this->Center = this->cord +this->rot*cv::Vec3d(this->labelMap->n_cols/2.0,this->labelMap->n_rows/2.0,this->labelMap->n_slices/2.0)*scale;
    this->Lz = new std::vector<SFM_point<double> >;

    //initializes the zero-level set
    for(int slice = 0; slice < this->labelMap->n_slices;slice++){
	//run through rows
	for(int row = 0; row < this->labelMap->n_rows; row++){
	    //next run through collums 
	    for(int collum =0; collum < this->labelMap->n_cols;collum++){
		//check to see if the point is in the zero levelset
		point.set(row,collum,slice);           
		if((*this->labelMap)(row,collum,slice) == 1){
		    if(point.checkForward() && (*this->labelMap)(point[0] +1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBackward() && (*this->labelMap)(point[0] -1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkUp() && (*this->labelMap)(point[0],point[1]+1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkDown() && (*this->labelMap)(point[0],point[1]-1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkFSlice() && (*this->labelMap)(point[0],point[1],point[2]+1) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBSlice() && (*this->labelMap)(point[0],point[1],point[2]-1) == 0)
			this->Lz->push_back(point);
		}//end if checking labelMap(row,collum)
	    }//end collum for loop
	}//end row for loop
    }//end slice for loop
  };

Object3D::Object3D(arma::cube  const &labelMap, double const &scale, cv::Vec3d const &cord){
    this->labelMap = new arma::cube(labelMap);
    Phi = NULL;
    this->scale = scale;
    this->cord = cord;
    SFM_point<double> point(labelMap.n_rows,labelMap.n_cols,labelMap.n_slices);
    this->rot = cv::Matx<double,3,3>::eye();
    this->Center = this->cord +this->rot*cv::Vec3d(this->labelMap->n_cols/2.0,this->labelMap->n_rows/2.0,this->labelMap->n_slices/2.0)*scale;
    this->Lz = new std::vector<SFM_point<double> >;

    //initializes the zero-level set
    for(int slice = 0; slice < this->labelMap->n_slices;slice++){
	//run through rows
	for(int row = 0; row < this->labelMap->n_rows; row++){
	    //next run through collums 
	    for(int collum =0; collum < this->labelMap->n_cols;collum++){
		//check to see if the point is in the zero levelset
		point.set(row,collum,slice);           
		if((*this->labelMap)(row,collum,slice) == 1){
		    if(point.checkForward() && (*this->labelMap)(point[0] +1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBackward() && (*this->labelMap)(point[0] -1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkUp() && (*this->labelMap)(point[0],point[1]+1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkDown() && (*this->labelMap)(point[0],point[1]-1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkFSlice() && (*this->labelMap)(point[0],point[1],point[2]+1) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBSlice() && (*this->labelMap)(point[0],point[1],point[2]-1) == 0)
			this->Lz->push_back(point);
		}//end if checking labelMap(row,collum)
	    }//end collum for loop
	}//end row for loop
    }//end slice for loop
  };
Object3D::Object3D(arma::cube  const &labelMap, double const &scale){
    this->labelMap = new arma::cube(labelMap);
    Phi = NULL;
    this->scale = scale;
    this->cord = cv::Vec3d(0,0,0);
    SFM_point<double> point(labelMap.n_rows,labelMap.n_cols,labelMap.n_slices);
    this->rot = cv::Matx<double,3,3>::eye();
    this->Center = this->cord +this->rot*cv::Vec3d(this->labelMap->n_cols/2.0,this->labelMap->n_rows/2.0,this->labelMap->n_slices/2.0)*scale;
    this->Lz = new std::vector<SFM_point<double> >;

    //initializes the zero-level set
    for(int slice = 0; slice < this->labelMap->n_slices;slice++){
	//run through rows
	for(int row = 0; row < this->labelMap->n_rows; row++){
	    //next run through collums 
	    for(int collum =0; collum < this->labelMap->n_cols;collum++){
		//check to see if the point is in the zero levelset
		point.set(row,collum,slice);           
		if((*this->labelMap)(row,collum,slice) == 1){
		    if(point.checkForward() && (*this->labelMap)(point[0] +1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBackward() && (*this->labelMap)(point[0] -1,point[1],point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkUp() && (*this->labelMap)(point[0],point[1]+1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkDown() && (*this->labelMap)(point[0],point[1]-1,point[2]) == 0)
			this->Lz->push_back(point);
		    else if(point.checkFSlice() && (*this->labelMap)(point[0],point[1],point[2]+1) == 0)
			this->Lz->push_back(point);
		    else if(point.checkBSlice() && (*this->labelMap)(point[0],point[1],point[2]-1) == 0)
			this->Lz->push_back(point);
		}//end if checking labelMap(row,collum)
	    }//end collum for loop
	}//end row for loop
    }//end slice for loop
  };
