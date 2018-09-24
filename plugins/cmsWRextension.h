#ifndef cmsWRextension_included
#define cmsWRextension_included 1
// -*- C++ -*-
//
// Package:    ExoAnalysis/cmsWRextension
// Class:      cmsWRextension
// 
/**\class cmsWRextension cmsWRextension.cc ExoAnalysis/cmsWRextension/plugins/cmsWRextension.cc

 Description: [one line class summary]
Accesses GenParticle collection to plot various kinematic variables associated with the event

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrew Christopher Evans
//         Created:  Thu, 30 Mar 2017 09:00:20 GMT
//
//

// system include files
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Particle.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/LorentzVector.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

#include "HEEP/VID/interface/CutNrs.h"
#include "HEEP/VID/interface/VIDCutCodes.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/EDGetToken.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/TriggerUtils/interface/GenericTriggerEventFlag.h"

#include "JetMETCorrections/JetCorrector/interface/JetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

//ROOT includes
#include "TH1D.h"
#include "TTree.h"
#include "TF1.h"
//local includes
#include "ExoAnalysis/cmsWRextensions/interface/eventBits.h"
#include "ExoAnalysis/cmsWRextensions/interface/eventHistos.h"
#include "ExoAnalysis/cmsWRextensions/interface/HEEP.h"
#include "ExoAnalysis/cmsWRextensions/interface/egammaEffi.h"
#include "ExoAnalysis/cmsWRextensions/interface/eventInfo.h"
#include "ExoAnalysis/cmsWRextensions/interface/tools.h"
#include "ExoAnalysis/cmsWRextensions/interface/Muons.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "JetMETCorrections/Modules/interface/JetResolution.h"

#include "TRandom3.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.
class FactorizedJetCorrector;
class JetCorrectionUncertainty;
class cmsWRextension : public edm::EDAnalyzer {
   public:
      explicit cmsWRextension(const edm::ParameterSet& iConfig);
      ~cmsWRextension();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void beginRun(const  edm::Run& run, const edm::EventSetup& setup ) override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      // ----------member functions---------------------
      void selectMuons(const edm::Event&, eventBits&);
      bool preSelectGen (const edm::Event&, eventBits&);
      bool preSelectReco (const edm::Event&, const edm::EventSetup&, eventBits&);
      bool preSelectReco_Fast (const edm::Event&, const edm::EventSetup&, eventBits&);
      bool passMuonTrig (const edm::Event&, eventBits&);
      bool passElectronTrig (const edm::Event&, eventBits&);
      bool passWR2016GEN (const edm::Event&, eventBits&);
      bool passExtensionGEN (const edm::Event&, eventBits&);
      bool passWR2016RECO (const edm::Event&, eventBits&);
      bool passExtensionRECO(const edm::Event&, eventBits&);
      void passExtensionRECO_Fast(const edm::Event&, eventBits&);
      bool passFlavorSideband(const edm::Event&, eventBits&);
      bool selectHighPtISOMuon(const edm::Event&, eventBits&);
      bool passWR2016Reco(const edm::Event&, eventBits&);
      bool jetSelection(const edm::Event& iEvent, const edm::EventSetup&, eventBits& myEvent);
      bool additionalMuons(const edm::Event& iEvent, eventBits& myEvent, bool);
      bool electronSelection(const edm::Event& iEvent, eventBits& myEvent);
      bool muonSelection(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband(const edm::Event& iEvent, eventBits& myEvent, bool nonISO);
      bool METselection(const edm::Event& iEvent, eventBits& myEvent);
      bool METcuts(const edm::Event& iEvent, eventBits& myEvent);
      bool metCuts(const edm::Event& iEvent, eventBits& myEvent);
      void vertexDiff(eventBits& myEvent);
      bool sameSign(eventBits& myEvent, bool noISO);
      //bool massCut(const edm::Event& iEvent, eventBits& myEvent);
      bool genCounter(const edm::Event& iEvent, eventBits& myEvent);
      void setEventWeight(const edm::Event& iEvent, eventBits& myEvent, double MuonLooseIDWeight, double MuonHighPtIDWeight);
      void setEventWeight_FSB(const edm::Event& iEvent, eventBits& myEvent, double MuonLooseIDWeight);
      void setEventWeight_FSB_noISO(const edm::Event& iEvent, eventBits& myEvent, double MuonLooseIDWeight);
      double PUPPIweight(double puppipt, double puppieta);
      void loadCMSSWPath();
      // ----------member data ---------------------------
      eventHistos m_allEvents;
      eventHistos m_eventsPassingWR2016;
      eventHistos m_eventsPassingExtension;
      eventHistos m_eventsPassingExtensionRECO;
      eventHistos m_eventsPassingExtensionRECO2016VETO;
      eventHistos m_eventsPassingExtensionRECO2016VETO_noTrig;
      eventHistos m_eventsPassingExtensionRECO2016VETOMASSMETCUT;
      eventHistos m_eventsPassingExtensionRECO2016VETOMASSCUT;
      eventHistos m_eventsPassingExtensionRECO2016VETOZMASS;
      eventHistos m_eventsPassingExtensionRECO2016VETOSINGLEMUON;
      eventHistos m_eventsPassingWR2016RECO;
      eventHistos m_eventsPassingFlavorSidebandRECOelePt50;
      eventHistos m_eventsPassingFlavorSidebandRECOelePt100;
      eventHistos m_eventsPassingFlavorSidebandRECOelePt150;
      eventHistos m_eventsPassingFlavorSidebandRECO_noTrig;
      eventHistos m_eventsPassingFlavorSidebandRECOelePt50_noISO;

      eventHistos m_eventsPassingFlavorSidebandRECOelePt200_noISO;
      eventHistos m_eventsPassingFlavorSidebandRECOelePt200_noISO_samesign;
      eventHistos m_eventsPassingFlavorSidebandRECOelePt200;
      eventHistos m_eventsPassingFlavorSidebandRECOelePt200_samesign;

      HEEP myHEEP;
      egammaEffi myEgammaEffi;
      eventInfo myEventInfo;
      Muons myMuons;
      edm::EDGetToken m_genParticleToken;
      edm::EDGetToken m_genJetsToken;
      edm::EDGetToken m_AK8genJetsToken;
      edm::EDGetToken m_highMuonToken;
      edm::EDGetToken m_highElectronToken;
      edm::EDGetToken m_regMuonToken;
      edm::EDGetToken m_recoJetsToken;
      edm::EDGetToken m_AK8recoCHSJetsToken;
      edm::EDGetToken m_AK8recoPUPPIJetsToken;
      edm::EDGetToken JECName;
      edm::EDGetToken m_offlineVerticesToken;
      edm::EDGetToken m_genEventInfoToken;
      edm::EDGetToken m_metToken;
      edm::EDGetToken m_trigResultsToken;
      edm::EDGetToken m_trigObjsToken;
      edm::EDGetToken m_PUInfoToken;
      edm::EDGetToken m_rhoLabel;
      bool m_wantHardProcessMuons;
      bool m_doGen;
      bool m_amcatnlo;
      bool m_doReco;
      bool m_isMC;
      bool m_doTrig;
      bool m_doFast;
      double m_MCL;    //MASS UPPER AND LOWER CUTS
      double m_MCU;

      
      double m_highPTleptonCut = 200;
      double m_subleadPTleptonCut = 10;
      double m_leptonEtaCut = 2.4;
      double m_muonIsoCut = .05;

      std::string m_jettiness;
      std::string JECUName;

      std::vector<std::string> m_muonPathsToPass;
      std::vector<std::string> m_muonFiltersToPass;
      std::vector<std::string> m_electronPathsToPass;
      std::vector<std::string> m_electronFiltersToPass;
      bool m_flavorSideband;
      TTree* hardProcessKinematics;
      GenericTriggerEventFlag* m_genericTriggerEventFlag;

      std::string m_outputTag;

      FactorizedJetCorrector   *fJetCorr;
      JetCorrectionUncertainty *fJetUnc;

      JME::JetResolution resolution;
      JME::JetResolutionScaleFactor resolution_sf;

      TRandom3* r;

      std::string cmsswPath;

};

//define this as a plug-in
DEFINE_FWK_MODULE(cmsWRextension);
#endif
