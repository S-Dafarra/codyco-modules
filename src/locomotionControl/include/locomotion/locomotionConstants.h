/* 
 * Copyright (C) 2013 CoDyCo
 * Author: Andrea Del Prete
 * email:  andrea.delprete@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#ifndef LOCOMOTION_CONSTANTS
#define LOCOMOTION_CONSTANTS

#include <paramHelp/paramHelp.h>
#include <Eigen/Core>                               // import most common Eigen types
#include <vector>

using namespace paramHelp;
using namespace Eigen;
using namespace std;

// *** CONSTANTS RELATED TO THE MODULE PARAMETERS
static const double    KP_MAX = 100.0;    // max value of proportional gains
static const int       ICUB_DOFS = 23;    // number of (the main) degrees of freedom of iCub

enum LocomotionSupportPhase
{ SUPPORT_DOUBLE, SUPPORT_LEFT, SUPPORT_RIGHT };     // foot support phase

// define some types
typedef Matrix<double,6,1>          Vector6d;
typedef Matrix<double,ICUB_DOFS,1>  VectorNd;
typedef Matrix<int,ICUB_DOFS,1>     VectorNi;

// *** DEFAULT PARAMETER VALUES
static const int            DEFAULT_CTRL_PERIOD     = 10;           // controller period in ms
static const char*          DEFAULT_ROBOT_NAME      = "icubSim";    // robot name
static const Vector2d       DEFAULT_KP_COM          = Vector2d::Constant(1.0);
static const Vector6d       DEFAULT_KP_FOOT         = Vector6d::Constant(1.0);
static const VectorNd       DEFAULT_KP_POSTURE      = VectorNd::Constant(1.0);
static const double         DEFAULT_TT_COM          = 2.0;
static const double         DEFAULT_TT_FOOT         = 2.0;
static const double         DEFAULT_TT_POSTURE      = 2.0;
static const VectorNi       DEFAULT_ACTIVE_JNTS     = VectorNi::Constant(1);
static const int            DEFAULT_SUPPORT_PHASE   = SUPPORT_DOUBLE;
static const double         DEFAULT_PINV_DAMP       = 1e-4;

// *** IDs of all the module parameters
enum LocomotionParamId { 
    PARAM_ID_KP_COM,            PARAM_ID_KP_FOOT,           PARAM_ID_KP_POSTURE, 
    PARAM_ID_TRAJ_TIME_COM,     PARAM_ID_TRAJ_TIME_FOOT,    PARAM_ID_TRAJ_TIME_POSTURE,
    PARAM_ID_ACTIVE_JOINTS,     PARAM_ID_SUPPORT_PHASE,     PARAM_ID_PINV_DAMP,
    PARAM_ID_SIZE
};

// ******************************************************************************************************************************
// ****************************************** DESCRIPTION OF ALL THE MODULE PARAMETERS ******************************************
// ******************************************************************************************************************************
const ParamDescription locomotionParamDescr[]  = 
{ 
//               NAME               ID                          TYPE                SIZE                        BOUNDS
ParamDescription("kp com",          PARAM_ID_KP_COM,            PARAM_DATA_FLOAT,   2,                          ParamBounds(0.0, KP_MAX),           
    PARAM_IN_OUT,       DEFAULT_KP_COM.data(),          "Proportional gain for the COM position control"), 
// ******************************************************************************************************************************
ParamDescription("kp foot",         PARAM_ID_KP_FOOT,           PARAM_DATA_FLOAT,   6,                          ParamBounds(0.0, KP_MAX),           
    PARAM_IN_OUT,       DEFAULT_KP_FOOT.data(),         "Proportional gain for the foot pose control"), 
// ******************************************************************************************************************************
ParamDescription("kp posture",      PARAM_ID_KP_POSTURE,        PARAM_DATA_FLOAT,   ParamSize(ICUB_DOFS,true),  ParamBounds(0.0, KP_MAX),    
    PARAM_IN_OUT,       DEFAULT_KP_POSTURE.data(),      "Proportional gain for the joint posture control"), 
// ******************************************************************************************************************************
ParamDescription("tt com",          PARAM_ID_TRAJ_TIME_COM,     PARAM_DATA_FLOAT,   1,                          ParamBounds(0.1, PARAM_BOUND_INF),  
    PARAM_IN_OUT,       &DEFAULT_TT_COM,                "Trajectory time for the COM minimum jerk trajectory generator"), 
// ******************************************************************************************************************************
ParamDescription("tt foot",         PARAM_ID_TRAJ_TIME_FOOT,    PARAM_DATA_FLOAT,   1,                          ParamBounds(0.1, PARAM_BOUND_INF),  
    PARAM_IN_OUT,       &DEFAULT_TT_FOOT,               "Trajectory time for the foot minimum jerk trajectory generator"), 
// ******************************************************************************************************************************
ParamDescription("tt posture",      PARAM_ID_TRAJ_TIME_POSTURE, PARAM_DATA_FLOAT,   1,                          ParamBounds(0.1, PARAM_BOUND_INF),  
    PARAM_IN_OUT,       &DEFAULT_TT_POSTURE,            "Trajectory time for the posture minimum jerk trajectory generator"), 
// ******************************************************************************************************************************
ParamDescription("active joints",   PARAM_ID_ACTIVE_JOINTS,     PARAM_DATA_INT,     ICUB_DOFS,                  ParamBounds(0, 1),                  
    PARAM_IN_OUT,       DEFAULT_ACTIVE_JNTS.data(),     "Selection of which joints are used in the control (1: active, 0: inactive)"), 
// ******************************************************************************************************************************
ParamDescription("support phase",   PARAM_ID_SUPPORT_PHASE,     PARAM_DATA_INT,     1,                          ParamBounds(0.0, 2.0),              
    PARAM_IN_OUT,       &DEFAULT_SUPPORT_PHASE,         "Foot support phase, 0: double, 1: left foot, 2: right foot"), 
// ******************************************************************************************************************************
ParamDescription("pinv damp",       PARAM_ID_PINV_DAMP,         PARAM_DATA_FLOAT,   1,                          ParamBounds(1e-8, 1.0),             
    PARAM_IN_OUT,       &DEFAULT_PINV_DAMP,             "Damping factor used in the pseudoinverses")
};

#endif
