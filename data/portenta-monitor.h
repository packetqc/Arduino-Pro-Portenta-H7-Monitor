#pragma once

class MPMON {
  private:
    bool status;
    MPMON() = default; // Make constructor private  

  public:
    //SINGLETON
    static MPMON &getInstance(); // Accessor for singleton instance
    MPMON(const MPMON &) = delete; // no copying
    MPMON &operator=(const MPMON &) = delete;

  public:    
    bool Status();
};

extern MPMON &mpMON;
