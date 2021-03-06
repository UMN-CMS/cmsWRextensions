#!/usr/bin/perl

$template=$ARGV[0];
$runs=$ARGV[1];
$firstrun=1;
if ($runs=~/-/) {
  $runs=~/([0-9]+)-([0-9]+)/;
  $runs=$2;
  $firstrun=$1;
}
print "$firstrun $runs \n";

#------------------------

$prodSpace="/data/whybee0b/user/aevans";
$workSpacePref="/export/scratch/user/aevans";
$executable=$ENV{"HOME"}."/bin/batch_cmsRun";
$rt=$ENV{"LOCALRT"};
$arch=$ENV{"SCRAM_ARCH"};


if (length($rt)<2) {
	print "You must run eval `scram runtime -[c]sh` in the right release\n";
        print "before running this script!\n";
	exit(1);
}

#------------------------

$jobBase=$template;
$jobBase=~s/[.]py$//;
$jobBase=~s/_cfg$//;

system("mkdir -p $prodSpace/$jobBase");
mkdir("$prodSpace/$jobBase/cfg");
mkdir("$prodSpace/$jobBase/log");

srand(); # make sure rand is ready to go

#open(SUBMIT,">condor_submit.txt");
open(SUBMIT,"|condor_submit");
print(SUBMIT "Executable = $executable\n");
print(SUBMIT "Universe = vanilla\n");
print(SUBMIT "Nice_User = true\n");
print(SUBMIT "Requirements = Memory > 400 && Arch == \"X86_64\"");
#print(SUBMIT "Requirements = Memory > 400 && Arch == \"X86_64\" && (SlotID==3 || SlotID==5 || SlotID==7 || SlotID==8 || SlotID==9 || SlotID==10 || SlotID == 12)");
print(SUBMIT " && (Machine != \"zebra01.spa.umn.edu\" && Machine != \"zebra02.spa.umn.edu\" && Machine != \"zebra03.spa.umn.edu\" && Machine != \"zebra04.spa.umn.edu\" && Machine != \"scorpion3.spa.umn.edu\")");
print(SUBMIT "\n");
print(SUBMIT "+CondorGroup=\"cmsfarm\"\n");

for ($i=$firstrun; $i<=$runs; $i++) {
    $workSpace=$workSpacePref."/prod_$i";
    $jobCfg=specializeCfg($template,$i);
    $stub=$jobCfg;
    $stub=~s|.*/([^/]+)_cfg.py$|$1|;
    $log="$prodSpace/$jobBase/log/$stub.log";
    $elog="$prodSpace/$jobBase/log/$stub.err";
    print(SUBMIT "Arguments = $arch $rt $workSpace $jobCfg $log $elog $fname\n");
#    print(SUBMIT "Arguments = $rt $prodSpace/$jobBase $jobCfg $log $elog $fname\n");
    print(SUBMIT "Queue\n");
}

close(SUBMIT);


sub specializeCfg($$) {
    my ($inp, $i)=@_;

    my $jobBase=$inp;
    $jobBase=~s/[.]py$//;
    $jobBase=~s/_cfg$//;
    $stub=$jobBase;
    $jobBase=$jobBase."_";
    $jobBase.=sprintf("%03d",$i);

    $mycfg="$prodSpace/$stub/cfg/".$jobBase."_cfg.py";
    open(INP,$inp);
    open(OUTP,">$mycfg");
    $sector=0;
    $depth=0;
    while(<INP>) {
	if ($sector==0 && /PoolOutputModule/) {
	    $sector=2;
	    $depth=0;
	}
	if ($sector==0 && /TFileService/) {
	    $sector=3;
	    $depth=0;
	}
#	if ($sector==0 && /source.*=/) {
#	    $sector=3;
#	    $depth=0;
#	}
	if (/process.RandomNumberGeneratorService/) {
	    /(\s*)untracked\s+uint32\s+([A-Za-z0-9]+)\s*=/;
	    $seed=20000000+$i*10000+int(rand(10000));
	    s/\([0-9]+\)/($seed)/;
	    print OUTP;
	} elsif (/firstRun/) {
	    printf(OUTP "    firstRun=cms.untracked.uint32(%d),\n",$i+100);
	} elsif ($sector==2 && /fileName/) {
	    $fname="$prodSpace/$stub/$jobBase".".root";
	    unlink($fname);
	    print OUTP "       fileName = cms.untracked.string(\"$fname\"),\n";
#            print OUTP "   untracked string catalog = \"file:".$jobBase.".xml\"\n";
	} elsif ($sector==3 && /fileName/) {
	    $fname="$prodSpace/$stub/$jobBase".".root";
	    unlink($fname);
	    print OUTP "       fileName = cms.string(\"$fname\"),\n";
	} else {
	    print OUTP;
	}

	$depth++ if (/\{/ && $sector!=0);
	if (/\}/ && $sector!=0) {
	    $depth--;
	    $sector=0 if ($depth==0);
	}
#	printf("%d %d %s",$sector,$depth,$_);
       
    }
    close(OUTP);
    close(INP);   
    return $mycfg;
} 
