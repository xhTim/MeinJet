#include "TGEtoCanvas.C"

void VnEta()
{
        TCanvas *c1 = new TCanvas("c1", "", 0, 0, 800, 600);
        TLegend *leg1 = new TLegend(.6, .2, .8, .5, "");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_eta1.7.root", "V1", leg1, "#eta_{th}=1.7", 801, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>#eta_{th}}");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_eta2.0.root", "V1", leg1, "#eta_{th}=2.0", 417, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_eta2.3.root", "V1", leg1, "#eta_{th}=2.3", 891, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_eta2.6.root", "V1", leg1, "#eta_{th}=2.6", 616, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_2024_Jet275_newCut.root", "V1", leg1, "new trigger jet p_{T}>310GeV", 886, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_2024_Jet275.root", "V1", leg1, "new trigger jet p_{T}>550GeV", 601, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_2024_Jet275_310_550.root", "V1", leg1, "new trigger 310-550GeV", 861, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        leg1->Draw("same");
        TLine* l0=new TLine(9.0,0.0,110.0,0.0);
        l0->Draw("same");
        c1->SaveAs("../Figuren/Vn/V1.png");

        TCanvas *c2 = new TCanvas("c2", "", 0, 0, 800, 600);
        TLegend *leg2 = new TLegend(.2, .15, .4, .45, "");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_eta1.7.root", "V2", leg2, "#eta_{th}=1.7", 801, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>#eta_{th}}");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_eta2.0.root", "V2", leg2, "#eta_{th}=2.0", 417, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_eta2.3.root", "V2", leg2, "#eta_{th}=2.3", 891, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_eta2.6.root", "V2", leg2, "#eta_{th}=2.6", 616, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_2024_Jet275_newCut.root", "V2", leg2, "new trigger jet p_{T}>310GeV", 886, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_2024_Jet275.root", "V2", leg2, "new trigger jet p_{T}>550GeV", 601, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_2024_Jet275_310_550.root", "V2", leg2, "new trigger 310-550GeV", 861, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        leg2->Draw("same");
        l0->Draw("same");
        c2->SaveAs("../Figuren/Vn/V2.png");

        TCanvas *c3 = new TCanvas("c3", "", 0, 0, 800, 600);
        TLegend *leg3 = new TLegend(.6, .2, .8, .5, "");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_eta1.7.root", "V3", leg3, "#eta_{th}=1.7", 801, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>#eta_{th}}");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_eta2.0.root", "V3", leg3, "#eta_{th}=2.0", 417, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_eta2.3.root", "V3", leg3, "#eta_{th}=2.3", 891, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_eta2.6.root", "V3", leg3, "#eta_{th}=2.6", 616, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_2024_Jet275_newCut.root", "V3", leg3, "new trigger jet p_{T}>310GeV", 886, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_2024_Jet275.root", "V3", leg3, "new trigger jet p_{T}>550GeV", 601, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
//        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_2024_Jet275_310_550.root", "V3", leg3, "new trigger 310-550GeV", 861, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        leg3->Draw("same");
        l0->Draw("same");
        c3->SaveAs("../Figuren/Vn/V3.png");
}
