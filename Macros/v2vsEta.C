#include "../include/headers.h"
#include "../include/1d2d_constants.h"

void v2vsEta(){
    TH2D* hSignal[trackbin][2];//Ntrk,pt
    TH2D* hBkg[trackbin][2];
    TH1D* h1DFlow[trackbin][2];
    TH1D* hBinDist[trackbin];

    TFile *f = new TFile("/home/tk/MeinJet/Dokumente/ana_run2_basicAna_hlt_100times_newBkg.root", "READ");
    TFile *fstat = new TFile("/home/tk/MeinJet/Dokumente/ana_run2_basicAna_hlt.root", "READ");
    //TFile *f = new TFile("../Dokumente/ana_Run2_83bin_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("../Dokumente/ana_Run2_83bin.root", "READ");
    //TFile *f = new TFile("/home/tk/MeinJet/Dokumente/new_default_complete_vn_newBkg_for_high_Nch.root", "READ");
    //TFile *fstat = new TFile("/home/tk/MeinJet/Dokumente/new_default_complete_vn.root", "READ");

    //int   trackbinbounds[5]= {76,78,80,81,82};
    int ptbinbounds[2]={3,5};
    float ptname[2]={0.3,0.5};
    const int detabins = 11;
    double detacuts[detabins] = {0,0.3,0.6,0.9,1.1,1.4, 1.7, 2.0, 2.3, 2.6,2.9};
    TH1D* hJetPass = (TH1D*)f->Get("hJet_Pass550");
    //TH1D* hJetPass = (TH1D*)f->Get("hJet_Pass550_hltCor");
    
    double mAve_Nch[trackbin];
    double mAve_Nch_err[trackbin];
    double mFit_par[2][5][trackbin][detabins];
    double mFit_par_err[2][5][trackbin][detabins];
    double v2[2][trackbin][detabins];
    double v2_err[2][trackbin][detabins];

    for (int n = 0; n < detabins; n++)
    {
        for (int i = 0; i < trackbin; i++)
        {
            hBinDist[i] = (TH1D *)fstat->Get(Form("hBinDist_cor_%d", i + 1));
            mAve_Nch[i] = hBinDist[i]->GetMean();
            //cout << "mAve: " << mAve_Nch[i] << endl;
            mAve_Nch_err[i] = 0.0;

            for (int j = 0; j < 2; j++)
            {
                // hSignal[i][j]=(TH2D*)f->Get(Form("hSigS_Cor_%d_to_1000_and_%d_to_30_w_PU_1",trackbinbounds[i],ptbinbounds[j]));
                // hBkg[i][j]=(TH2D*)f_bkg->Get(Form("hBckS_Cor_%d_to_1000_and_%d_to_30_w_PU_1",trackbinbounds[i],ptbinbounds[j]));

                hSignal[i][j] = (TH2D *)f->Get(Form("hSigS_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));
                hBkg[i][j] = (TH2D *)f->Get(Form("hBckS_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));

                // h2DCorr[i][j]=(TH2D*)hSignal[i][j]->Clone(Form("h2DCorr_Cor_%d_to_1000_and_%d_to_30_w_PU_1",trackbinbounds[i],ptbinbounds[j]));
                // h2DCorr[i][j]->Reset();
                double eta_bw = hSignal[i][j]->GetXaxis()->GetBinWidth(1); // x:delta eta; y:delta phi
                double phi_bw = hSignal[i][j]->GetYaxis()->GetBinWidth(1);

                hSignal[i][j]->Scale(1.0 / (hJetPass->GetBinContent(i + 1, j + 1)));
                hSignal[i][j]->Scale(1. / (phi_bw));

                int YPlo = hSignal[i][j]->GetXaxis()->FindBin(detacuts[n]);

                TH1D *histfit1 = (TH1D *)hSignal[i][j]->ProjectionY("", YPlo, -1)->Clone();
                TH1D *histfit2 = (TH1D *)hBkg[i][j]->ProjectionY("", YPlo, -1)->Clone();

                histfit1->Divide(histfit2);
                histfit1->Scale(hBkg[i][j]->GetMaximum());

                h1DFlow[i][j] = (TH1D *)histfit1->Clone();
                std::string function = "[0]/(TMath::Pi()*2)*(1+2*([1]*TMath::Cos(x)+[2]*TMath::Cos(2*x)+[3]*TMath::Cos(3*x)))"; //+[4]*TMath::Cos(4*x)+[5]*TMath::Cos(5*x)))";
                TF1 func1("deltaPhi1", function.c_str(), -0.5 * TMath::Pi(), 1.5 * TMath::Pi());
                func1.SetParameter(0, histfit1->GetMaximum());
                func1.SetParameter(1, 0.1);
                func1.SetParameter(2, 0.1);
                func1.SetParameter(3, 0.1);
                // func1.SetParameter(4, 0.1);
                // func1.SetParameter(5, 0.1);
                h1DFlow[i][j]->Fit(&func1, "m E q");

                for (int ip = 0; ip < 3; ip++)
                {
                    mFit_par[j][ip][i][n] = func1.GetParameter(ip + 1);
                    mFit_par_err[j][ip][i][n] = func1.GetParError(ip + 1);
                    mFit_par_err[j][ip][i][n] *= sqrt(2);

                    if (ip == 1)
                    {
                        v2[j][i][n] = sqrt(mFit_par[j][1][i][n]);
                        v2_err[j][i][n] = mFit_par_err[j][1][i][n] / v2[j][i][n] / 2;
                        
                        //if (j == 0 && n==(detabins-1))
                        //    cout << "v2: " << v2[j][i][n] << endl;
                        //if (j == 0)
                        //    cout << "v2_err: " << v2_err[j][i] << endl;
                    }
                }

                // Set the histogram title
                // h1DFlow[i][j]->SetTitle(Form("Nch>%d, %.2f<jT<3 GeV/c",trackbinbounds[i],ptname[j]));
                h1DFlow[i][j]->SetTitle(Form("%d<Nch<%d, %.2f<jT<3 GeV/c", trackbinbounds[i], trackbinboundsUpper[i], ptname[j]));
            }
        }
    }

    int Farben[trackbin] = {401, 432, 418, 800, 2, 4, 616, 1, 797};

    TGraphErrors *gv2[2][trackbin];
    TCanvas *cKuchen = new TCanvas("cKuchen", "", 0, 0, 1600, 1200);
    cKuchen->Divide(3, 3);
    for (int j = 0; j < 1; j++)
    {
        for (int i = 0; i < trackbin;i++)
        {
            gv2[j][i] = new TGraphErrors(detabins, detacuts, v2[j][i], nullptr, v2_err[j][i]);
            //gv2[j][i]->SetMarkerColor(Farben[i]);
            //gv2[j][i]->SetLineColor(Farben[i]);
            gv2[j][i]->SetTitle(";#Delta#eta*;v_{2}");
            gv2[j][i]->GetXaxis()->SetTitleSize(0.07);
            gv2[j][i]->GetXaxis()->SetLabelSize(0.07);
            gv2[j][i]->GetYaxis()->SetTitleSize(0.08);
            gv2[j][i]->GetYaxis()->SetLabelSize(0.07);
            //gv2[j][i]->GetXaxis()->SetTitleOffset(0.8);
            gv2[j][i]->GetYaxis()->SetTitleOffset(0.8);
            gv2[j][i]->GetXaxis()->CenterTitle();
            gv2[j][i]->GetYaxis()->CenterTitle();

            //if (j == 0)
            {
                cKuchen->cd(i + 1);
                gPad->SetTopMargin(0.05);
                gv2[0][i]->Draw("ap");
                TLatex text;
                text.SetTextAlign(33);
                text.DrawLatexNDC(0.8, 0.9, Form("<N_{ch}> = %d", (int)mAve_Nch[i]));
            }
        }
    }
    cKuchen->SaveAs("Kuchen0p3.png");
}
