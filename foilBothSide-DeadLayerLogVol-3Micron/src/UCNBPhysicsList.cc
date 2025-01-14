#include "globals.hh"
#include "UCNBPhysicsList.hh"

#include "G4ProcessManager.hh"

#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ProcessVector.hh"

#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"

#include "G4LossTableManager.hh"
#include "G4EmSaturation.hh"

#include "G4IonConstructor.hh"

#include "G4StepLimiter.hh"
//-----------------------------------
#include "G4MuonMinusCapture.hh"
#include "G4SystemOfUnits.hh"
#include "G4RegionStore.hh"
#include "G4VEmModel.hh"
#include "globals.hh"
 #include "G4HadronicInteraction.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

UCNBPhysicsList::UCNBPhysicsList():  G4VUserPhysicsList()
{
  theCerenkovProcess           = 0;
  theScintillationProcess      = 0;
  theAbsorptionProcess         = 0;
  theRayleighScatteringProcess = 0;
  theBoundaryProcess           = 0;

  //defaultCutValue = 0.0001*cm;
  defaultCutValue = 0.0001*cm;
// G4cout<<" Physics list is set "<<G4endl;
//  SetVerboseLevel(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

UCNBPhysicsList::~UCNBPhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  ConstructIons();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructLeptons()
{
  // leptons
  //  e+/-
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  // mu+/-
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  // nu_e
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  // nu_mu
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructMesons()  
{
  //  mesons
  //    light mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void UCNBPhysicsList::ConstructIons()
{
  //  Construct (all) light ions: (from Example N05)
  G4IonConstructor pConstructor;
  pConstructor.ConstructParticle();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructBaryons()
{
  //  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();

  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
  AddStepMax();
  ConstructOp();
  //ConstructHad();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//#include "G4ComptonScattering.hh"
//#include "G4GammaConversion.hh"
//#include "G4PhotoElectricEffect.hh"

//#include "G4eMultipleScattering.hh"
//#include "G4eIonisation.hh"
//#include "G4eBremsstrahlung.hh"
//#include "G4eplusAnnihilation.hh"

//#include "G4MuMultipleScattering.hh"
//#include "G4MuIonisation.hh"
//#include "G4MuBremsstrahlung.hh"
//#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
//#include "G4hLowEnergyIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

//#include "G4ionIonisation.hh"

// Electromagnetic Processes ////////////////////////////////////////////////
// all charged particles:  List of processes from example DMX

// gamma
#include "G4PhotoElectricEffect.hh"
#include "G4LivermorePhotoElectricModel.hh"

#include "G4ComptonScattering.hh"
#include "G4LivermoreComptonModel.hh"

#include "G4GammaConversion.hh"
#include "G4LivermoreGammaConversionModel.hh"

#include "G4RayleighScattering.hh" 
#include "G4LivermoreRayleighModel.hh"


// e-  “low	 energy”
#include "G4eMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4LivermoreIonisationModel.hh"

#include "G4eBremsstrahlung.hh"
#include "G4LivermoreBremsstrahlungModel.hh"


// e+
#include "G4eIonisation.hh" 
#include "G4eBremsstrahlung.hh" 
#include "G4eplusAnnihilation.hh"


// alpha and GenericIon and deuterons, triton, He3:
//hIonisation #include "G4howEnergyIonisation.hh" -> moved to G4hIonisation
#include "G4EnergyLossTables.hh"
// hLowEnergyIonisation uses Ziegler 1988 as the default


//muon:
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
//#include "G4MuonMinusCaptureAtRest.hh"
#include "G4MuonMinusCapture.hh"
#include "G4MuMultipleScattering.hh"

//OTHERS:
#include "G4hIonisation.hh" 
#include "G4hMultipleScattering.hh"
#include "G4hBremsstrahlung.hh"
#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructEM()
{
  //  theParticleIterator->reset();
  // while( (*theParticleIterator)() ){
  //  G4ParticleDefinition* particle = theParticleIterator->value();

  //  G4ProcessManager* pmanager = particle->GetProcessManager();
  //  G4String particleName = particle->GetParticleName();
  //   
  //  if (particleName == "gamma") {
  //    // gamma         
  //    pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
  //    pmanager->AddDiscreteProcess(new G4ComptonScattering);  “low	
 // energy”
  //    pmanager->AddDiscreteProcess(new G4GammaConversion);
  //    
  //  } else if (particleName == "e-") {
  //    //electron
  //    pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
  //    pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
  //    pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);      
  //
  //  } else if (particleName == "e+") {
  //    //positron
  //    pmanager->AddProcess(new G4eMultipleScattering, -1, 1, 1);
  //    pmanager->AddProcess(new G4eIonisation,         -1, 2, 2);
  //    pmanager->AddProcess(new G4eBremsstrahlung,     -1, 3, 3);
  //    pmanager->AddProcess(new G4eplusAnnihilation,    0,-1, 4);
  //
  //  } else if( particleName == "mu+" || 
  //             particleName == "mu-"    ) {
  //    //muon  
  //    pmanager->AddProcess(new G4MuMultipleScattering, -1, 1, 1);
  //    pmanager->AddProcess(new G4MuIonisation,         -1, 2, 2);
  //    pmanager->AddProcess(new G4MuBremsstrahlung,     -1, 3, 3);
  //    pmanager->AddProcess(new G4MuPairProduction,     -1, 4, 4);       
  //           
  //  } else if( particleName == "proton" ||
  //             particleName == "pi-" ||
  //             particleName == "pi+"    ) {
  //    //proton  
  //    pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
  //    pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
  //    pmanager->AddProcess(new G4hBremsstrahlung,     -1, 3, 3);
  //    pmanager->AddProcess(new G4hPairProduction,     -1, 4, 4);       
  //   
  //  } else if( particleName == "alpha" || 
  //	       particleName == "He3" )     {
  //    //alpha 
  //    pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
  //    pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
  //   
  //  } else if( particleName == "GenericIon" ||
  //             particleName == "triton" ) { 
  //    //Ions 
  //    pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
  //    pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
  //               
  //  } else if ((!particle->IsShortLived()) &&  “low	
 // energy”
  //	       (particle->GetPDGCharge() != 0.0) && 
  //	       (particle->GetParticleName() != "chargedgeantino")) {
  //    //all others charged particles except geantino
  //    pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
  //    pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
  //  }
  //}
   ///////////////////////////////////////////////////////////////1 added
G4ParticleTable::G4PTblDicIterator* theParticleIterator
= G4ParticleTable::GetParticleTable()->GetIterator();
/////////////////////////////////////////////////////////////
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    G4String particleType = particle->GetParticleType();
    G4double charge = particle->GetPDGCharge();
    
    if (particleName == "gamma") 
      {
	//gamma
	//G4RayleighScattering* theRayleigh = new G4RayleighScattering();
	G4OpRayleigh* theRayleigh = new G4OpRayleigh();
//	theRayleigh->SetModel(new G4LivermoreRayleighModel());  //not strictly necessary
	pmanager->AddDiscreteProcess(theRayleigh);

	G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
	//thePhotoElectricEffect->SetModel(new G4LivermorePhotoElectricModel());
	pmanager->AddDiscreteProcess(thePhotoElectricEffect);
	
	G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
	//theComptonScattering->SetModel(new G4LivermoreComptonModel());
	pmanager->AddDiscreteProcess(theComptonScattering);
	
	G4GammaConversion* theGammaConversion = new G4GammaConversion();
	//theGammaConversion->SetModel(new G4LivermoreGammaConversionModel());
	pmanager->AddDiscreteProcess(theGammaConversion);

      } 
    else if (particleName == "e-") 
      {
	//electron
	// process ordering: AddProcess(name, at rest, along step, post step)
	// Multiple scattering
	G4eMultipleScattering* msc = new G4eMultipleScattering();
	msc->SetStepLimitType(fUseDistanceToBoundary);
	pmanager->AddProcess(msc,-1, 1, 1); 	
 

	// Ionisation
	G4eIonisation* eIonisation = new G4eIonisation();
	eIonisation->SetEmModel(new G4LivermoreIonisationModel());
	eIonisation->SetStepFunction(0.2, 100*um); //improved precision in tracking  
	pmanager->AddProcess(eIonisation,-1, 2, 2);
	
	// Bremsstrahlung
	G4eBremsstrahlung* eBremsstrahlung = new G4eBremsstrahlung();
	eBremsstrahlung->SetEmModel(new G4LivermoreBremsstrahlungModel());
	pmanager->AddProcess(eBremsstrahlung, -1,-3, 3);
      } 
    else if (particleName == "e+") 
      {
	//positron	
	G4eMultipleScattering* msc = new G4eMultipleScattering();
	msc->SetStepLimitType(fUseDistanceToBoundary);
	pmanager->AddProcess(msc,-1, 1, 1);
	
	// Ionisation
	G4eIonisation* eIonisation = new G4eIonisation();
	eIonisation->SetStepFunction(0.2, 100*um); //     
	pmanager->AddProcess(eIonisation,                 -1, 2, 2);

	//Bremsstrahlung (use default, no low-energy available)
	pmanager->AddProcess(new G4eBremsstrahlung(), -1,-1, 3);

	//Annihilation
	pmanager->AddProcess(new G4eplusAnnihilation(),0,-1, 4);      
      } 
    else if( particleName == "mu+" || 
	     particleName == "mu-"    ) 
      {
	//muon  
	pmanager->AddProcess(new G4eMultipleScattering,           -1, 1, 1);
	pmanager->AddProcess(new G4MuIonisation(), -1, 2, 2);
	pmanager->AddProcess(new G4MuBremsstrahlung(),      -1,-1, 3);
	pmanager->AddProcess(new G4MuPairProduction(),      -1,-1, 4);
	if( particleName == "mu-" )
	  pmanager->AddProcess(new G4MuonMinusCapture(), 0,-1,-1);//changes made here
      }  	
  
    else if (particleName == "proton" || 
	     particleName == "pi+" || 
	     particleName == "pi-")
      {
	//multiple scattering
	pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      
	//ionisation
       G4hIonisation* hIonisation = new G4hIonisation();
	hIonisation->SetStepFunction(0.2, 50*um);
      //  hIonisation->SetStepFunction(0.2, 0.01*um);
	pmanager->AddProcess(hIonisation,                     -1, 2, 2);      
	
	//bremmstrahlung
	pmanager->AddProcess(new G4hBremsstrahlung,     -1,-3, 3);
      }
    else if(particleName == "alpha"      ||
	     particleName == "deuteron"   ||
	     particleName == "triton"     ||
	     particleName == "He3")
      {
	//multiple scattering
	pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);
	
	//ionisation
	G4ionIonisation* ionIoni = new G4ionIonisation();
	ionIoni->SetStepFunction(0.1, 20*um);
	pmanager->AddProcess(ionIoni,                   -1, 2, 2);
      }
    else if (particleName == "GenericIon")
      {
	// OBJECT may be dynamically created as either a GenericIon or nucleus
	// G4Nucleus exists and therefore has particle type nucleus
	// genericIon:
	
	//multiple scattering
	pmanager->AddProcess(new G4hMultipleScattering,-1,1,1);

	//ionisation
	G4ionIonisation* ionIoni = new G4ionIonisation();
	ionIoni->SetEmModel(new G4IonParametrisedLossModel());
	ionIoni->SetStepFunction(0.1, 20*um);
	pmanager->AddProcess(ionIoni,                   -1, 2, 2);
      } 

    else if ((!particle->IsShortLived()) &&
	     (charge != 0.0) && 
	     (particle->GetParticleName() != "chargedgeantino")) 
      {
	//all others charged particles except geantino
        G4hMultipleScattering* aMultipleScattering = new G4hMultipleScattering();
        G4hIonisation* ahadronIon = new G4hIonisation();
	
 
	//multiple scattering
	pmanager->AddProcess(aMultipleScattering,-1,1,1);

	//ionisation
	pmanager->AddProcess(ahadronIon,       -1,2,2);      
      }
    
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// Hadronic processes ////////////////////////////////////////////////////////

// Elastic processes:
#include "G4HadronElasticProcess.hh"

 //Inelastic processes:
#include "G4ProtonInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"

 //Low-energy Models: < 20GeV
/*#include "G4LElastic.hh"
#include "G4LEProtonInelastic.hh"
#include "G4LETritonInelastic.hh"
#include "G4HadronCaptureProcess.hh"

void UCNBPhysicsList::ConstructHad()
{
G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess;
G4LElastic* theElasticModel = new G4LElastic;
theElasticProcess->RegisterMe(theElasticModel);

theParticleIterator->reset();
while ((*theParticleIterator)()) 
  {
   G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
   G4String particleName = particle->GetParticleName();
  if (particleName == "proton") 
{
  pmanager->AddDiscreteProcess(theElasticProcess);
  G4ProtonInelasticProcess* theInelasticProcess = 
   new G4ProtonInelasticProcess("inelastic");
  G4LEProtonInelastic* theLEInelasticModel = new G4LEProtonInelastic;
  theInelasticProcess->RegisterMe(theLEInelasticModel);
  pmanager->AddDiscreteProcess(theInelasticProcess);
}
    else if (particleName == "triton") 
   {
        pmanager->AddDiscreteProcess(theElasticProcess);
        G4TritonInelasticProcess* theInelasticProcess = 
          new G4TritonInelasticProcess("inelastic");
      G4LETritonInelastic* theLEInelasticModel = 
          new G4LETritonInelastic;
       theInelasticProcess->RegisterMe(theLEInelasticModel);
        pmanager->AddDiscreteProcess(theInelasticProcess);
   }
  }
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructOp()
{
  theCerenkovProcess           = new G4Cerenkov("Cerenkov");
  theScintillationProcess = new G4Scintillation("Scintillation");
  theAbsorptionProcess     = new G4OpAbsorption();
  theRayleighScatteringProcess = new G4OpRayleigh();
  theBoundaryProcess  = new G4OpBoundaryProcess();

//  theCerenkovProcess->DumpPhysicsTable();
//  theScintillationProcess->DumpPhysicsTable();
//  theAbsorptionProcess->DumpPhysicsTable();
//  theRayleighScatteringProcess->DumpPhysicsTable();

  SetVerbose(1);
  
  theCerenkovProcess->SetMaxNumPhotonsPerStep(20);
  //theCerenkovProcess->SetMaxNumPhotonsPerStep(1000);
  theCerenkovProcess->SetMaxBetaChangePerStep(10.0);
  theCerenkovProcess->SetTrackSecondariesFirst(true);
  
  theScintillationProcess->SetScintillationYieldFactor(1.);
  theScintillationProcess->SetTrackSecondariesFirst(true);

  // Use Birks Correction in the Scintillation process

  G4EmSaturation* emSaturation = G4LossTableManager::Instance()->EmSaturation();
  theScintillationProcess->AddSaturation(emSaturation);

 // G4OpticalSurfaceModel themodel = unified;
  //theBoundaryProcess->SetModel(themodel);
   //////////////////////////////////////////////////2 added
G4ParticleTable::G4PTblDicIterator* theParticleIterator
= G4ParticleTable::GetParticleTable()->GetIterator();
//////////////////////////////////////////////////////
theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    if (theCerenkovProcess->IsApplicable(*particle)) {
    pmanager->AddProcess(theCerenkovProcess);
    pmanager->SetProcessOrdering(theCerenkovProcess,idxPostStep);
    }
    if (theScintillationProcess->IsApplicable(*particle)) {
    //  pmanager->AddProcess(theScintillationProcess);
    //  pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
    //  pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
    }
    if (particleName == "opticalphoton") {
      //G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
      //pmanager->AddDiscreteProcess(theAbsorptionProcess);
      //pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
      //pmanager->AddDiscreteProcess(theBoundaryProcess);
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::SetVerbose(G4int verbose)
{
  //theCerenkovProcess->SetVerboseLevel(verbose);
 // G4int iii = 0;
 // theCerenkovProcess->SetVerboseLevel(iii);
  //theScintillationProcess->SetVerboseLevel(verbose);
  //theAbsorptionProcess->SetVerboseLevel(verbose);
  //theRayleighScatteringProcess->SetVerboseLevel(verbose);
  //theBoundaryProcess->SetVerboseLevel(verbose);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::ConstructGeneral()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
   //////////////////////////////////////////3 added
G4ParticleTable::G4PTblDicIterator* theParticleIterator
= G4ParticleTable::GetParticleTable()->GetIterator();
////////////////////////////////////////
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

void UCNBPhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  G4StepLimiter* stepLimiter = new G4StepLimiter();
  ////G4UserSpecialCuts* userCuts = new G4UserSpecialCuts();
  ////////////////////////////////////////4 added
   G4ParticleTable::G4PTblDicIterator* theParticleIterator
= G4ParticleTable::GetParticleTable()->GetIterator();
  //////////////////////////////////////////////////
  theParticleIterator->reset();
  while ((*theParticleIterator)()){
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();

      if (particle->GetPDGCharge() != 0.0)
        {
	  pmanager ->AddDiscreteProcess(stepLimiter);
	 // pmanager ->AddDiscreteProcess(userCuts);//chaged here
        }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void UCNBPhysicsList::SetCuts()
{
  //G4VUserPhysicsList::SetCutsWithDefault method sets 
  //the default cut value for all particle types 
  //
  SetCutsWithDefault();
  SetParticleCuts(0.5*um,G4Electron::Electron());  // STANDARD CUT
  SetParticleCuts(1.0*um,G4Gamma::Gamma());
  SetParticleCuts(1.0*um,G4Positron::Positron());
  SetParticleCuts(0.5*um,G4Proton::Proton()); 
 if (verboseLevel>0) DumpCutValuesTable();
}

//oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

