#include "../include/headers.h"

void SBRatio(int baseline_Jahr = 22, int test_Jahr = 23)
{
    TH2D *hSignal_1[10][2]; // Ntrk,pt
    TH2D *hBkg_1[10][2];
    TH2D *hSignal_2[10][2];
    TH2D *hBkg_2[10][2];
    TH1D *hSignal_phi_1[10][2];
    TH1D *hBkg_phi_1[10][2];
    TH1D *hSignal_phi_2[10][2];
    TH1D *hBkg_phi_2[10][2];
    TH1D *hSignal_ratio[10][2];
    TH1D *hBkg_ratio[10][2];

    int num_run = baseline_Jahr > 18 ? 3 : 2;

    cout << "Baseline: 20" << baseline_Jahr << " Run " << num_run << endl
         << "Test: 20" << test_Jahr << " Run " << num_run << endl;
    TFile *file_1 = new TFile(Form("../Dokumente/ana_run%d_allNch_20%d.root", num_run, baseline_Jahr), "read");
    TFile *file_2 = new TFile(Form("../Dokumente/ana_run%d_allNch_20%d.root", num_run, test_Jahr), "read");

    int ptbinbounds[2] = {3, 5};
    float ptname[2] = {0.3, 0.5};
    const int trackbinbounds[10] = {0, 20, 30, 40, 50, 59, 66, 76, 83, 78};
    const int trackbinboundsUpper[10] = {20, 30, 40, 50, 59, 66, 76, 83, 1000, 1000};
    int YPlo=28;
    int YPhi=34;

    // for(int i=0;i<5;i++){
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            hSignal_1[i][j] = (TH2D *)file_1->Get(Form("hSigS_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));
            hBkg_1[i][j] = (TH2D *)file_1->Get(Form("hBckS_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));
            hSignal_2[i][j] = (TH2D *)file_2->Get(Form("hSigS_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));
            hBkg_2[i][j] = (TH2D *)file_2->Get(Form("hBckS_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));

            hSignal_phi_1[i][j] = (TH1D *)hSignal_1[i][j]->ProjectionY(Form("hSigS_phi_Cor_%d_to_%d_and_%d_to_30_w_PU_1_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]), YPlo, YPhi);
            hBkg_phi_1[i][j] = (TH1D *)hBkg_1[i][j]->ProjectionY(Form("hBckS_phi_Cor_%d_to_%d_and_%d_to_30_w_PU_1_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]), YPlo, YPhi);
            hSignal_phi_2[i][j] = (TH1D *)hSignal_2[i][j]->ProjectionY(Form("hSigS_phi_Cor_%d_to_%d_and_%d_to_30_w_PU_1_2", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]), YPlo, YPhi);
            hBkg_phi_2[i][j] = (TH1D *)hBkg_2[i][j]->ProjectionY(Form("hBckS_phi_Cor_%d_to_%d_and_%d_to_30_w_PU_1_2", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]), YPlo, YPhi);

            hSignal_phi_1[i][j]->Scale(1. / hSignal_phi_1[i][j]->Integral());
            hBkg_phi_1[i][j]->Scale(1. / hBkg_phi_1[i][j]->Integral());
            hSignal_phi_2[i][j]->Scale(1. / hSignal_phi_2[i][j]->Integral());
            hBkg_phi_2[i][j]->Scale(1. / hBkg_phi_2[i][j]->Integral());

            hSignal_ratio[i][j] = (TH1D *)hSignal_phi_2[i][j]->Clone(Form("hSigR_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));
            hSignal_ratio[i][j]->Divide(hSignal_phi_1[i][j]);
            hSignal_ratio[i][j]->SetTitle(Form("%d<Nch<%d, %.2f<jT<3 GeV/c, Signal;#Delta#phi*;count 20%d / count 20%d", trackbinbounds[i], trackbinboundsUpper[i], ptname[j], test_Jahr, baseline_Jahr));
            hSignal_ratio[i][j]->SetStats(kFALSE);
            hBkg_ratio[i][j] = (TH1D *)hBkg_phi_2[i][j]->Clone(Form("hBckR_Cor_%d_to_%d_and_%d_to_30_w_PU_1", trackbinbounds[i], trackbinboundsUpper[i], ptbinbounds[j]));
            hBkg_ratio[i][j]->Divide(hBkg_phi_1[i][j]);
            hBkg_ratio[i][j]->SetTitle(Form("%d<Nch<%d, %.2f<jT<3 GeV/c, Background;#Delta#phi*;count 20%d / count 20%d", trackbinbounds[i], trackbinboundsUpper[i], ptname[j], test_Jahr, baseline_Jahr));
            hBkg_ratio[i][j]->SetStats(kFALSE);
        }
    }
    
    TCanvas *cSignal_1 = new TCanvas("cSignal_1", "", 800, 1200);
    cSignal_1->Divide(2, 5); // Divide canvas into 2 columns and 5 rows
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cSignal_1->cd(i * 2 + j + 1);
            hSignal_ratio[i][j]->Draw("ehist");
        }
    }
    cSignal_1->SaveAs(Form("../Figuren/year_ratios/Signal_canvas1_20%dto20%d.pdf", test_Jahr, baseline_Jahr));

    TCanvas *cSignal_2 = new TCanvas("cSignal_2", "", 800, 1200);
    cSignal_2->Divide(2, 5); // Divide canvas into 2 columns and 5 rows
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cSignal_2->cd(i * 2 + j + 1);
            hSignal_ratio[i + 5][j]->Draw("ehist");
        }
    }
    cSignal_2->SaveAs(Form("../Figuren/year_ratios/Signal_canvas2_20%dto20%d.pdf", test_Jahr, baseline_Jahr));

    TCanvas *cBkg_1 = new TCanvas("cBkg_1", "", 800, 1200);
    cBkg_1->Divide(2, 5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cBkg_1->cd(i * 2 + j + 1);
            hBkg_ratio[i][j]->Draw("ehist");
        }
    }
    cBkg_1->SaveAs(Form("../Figuren/year_ratios/Background_canvas1_20%dto20%d.pdf", test_Jahr, baseline_Jahr));

    TCanvas *cBkg_2 = new TCanvas("cBkg_2", "", 800, 1200);
    cBkg_2->Divide(2, 5);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cBkg_2->cd(i * 2 + j + 1);
            hBkg_ratio[i + 5][j]->Draw("ehist");
        }
    }
    cBkg_2->SaveAs(Form("../Figuren/year_ratios/Background_canvas2_20%dto20%d.pdf", test_Jahr, baseline_Jahr));
}
