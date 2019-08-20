#include "trees.h"
#include "TMatrixDSym.h"
#include "TFitResult.h"

ofstream out;

int main(/*int argc, char* argv[]*/) {
  
    //TString arg = argv[1];
    //int counter_min = arg.Atoi();
       
    cout << " " << endl;    
    
    create_tree();
    
    read_tree();
}

void create_tree(){
    
    cout << " Creating a root tree and saving it to a file ... " << endl;    
    
    TFile* file = TFile::Open("file_TLV.root","RECREATE");
    
    file->SetCompressionLevel(1);
      
    TTree *tree = new TTree("tree", "tree");
    
    double pt(0.0);
    double mass(0.0);
    double eta(0.0);
    double phi(0.0);

    // Function to generate random gaussian points
    TF1 * pt_rand = new TF1("pt_rand", "gaus", 0.0, 500.0);
    pt_rand->SetParameters(10., 15.5, 10.8);
    
    TF1 * mass_rand = new TF1("mass_rand", "gaus", 110.0, 130.0);
    mass_rand->SetParameters(10., 125.5, 0.004);
    
    TF1 * eta_rand = new TF1("eta_rand", "gaus", -5.0, 5.0);
    eta_rand->SetParameters(10., 0.0, 1.0);
    
    TF1 * phi_rand = new TF1("phi_rand", "[0]", -3.1416, 3.1416);
    phi_rand->SetParameter(0., 10.0);
    
    TLorentzVector * fvect = 0; 
    
    tree->Branch("fvect", "TLorentzVector", &fvect);
    
    for(int i = 0; i<1000; ++i){
    
        pt = pt_rand->GetRandom();
        mass = mass_rand->GetRandom();
        eta = eta_rand->GetRandom();
        phi = phi_rand->GetRandom();
        
        fvect->SetPtEtaPhiM(pt, eta, phi, mass);

        tree->Fill();
    }
        
    file->cd();
    
    tree->Write();
    
    delete tree;
    
    file->Close();
}

void read_tree(){
    
    cout << " Creating a root tree and saving it to a file ... " << endl;    
    
    TFile* file = TFile::Open("file_TLV.root"); 
      
    TTree *tree = (TTree*) file->Get("tree");
    
    TLorentzVector * fvect = 0; 
  
    tree->SetBranchAddress("fvect", &fvect); // 1.0
    
    tree->Print();
    
    for(Long64_t i = 0; i<10; ++i){
    
        tree->GetEntry(i);
        
        cout << " fvect->Eta() = " << fvect->Eta() << endl;

        cout << " fvect->Pt() = " << fvect->Pt() << endl;
    }
    
    delete tree;
    
    file->Close();
}
