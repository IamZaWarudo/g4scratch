#ifndef __EXPERIMENTCONSTUCTION_H__
#define __EXPERIMENTCONSTUCTION_H__

#include <G4VUserDetectorConstruction.hh>

class G4VPhysicalVolume;

class ExperimentConstruction : public G4VUserDetectorConstruction {
  public:
    ExperimentConstruction();  
    ~ExperimentConstruction();  

    virtual G4VPhysicalVolume *Construct();

    void writeGDML();


  private:
    


};


#endif
