#!/usr/bin/perl
use strict;
use warnings;
 use IPC::SysV qw(IPC_PRIVATE S_IRUSR S_IWUSR IPC_CREAT);
   
my $dictionary = {
	"1"=> ["size", "clique"],
	"2"=> [ "length", "shortest", "path", "between","distance"],
	"3"=> [ "list", "shortest", "path", "between", "names", "people","persons"],
	"4"=> ["shortest", "path","graph"],
	"5"=> ["importance", "number"],
	"6"=> [ "more", "important", "friends", "than","friend"],
	"7"=> ["quit","exit","bye","q"]
};
my @keys = sort keys %$dictionary;

my @query;
my $message;

sub makeMessage{

	my $occurence = {"1"=>"0","2"=>"0","3"=>"0","4"=>"0","5"=>"0","6"=>"0","7"=>"0"};

	for (my $i=0;$i<@query;$i++){
		my $query_word = $query[($i)];
		for (my $j=1;$j<8;$j++){
			for (my $k=0; $k<@{$dictionary->{$j}}; $k++){
				if ($query_word eq $dictionary->{$j}->[$k]) {
					($occurence->{$j})++;
				}
			}
		}
	};


	my @query_number = sort keys %{$occurence};

	#### Give the required QUERY NUMBER :: should be placed in subroutine #####

	my %occurence_reverse =  reverse %{$occurence};
	my @values_occurence = sort values %{$occurence};

	my $message_string = "";
	if ($values_occurence[6]==0){
		$message_string=$message_string."#"
	}
	else{
		$message_string=$message_string.$occurence_reverse{$values_occurence[6]}."!";
	
		for (my $i=0;$i<@query;$i++){
			if ($query[$i]=~ m{\d}){
				$message_string=$message_string.$query[$i]."!";
			}
		};
		
	}
	$message = $message_string."\0";
	#print "Perl :: Sending the message => ",$message,"\n";
};


sub main {
	my $ipckey = 123456;
	my $msgid = msgget($ipckey, IPC_CREAT | 0666);
	my $msg_type = 1;
	
	my $pID = fork();
	if ($pID!=0){
		my $arbit_message;
		msgrcv($msgid,$arbit_message,4,2,0);
		my $input;
		while (){
			print "Gyani :: Please Enter your Query?","\n";
			$input = <STDIN>;
			
			@query = split(/\s+/, $input);
			&makeMessage;
			if ("#\0" eq $message ){
				print "Gyani :: Query cant be identified. Please enter your query again.","\n"
			}
			else{
				msgsnd($msgid,pack("l!a*",$msg_type,$message), 0);
				msgrcv($msgid,$arbit_message,4,2,0); # this will make the function wait till the analyzer function gets completed and sends a message of type 2
				print "Gyani :: Analyzer completed the query. Now asking for another query","\n";
			}
		}
	}
	else {
		exec ('./PartB/analyzer');
	}
};

&main;






















