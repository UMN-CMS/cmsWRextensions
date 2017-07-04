#include "eventHistos.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH2D.h"
//C++ CLASSES
#include <iostream>
////LOCAL CLASSES
#include "eventBits.h"
#include "tools.h"





eventHistos::eventHistos () {}




void eventHistos::book(TFileDirectory histoFolder, uint16_t flavor) {

  //CREATED FOLDER IN HISTO
  m_flavor = flavor;
  m_histoFolder = histoFolder;

  if (m_flavor == 1) {
  //MAKE GEN PLOTS
    m_parton1Et =                       m_histoFolder.make<TH1D>("parton1Et", "Parton 1 Et",                         100, 0.0, 8000);
    m_parton2Et =                       m_histoFolder.make<TH1D>("parton2Et", "Parton 2 Et",                         100, 0.0, 8000);
    m_muon1Et =                         m_histoFolder.make<TH1D>("muon1Et", "Muon 1 Et",                             100, 0.0, 8000);
    m_muon2Et =                         m_histoFolder.make<TH1D>("muon2Et", "Muon 2 Et",                             100, 0.0, 8000);

    m_parton1Eta =                      m_histoFolder.make<TH1D>("parton1Eta", "Parton 1 Eta",                        100, -4.0, 4.0);
    m_parton2Eta =                      m_histoFolder.make<TH1D>("parton2Eta", "Parton 2 Eta",                        100, -4.0, 4.0);
    m_muon1Eta =                        m_histoFolder.make<TH1D>("muon1Eta", "Muon 1 eta",                            100, -4.0, 4.0);
    m_muon2Eta =                        m_histoFolder.make<TH1D>("muon2Eta", "Muon 2 eta",                            100, -4.0, 4.0);
    m_firstPartonJetEta     =           m_histoFolder.make<TH1D>("firstPartonJetEta", "Jet 1 Eta",                    100, -4.0, 4.0);
    m_secondPartonJetEta    =           m_histoFolder.make<TH1D>("secondPartonJetEta", "Jet 2 Eta",                   100, -4.0, 4.0);
    m_firstPartonAK8JetEta  =           m_histoFolder.make<TH1D>("firstPartonAK8JetEta", "AK8Jet 1 Eta",              100, -4.0, 4.0); 
    m_secondPartonAK8JetEta =           m_histoFolder.make<TH1D>("secondPartonAK8JetEta", "AK8Jet 2 Eta",             100, -4.0, 4.0);

    m_parton1Phi             =          m_histoFolder.make<TH1D>("parton1Phi", "Parton 1 Phi",                        100, -4.0, 4.0);        
    m_parton2Phi             =          m_histoFolder.make<TH1D>("parton2Phi", "Parton 2 Phi",                        100, -4.0, 4.0);       
    m_muon1Phi               =          m_histoFolder.make<TH1D>("muon1Phi", "Muon 1 Phi",                            100, -4.0, 4.0);        
    m_muon2Phi               =          m_histoFolder.make<TH1D>("muon2Phi", "Muon 2 Phi",                            100, -4.0, 4.0);        
    m_firstPartonJetPhi      =          m_histoFolder.make<TH1D>("firstPartonJetPhi", "Jet 1 Phi",                    100, -4.0, 4.0);     
    m_secondPartonJetPhi     =          m_histoFolder.make<TH1D>("secondPartonJetPhi", "Jet 2 Phi",                   100, -4.0, 4.0);       
    m_firstPartonAK8JetPhi   =          m_histoFolder.make<TH1D>("firstPartonAK8JetPhi", "AK8Jet 1 Phi",              100, -4.0, 4.0);        
    m_secondPartonAK8JetPhi  =          m_histoFolder.make<TH1D>("secondPartonAK8JetPhi", "AK8Jet 1 Phi",             100, -4.0, 4.0);           

    m_dRparton1parton2 =                m_histoFolder.make<TH1D>("dRparton1parton2", "deltaR between partons",             100, 0.0, 12.0);
    m_dRmuon1muon2 =                    m_histoFolder.make<TH1D>("dRmuon1muon2", "deltaR between muons",                   100, 0.0, 12.0);
    m_dRparton1muon2 =                  m_histoFolder.make<TH1D>("dRparton1muon2", "deltaR between parton1 and muon2",     100, 0.0, 12.0);
    m_dRparton1muon1 =                  m_histoFolder.make<TH1D>("dRparton1muon1", "deltaR between parton1 and muon1",     100, 0.0, 12.0);
    m_dRparton2muon2 =                  m_histoFolder.make<TH1D>("dRparton2muon2", "deltaR between parton2 and muon2",     100, 0.0, 12.0);
    m_dRparton2muon1 =                  m_histoFolder.make<TH1D>("dRparton2muon1", "deltaR between parton2 and muon1",     100, 0.0, 12.0);
    m_dRparton1jet =                    m_histoFolder.make<TH1D>("dRparton1jet", "deltaR between parton1 and closest jet", 100, 0.0, 12.0);
    m_dRparton2jet =                    m_histoFolder.make<TH1D>("dRparton2jet", "deltaR between parton2 and closest jet", 100, 0.0, 12.0);

    m_firstPartonJetEt =                m_histoFolder.make<TH1D>("firstPartonJetEt", " Jet Et for Leading Parton",            100,0.0,8000);
    m_secondPartonJetEt =               m_histoFolder.make<TH1D>("secondPartonJetEt"," Jet Et for Subleading Parton",         100,0.0,8000);
    m_firstPartonJetEtHadronic =        m_histoFolder.make<TH1D>("firstPartonJetEtHadronic", "Hadronic Jet Et for Leading Parton",      100,0.0,8000);
    m_secondPartonJetEtHadronic =       m_histoFolder.make<TH1D>("secondPartonJetEtHadronic","Hadronic Jet Et for Subleading Parton",   100,0.0,8000);
    m_firstPartonJetEtEM =              m_histoFolder.make<TH1D>("firstPartonJetEtEM", "EM Jet Et for Leading Parton",                  100,0.0,8000);
    m_secondPartonJetEtEM =             m_histoFolder.make<TH1D>("secondPartonJetEtEM","EM Jet Et for Subleading Parton",               100,0.0,8000);
    m_firstPartonJetEtInvisible =       m_histoFolder.make<TH1D>("firstPartonJetEtInvisible", "Invisible Jet Et for Leading Parton",    100,0.0,8000);
    m_secondPartonJetEtInvisible =      m_histoFolder.make<TH1D>("secondPartonJetEtInvisible","Invisible Jet Et for Subleading Parton", 100,0.0,8000);

    m_firstPartonAK8JetEt =             m_histoFolder.make<TH1D>("firstPartonAK8JetEt", " AK8Jet Et for Leading Parton",            100,0.0,8000);
    m_secondPartonAK8JetEt =            m_histoFolder.make<TH1D>("secondPartonAK8JetEt"," AK8Jet Et for Subleading Parton",         100,0.0,8000);
    m_firstPartonAK8JetEtHadronic =     m_histoFolder.make<TH1D>("firstPartonAK8JetEtHadronic", "Hadronic AK8Jet Et for Leading Parton",      100,0.0,8000);
    m_secondPartonAK8JetEtHadronic =    m_histoFolder.make<TH1D>("secondPartonAK8JetEtHadronic","Hadronic AK8Jet Et for Subleading Parton",   100,0.0,8000);
    m_firstPartonAK8JetEtEM =           m_histoFolder.make<TH1D>("firstPartonAK8JetEtEM", "EM AK8Jet Et for Leading Parton",                  100,0.0,8000);
    m_secondPartonAK8JetEtEM =          m_histoFolder.make<TH1D>("secondPartonAK8JetEtEM","EM AK8Jet Et for Subleading Parton",               100,0.0,8000);
    m_firstPartonAK8JetEtInvisible =    m_histoFolder.make<TH1D>("firstPartonAK8JetEtInvisible", "Invisible AK8Jet Et for Leading Parton",    100,0.0,8000);
    m_secondPartonAK8JetEtInvisible =   m_histoFolder.make<TH1D>("secondPartonAK8JetEtInvisible","Invisible AK8Jet Et for Subleading Parton", 100,0.0,8000);


    m_leadSubleadingJetsMuonsMass  =    m_histoFolder.make<TH1D>("leadingSubleadingJetsMuonsMass","Four Object Mass of the 2 leading Jets and Muons",      100, 0.0,8000);
    m_leadSubleadingAK8JetsMuonsMass  = m_histoFolder.make<TH1D>("leadingSubleadingAK8JetsMuonsMass","Four Object Mass of the 2 leading AK8Jets and Muons",100, 0.0,8000);
    m_leadSubleadingPartonsMuonsMass  = m_histoFolder.make<TH1D>("leadingSubleadingPartonsMuonsMass","Four Object Mass of the 2 leading Partons and Muons",100, 0.0,8000);
    m_leadAK8JetMuonMass  =             m_histoFolder.make<TH1D>("leadAK8JetMuonMass","2 Object Mass of the leading Jet and Muon"                         ,100, 0.0,8000);

    m_leadSubleadingJetsMuonsPt  =      m_histoFolder.make<TH1D>("leadingSubleadingJetsMuonsPt","Four Object Pt of the 2 leading Jets and Muons",          100, 0.0,8000);
    m_leadSubleadingAK8JetsMuonsPt  =   m_histoFolder.make<TH1D>("leadingSubleadingAK8JetsMuonsPt","Four Object Pt of the 2 leading AK8Jets and Muons",    100, 0.0,8000);
    m_leadSubleadingPartonsMuonsPt  =   m_histoFolder.make<TH1D>("leadingSubleadingPartonsMuonsPt","Four Object Pt of the 2 leading Partons and Muons",    100, 0.0,8000);
    m_leadAK8JetMuonPt  =               m_histoFolder.make<TH1D>("leadAK8JetMuonPt","2 Object Pt of the leading Jet and Muon"                             ,100, 0.0,8000);

    m_leadSubleadingJetsMuonsEta  =     m_histoFolder.make<TH1D>("leadingSubleadingJetsMuonsEta","Four Object Eta of the 2 leading Jets and Muons",        100, -4.0,4.0);
    m_leadSubleadingAK8JetsMuonsEta  =  m_histoFolder.make<TH1D>("leadingSubleadingAK8JetsMuonsEta","Four Object Eta of the 2 leading AK8Jets and Muons",  100, -4.0,4.0);
    m_leadSubleadingPartonsMuonsEta  =  m_histoFolder.make<TH1D>("leadingSubleadingPartonsMuonsEta","Four Object Eta of the 2 leading Partons and Muons",  100, -4.0,4.0);
    m_leadAK8JetMuonEta  =              m_histoFolder.make<TH1D>("leadAK8JetMuonEta","2 Object Eta of the leading Jet and Muon"                           ,100, -4.0,4.0);

    m_EtPlacementMuon2 =                m_histoFolder.make<TH1D>("EtPlacementMuon2", "Et ranking idx of muon 2",                                           10, 0, 10);
    m_nJets =                           m_histoFolder.make<TH1D>("nJets", "# of matched jets",                                                             10, 0, 10);
    m_nAK8Jets =                        m_histoFolder.make<TH1D>("nAK8Jets", "# of matched AK8Jets",                                                       10, 0, 10);



  } else if (m_flavor == 2) {
  //MAKE RECO PLOTS




  } else if (m_flavor == 3) {
  //MAKE GEN & RECO PLOTS


  } else {
  //NOTHING FOR NOW
  }


}
void eventHistos::fill(eventBits& event) {
  if(m_flavor == 1) fillGen(event);
  else if(m_flavor == 2) fillReco(event);
  else if(m_flavor == 3) {
    fillGen(event);
    fillReco(event);
  }
  else return;
}

//SPECIFIC 
void eventHistos::fillGen(eventBits& event) {
  std::cout << "Making GEN plots" << std::endl;
  if(!(event.passesGenCuts())) {
    std::cout << "ERROR! THIS EVENT SHOULD HAVE FAILED" <<std::endl;
    return;
  }
//  std::cout << "Filling Event plots" << std::endl;
  m_parton1Et->Fill(event.parton1EtVal);
  m_parton2Et->Fill(event.parton2EtVal);
  m_muon1Et->Fill(event.muon1EtVal);
  m_muon2Et->Fill(event.muon2EtVal);
  m_firstPartonJetEt->Fill(event.firstPartonJetEtVal);
  m_secondPartonJetEt->Fill(event.secondPartonJetEtVal);
  m_firstPartonAK8JetEt->Fill(event.firstPartonAK8JetEtVal);
  m_secondPartonAK8JetEt->Fill(event.secondPartonAK8JetEtVal);
//  std::cout << "FILLING 1"<<std::endl;

  m_parton1Eta->Fill(event.parton1EtaVal);
  m_parton2Eta->Fill(event.parton2EtaVal);
  m_muon1Eta->Fill(event.muon1EtaVal);
  m_muon2Eta->Fill(event.muon2EtaVal);
  m_firstPartonJetEta->Fill(event.firstPartonJetEtaVal);
  m_secondPartonJetEta->Fill(event.secondPartonJetEtaVal);
  m_firstPartonAK8JetEta->Fill(event.firstPartonAK8JetEtaVal);
  m_secondPartonAK8JetEta->Fill(event.secondPartonAK8JetEtaVal);
  //std::cout << "FILLING 2"<<std::endl;

  m_parton1Phi->Fill(event.parton1PhiVal);
  m_parton2Phi->Fill(event.parton2PhiVal);
  m_muon1Phi->Fill(event.muon1PhiVal);
  m_muon2Phi->Fill(event.muon2PhiVal);
  m_firstPartonJetPhi->Fill(event.firstPartonJetPhiVal);
  m_secondPartonJetPhi->Fill(event.secondPartonJetPhiVal);
  m_firstPartonAK8JetPhi->Fill(event.firstPartonAK8JetPhiVal);
  m_secondPartonAK8JetPhi->Fill(event.secondPartonAK8JetPhiVal);
//  std::cout << "FILLING 3"<<std::endl;

  m_dRparton1parton2->Fill(event.dRparton1parton2Val);
  m_dRmuon1muon2->Fill(event.dRmuon1muon2Val);
  m_dRparton1muon2->Fill(event.dRparton1muon2Val);
  m_dRparton1muon1->Fill(event.dRparton1muon1Val);
  m_dRparton2muon2->Fill(event.dRparton2muon2Val);
  m_dRparton2muon1->Fill(event.dRparton2muon1Val);
  m_dRparton1jet->Fill(event.dRparton1jetVal);
  m_dRparton2jet->Fill(event.dRparton2jetVal);
  //std::cout << "FILLING 4"<<std::endl;



  m_firstPartonJetEtHadronic->Fill(event.firstPartonJetEtHadronicVal);
  m_secondPartonJetEtHadronic->Fill(event.secondPartonJetEtHadronicVal);
  m_firstPartonJetEtEM->Fill(event.firstPartonJetEtEMVal);
  m_secondPartonJetEtEM->Fill(event.secondPartonJetEtEMVal);
  m_firstPartonJetEtInvisible->Fill(event.firstPartonJetEtInvisibleVal);
  m_secondPartonJetEtInvisible->Fill(event.secondPartonJetEtInvisibleVal);
  //std::cout << "FILLING 5"<<std::endl;
  

  m_firstPartonAK8JetEtHadronic->Fill(event.firstPartonAK8JetEtHadronicVal);
  m_secondPartonAK8JetEtHadronic->Fill(event.secondPartonAK8JetEtHadronicVal);
  m_firstPartonAK8JetEtEM->Fill(event.firstPartonAK8JetEtEMVal);
  m_secondPartonAK8JetEtEM->Fill(event.secondPartonAK8JetEtEMVal);
  m_firstPartonAK8JetEtInvisible->Fill(event.firstPartonAK8JetEtInvisibleVal);
  m_secondPartonAK8JetEtInvisible->Fill(event.secondPartonAK8JetEtInvisibleVal);
  //std::cout << "FILLING 6"<<std::endl;

  m_leadSubleadingPartonsMuonsMass->Fill(event.leadSubleadingPartonsMuonsMassVal);
  m_leadSubleadingJetsMuonsMass->Fill(event.leadSubleadingJetsMuonsMassVal);
  m_leadSubleadingAK8JetsMuonsMass->Fill(event.leadSubleadingAK8JetsMuonsMassVal);
  m_leadAK8JetMuonMass->Fill(event.leadAK8JetMuonMassVal);
 // std::cout << "FILLING 7"<<std::endl;

  m_leadSubleadingJetsMuonsPt->Fill(event.leadSubleadingJetsMuonsPtVal);
  m_leadSubleadingPartonsMuonsPt->Fill(event.leadSubleadingPartonsMuonsPtVal);
  m_leadSubleadingAK8JetsMuonsPt->Fill(event.leadSubleadingAK8JetsMuonsPtVal);
  m_leadAK8JetMuonPt->Fill(event.leadAK8JetMuonPtVal);
 // std::cout << "FILLING 8"<<std::endl;

  m_leadSubleadingJetsMuonsEta->Fill(event.leadSubleadingJetsMuonsEtaVal);
  m_leadSubleadingPartonsMuonsEta->Fill(event.leadSubleadingPartonsMuonsEtaVal);
  m_leadSubleadingAK8JetsMuonsEta->Fill(event.leadSubleadingAK8JetsMuonsEtaVal);
  m_leadAK8JetMuonEta->Fill(event.leadAK8JetMuonEtaVal);
 // std::cout << "FILLING 9"<<std::endl;

  m_EtPlacementMuon2->Fill(event.secondInDecayMuon);
  m_nJets->Fill(event.myGenJets.size());
  m_nAK8Jets->Fill(event.myAK8GenJets.size());
}
void eventHistos::fillReco(eventBits& event) {


}
