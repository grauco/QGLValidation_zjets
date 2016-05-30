import os
import optparse 
import os.path
import optparse
import subprocess
import sys
import glob

from os.path import join,exists

print 'Python version', sys.version_info
if sys.version_info < (2, 7):
    raise "Must use python 2.7 or greater. Have you forgotten to do cmsenv?"

workdir = 'work'
fileListDir = join(workdir,'files')

#define samples paths
#lPath = "/mnt/t3nfs01/data01/shome/grauco/JetMET/CMSSW_7_6_3_patch2/src/ttDM/newTTDManalysis/"
lPath="/mnt/t3nfs01/data01/shome/grauco/JetMET_z/CMSSW_7_6_3/src/ttDM/newTTDManalysis/"
#path = "/scratch/grauco/B2G_25ns/"
#path = "/scratch/decosa/07Oct2015/"
t3Path = '//pnfs/psi.ch/cms/trivcat/store/user/grauco/JetMet_76X_v7/'
#t3Path = '/store/user/grauco/B2G_Fw76X/'
#t3Ls = 'xrdfs  xrootd-cms.infn.it ls -u'
t3Ls = 'xrdfs t3dcachedb03.psi.ch ls -u'

#define samples, one folder for each mass value
samples = []
samples.append("SingleMuon_v2")
#samples.append("DY_v2")
#samples.append("SingleMuon")
#samples.append("test")
#samples.append("BprimeBprime800")
#samples.append("BprimeBprime1000") 
#samples.append("BprimeBprime1200") 
#samples.append("BprimeBprime1500") 
#samples.append("TT")
#samples.append("WJets_100_200")
#samples.append("WJets_200_400")
#samples.append("WJets_400_600")
#samples.append("WJets_600_800")
#samples.append("WJets_800_1200")
#samples.append("WJets_1200_2500")
#samples.append("WJets_2500_Inf")
#samples.append("ZJets_100_200")
#samples.append("ZJets_200_400")
#samples.append("ZJets_400_600")
#samples.append("ZJets_600_Inf")
#samples.append("QCD_HT2000toInf")
#samples.append("QCD_HT1000to1500")
#samples.append("QCD_HT1500to2000")
#samples.append("QCD_HT700to1000")
#samples.append("QCD_HT500to700")
#samples.append("QCD_HT300to500")
#samples.append("QCD_HT200to300")
#samples.append("QCD_HT100to200")

#samples.append("BprimeToHB800")                                                                                                                        
#samples.append("BprimeToHB1000")
#samples.append("BprimeToHB1200")
#samples.append("BprimeToHB1400")
#samples.append("BprimeToHB1600")
#samples.append("BprimeToHB1800")
#samples.append("JetHT")
#samples.append("QCD_pythia")
#samples.append("QCD_herwig")
#samples.append("DoubleMuon")
#samples.append("DY")

#samples.append("JetHT_05Oct")
#samples.append("JetHT_Promptv4")
#samples.append("TprimeTprime800")#
#samples.append("QCD_HT2000toInf")
#samples.append("QCD_HT1000to1500")
#samples.append("QCD_HT1500to2000")
#samples.append("QCD_HT700to1000")
#samples.append("QCD_HT500to700")
#samples.append("QCD_HT300to500")
#samples.append("QCD_HT200to300")
#samples.append("QCD_HT100to200")

#samples.append("TprimeTprime800")
#samples.append("TprimeTprime1000")
#samples.append("TprimeTprime1500")
#samples.append("TprimeTprime1200")

#samples.append("BprimeToZB800")
#samples.append("BprimeToZB1800")
#samples.append("BprimeToZB1300")

#samples.append("BprimeToHB800")
#samples.append("BprimeToHB1000")
#samples.append("BprimeToHB1200")
#samples.append("BprimeToHB1500")

usage = 'usage: %prog -l lumi'
parser = optparse.OptionParser(usage)
parser.add_option('-c', '--channel', dest='channel', type='string', default = 'singleH', help='Channel to analyze: singleH or singleZ')
parser.add_option('-C', '--cat', dest='cat', type='string', default = 'cat2', help='Category to analyze: cat0 or cat1 or cat2')
parser.add_option('-s', '--sys', dest='sys', type='string', default = 'noSys', help='Systematics: jesUp, jesDown, jerUp, jerDown')
parser.add_option('', '--sync', dest='sync', type='string', default = 'noSync', help='Synchro exercise')
parser.add_option('-d', '--isData', dest='isData', type='string', default = 'MC', help='is Data or MC?')
parser.add_option('-g','--gdb', dest='gdb', action='store_true', default=False)
parser.add_option('-n','--dryrun', dest='dryrun', action='store_true', default=False)
parser.add_option('-m','--mode', dest='mode', default='t3se', choices=['local','t3se'])
parser.add_option('--t3batch', dest='t3batch', action='store_true', default=True)

isData="MC"
(opt, args) = parser.parse_args()

if opt.sys not in ["noSys", "jesUp", "jesDown", "jerUp", "jerDown", "metUnclUp", "metUnclDown"]:
    parser.error('Please choose an allowed value for sys: "noSys", "jesUp", "jesDown", "jerUp", "jerDown","metUnclUp", "metUnclDown"')

# Create working area if it doesn't exist
if not exists(fileListDir):
    os.makedirs(fileListDir)

for s in samples:
    if (s.startswith("DoubleMuon") or s.startswith("SingleMuon") or s.startswith("SingleEl") or  s.startswith("Jet")): isData="DATA"
    if (s.startswith("DY") or s.startswith("QCD")): isData="MC"
    print s
    print str(opt.sync)
    #cmd = "ttDManalysis "+ s + " " + path + s  + " " + opt.channel + " " +opt.cat + " " + opt.sys + " " + opt.sync + " " + isData
    #print cmd
    #os.system(cmd)
    if opt.mode == 'local':
        print 'Local mode not yet supported'

        sPath = join(lPath,s,'*.root')
        # print ' '.join([lLs,sPath])
        # Get the complete list of files
        # listing = subprocess.check_output(lLs.split()+[sPath])
        files = glob.glob(sPath)
        print 'Sample',s,'Files found',len(files)

    elif opt.mode == 't3se':
        # Build the full path of sample files
        sT3Path = join(t3Path,s)
        print ' '.join([t3Ls,sT3Path])

        # Get the complete list of files
        listing = subprocess.check_output(t3Ls.split()+[sT3Path])
        files = listing.split()
        print 'Sample',s,'Files found',len(files)

    # Save it to a semi-temp file
    sampleFileList = join(fileListDir,s+'.txt')
    print sampleFileList
    with open(sampleFileList,'w') as sl:
        sl.write('\n'.join(files))

    outDirs = ['res','trees']

    for d in outDirs:
        if exists(d): continue
        os.makedirs(d)

    cmd = 'ttDManalysis_zjets '+ s + ' ' + sampleFileList  + ' ' + opt.channel + ' ' + opt.cat + ' ' + opt.sys + ' ' + opt.sync + ' ' + isData
#    cmd = "ttDManalysis "+ s + " " + path + s  + " " + opt.channel + " " +opt.cat + " " + opt.sys + " " + opt.sync + " " + isData

    if opt.gdb:
        cmd = 'gdb --args '+cmd
    elif opt.t3batch:
        jid = '%s_%s_%s_%s' % (s,opt.channel,opt.cat,opt.sys)
        cmd = 'qexe.py -w ' + workdir + ' ' + jid+' -- '+cmd
    print cmd
 
    if opt.dryrun:
        print 'Dry Run (command will not be executed)'
        continue



    subprocess.call(cmd,shell=True)

