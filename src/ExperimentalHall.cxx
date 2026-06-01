
#include "ExperimentalHall.h"

#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>

ExperimentalHall::ExperimentalHall() {


}

ExperimentalHall::~ExperimentalHall() { }

G4VPhysicalVolume *ExperimentalHall::Construct() {
    return nullptr; 	
}

void ExperimentalHall::SetXYZ(double x,double y, double z) {
  fExpHallX = x;
  fExpHallY = y;
  fExpHallZ = z;

}




