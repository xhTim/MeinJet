#include "TH1DtoCanvas.C"

void QA()
{
        TCanvas *c_jT = new TCanvas("c_jT", "", 0, 0, 800, 600);
        TLegend *leg_jT = new TLegend(.6, .6, .8, .8, "");
        TH1DtoCanvas(c_jT, "../Dokumente/ana_run3_allNch_2024CDEFG.root", "jet_jT", leg_jT, "HLT500", 2, ";j_{T};Count");
        TH1DtoCanvas(c_jT, "../Dokumente/ana_run3_allNch_2024_Jet275_newCut.root", "jet_jT", leg_jT, "new trigger", 1, ";j_{T};Count");
        leg_jT->Draw("same");
        c_jT->SaveAs("../Figuren/jT.png");

        TCanvas *c_es = new TCanvas("c_es", "", 0, 0, 800, 600);
        TLegend *leg_es = new TLegend(.6, .6, .8, .8, "");
        TH1DtoCanvas(c_es, "../Dokumente/ana_run3_allNch_2024_Jet275_newCut.root", "jet_etastar", leg_es, "new trigger", 1, ";#eta*;Count");
        TH1DtoCanvas(c_es, "../Dokumente/ana_run3_allNch_2024CDEFG.root", "jet_etastar", leg_es, "HLT500", 2, ";#eta*;Count");
        leg_es->Draw("same");
        c_es->SaveAs("../Figuren/etastar.png");
}