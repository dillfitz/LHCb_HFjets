from Configurables import DecayTreeTuple, TupleToolTISTOS, TriggerTisTos, TupleToolJets, TupleToolRecoTruthJetMatch
from DecayTreeTuple.Configuration import *
from DecayTreeTupleMC import *
from LoKiPhys import *
from GaudiConf import IOHelper
from Configurables import MCDecayTreeTuple, CombineParticles
from PhysSelPython.Wrappers import Selection, SelectionSequence
from StandardParticles import StdLooseDiMuon, StdLooseMuons
from StandardParticles import StdAllLooseProtons as Protons
from StandardParticles import StdAllLooseKaons as Kaons
from StandardParticles import StdAllNoPIDsPions as Pions
from Configurables import DaVinci
from Configurables import FilterInTrees
from JetAccessoriesMC.ConfigurationHelpers import ConfigureDoD
from Gaudi.Configuration import *
from Configurables import LoKi__Hybrid__EvtTupleTool, LoKi__Hybrid__TupleTool
from StandardParticles import StdJets
from JetAccessories.ParticleFlow_Config import ParticleFlowConf
from JetAccessories.JetMaker_Config import JetMakerConf
#from PhysConf.Selection import AutomaticData
from PhysSelPython.Wrappers import AutomaticData, DataOnDemand
from Configurables import LoKi__FastJetMaker
from Configurables import LoKi__JetMaker
from STTools import STOfflineConf
from LoKiPhys.decorators import GeV, perCent
#from CommonParticles import Bs2MuMuLinesLc2Lambda_cKSelLambda_c

#Set this to True when doing Monte Carlo
#DaVinci().Simulation = False

#Check if this is the issue, it was not in Ibrahim's OG options file

# runs a stripping line on data
if(DaVinci().Simulation == False):
	from PhysConf.Filters import LoKi_Filters
	flters = LoKi_Filters (
		
		#select only events with one primary vertex
		VOID_Code  = " CONTAINS    ('Rec/Vertex/Primary') == 1 ",
		
		# removed for semileptonic decay
		#STRIP_Code = "HLT_PASS_RE('StrippingLambdaCForPromptCharmDecision')"
		)
	DaVinci().EventPreFilters = flters.filters('Filters')


# The part below was used in the attempt for the prompt Lc decay

"""""
stream = 'AllStreams'
line = 'LambdaCForPromptCharm'

if(DaVinci().Simulation == True):
	stream = 'AllStreams'
else: 
	stream = 'CharmCompleteEvent'

# retrieve the lambdas from this stripping line
select_Lambda_c = AutomaticData('/Event/{0}/Phys/{1}/Particles'.format(stream, line)
"""

#set up an Lc TES location, this info comes from the stripping project page
Lambda_c = CombineParticles('combine_Lambda_c')
Lambda_c.DecayDescriptor='[Lambda_c+ -> p+ K- pi+]cc'
# updated this for new stripping
Lambda_c.DaughtersCuts = {
     '' : 'ALL'
   , 'pi+' : ' (PT > 300*MeV) & (BPVIPCHI2() > 9) & (TRCHI2DOF < 4.0) & (TRGHP < 0.4) '
   , 'p~-' : ' (PT > 300*MeV) & (BPVIPCHI2() > 9) & (TRCHI2DOF < 4.0) & (TRGHP < 0.4) & ((PIDp-PIDpi)>5) & ((PIDp-PIDK)>0)'
   , 'pi-' : ' (PT > 300*MeV) & (BPVIPCHI2() > 9) & (TRCHI2DOF < 4.0) & (TRGHP < 0.4) '
   , 'K+' : ' (PT > 300*MeV) & (BPVIPCHI2() > 9) & (TRCHI2DOF < 4.0) & (TRGHP < 0.4) & ((PIDK-PIDpi)>5) & ((PIDK-PIDp)>0)'
   , 'K-' : ' (PT > 300*MeV) & (BPVIPCHI2() > 9) & (TRCHI2DOF < 4.0) & (TRGHP < 0.4) & ((PIDK-PIDpi)>5) & ((PIDK-PIDp)>0)'
   , 'p+' : ' (PT > 300*MeV) & (BPVIPCHI2() > 9) & (TRCHI2DOF < 4.0) & (TRGHP < 0.4) & ((PIDp-PIDpi)>5) & ((PIDp-PIDK)>0)'
}

# these change depending on the stripping
Lambda_c.CombinationCut="(ADAMASS('Lambda_c+') < 60*MeV) & (ADOCA(1,3) < 0.3*mm) & (ADOCA(2,3) < 0.3*mm)"
# Lambda_c.MotherCut=' ( VFASPF(VCHI2) < 15 ) & ( (BPVLTIME()*c_light) > 70*micrometer ) & ( BPVIPCHI2() < 100 )'
Lambda_c.MotherCut=' ( VFASPF(VCHI2) < 15 ) & ( (BPVLTIME()*c_light) > 70*micrometer )' # Removed the IP-chi^2 cut

#Lambda_c.ParticleCombiners.update({ "" : "ParticleAdder"})

# select_mother /// Algorithm = mother /// RequiredSelections = daughters
select_Lambda_c = Selection('select_Lambda_c',
                            Algorithm = Lambda_c,
                            RequiredSelections=[Protons, Pions, Kaons]
                            )


Lc_seq = SelectionSequence('Lc_seq', TopSelection = select_Lambda_c)
DaVinci().UserAlgorithms += [Lc_seq.sequence()]

# the stuff below is used for more complex decays (like reconstructing two particles isntead of one)

kaons_from_Lc = FilterInTrees('kaons_from_Lc_filter', Code="('K+' == ABSID)")
kaons_from_Lc_sel = Selection("kaons_from_Lc_sel",
                            Algorithm=kaons_from_Lc,
                            RequiredSelections=[DataOnDemand(Location=Lc_seq.outputLocation())])

kaons_seq = SelectionSequence('kaons_seq', TopSelection = kaons_from_Lc_sel)
DaVinci().UserAlgorithms += [kaons_seq.sequence()]

pions_from_Lc = FilterInTrees('pions_from_Lc_filter', Code="('pi+' == ABSID)")
pions_from_Lc_sel = Selection("pions_from_Lc_sel",
                            Algorithm=pions_from_Lc,
                            RequiredSelections=[DataOnDemand(Location=Lc_seq.outputLocation())])

pions_seq = SelectionSequence('pions_seq', TopSelection = pions_from_Lc_sel)
DaVinci().UserAlgorithms += [pions_seq.sequence()]

proton_from_Lc = FilterInTrees('proton_from_Lc_filter', Code="('p+' == ABSID)")
proton_from_Lc_sel = Selection("proton_from_Lc_sel",
                            Algorithm=proton_from_Lc,
                            RequiredSelections=[DataOnDemand(Location=Lc_seq.outputLocation())])

proton_seq = SelectionSequence('proton_seq', TopSelection = proton_from_Lc_sel)
DaVinci().UserAlgorithms += [proton_seq.sequence()]


Lc_from_Lc = FilterInTrees('Lc_from_Lc_filter', Code="('Lambda_c+' == ABSID)") #decay descriptor
Lc_from_Lc_sel = Selection("Lc_from_Lc_sel",
                            Algorithm=Lc_from_Lc,
                            RequiredSelections=[select_Lambda_c])

LcfromLc_seq = SelectionSequence('LcfromLc_seq', TopSelection = Lc_from_Lc_sel)
DaVinci().UserAlgorithms += [LcfromLc_seq.sequence()]


# import jet building tuple tools
from Configurables import HltJetBuilder, HltParticleFlow, GaudiSequencer
from JetAccessories.HltJetConf import HltJetBuilderConf, HltParticleFlowConf
#from Gaudi.Configuration import *
from CommonParticles.Utils import *

ParticleFlow = HltParticleFlowConf('CustomStdHltPF', SprRecover=True, isMC = DaVinci().Simulation)
JetBuilder = HltJetBuilderConf(
    'CustomStdHltJets',
    #clustering jets with Lambda C s in mind, reconstructing the particle before we build the jet ensures we are more accurate
	[ParticleFlow.getOutputLocation(),  LcfromLc_seq.outputLocation()],
	
	## This line made the options file not-work. See correct line above
	#[ParticleFlow.getOutputLocation()]
	
	#ban particles
	InputBans = [kaons_seq.outputLocation(), pions_seq.outputLocation(), proton_seq.outputLocation()], 

	jetid =False,
	# InputTags = [LcfromLc_seq.outputLocation()], # different from OG
    JetEcPath='',
    JetPtMin=15*GeV,
    JetVrt=False
	)

algorithm = GaudiSequencer('CustomStdHltJetsSeq')
algorithm.Members += [ParticleFlow.getSeq()]
algorithm.Members += [JetBuilder.getSeq()]

## configure Data-On-Demand service
locations = updateDoD(algorithm, name='CustomStdHltJets')
_jetsHlt = DataOnDemand(Location = 'Phys/CustomStdHltJets/Particles')

# from Configurables import FilterJet
# filterHltJet = FilterJet('BDTTagHltJets')
# #filterJet.Inputs = ['Phys/HltHltJB_withjetid/Particles']
# filterHltJet.Inputs = [_jetsHlt.outputLocation()]

# filterHltJet.tagToolName = "LoKi::BDTTag"
# filterHltJet.Cut = 0
# filterHltJet.saveAllJetWithInfo = True
# updateDoD(filterHltJet)
# _jetsHlt = DataOnDemand(Location = 'Phys/BDTTagHltJets/Particles')

# the particles that we want in the jet
LcInJet = CombineParticles('combine_LcJet',
                            DecayDescriptor='[system -> Lambda_c+ CELLjet]cc',
                            # DaughtersCuts={'CELLjet':'PT > 5.*GeV'},
							DaughtersCuts = {'CELLjet': '(ETA > 2.2) & (ETA < 4.2)'},
                            #CombinationCut = 'monitor(ATRUE)',
                            #CombinationCut = '((CHILD(ETA,2) - CHILD(ETA,1))*(CHILD(ETA,2) - CHILD(ETA,1))+(CHILD(PHI,2) - CHILD(PHI,1))*(CHILD(PHI,2) - CHILD(PHI,1)))<0.1',
                             #MotherCut = "(pow((CHILD(ETA, 1) - CHILD(ETA, 2)),2) + pow((CHILD(PHI, 1) - CHILD(PHI, 2)),2)) < 0.5")
                            #MotherCut = "ALL") #this was from before
							MotherCut = "((pow((CHILD(ETA, 1) - CHILD(ETA, 2)),2) + pow((CHILD(PHI, 1) - CHILD(PHI, 2)),2)) < 0.25)") # eta squared + phi squared
# LcInJet.ParticleCombiners.update({ "" : "ParticleAdder"})
LcInJet.ParticleCombiners.update({ "" : "ParticleVertexFitter"})

# LcInJet.OutputLevel = VERBOSE


# Primary vertex stuff
from Configurables import LoKi__PVReFitter
LcInJet.ReFitPVs = True
LcInJet.IgnoreP2PVFromInputLocations = True
pvrefitter = LcInJet.addTool(LoKi__PVReFitter, name = 'pvrefitter')
LcInJet.PVReFitters.update({ "" : "LoKi::PVReFitter/pvrefitter"})

select_LcInJet = Selection('select_LcInJet',
                            Algorithm = LcInJet,
                            RequiredSelections=[select_Lambda_c, _jetsHlt] #different from OG
                            )

LcInJet_seq = SelectionSequence('LcInJet_seq', TopSelection = select_LcInJet) 


DaVinci().UserAlgorithms += [LcInJet_seq.sequence()]


# This is Code for Monte Carlo stuff
"--------------------------------------------------------------------------------------------------------------------------------------------------------------"
if(DaVinci().Simulation):

	# from Configurables import FilterDesktop
	# MC_Bmesons = FilterDesktop(
	# 'MC_Bmesons',
	# Inputs=["Event/MC/Particles"],
	# Code="('B+' == ABSID)",
	# )
	# locations = updateDoD(MC_Bmesons, name='MC_Bmesons')
	# _MCBmesons = DataOnDemand(Location = 'Phys/MC_Bmesons/Particles')
	# DaVinci().UserAlgorithms += [MC_Bmesons.sequence()]
	#


	# MC_Bmesons_Seq = SelectionSequence('MC_Bmesons_Seq', TopSelection = MC_Bmesons_Sel)
	# DaVinci().UserAlgorithms += [MC_Bmesons_Seq.sequence()]
	    
		
		### MC reconstruction ######################################

	from Configurables import McParticleFlow, McJetBuilder
	genPF = McParticleFlow('genPF')
	genPF.Inputs = [
	       ['PID',        'ban',       '12,-12,14,-14,16,-16'], # neutrinos
	       ['PID',        'particle',  '211,130,3222,321,310,3122,3112,3312,3322,' 
	        '30221,9010221,-211,-130,-3222,-321,-310,-3122,-3112,-3312,-3322,-30221,'
	        '-9010221,-4122,4122'],
	       ['MCParticle', 'daughters', 'MC/Particles'],
	       ]
	genPF.Output = 'Phys/PF/MCParticles'
	genJB = McJetBuilder('genJB')
	JetPtMin = 15000
	genJB.JetPtMin = JetPtMin
	genJB.JetR = 0.5
	genJB.ChrVrt = True
	genJB.NeuVrt = True
	genJB.Inputs = [genPF.Output]
	genJB.Output = 'Phys/JB/MCParticles'
	DaVinci().UserAlgorithms += [genPF, genJB]
	
	#now Lc build a MC jet tuple
	from Configurables import MCJetTuple, MCTupleToolJetDaughters

	mcjt = MCJetTuple('mcjettuple')
	mcjt.Inputs = [_jetsHlt.outputLocation()]
	mcjt.Decay = 'CELLjet'
	mcjt.ToolList+=['MCTupleToolJetDaughters']
	mcjt.addTool(MCTupleToolJetDaughters)

	mcjt.MCTupleToolJetDaughters.GetTruthLc = True  #CHECK THIS
	mcjt.MCTupleToolJetDaughters.JetLocation = _jetsHlt.outputLocation()
	#DaVinci().UserAlgorithms += [mcjt]

	# mcjt.OutputLevel = DELcG

	mc_basic_loki_vars = {
    'ETA': 'MCETA',
    'PHI': 'MCPHI',
    'PT': 'MCPT',
    'PX': 'MCPX',
    'PY': 'MCPY',
    'PZ': 'MCPZ',
    'E': 'MCE',
    'P': 'MCP',
	'ID': 'MCID',
	'ThreeCharge': 'MC3Q'
}

	mcdecay = MCDecayTreeTuple("MCDecay")
	mcdecay.Decay = '^[Lambda_c+ -> p+ K- ^pi+]CC'
	mcdecay.ToolList = ['MCTupleToolReconstructed']
	mcdecay.addTupleTool(
	'LoKi::Hybrid::MCTupleTool/basicLoKiTT'
	).Variables = mc_basic_loki_vars
	mcdecay.addBranches({#'Lc' : 'system -> ^[Lambda_c+ -> p+ K- pi+]CC CELLjet',
			 'pi' : '[Lambda_c+ -> p+ K- ^pi+]CC',
			 'p' : '[Lambda_c+ -> ^p+ K- pi+]CC',
	         'K' : '[Lambda_c+ -> p+ ^K- pi+]CC',
			 'Lc' : '^[Lambda_c+ -> p+ K- ^pi+]CC'})

	# DaVinci().UserAlgorithms += [mcdecay]

# bjet = CombineParticles('Combine_bjet',
# 			DecayDescriptor='H_10 -> [B+]CC CELLjet',
# 			DaughtersCuts={'CELLjet': '(PT > 10000) & (ETA > 2.5) & (ETA < 4.0) & '},
#             CombinationCut = {'DELTAR2("B+")("CELLjet")'},
# 			#MotherCut="VFASPF(VCHI2/VDOF) < 12"
# 			MotherCut="ALL"
# 			#mother cut applied to dijets for same vertex from twiki https://twiki.cern.ch/twiki/bin/view/LHCbPhysics/JetFAQ
# 	       		)
# bjet.ParticleCombiners.update({ "" : "ParticleAdder"})


# from STTools import STOfflineConf
# STOfflineConf.DefaultConf().configureTools()
"--------------------------------------------------------------------------------------------------------------------------------------------------------------"

jettuple = DecayTreeTuple('Jets')
jettuple.Inputs = [LcInJet_seq.outputLocation()] # Different from OG (1 reconstruction)
# jettuple.InputPrimaryVertices = '/Rec/Vertex/Primary'
#jettuple.Decay = 'CELLjet'
jettuple.Decay = 'system -> ^[Lambda_c+ -> ^p+ ^K- ^pi+]CC ^CELLjet'


#jettuple.addBranches({"Jet": "CELLjet"})
jettuple.addBranches({'Lc' : 'system -> ^[Lambda_c+ -> p+ K- pi+]CC CELLjet',
		 'pi' : 'system -> [Lambda_c+ -> p+ K- ^pi+]CC CELLjet',
		 'p' : 'system -> [Lambda_c+ -> ^p+ K- pi+]CC CELLjet',
         'K' : 'system -> [Lambda_c+ -> p+ ^K- pi+]CC CELLjet',
		 'Jet' : 'system -> [Lambda_c+ -> p+ K- pi+]CC ^CELLjet'})


# # The following was in the OG, but is only used for 2 reconstructions
"--------------------------------------------------------------------------------------------------------------------------------------------------------------"
# jettuple.Bu.addTupleTool('TupleToolDecayTreeFitter/ConsBu')
# jettuple.Bu.ConsBu.constrainToOriginVertex = True
# jettuple.Bu.ConsBu.Verbose = True
# jettuple.Bu.ConsBu.daughtersToConstrain = ['J/psi(1S)']
"--------------------------------------------------------------------------------------------------------------------------------------------------------------"

jettuple.ToolList.remove('TupleToolGeometry')
jettuple.Jet.addTupleTool('TupleToolJets')
ttjd = jettuple.Jet.addTupleTool('TupleToolJetDaughters')
ttjd.Simulation = DaVinci().Simulation
jettuple.addTupleTool('TupleToolRecoStats')

bdtToolHlt = jettuple.Jet.addTupleTool("TupleToolJetTag/BDTTag")
bdtToolHlt.tagToolName = "LoKi::BDTTag"
bdtToolHlt.tagToolLabel = "BDTTag"
bdtToolHlt.VerboseTag = True

svToolHlt = jettuple.Jet.addTupleTool("TupleToolJetTag/SVTag")
svToolHlt.tagToolName = "LoKi::SVTag"
svToolHlt.tagToolLabel = "SVTag"
svToolHlt.VerboseTag = True
#jettuple.TupleToolJets.Verbose = True

## Trigger list options were commented out

# jettuple.addTool ( TupleToolTISTOS, name = "TISTOS")
# jettuple.ToolList += ['TupleToolTISTOS/TISTOS']
# jettuple.TISTOS.TriggerList = triggerlist
# jettuple.TISTOS.Verbose = True
# jettuple.TISTOS.addTool( TriggerTisTos, name = "TriggerTisTos")
# jettuple.TISTOS.TriggerTisTos.TOSFracEcal = 0.
# jettuple.TISTOS.TriggerTisTos.TOSFracHcal = 0.

jettuple.pi.addTupleTool('TupleToolTrackInfo')
jettuple.p.addTupleTool('TupleToolTrackInfo') #gives track info
jettuple.pi.addTupleTool('TupleToolGeometry') # gives PV info
jettuple.p.addTupleTool('TupleToolGeometry')
jettuple.K.addTupleTool('TupleToolGeometry')
jettuple.K.addTupleTool('TupleToolTrackInfo')
jettuple.Lc.addTupleTool('TupleToolGeometry')
jettuple.Lc.addTupleTool('TupleToolTrackInfo')


jettuple.pi.addTupleTool('TupleToolMCTruth')
jettuple.p.addTupleTool('TupleToolMCTruth')
jettuple.K.addTupleTool('TupleToolMCTruth')
jettuple.Lc.addTupleTool('TupleToolMCTruth')


#Check this
triggerlist = [
    #L0 TCKsh getL0Channels(0x11741801)
    "L0HadronDecision",

    #Hlt1 lines TCKsh getHlt1Lines(0x11741801)
    "Hlt1TrackMVADecision",
    "Hlt1TwoTrackMVADecision",
    "Hlt1TrackMVATightDecision",
    "Hlt1TwoTrackMVATightDecision",
    #Hlt2 lines TCKsh getHlt2(0x21751801)
    "Hlt2Topo2BodyDecision",
    "Hlt2Topo3BodyDecision",
    "Hlt2Topo4BodyDecision",
]

#add trigger list options, different from OG
jettuple.addTool ( TupleToolTISTOS, name = "TISTOS")
jettuple.ToolList += ['TupleToolTISTOS/TISTOS']
jettuple.TISTOS.TriggerList = triggerlist
jettuple.TISTOS.Verbose = True
jettuple.TISTOS.addTool( TriggerTisTos, name = "TriggerTisTos")
jettuple.TISTOS.TriggerTisTos.TOSFracEcal = 0.
jettuple.TISTOS.TriggerTisTos.TOSFracHcal = 0.

# if(DaVinci().Simulation):
# 	jetrecotruth = jettuple.Jet.addTupleTool('TupleToolRecoTruthJetMatch')
# 	jetrecotruth.JetLocation = _jetsHlt.outputLocation()


etuple = EventTuple()
etuple.addTupleTool('TupleToolRecoStats')
etuple.addTupleTool('TupleToolTrigger')
etuple.addTupleTool('TupleToolTriggerRecoStats')



#DaVinci().UserAlgorithms += [idtt]
#DaVinci().UserAlgorithms += [etuple]

from GaudiConf import IOHelper
from Gaudi.Configuration import FileCatalog, importOptions

DaVinci().TupleFile = 'LcpKpi_in_jet_13TeV_nojetid_dtf.root'
DaVinci().InputType = 'DST'

## In the OG we had:
#DaVinci().Lumi = not DaVinci().Simulation

"Select and do 'command /' when running ganga (to comment) and locally (uncomment)"
"------------------------------------------------------------------------------------------------------------------------------------------------------------------"
# Remove for running the ganga file
# IOHelper().inputFiles(['/afs/cern.ch/work/r/ramirezg/DST_Storage/00103400_00000241_1.charmcompleteevent.dst'], clear=True) # data
# IOHelper().inputFiles(['/afs/cern.ch/work/r/ramirezg/DST_Storage/00124188_00000063_7.AllStreams.dst'], clear=True) # MonteCarlo

# # Remove for running the ganga file, see: https://lhcb.github.io/starterkit-lessons/first-analysis-steps/minimal-dv-job.html
# DaVinci().DataType = "2016"

#DaVinci().HistogramFile = "DVHistos.root"

# Remove for running the ganga file
DaVinci().PrintFreq = 1000

# # Remove for running ganga file
# DaVinci().Lumi = not DaVinci().Simulation
"------------------------------------------------------------------------------------------------------------------------------------------------------------------"

DaVinci().EvtMax = -1
DaVinci().UserAlgorithms += [jettuple]

#	importOptions("/afs/cern.ch/work/k/kmattiol/MC/Run2/MC_2016_Beam6500GeV2016MagDownNu1.625nsPythia8_Sim09g_Trig0x6139160F_Reco16_Turbo03_Stripping28r1NoPrescalingFlagged_49000053_ALLSTREAMS.DST.py")
#	FileCatalog().Catalogs = ["xmlcatalog_file:/afs/cern.ch/work/k/kmattiol/MC/Run2/MC_2016_pt20pt50_28r1_catalog.xml"]
	#IOHelper().inputFiles(['/afs/cern.ch/work/k/kmattiol/MC/Run2/00124194_00000367_7.AllStreams.dst'], clear=True)
	#IOHelper().inputFiles(['/afs/cern.ch/work/i/ichahrou/MC/Run2/00139114_00000031_7.AllStreams.dst'], clear=True)

#Real data:
#else:
#	IOHelper().inputFiles(['/afs/cern.ch/work/k/kmattiol/data/Run2/00103398_00011105_1.bhadroncompleteevent.dst', '/afs/cern.ch/work/k/kmattiol/data/Run2/00103398_00013462_1.bhadroncompleteevent.dst'], clear=True)



# from PhysConf.Filters import LoKi_Filters
# flters = LoKi_Filters (
#     L0DU_Code = "L0_CHANNEL_RE ( 'DiMuon' )",
#     HLT1_Code = "HLT_PASS_RE ( 'Hlt1DiMuonHighMassDecision' )",
#     HLT2_Code = "HLT_PASS_RE ( 'Hlt2DiMuonB.*Decision' )",
#     STRIP_Code = "HLT_PASS_RE ( 'Stripping.*DiMuonDiMuonHighMass.*' )"
#     )
#
# DaVinci().EventPreFilters = flters.filters('Filters')
#