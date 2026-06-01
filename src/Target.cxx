
#include "Target.h"
#include "Materials.h"

#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4Box.hh>

Target::Target(G4LogicalVolume *parent) : fParent(parent) {

}

Target::~Target() { } 

G4VPhysicalVolume *Target::Construct() {

  G4Box *target = new G4Box("target",1.*CLHEP::cm,1.*CLHEP::cm,0.1*CLHEP::cm);
  G4LogicalVolume *targetLogical = new G4LogicalVolume(target, nullptr ,"targetLogical",0,0,0);  
  //TODO set user limits

  G4VPhysicalVolume *targetPhysical = new G4PVPlacement(0,G4ThreeVector(),
                                                        targetLogical,"targetPhysical",fParent,false,0,true);

  return targetPhysical;
}

