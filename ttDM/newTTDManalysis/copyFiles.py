import os, commands

scratch = True

cmdls = "lcg-ls"
#srm = "  -b -D srmv2 srm://storage01.lcg.cscs.ch:8443/srm/managerv2\?SFN="
srm = "  -b -D srmv2 srm://storage01.lcg.cscs.ch:8443/srm/managerv2\?SFN="
#srm = " -b -D srmv2 srm://t3se01.psi.ch"
### To store on t3 storage element
cmdcp = "globus-url-copy -continue-on-error -rst -nodcau -fast -vb -v -cd -r gsiftp://storage01.lcg.cscs.ch/"
#outdir = "gsiftp://t3se01.psi.ch/pnfs/psi.ch/cms/trivcat/store/user/decosa/ttDM/Moriond_v3/jes/"
outdir = "gsiftp://t3se01.psi.ch/pnfs/psi.ch/cms/trivcat/store/user/grauco/JetMet_76X_v7/"

### To store on t3 scratch area
if(scratch):
    cmdcp = "lcg-cp "
    outdir = "/scratch/grauco/"

samples = {}
#samples["QCD_HT100to200"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_30May/160530_162044/0000/"

samples["test"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_2Jun/160602_061436/0000/"
#samples["QCD_HT200to300_ext"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_2Junv2/160602_061628/0000/"
#samples["QCD_HT300to500"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_2Junv2/160602_061635/0000/"
#samples["QCD_HT300to500_ext"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_2Jun/160602_061444/0000/"
#samples["QCD_HT500to700"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_2Jun/160602_061451/0000/"

#samples["QCD_Pt50to80"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160510_102950/0000/"
#samples["QCD_Pt85to120"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160510_102943/0000/"
#samples["QCD_Pt600to800"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160510_102958/0000/"
#samples["QCD_Pt800to1000"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160510_103009/0000/"

#samples["QCD_Pt15to30"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145730/0000/"
#samples["QCD_Pt30to50"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145816/0000/"
#samples["QCD_Pt120to170"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145715/0000/"
#samples["QCD_Pt170to300"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145738/0000/"
#samples["QCD_Pt300to470"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145804/0000/"
#samples["QCD_Pt470to600"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145823/0000/"
#samples["QCD_Pt1000to1400"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145707/0000/"
#samples["QCD_Pt1400to1800"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145723/0000/"
#samples["QCD_Pt1800to2400"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145744/0000/"
#samples["QCD_Pt2400to3200"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/Root76xV1_QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8_JetMet_09May/160509_145752/0000/"

#samples["SingleMuon_v2"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/SingleMuon/Root76xV1_SingleMuon_JetMet_09May/160509_191020/0000/"
#samples["DY_v2"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_09May/160509_190925/0000/"
#samples["SingleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/SingleMuon/Root76xV1_SingleMuon_JetMet_03May/160504_071706/0000/"
#samples["Template"]="/pnfs/psi.ch/cms/trivcat/store/user/grauco/PixelResolution_2016/ZeroBias1/PixRes_ZeroBias1_Run2016B-PromptReco-v1_272022_Templatev1/160509_124935/0000/"
#samples["Generic"]="/pnfs/psi.ch/cms/trivcat/store/user/grauco/PixelResolution_2016/ZeroBias1/PixRes_ZeroBias1_Run2016B-PromptReco-v1_272022_Genericv1/160509_125434/0000/"
#samples["ZeroBias"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/ZeroBias/Root76xV1_ZeroBias_JetMet_03May/160503_193838/0002/"

#samples["QCD_herwig"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp/Root76xV1_QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp_JetMet_03May/160504_071801/0000/"
#samples["QCD_pythia"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/Root76xV1_QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8_JetMet_03May/160504_071747/0000/"
#samples["DY"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_03May/160503_193712/0000/"
#samples["SingleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/SingleMuon/Root76xV1_SingleMuon_JetMet_23Aprv3/160423_100059/0000/"
#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/DoubleMuon/Root76xV1_DoubleMuon_JetMet_23Aprv3/160423_100043/0000/"
#samples["JetHT"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/JetHT/Root76xV1_JetHT_JetMet_23Aprv3/160423_100052/0000/"
#samples["DY"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/Root76xV1_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_JetMet_23Aprv4/160424_200443/0000/"
#samples["QCD_pythia"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/Root76xV1_QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8_JetMet_23Aprv4/160424_200458/0000/"
#samples["QCD_herwig"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV2/QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp/Root76xV1_QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp_JetMet_23Aprv4/160424_200507/0000/"
#samples["DY_v2"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_16Apr/160416_173648/0000/"

#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_JetMet_07Apr_v1/160407_121304/0003/"
#samples["DY"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root76xV1_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_JetMet_07Apr_v1/160407_121733/0003/"
#samples["QCD_pythia"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/Root76xV1_QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8_JetMet_08Apr_v1/160408_090651/0003/"
#samples["QCD_herwig"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp/Root76xV1_QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp_JetMet_08Apr_v1/160408_090658/0003/"
#samples["QCD_pythia"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/Root76xV1_QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8_JetMet_20Mar/160320_080906/0003/"
#samples["QCD_pythiav"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8/Root76xV1_QCD_Pt-15to3000_TuneCUETP8M1_Flat_13TeV_pythia8_JetMet_22Mar_v1/160322_115225/0000/"
#samples["QCD_herwigg"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp/Root76xV1_QCD_Pt-15to7000_TuneCUETHS1_Flat_13TeV_herwigpp_JetMet_20Mar/160320_080914/0003/"
#samples["GJets"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/GJet_Pt-15To6000_TuneCUETP8M1-Flat_13TeV_pythia8/Root76xV1_GJet_Pt-15To6000_TuneCUETP8M1-Flat_13TeV_pythia8_JetMet_20Mar/160320_080923/"
#samples["SinglePhoton"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/SinglePhoton/Root76xV1_SinglePhoton_JetMet_20Mar/160320_081218/"
#samples["JetHT"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/JetHT/Root76xV1_JetHT_JetMet_08Apr_v1/160408_090954/0003/"
#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_12Mar/160312_045353/0000/"
#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_12Mar/160312_045353/0001/"
#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_12Mar/160312_045353/0002/"
#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_12Mar/160312_045353/0003/"
#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_12Mar/160312_045353/0004/"
#samples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_12Mar/160312_045353/0005/"
#xssamples["DoubleMuon"]="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/grauco/JetMet_Fw76XV1/DoubleMuon/Root76xV1_DoubleMuon_12Mar/160312_045353/0006/"

##samples["MET"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/TTDM_CMSSW_74X_V4/MET/MET25ns_Root1Oct/151001_143915/0000/"

#samples["DMtt_sc_Mchi1Mphi10"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172953/0000/" 
#samples["DMtt_sc_Mchi10Mphi10"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-10_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-10_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172915/0000/"

#samples["DMtt_sc_Mchi1Mphi20"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173007/0000/" 

#samples["DMtt_sc_Mchi1Mphi50"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172900/0000/"
#samples["DMtt_sc_Mchi10Mphi50"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-10_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-10_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172923/0000/"
#samples["DMtt_sc_Mchi50Mphi50"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-50_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-50_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173114/0000/"

#samples["DMtt_sc_Mchi1Mphi100"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172945/0000/"
#samples["DMtt_sc_Mchi10Mphi100"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-10_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-10_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172908/0000/"

#samples["DMtt_sc_Mchi1Mphi200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172959/0000/"
#samples["DMtt_sc_Mchi50Mphi200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-50_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-50_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173043/0000/"
#samples["DMtt_sc_Mchi150Mphi200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-150_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-150_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172930/0000/"

#samples["DMtt_sc_Mchi1Mphi300"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173015/0000/"
#samples["DMtt_sc_Mchi50Mphi300"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-50_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-50_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173051/0000/"

#samples["DMtt_sc_Mchi1Mphi500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173024/0000/"
#samples["DMtt_sc_Mchi500Mphi500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-500_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-500_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173033/0000/"

#samples["DMtt_sc_Mchi1Mphi1000"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_scalar_Mchi-1_Mphi-1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_scalar_Mchi-1_Mphi-1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_172936/0000/"


#samples["DMtt_ps_Mchi1Mphi10"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-1_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173216/0000/"
#samples["DMtt_ps_Mchi10Mphi10"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-10_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-10_Mphi-10_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173130/0000/"

#samples["DMtt_ps_Mchi1Mphi20"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-1_Mphi-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-20_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173238/0000/"

#samples["DMtt_ps_Mchi1Mphi50"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-1_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173317/0000/"
#samples["DMtt_ps_Mchi50Mphi50"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-10_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-10_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173137/0000/"
#samples["DMtt_ps_Mchi50Mphi50"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-50_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-50_Mphi-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173347/0000/"

#samples["DMtt_ps_Mchi1Mphi100"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-1_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173208/0000/"
#samples["DMtt_ps_Mchi10Mphi100"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-10_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-10_Mphi-100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173122/0000/"

#samples["DMtt_ps_Mchi1Mphi200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-1_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173225/0000/"
#samples["DMtt_ps_Mchi50Mphi200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-50_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-50_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173332/0000/"
#samples["DMtt_ps_Mchi150Mphi200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-150_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-150_Mphi-200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173153/0000/"

#samples["DMtt_ps_Mchi1Mphi300"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-1_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173246/0000/"
#samples["DMtt_ps_Mchi50Mphi300"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-50_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-50_Mphi-300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173339/0000/"

#samples["DMtt_ps_Mchi1Mphi500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-1_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173305/0000/"
#samples["DMtt_ps_Mchi150Mphi500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-150_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-150_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173200/0000/"
#samples["DMtt_ps_Mchi500Mphi500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/TTbarDMJets_pseudoscalar_Mchi-500_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_TTbarDMJets_pseudoscalar_Mchi-500_Mphi-500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173325/0000/"


#samples["WJets_HT100to200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJets_HT100to200noSyst_10Feb_jesmet/160213_031229/0000/"
#samples["WJets_HT200to400"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJets_HT200to400noSyst_10Feb_jesmet/160213_031243/0000/"
#samples["WJets_HT400to600"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJets_HT400to600noSyst_10Feb_jesmet/160213_031300/0000/"
#samples["WJets_HT600to800"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJets_HT600to800noSyst_10Feb_jesmet/160213_031314/0000/"
#samples["WJets_HT800to1200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJets_HT800to1200noSyst_10Feb_jesmet/160213_031328/0000/"
#samples["WJets_HT1200to2500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJets_HT1200to2500noSyst_10Feb_jesmet/160213_031341/0000/"
#samples["WJets_HT2500toInf"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/WJets_HT2500toInfnoSyst_10Feb_jesmet/160213_031355/0000/"

#samples["ZJets_HT100to200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-100To200_13TeV-madgraph/Root_ZJetsToNuNu_HT-100To200_13TeV-madgraph_jes_2F/160305_131158/0000/"
#samples["ZJets_HT200to400"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-200To400_13TeV-madgraph/Root_ZJetsToNuNu_HT-200To400_13TeV-madgraph_jes_2F/160305_131205/0000/"
#samples["ZJets_HT400to600"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-400To600_13TeV-madgraph/Root_ZJetsToNuNu_HT-400To600_13TeV-madgraph_jes_2F/160305_131211/0000/"
#samples["ZJets_HT600toInf"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/Root_ZJetsToNuNu_HT-600ToInf_13TeV-madgraph_jes_2F/160305_130518/0000/"


#samples["ZJets_HT100to200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-100To200_13TeV-madgraph/Root_ZJetsToNuNu_HT-100To200_13TeV-madgraph_jer_2F/160211_172716/0000/"
#samples["ZJets_HT200to400"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-200To400_13TeV-madgraph/Root_ZJetsToNuNu_HT-200To400_13TeV-madgraph_jer_2F/160211_172725/0000/"
#samples["ZJets_HT400to600"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-400To600_13TeV-madgraph/Root_ZJetsToNuNu_HT-400To600_13TeV-madgraph_jer_2F/160211_172735/0000/"
#samples["ZJets_HT600toInf"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/Root_ZJetsToNuNu_HT-600ToInf_13TeV-madgraph_jer_2F/160211_172741/0000/"


#samples["ZJets_HT100to200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-100To200_13TeV-madgraph/Root_ZJetsToNuNu_HT-100To200_13TeV-madgraph_met_2F/160211_173849/0000/"
#samples["ZJets_HT200to400"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-200To400_13TeV-madgraph/Root_ZJetsToNuNu_HT-200To400_13TeV-madgraph_met_2F/160211_173902/0000/"
#samples["ZJets_HT400to600"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-400To600_13TeV-madgraph/Root_ZJetsToNuNu_HT-400To600_13TeV-madgraph_met_2F/160211_173911/0000/"
#samples["ZJets_HT600toInf"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/Root_ZJetsToNuNu_HT-600ToInf_13TeV-madgraph_met_2F/160211_173919/0000/"


#samples["SingleEl_05Oct"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/SingleElectron/Root_SingleElectrondecosa-SingleEl_Run2015D_miniAODv2_13Nov-ff3168b63d5cee365f49bf7ea3ba6ef3_2F/160222_002842/0000/"
#samples["SingleEl_Promptv4"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/SingleElectron/Root_SingleElectrondecosa-SingleEl_Run2015D_PromptV4_13Nov-5daaa7fbf157b0642c1d3dfb260fbeff_2F/160222_002835/0000/"
#samples["SingleMu_05Oct"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/SingleMuon/Root_SingleMuondecosa-SingleMu_Run2015D_miniAODv2_v2_13Nov-ff3168b63d5cee365f49bf7ea3ba6ef3_2F/160222_002828/0000/"
#samples["SingleMu_Promptv4"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/SingleMuon/Root_SingleMuondecosa-SingleMu_Run2015D_PromptV4_v2_13Nov-5daaa7fbf157b0642c1d3dfb260fbeff_2F/160222_002822/0000/"


#samples["MET_05Oct"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/MET/Root_METdecosa-MET_Run2015D_miniAODv2_13Nov-ff3168b63d5cee365f49bf7ea3ba6ef3_2F/160222_002855/0000/"
#samples["MET_Promptv4"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/MET/Root_METdecosa-MET_Run2015D_PromptV4_13Nov-5daaa7fbf157b0642c1d3dfb260fbeff_2F/160222_002849/0000/"


#samples["TT"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/oiorio/ttDM/trees/2016/Feb/10Feb/TT_TuneCUETP8M1_13TeV-powheg-pythia8/TTnoSyst_10Feb_jesmet/160213_031017/0000/"



#samples["QCD_HT100_200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/dpinna/Samples_v2_Fw7_4_15_2016/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_njes_14J/160114_173407/0000/"



#samples["QCD_HT100_200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131431/0000/"
#samples["QCD_HT200_300"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131437/0000/"
#samples["QCD_HT300_500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131443/0000/"
#samples["QCD_HT500_700"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131449/0000/"
#samples["QCD_HT700_1000"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131456/0000/"
#samples["QCD_HT1000_1500"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131502/0000/"
#samples["QCD_HT1500_2000"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131508/0000/"
#samples["QCD_HT2000_Inf"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/7_4_15_Moriond2016_v3/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/Root_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_jes_2F/160305_131518/0000/"


#samples["ttDM1"] ="/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/Phys14_Synchro/TTDMDMJets_M1GeV_Tune4C_13TeV-madgraph-tauola/DM1/150603_132943/0000/"
#samples["ttDM10"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/Phys14_Tree_sys_v4/TTDMDMJets_M10GeV_Tune4C_13TeV-madgraph-tauola/DM10/150523_175813/0000/"
#samples["ttDM50"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/Phys14_Tree_sys_v4/TTDMDMJets_M50GeV_Tune4C_13TeV-madgraph-tauola/DM50/150523_180045/0000/"
#samples["ttDM100"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/Phys14_Tree_sys_v4/TTDMDMJets_M100GeV_Tune4C_13TeV-madgraph-tauola/DM100/150523_175839/0000/"
#samples["ttDM200"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/Phys14_Tree_sys_v4/TTDMDMJets_M200GeV_Tune4C_13TeV-madgraph-tauola/DM200/150523_175936/0000/"
#samples["ttDM600"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/Phys14_Tree_sys_v4/TTDMDMJets_M600GeV_Tune4C_13TeV-madgraph-tauola/DM600/150523_180003/0000/"
#samples["ttDM1000"] = "/pnfs/lcg.cscs.ch/cms/trivcat/store/user/decosa/ttDM/Phys14_Tree_sys_v4/TTDMDMJets_M1000GeV_Tune4C_13TeV-madgraph-tauola/DM1000/150524_174542/0000/"

#samples.append("SingleTop_T_tchan")
#samples.append("SingleTop_Tbar_tchan")
#samples.append("T_tW")
#samples.append("Tbar_tW")

newpath = 'work/'
if not os.path.exists(newpath):
    os.makedirs(newpath)

for sample ,path in samples.iteritems():
    cmd = cmdls + srm + path
    status,ls_la = commands.getstatusoutput( cmd )
    dir = [ ]
    list = ls_la.split(os.linesep)
    #print list
    if(scratch): cmd_cp = cmdcp + srm + path
    else: cmd_cp = cmdcp +  path
    files =[ l.split('/')[-1] for l in list]
    #print files
    cmd = "mkdir " + outdir + sample
    os.system(cmd)


    for f in files:
        newcmd = cmd_cp + f + " " + outdir + sample + "/" +f
        print newcmd
        os.system(newcmd)

    
#    for f in files:
#        workdir = 'work/' + sample + "_" + str(files.index(f))
#        jobid = sample + "_" + str(files.index(f))
        #        newcmd = cmd_cp + f + " " + outdir + sample + "/" +f
#        newcmd = "qexe.py -w " + workdir + " " +  jobid + " -- " + cmd_cp + f + " " + outdir + sample + "/" +f
#        print newcmd
#        os.system(newcmd)
