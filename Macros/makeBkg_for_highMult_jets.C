#include "../include/1d2d_constants.h"

void makeBkg_for_highMult_jets(){
    gRandom->SetSeed(0);
    int ptbinbounds[2]={3,5};

    TH2D* hSignal[trackbin][2];//Ntrk,pt
    TH2D* hBckrndShiftedCor[trackbin][2];
    TH2D* hEPDrawCor[trackbin][2];
    TH2D* hPairs;
    TH1D* hJetPass;
    //TFile* f= new TFile("/Users/xl155/Documents/JetFlow_Run3_data/ana_run3.root","READ");
    //TFile* f= new TFile("/Users/xl155/Documents/JetFlow_Run3_data/output_parkersbin.root","READ");
    //TFile* f= new TFile("/Users/xl155/Documents/JetFlow_Run3_data/ana_run3_allNch.root","READ");
    //TFile* f= new TFile("../Dokumente/ana_run3_hlt500_highnch.root","READ");
    //TFile* f= new TFile("../Dokumente/ana_Run2_83bin.root","READ");
    //TFile* f= new TFile("../Dokumente/ana_run2_allNch_MC.root","READ");
    TFile* f= new TFile("/home/tk/MeinJet/Dokumente/ana_Run2_gebrocheneKlassen.root","READ");

    hPairs=(TH2D*)f->Get("hPairs");
    hJetPass = (TH1D*)f->Get("hJet_Pass550");
    
    for(int i=0;i<trackbin;i++){
        for(int j=0;j<2;j++){
            hSignal[i][j]=(TH2D*)f->Get(Form("hSigS_Cor_%d_to_%d_and_%d_to_30_w_PU_1",trackbinbounds[i],trackbinboundsUpper[i],ptbinbounds[j]));
            hSignal[i][j]->SetName(Form("hSigS_Cor_%d_to_%d_and_%d_to_30_w_PU_1",trackbinbounds[i],trackbinboundsUpper[i],ptbinbounds[j]));
            hEPDrawCor[i][j]=(TH2D*)f->Get(Form("hEPD_Cor_%d_to_%d_and_%d_to_30_w_PU_1",trackbinbounds[i],trackbinboundsUpper[i],ptbinbounds[j]));
            hBckrndShiftedCor[i][j]=(TH2D*)f->Get(Form("hBckS_Cor_%d_to_%d_and_%d_to_30_w_PU_1",trackbinbounds[i],trackbinboundsUpper[i],ptbinbounds[j]));
            hBckrndShiftedCor[i][j]->SetName(Form("hBckS_Cor_%d_to_%d_and_%d_to_30_w_PU_1",trackbinbounds[i],trackbinboundsUpper[i],ptbinbounds[j]));
            if(i>6){
                hBckrndShiftedCor[i][j]->Reset();
            }
        }
    }
    
    int backMult =10;
    for(int wtrk = 8; wtrk < trackbin+1; wtrk++){
        std::cout << wtrk << "/" << trackbin << std::endl;
        for(int wppt = 1; wppt < 3; wppt++){ 
            std::cout << wppt << "/" << ptbin << std::endl;
            //Nent is the number of pairs in the signal which we will try to 10x
            //Xent is the number of pseudoparticles requried such that when we build the pairs nCp = Xent CHOOSE 2 will give 
            //us 10 times as many pairs as we have in the signal histogrm.

            //long int NENT =  hPairsPU[wpPU-1]->GetBinContent(wtrk, wppt);
            long int NENT =  hPairs->GetBinContent(wtrk, wppt);
            //long int NENT =  10;
            //long int XENT =  ((1+floor(sqrt(1+(4*2*backMult*NENT))))/2) ;
            long int XENT =  floor((1+sqrt(1+(4*2*backMult*NENT)))/2) ;
            //float A_ETA[XENT] = {0};
            //float A_PHI[XENT] = {0};
            std::vector<float> A_PHI_Cor(XENT, 0.0f);
            std::vector<float> A_ETA_Cor(XENT, 0.0f);
            //float A_ETA_Cor[XENT] = {0};
            //float A_PHI_Cor[XENT] = {0};
            for(int x = 0; x<XENT; x++){
                double WEta1_Cor, WPhi1_Cor;//making the pseudoparticles
                hEPDrawCor[wtrk-1][wppt-1]->GetRandom2(WEta1_Cor, WPhi1_Cor);
                A_ETA_Cor[x] = WEta1_Cor;
                A_PHI_Cor[x] = WPhi1_Cor;
            }
            for(long int i = 0; i < (XENT-1); i++){
                for(long int j = (i+1); j < XENT; j++){
                    double WdeltaEta_Cor = (A_ETA_Cor[i]-A_ETA_Cor[j]);
                    double WdeltaPhi_Cor = (TMath::ACos(TMath::Cos(A_PHI_Cor[i]-A_PHI_Cor[j])));
                    hBckrndShiftedCor[wtrk-1][wppt-1]->Fill(WdeltaEta_Cor, WdeltaPhi_Cor,   1);//./XENT);
                    hBckrndShiftedCor[wtrk-1][wppt-1]->Fill(-WdeltaEta_Cor, WdeltaPhi_Cor,  1);//./XENT);
                    hBckrndShiftedCor[wtrk-1][wppt-1]->Fill(WdeltaEta_Cor, -WdeltaPhi_Cor,  1);//./XENT);
                    hBckrndShiftedCor[wtrk-1][wppt-1]->Fill(-WdeltaEta_Cor, -WdeltaPhi_Cor, 1);//./XENT);
                    hBckrndShiftedCor[wtrk-1][wppt-1]->Fill(WdeltaEta_Cor, 2*TMath::Pi() - WdeltaPhi_Cor, 1);//./XENT);
                    hBckrndShiftedCor[wtrk-1][wppt-1]->Fill(-WdeltaEta_Cor,2*TMath::Pi() - WdeltaPhi_Cor, 1);//./XENT);
                }
            }
        }
    }

    //TFile* fout= new TFile("/Users/xl155/Documents/JetFlow_Run3_data/output_parkersbin_newBkg_for_high_Nch.root","RECREATE");
    TFile* fout= new TFile("/home/tk/MeinJet/Dokumente/ana_Run2_gebrocheneKlassen_newBkg_for_high_Nch.root","RECREATE");
    
    for(int i=0;i<trackbin;i++){
        for(int j=0;j<2;j++){
            hBckrndShiftedCor[i][j]->Write();
            hSignal[i][j]->Write();
        }
    }
    hJetPass->Write(); 

    f->Close();
    delete f;
    fout->Close();
    delete fout;
     



}
