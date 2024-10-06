#include "../include/headers.h"

void TH1DtoCanvas(TCanvas* c, TString FileName, TString HistoName, TLegend* leg, TString LegName, int color)
{
        TFile *inputFile = new TFile(FileName, "read");
        TH1D *hist = (TH1D *)inputFile->Get(HistoName);
        hist->SetLineColor(color);
        hist->SetYTitle("Statistics");
        leg->AddEntry(hist, LegName);
        c->cd();
        hist->Draw("samehist");
}