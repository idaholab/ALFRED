// Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "TrackingAction.hh"
#include "SteppingAction.hh"
#include "StackingAction.hh"

ActionInitialization::ActionInitialization(DetectorConstruction* detector) 
{
  fDetector = detector;
}

void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction();
  SetUserAction(runAction);
}

void ActionInitialization::Build() const
{
  RunAction* runAction = new RunAction();
  PrimaryGeneratorAction* kinematics = new PrimaryGeneratorAction(fDetector, runAction);
  EventAction* eventAction = new EventAction();
  TrackingAction* trackingAction = new TrackingAction();
  SteppingAction* steppingAction = new SteppingAction(runAction, eventAction, trackingAction, fDetector);
  StackingAction* stackingAction = new StackingAction();
  
  SetUserAction(runAction);
  SetUserAction(kinematics);
  SetUserAction(eventAction);
  SetUserAction(trackingAction);
  SetUserAction(steppingAction);
  SetUserAction(stackingAction);
}  
