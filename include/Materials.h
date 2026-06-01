#ifndef __MATERIALS_H__
#define __MATERIALS_H__

class Materials {
  private:
    static Materials *fMaterials; 
    Materials();

  public:
    static Materials* Get(); 
    ~Materials();

  private:

};


#endif

