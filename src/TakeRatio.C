#include "../include/headers.h"

void TakeRatio(int baseline_Jahr = 22, int test_Jahr = 23)
{
        int num_run = baseline_Jahr > 18 ? 3 : 2;

        cout << "Baseline: 20" << baseline_Jahr << " Run " << num_run << endl
             << "Test: 20" << test_Jahr << " Run " << num_run << endl;
        TFile *file_1 = new TFile(Form("../Dokumente/ana_run%d_allNch_20%d.root", num_run, baseline_Jahr), "read");
        TFile *file_2 = new TFile(Form("../Dokumente/ana_run%d_allNch_20%d.root", num_run, test_Jahr), "read");

        TH2D *h_lab_JetMult_pT_1 = (TH2D *)file_1->Get("lab_JetMult_pT");
        TH2D *h_lab_JetMult_eta_1 = (TH2D *)file_1->Get("lab_JetMult_eta");
        TH2D *h_lab_JetMult_phi_1 = (TH2D *)file_1->Get("lab_JetMult_phi");
        TH1D *h_jT_1 = (TH1D *)file_1->Get("jet_jT");
        TH1D *h_etastar_1 = (TH1D *)file_1->Get("jet_etastar");
        TH2D *h_lab_JetMult_pT_2 = (TH2D *)file_2->Get("lab_JetMult_pT");
        TH2D *h_lab_JetMult_eta_2 = (TH2D *)file_2->Get("lab_JetMult_eta");
        TH2D *h_lab_JetMult_phi_2 = (TH2D *)file_2->Get("lab_JetMult_phi");
        TH1D *h_jT_2 = (TH1D *)file_2->Get("jet_jT");
        TH1D *h_etastar_2 = (TH1D *)file_2->Get("jet_etastar");

        TH1D *h_lab_pT_1 = (TH1D *)h_lab_JetMult_pT_1->ProjectionX("h_lab_pT_1");
        TH1D *h_lab_pT_2 = (TH1D *)h_lab_JetMult_pT_2->ProjectionX("h_lab_pT_2");
        TH1D *h_JetMult_550_1 = (TH1D *)h_lab_JetMult_pT_1->ProjectionY("h_JetMult_550_1", h_lab_JetMult_pT_1->GetXaxis()->FindBin(550));
        TH1D *h_JetMult_550_2 = (TH1D *)h_lab_JetMult_pT_2->ProjectionY("h_JetMult_550_2", h_lab_JetMult_pT_2->GetXaxis()->FindBin(550));
        TH1D *h_lab_eta_1 = (TH1D *)h_lab_JetMult_eta_1->ProjectionX("h_lab_eta_1");
        TH1D *h_lab_eta_2 = (TH1D *)h_lab_JetMult_eta_2->ProjectionX("h_lab_eta_2");
        TH1D *h_lab_phi_1 = (TH1D *)h_lab_JetMult_phi_1->ProjectionX("h_lab_phi_1");
        TH1D *h_lab_phi_2 = (TH1D *)h_lab_JetMult_phi_2->ProjectionX("h_lab_phi_2");

        // Normalization
        // h_lab_pT_1->Scale(1. / h_lab_pT_1->Integral());
        h_lab_pT_1->Scale(1. / h_lab_pT_1->GetBinContent(h_lab_pT_1->GetXaxis()->FindBin(600)));
        h_JetMult_550_1->Scale(1. / h_JetMult_550_1->Integral());
        h_lab_eta_1->Scale(1. / h_lab_eta_1->Integral());
        h_lab_phi_1->Scale(1. / h_lab_phi_1->Integral());
        h_jT_1->Scale(1. / h_jT_1->Integral());
        h_etastar_1->Scale(1. / h_etastar_1->Integral());
        // h_lab_pT_2->Scale(1. / h_lab_pT_2->Integral());
        h_lab_pT_2->Scale(1. / h_lab_pT_2->GetBinContent(h_lab_pT_2->GetXaxis()->FindBin(600)));
        h_JetMult_550_2->Scale(1. / h_JetMult_550_2->Integral());
        h_lab_eta_2->Scale(1. / h_lab_eta_2->Integral());
        h_lab_phi_2->Scale(1. / h_lab_phi_2->Integral());
        h_jT_2->Scale(1. / h_jT_2->Integral());
        h_etastar_2->Scale(1. / h_etastar_2->Integral());

        TString yTitle = Form("count 20%d / count 20%d", test_Jahr, baseline_Jahr);
        TH1D *h_lab_pT_ratio = (TH1D *)h_lab_pT_2->Clone("h_lab_pT_ratio");
        h_lab_pT_ratio->Divide(h_lab_pT_1);
        h_lab_pT_ratio->SetTitle(";p_{T};"+yTitle);
        TH1D *h_JetMult_550_1_ratio = (TH1D *)h_JetMult_550_2->Clone("h_JetMult_550_ratio");
        h_JetMult_550_1_ratio->Divide(h_JetMult_550_1);
        h_JetMult_550_1_ratio->SetTitle(";N_{ch};"+yTitle);
        TH1D *h_lab_eta_ratio = (TH1D *)h_lab_eta_2->Clone("h_lab_eta_ratio");
        h_lab_eta_ratio->Divide(h_lab_eta_1);
        h_lab_eta_ratio->SetTitle(";#eta;" + yTitle);
        TH1D *h_lab_phi_ratio = (TH1D *)h_lab_phi_2->Clone("h_lab_phi_ratio");
        h_lab_phi_ratio->Divide(h_lab_phi_1);
        h_lab_phi_ratio->SetTitle(";#phi;" + yTitle);
        TH1D *h_jT_ratio = (TH1D *)h_jT_2->Clone("h_jT_ratio");
        h_jT_ratio->Divide(h_jT_1);
        h_jT_ratio->SetTitle(";j_{T};"+yTitle);
        TH1D *h_etastar_ratio = (TH1D *)h_etastar_2->Clone("h_etastar_ratio");
        h_etastar_ratio->Divide(h_etastar_1);
        h_etastar_ratio->SetTitle(";#eta*;"+yTitle);

        TString Jahren = Form("20%dto20%d.png", test_Jahr, baseline_Jahr);
        TCanvas *c_lab_pT_ratio = new TCanvas("c_lab_pT_ratio", "", 0, 0, 800, 600);
        h_lab_pT_ratio->Draw("hist");
        c_lab_pT_ratio->SaveAs("../Figuren/year_ratios/lab_pT_ratio_"+Jahren);
        TCanvas *c_JetMult_550_ratio = new TCanvas("c_JetMult_550_ratio", "", 0, 0, 800, 600);
        h_JetMult_550_1_ratio->Draw("hist");
        c_JetMult_550_ratio->SaveAs("../Figuren/year_ratios/JetMult_550_ratio_"+Jahren);
        TCanvas *c_lab_eta_ratio = new TCanvas("c_lab_eta_ratio", "", 0, 0, 800, 600);
        h_lab_eta_ratio->Draw("hist");
        c_lab_eta_ratio->SaveAs("../Figuren/year_ratios/lab_eta_ratio_"+Jahren);
        TCanvas *c_lab_phi_ratio = new TCanvas("c_lab_phi_ratio", "", 0, 0, 800, 600);
        h_lab_phi_ratio->Draw("hist");
        c_lab_phi_ratio->SaveAs("../Figuren/year_ratios/lab_phi_ratio_"+Jahren);
        TCanvas *c_jT_ratio = new TCanvas("c_jT_ratio", "", 0, 0, 800, 600);
        h_jT_ratio->Draw("hist");
        c_jT_ratio->SaveAs("../Figuren/year_ratios/jT_ratio_"+Jahren);
        TCanvas *c_etastar_ratio = new TCanvas("c_etastar_ratio", "", 0, 0, 800, 600);
        h_etastar_ratio->Draw("hist");
        c_etastar_ratio->SaveAs("../Figuren/year_ratios/etastar_ratio_"+Jahren);
}
