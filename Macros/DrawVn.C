#include "../include/headers.h"
#include "../include/1d2d_constants.h"

void DrawVn(TString era = "22C"){
    TH2D* hSignal[trackbin][2];//Ntrk,pt
    TH2D* hBkg[trackbin][2];
    TH1D* h1DFlow[trackbin][2];
    TH1D* hBinDist[trackbin];

    //TFile *f = new TFile("../Dokumente/ana_run3_allNch_20" + era + "_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("../Dokumente/ana_run3_allNch_20" + era + ".root", "READ");
    //TFile *f = new TFile("../Dokumente/ana_run2_allNch_MC_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("../Dokumente/ana_run2_allNch_MC.root", "READ");
    //TFile *f = new TFile("../Dokumente/ana_Run2_3bins_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("../Dokumente/ana_Run2_3bins.root", "READ");
    //TFile *f = new TFile("../Dokumente/ana_run2_allNch_MC_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("../Dokumente/ana_run2_allNch_MC.root", "READ");
    TFile *f = new TFile("../Dokumente/ana_run3_hlt500_newBkg.root", "READ");
    TFile *fstat = new TFile("../Dokumente/ana_run3_hlt500_3ass.root", "READ");
    //TFile *f = new TFile("/home/tk/MeinJet/Dokumente/ana_run3_hlt500_highnch_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("/home/tk/MeinJet/Dokumente/ana_run3_hlt500_highnch.root", "READ");
    //TFile *f = new TFile("../Dokumente/ana_Run2_83bin_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("../Dokumente/ana_Run2_83bin.root", "READ");
    //TFile *f = new TFile("/home/tk/MeinJet/Dokumente/new_default_complete_vn_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("/home/tk/MeinJet/Dokumente/new_default_complete_vn.root", "READ");
    
    //TFile *f = new TFile("/home/tk/MeinJet/Dokumente/ana_Run2_gebrocheneKlassen_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("/home/tk/MeinJet/Dokumente/ana_Run2_gebrocheneKlassen.root", "READ");

    //int   trackbinbounds[5]= {76,78,80,81,82};
    int ptbinbounds[2]={3,5};
    
    float ptname[2]={0.3,0.5};
    int YPlo=28; //2.0
    int YPhi=34; //4.0
    TH1D* hJetPass = (TH1D*)f->Get("hJet_Pass550");
    //TH1D* hJetPass = (TH1D*)f->Get("hJet_Pass550_hltCor");
    
    double mAve_Nch[trackbin];
    double mAve_Nch_err[trackbin];
    double mFit_par[2][5][trackbin];
    double mFit_par_err[2][5][trackbin];
    double v2[2][trackbin];
    double v2_err[2][trackbin];

    //for(int i=0;i<5;i++){
    for(int i=0;i<trackbin;i++){
        hBinDist[i]=(TH1D*)fstat->Get(Form("hBinDist_cor_%d",i+1)); 
        mAve_Nch[i]=hBinDist[i]->GetMean();
        cout<<"mAve: "<<mAve_Nch[i]<<endl;
        mAve_Nch_err[i]=0.0;

        for(int j=0;j<2;j++){
            //hSignal[i][j]=(TH2D*)f->Get(Form("hSigS_Cor_%d_to_1000_and_%d_to_30_w_PU_1",trackbinbounds[i],ptbinbounds[j]));
            //hBkg[i][j]=(TH2D*)f_bkg->Get(Form("hBckS_Cor_%d_to_1000_and_%d_to_30_w_PU_1",trackbinbounds[i],ptbinbounds[j]));

            hSignal[i][j]=(TH2D*)f->Get(Form("hSigS_Cor_%d_to_%d_and_%d_to_30_w_PU_1",trackbinbounds[i],trackbinboundsUpper[i],ptbinbounds[j]));
            hBkg[i][j]=(TH2D*)f->Get(Form("hBckS_Cor_%d_to_%d_and_%d_to_30_w_PU_1",trackbinbounds[i],trackbinboundsUpper[i],ptbinbounds[j]));
            
            //h2DCorr[i][j]=(TH2D*)hSignal[i][j]->Clone(Form("h2DCorr_Cor_%d_to_1000_and_%d_to_30_w_PU_1",trackbinbounds[i],ptbinbounds[j]));
            //h2DCorr[i][j]->Reset();
            double eta_bw=hSignal[i][j]->GetXaxis()->GetBinWidth(1);//x:delta eta; y:delta phi
            double phi_bw=hSignal[i][j]->GetYaxis()->GetBinWidth(1);

            hSignal[i][j]->Scale(1.0/(hJetPass->GetBinContent(i+1,j+1)));
            hSignal[i][j]->Scale(1./(phi_bw));

            TH1D *histfit1 = (TH1D*) hSignal[i][j]->ProjectionY("",YPlo,YPhi)->Clone();
            TH1D *histfit2 = (TH1D*) hBkg[i][j]->ProjectionY("",YPlo,YPhi)->Clone();

            histfit1->Divide(histfit2);
            histfit1->Scale(hBkg[i][j]->GetMaximum());

            h1DFlow[i][j]=(TH1D*)histfit1->Clone(); 
            std::string function = "[0]/(TMath::Pi()*2)*(1+2*([1]*TMath::Cos(x)+[2]*TMath::Cos(2*x)+[3]*TMath::Cos(3*x)))";//+[4]*TMath::Cos(4*x)+[5]*TMath::Cos(5*x)))";
            TF1 func1("deltaPhi1", function.c_str(), -0.5*TMath::Pi(), 1.5*TMath::Pi());
            func1.SetParameter(0, histfit1->GetMaximum());
            func1.SetParameter(1, 0.1);
            func1.SetParameter(2, 0.1);
            func1.SetParameter(3, 0.1);
            // func1.SetParameter(4, 0.1);
            // func1.SetParameter(5, 0.1);
            h1DFlow[i][j]->Fit(&func1, "m E q");

            for(int ip=0;ip<3;ip++){
                mFit_par[j][ip][i]=func1.GetParameter(ip+1);
                mFit_par_err[j][ip][i]=func1.GetParError(ip+1);
                mFit_par_err[j][ip][i]*=sqrt(2);

                if(ip == 1)
                {
                    v2[j][i] = sqrt(mFit_par[j][1][i]);
                    v2_err[j][i] = mFit_par_err[j][1][i] / v2[j][i] / 2;
                    if (j==0) cout<<"v2: "<<v2[j][i]<<endl;
                    if (j==0) cout<<"v2_err: "<<v2_err[j][i]<<endl;
                }
            } 

            // Set the histogram title
            //h1DFlow[i][j]->SetTitle(Form("Nch>%d, %.2f<jT<3 GeV/c",trackbinbounds[i],ptname[j]));
            h1DFlow[i][j]->SetTitle(Form("%d<Nch<%d, %.2f<jT<3 GeV/c",trackbinbounds[i],trackbinboundsUpper[i],ptname[j]));
             
        }
    }

    int color[5]={632,419,600,800,616};

    TGraphErrors* gVn[2][3];
    TGraphErrors *gv2[2];
    for (int j = 0; j < 2; j++)
    {
        for (int ip = 0; ip < 3; ip++)
        {
            gVn[j][ip]=new TGraphErrors(trackbin,mAve_Nch,mFit_par[j][ip],mAve_Nch_err,mFit_par_err[j][ip]);
            gVn[j][ip]->SetMarkerStyle(20);
            gVn[j][ip]->SetMarkerSize(0.8);
            gVn[j][ip]->SetLineColor(color[ip]);
            gVn[j][ip]->SetMarkerColor(color[ip]);

            if(ip == 1)
            {
                gv2[j] = new TGraphErrors(trackbin, mAve_Nch, v2[j], mAve_Nch_err, v2_err[j]);
                gv2[j]->SetMarkerStyle(20);
                gv2[j]->SetMarkerSize(0.8);
            }
        }
    }

    TLegend *leg = new TLegend(.7, .15, .85, .35, "");
    leg->AddEntry(gVn[0][0], "n=1");
    leg->AddEntry(gVn[0][1], "n=2");
    leg->AddEntry(gVn[0][2], "n=3");

    TLine* l1=new TLine(12.0,0.0,103.0,0.0);
    TCanvas* cVn=new TCanvas("cVn","cVn",600,500);
    gVn[0][1]->Draw("AP");
    gVn[0][1]->SetTitle("Run 2");
    gVn[0][1]->GetXaxis()->SetTitle("N_{ch}^{j}");
    //gVn[0][1]->GetXaxis()->SetRange(5,95); 
    gVn[0][1]->GetYaxis()->SetTitle("V^{*}_{n#Delta}{2,|#Delta#eta^{*}|>2}"); 
    gVn[0][1]->GetYaxis()->SetTitleOffset(1.2); 
    gVn[0][1]->SetMaximum(0.1);
    gVn[0][1]->SetMinimum(-0.27);
    gVn[0][0]->Draw("P");
    gVn[0][2]->Draw("P");
    l1->Draw("same");
    leg->Draw("same");
    //cVn->SaveAs("../Figuren/Vn/Vn_vs_Nch_Run2_83bin.pdf");
    //cVn->SaveAs("../Figuren/Vn/Vn_vs_Nch_Run2_83bin.png");

    TFile *fOut = new TFile("../Results/Vn/Vn_vs_Nch_Run3.root", "recreate");
    gVn[0][0]->Write("V1");
    gVn[0][1]->Write("V2");
    gVn[0][2]->Write("V3");
    gv2[0]->Write("v2");
    fOut->Close();

    /* 
    TCanvas *c1 = new TCanvas("canvas", "Fourier Series Fits", 800, 1200);
    c1->Divide(2, 5); // Divide canvas into 2 columns and 5 rows
    for(int i=0;i<5;i++){
        for(int j=0;j<2;j++){
            c1->cd(i*2+j+1);
            h1DFlow[i][j]->Draw();
        }
    } 
    c1->SaveAs("/Users/xl155/Documents/JetFlow_Run3_data/Flow_run3_allNch_2023_2024.pdf(");
    //c1->SaveAs("/Users/xl155/Documents/JetFlow_Run3_data/Flow_run2_unc_new.pdf(");

    TCanvas *c2 = new TCanvas("canvas", "Fourier Series Fits", 800, 1200);
    c2->Divide(2, 5); // Divide canvas into 2 columns and 5 rows
    for(int i=0;i<5;i++){
        for(int j=0;j<2;j++){
            c2->cd(i*2+j+1);
            h1DFlow[i+5][j]->Draw();
        }
    } 
    c2->SaveAs("/Users/xl155/Documents/JetFlow_Run3_data/Flow_run3_allNch_2023_2024.pdf)");
    //c2->SaveAs("/Users/xl155/Documents/JetFlow_Run3_data/Flow_run2_unc_new.pdf)");
    */
    f->Close();
    delete f;
}
