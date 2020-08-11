#ifndef analyzeLastBin_included
#define analyzeLastBin_included 1
// -*- C++ -*-
//
// Package:    ExoAnalysis/analyzeLastBin
// Class:      analyzeLastBin
// 
/**\class analyzeLastBin analyzeLastBin.cc ExoAnalysis/analyzeLastBin/plugins/analyzeLastBin.cc

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
#include "FWCore/Framework/interface/EDAnalyzer.h"

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
#include "ExoAnalysis/cmsWRextensions/interface/Zweight.h"

#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "JetMETCorrections/Modules/interface/JetResolution.h"

#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h" // -- LHE info like PDF
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h" // -- ??

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
class analyzeLastBin : public edm::EDAnalyzer {
   public:
      explicit analyzeLastBin(const edm::ParameterSet& iConfig);
      ~analyzeLastBin();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void beginRun(const  edm::Run& run, const edm::EventSetup& setup ) override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      // ----------member functions---------------------
      bool preSelectGen (const edm::Event&, eventBits&);
      bool preSelectBoostReco (const edm::Event&, const edm::EventSetup&, eventBits&);
      bool preSelectReco_Fast (const edm::Event&, const edm::EventSetup&, eventBits&);
      bool passMuonTrig (const edm::Event&, eventBits&);
      bool passElectronTrig (const edm::Event&, eventBits&);
      bool passResGEN (const edm::Event&, eventBits&);
      bool passBoostGEN (const edm::Event&, eventBits&);
      bool passResTightGEN (const edm::Event&, eventBits&);
      bool passBoostTightGEN (const edm::Event&, eventBits&);
      bool objectCompareGEN(const edm::Event&, eventBits&);
      bool signalGENidentifier(const edm::Event&, eventBits&);
      bool passZsidebandCutGEN(const edm::Event&, eventBits&);
      bool passResRECO (const edm::Event&, eventBits&);
      bool passFSBResRECO (const edm::Event&, eventBits&);
      std::vector<bool> passResRECO_Fast (const edm::Event&, eventBits&);
      std::vector<bool> passFSBResRECO_Fast (const edm::Event&, eventBits&);
      bool passBoostRECO(const edm::Event&, eventBits&);
      bool passExtensionRECO_ZPeak(const edm::Event&, eventBits&);
      void passExtensionRECO_Fast(const edm::Event&, eventBits&);
      bool passFlavorSideband(const edm::Event&, eventBits&);
      bool passFlavorSideband_Fast(const edm::Event&, eventBits&);
      bool selectHighPtISOMuon(const edm::Event&, eventBits&);
      bool jetSelection(const edm::Event& iEvent, eventBits& myEvent);
      bool resolvedJetSelection(const edm::Event& iEvent, eventBits& myEvent);
      bool resolvedFSBJetSelection(const edm::Event& iEvent, eventBits& myEvent);
      bool genJetAnalyzer(const edm::Event& iEvent, eventBits& myEvent);
      bool additionalMuons(const edm::Event& iEvent, eventBits& myEvent, bool flavorSideband, bool ZPeak, int JetCorrectionRegion, bool ISO);
      bool electronSelection(const edm::Event& iEvent, eventBits& myEvent, bool isSignal, std::string year);
      bool additionalElectrons(const edm::Event& iEvent, eventBits& myEvent, bool flavorSideband, int JetCorrectionRegion);
      bool muonSelection(const edm::Event& iEvent, eventBits& myEvent);
      bool resolvedMuonSelection(const edm::Event&, eventBits&);
      bool resolvedElectronSelection(const edm::Event&, eventBits&);
      bool resolvedFSBleptonSelection(const edm::Event&, eventBits&);
      int subLeadingMuonZMass(const edm::Event& iEvent, eventBits& myEvent, bool ZPeak, bool useResMu);
      int subLeadingMuonZMass_Nominal(const edm::Event& iEvent, eventBits& myEvent, bool ZPeak);
      int subLeadingMuonZMass_JECUp(const edm::Event& iEvent, eventBits& myEvent, bool ZPeak);
      int subLeadingMuonZMass_JECDown(const edm::Event& iEvent, eventBits& myEvent, bool ZPeak);
      int subLeadingMuonZMass_JERUp(const edm::Event& iEvent, eventBits& myEvent, bool ZPeak);
      int subLeadingMuonZMass_JERDown(const edm::Event& iEvent, eventBits& myEvent, bool ZPeak);
      bool subLeadingMuonZMass_FlavorSideband(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband_Nominal(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband_JECUp(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband_JECDown(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband_JERUp(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband_JERDown(const edm::Event& iEvent, eventBits& myEvent);
      bool subLeadingMuonZMass_FlavorSideband(const edm::Event& iEvent, eventBits& myEvent, bool nonISO);
      bool passFSBbin(eventBits& myEvent, bool ISO, int ptCut);
      bool passABCD(eventBits& myEvent, bool AvB /*versus AvC */);
      void vertexDiff(eventBits& myEvent);
      bool sameSign(eventBits& myEvent, bool noISO);
      //bool massCut(const edm::Event& iEvent, eventBits& myEvent);
      bool genCounter(const edm::Event& iEvent, eventBits& myEvent);
      bool ZFinder(const edm::Event& iEvent, eventBits& myEvent);
      void setEventWeight(const edm::Event& iEvent, eventBits& myEvent);
      void setEventWeight_Resolved(const edm::Event& iEvent, eventBits& myEvent);
      void setEventWeight_FSB(const edm::Event& iEvent, eventBits& myEvent);
      void setEventWeight_FSB_noISO(const edm::Event& iEvent, eventBits& myEvent);
      void setEventWeight_ResolvedFSB(const edm::Event& iEvent, eventBits& myEvent);
      bool WRresonanceStudy(const edm::Event& iEvent, eventBits& myEvent);
      bool electronPassesHEEP(const edm::Event& iEvent, eventBits& myEvent, const pat::Electron* electron, bool noIso); 

      std::vector<double> getZweight(const edm::Event& iEvent, eventBits& myEvent);
      double PUPPIweight(double puppipt, double puppieta, bool isMC);
      void LHEinfo(const edm::Event& iEvent, eventBits& myEvent);
      void loadCMSSWPath();
      // ----------member data ---------------------------
      eventHistos m_allEvents;

      eventHistos m_allOnShellEvents;
      eventHistos m_allOffShellEvents;
      eventHistos m_eventsFailResPassBoostRECO_onShell;
      eventHistos m_eventsFailResPassBoostRECO_offShell;
//      eventHistos m_eventsPassingWR2016;
//      eventHistos m_eventsPassingExtensionGEN;
//      eventHistos m_eventsPassingExtensionRECO;
//      eventHistos m_eventsPassingExtensionRECO2016VETO;
//      eventHistos m_eventsPassingExtensionRECO2016VETO_noTrig;
//      eventHistos m_eventsPassingExtensionRECO2016VETOMASSMETCUT;
//      eventHistos m_eventsPassingExtensionRECO2016VETOMASSCUT;
//      eventHistos m_eventsPassingExtensionRECO2016VETOSINGLEMUON;
//      eventHistos m_eventsPassingWR2016RECO;
      eventHistos m_eventsFailResFailBoostGEN;
      eventHistos m_eventsPassResPassBoostGEN;
      eventHistos m_eventsPassResFailBoostGEN;
      eventHistos m_eventsFailResPassBoostGEN;

      eventHistos m_eventsFailResFailBoostRECO;
      eventHistos m_eventsPassResPassBoostRECO;
      eventHistos m_eventsPassResFailBoostRECO;
      eventHistos m_eventsFailResPassBoostRECO;

      eventHistos m_eventsPassResFailBoostRECO_mll450;
      eventHistos m_eventsPassResFailBoostRECO_mll400;
      eventHistos m_eventsPassResFailBoostRECO_mll500;
      eventHistos m_eventsPassResFailBoostRECO_mll550;
      eventHistos m_eventsPassResFailBoostRECO_mll600;

      eventHistos m_eventsPassResLowMassCRRECO;
      eventHistos m_eventsPassResZMASSRECO;
      eventHistos m_eventsPassResFSBRECO;
      eventHistos m_eventsPassResFSBLowMassCRRECO;
      eventHistos m_eventsPassResFSBLowMassCRRECO_failBox;
      eventHistos m_eventsPassResFSBLowMassCRRECO_oppoBox;
      eventHistos m_eventsPassJetSelection;

      eventHistos m_eventsPassResFSBRECO_mll450;
      eventHistos m_eventsPassResFSBRECO_mll400;
      eventHistos m_eventsPassResFSBRECO_mll500;
      eventHistos m_eventsPassResFSBRECO_mll550;
      eventHistos m_eventsPassResFSBRECO_mll600;

      eventHistos m_eventsPassBoostFSBLowMassCRRECO;
      eventHistos m_eventsPassBoostFSBLowMassCRRECO_failBox;
      eventHistos m_eventsPassBoostFSBLowMassCRRECO_oppoBox;
      eventHistos m_eventsPassBoostFSBRECO;
      eventHistos m_eventsPassBoostLowMassCRRECO;
      eventHistos m_eventsPassBoostZMASSRECO;

//      eventHistos m_eventsFailResFailBoostGEN_boostMod;
//      eventHistos m_eventsPassResPassBoostGEN_boostMod;
//      eventHistos m_eventsPassResFailBoostGEN_boostMod;
//      eventHistos m_eventsFailResPassBoostGEN_boostMod;
//
//      eventHistos m_eventsFailResFailBoostGEN_resMod;
//      eventHistos m_eventsPassResPassBoostGEN_resMod;
//      eventHistos m_eventsPassResFailBoostGEN_resMod;
//      eventHistos m_eventsFailResPassBoostGEN_resMod;

      //eventHistos m_eventsPassingFlavorSidebandRECOelePt50;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt100;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt150;
      //eventHistos m_eventsPassingFlavorSidebandRECO_noTrig;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt50_noISO;

      //eventHistos m_eventsPassingFlavorSidebandRECOelePt200_noISO;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt200_noISO_samesign;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt200_noISO_noTrig;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt200_noISO_samesign_noTrig;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt200_samesign;
      //eventHistos m_eventsPassingFlavorSidebandRECOelePt200_all;

//      eventHistos m_eventsPassingFlavorSidebandRECOelePt200_A;
//      eventHistos m_eventsPassingFlavorSidebandRECOelePt200_B;
//      eventHistos m_eventsPassingFlavorSidebandRECOelePt200_C;
//      eventHistos m_eventsPassingFlavorSidebandRECOelePt200_D;
//
//      eventHistos m_eventsPassingFlavorSidebandRECOres;

      int flavor;
      HEEP myHEEP;
      egammaEffi myEgammaEffi;
      eventInfo myEventInfo;
      Muons myMuons;
      Zweight myZweights;
      edm::EDGetToken m_genParticleToken;
      edm::EDGetToken m_genJetsToken;
      edm::EDGetToken m_AK8genJetsToken;
      edm::EDGetToken m_highMuonToken;
      edm::EDGetToken m_highElectronToken;
      edm::EDGetToken m_electronToken2;
      edm::EDGetToken m_eleIdFullInfoMapToken;
      edm::EDGetToken m_regMuonToken;
      edm::EDGetToken m_recoJetsToken;
      edm::EDGetToken m_AK4recoCHSJetsToken;
      edm::EDGetToken m_AK8recoCHSJetsToken;
      edm::EDGetToken m_PackedPFCandiates;
      edm::EDGetToken m_AK8recoPUPPIJetsToken;
      edm::EDGetToken m_AK8recoPUPPISubJetsToken;
      edm::EDGetToken JECName;
      edm::EDGetToken m_offlineVerticesToken;
      edm::EDGetToken m_genEventInfoToken;
      edm::EDGetToken m_metToken;
      edm::EDGetToken m_trigResultsToken;
      edm::EDGetToken m_trigObjsToken;
      edm::EDGetToken m_PUInfoToken;
      edm::EDGetToken m_rhoLabel;
      edm::EDGetToken LHEEventProductToken;
      edm::EDGetTokenT< double > prefweight_token;
      edm::EDGetTokenT< double > prefweightup_token;
      edm::EDGetTokenT< double > prefweightdown_token;
      bool m_wantHardProcessMuons;
      bool m_doGen;
      bool m_amcatnlo;
      bool m_doReco;
      bool m_isSignal;
      bool m_isMC;
      bool m_doTrig;
      bool m_doFast;
      bool m_checkZ;
      double m_MCL;    //MASS UPPER AND LOWER CUTS
      double m_MCU;

      bool m_foundZ;
      
      double m_highPTleptonCut = 60;
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
	  std::string m_era;

      FactorizedJetCorrector   *fJetCorr;
      JetCorrectionUncertainty *fJetUnc;

      JME::JetResolution resolution;
      JME::JetResolutionScaleFactor resolution_sf;
      JME::JetResolution resolution_AK4;
      JME::JetResolutionScaleFactor resolution_sf_AK4;

      std::vector< int > ScaleIDRange_, PDFErrorIDRange_, PDFAlphaSIDRange_;
      std::string PDFErrorType_;
      std::vector< double > PDFAlphaSScaleValue_;

      TRandom3* r;

      std::string cmsswPath;

};

//define this as a plug-in
DEFINE_FWK_MODULE(analyzeLastBin);
#endif
