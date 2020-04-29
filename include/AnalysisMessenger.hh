// \file AnalysisMessenger.hh
// \brief definition of the AnalysisMessenger class

#ifndef AnalysisMessenger_h
#define AnalysisMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class AnalysisManager;
class G4UIcommand;
class G4UIcmdWithAString;
class G4UIdirectory;


class AnalysisMessenger : public G4UImessenger
{
  public:
    AnalysisMessenger(AnalysisManager* analysis);
    virtual ~AnalysisMessenger();

    virtual G4String GetCurrentValue(G4UIcommand *command);
    virtual void SetNewValue(G4UIcommand *command, G4String newValue);

  private:
    G4UIdirectory*    fOutputDirectory;
    G4UIcmdWithAString*      fFileName;
    AnalysisManager*  fAnalysisManager;

};


#endif
