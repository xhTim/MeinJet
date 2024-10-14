#include "TGEtoCanvas.C"

void Vn()
{
        TCanvas *c1 = new TCanvas("c1", "", 0, 0, 800, 600);
        TLegend *leg1 = new TLegend(.6, .3, .8, .5, "");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_2022.root", "V1", leg1, "2022", 2, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_2023.root", "V1", leg1, "2023", 3, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_2024CDEFG.root", "V1", leg1, "2024", 4, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_20run2.root", "V1", leg1, "Run2", kBlack, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c1, "../Results/Vn/Vn_vs_Nch_2024_Jet275_newCut.root", "V1", leg1, "new trigger jet p_{T}>310GeV", 6, ";N_{ch}^{j};V^{*}_{1#Delta}{2,|#Delta#eta^{*}|>2}");
        leg1->Draw("same");
        TLine* l0=new TLine(9.0,0.0,90.0,0.0);
        l0->Draw("same");
        c1->SaveAs("../Figuren/Vn/V1.png");

        TCanvas *c2 = new TCanvas("c2", "", 0, 0, 800, 600);
        TLegend *leg2 = new TLegend(.6, .3, .8, .5, "");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_2022.root", "V2", leg2, "2022", 2, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_2023.root", "V2", leg2, "2023", 3, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_2024CDEFG.root", "V2", leg2, "2024", 4, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_20run2.root", "V2", leg2, "Run2", kBlack, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c2, "../Results/Vn/Vn_vs_Nch_2024_Jet275_newCut.root", "V2", leg2, "new trigger jet p_{T}>310GeV", 6, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        leg2->Draw("same");
        l0->Draw("same");
        c2->SaveAs("../Figuren/Vn/V2.png");

        TCanvas *c3 = new TCanvas("c3", "", 0, 0, 800, 600);
        TLegend *leg3 = new TLegend(.6, .3, .8, .5, "");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_2022.root", "V3", leg3, "2022", 2, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_2023.root", "V3", leg3, "2023", 3, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_2024CDEFG.root", "V3", leg3, "2024", 4, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_20run2.root", "V3", leg3, "Run2", kBlack, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c3, "../Results/Vn/Vn_vs_Nch_2024_Jet275_newCut.root", "V3", leg3, "new trigger jet p_{T}>310GeV", 6, ";N_{ch}^{j};V^{*}_{3#Delta}{2,|#Delta#eta^{*}|>2}");
        leg3->Draw("same");
        l0->Draw("same");
        c3->SaveAs("../Figuren/Vn/V3.png");
}
