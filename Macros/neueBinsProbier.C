#include "TGEtoCanvas.C"

void neueBinsProbier()
{
        TCanvas *c = new TCanvas("c", "", 0, 0, 800, 600);
        TLegend *leg1 = new TLegend(.55, .6, .75, .8, "");

        //TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_Run3.root", "V2", leg1, "Run3 full bins", 600, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        //TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_Run2.root", "V2", leg1, "Run2 full bins", 801, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        //TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_run3_hlt500_highnch.root", "V2", leg1, "Run3", 419, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        //TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_Run2_3bins.root", "V2", leg1, "Run2", 632, ";N_{ch}^{j};V^{*}_{2#Delta}{2,|#Delta#eta^{*}|>2}");
        
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_Run3.root", "v2", leg1, "Run3 full bins", 600, ";N_{ch}^{j};v^{*}_{2}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_Run2.root", "v2", leg1, "Run2 full bins", 801, ";N_{ch}^{j};v^{*}_{2}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_Run2_gebrocheneKlassen.root", "v2", leg1, "Run2 broken bins", 1, ";N_{ch}^{j};v^{*}_{2}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_run3_hlt500_highnch.root", "v2", leg1, "Run3", 419, ";N_{ch}^{j};v^{*}_{2}{2,|#Delta#eta^{*}|>2}");
        TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_Run2_3bins.root", "v2", leg1, "Run2", 632, ";N_{ch}^{j};v^{*}_{2}{2,|#Delta#eta^{*}|>2}");
        
        //TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_i.root", "v2", leg1, "new", 600, ";N_{ch}^{j};v^{*}_{2}{2,|#Delta#eta^{*}|>2}");
        //TGEtoCanvas(c, "../Results/Vn/Vn_vs_Nch_p.root", "v2", leg1, "parker", 801, ";N_{ch}^{j};v^{*}_{2}{2,|#Delta#eta^{*}|>2}");

        leg1->Draw("same");
        c->SaveAs("../Figuren/v2_na.png");
}
