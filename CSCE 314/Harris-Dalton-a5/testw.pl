#!/usr/bin/perl
# a sample testw script
# written by Hyunyoung Lee for CSCE 314 Students
# ADDED ONTO BY DALTON HARRIS, UIN 123002242
 
$tested = 0; $succeeded = 0; $failed = 0; $intentional_error = 0;
 
# test case 1 should succeed
$tested += 1;
$output = `./w factorial-example.w`;
if( $output eq "result is 120\n" ) {
   $succeeded += 1;
}else{
   $failed += 1;
}
# test case 2 should succeed
$tested += 1;
$output = `./w empty-example.w`;
if( $output eq "Testing...\n" ) {
   $succeeded += 1;
}else{
   $failed += 1;
}
# test case 3 is for intentional error
$tested += 1;
$output = `./w factorial-wrong.w 2>&1 1>/dev/null`;
@words = split " ", $output;
if( $words[1] eq "Unused" && $words[4] eq "while") {
   $intentional_error += 1;
}else{
   $failed += 1;
}
# test case 4 should succeed
$tested += 1;
$output = `./w test1.w`;
if( $output eq "add = 8   sub = 4   mult = 12   div = 3   " ) {
    $succeeded += 1;
}else{
    $failed += 1;
}
# test case 5 should succeed
$tested += 1;
$output = `./w test2.w`;
if( $output eq "1234  12345  the block works  " ) {
    $succeeded += 1;
}else{
    $failed += 1;
    # test case 6 should succeed
    $tested += 1;
    $output = `./w test3.w`;
    if( $output eq "1 2 3 4 this should print only once. " ) {
        $succeeded += 1;
    }else{
        $failed += 1;
    }}


print "$tested tested\n";
print "$succeeded + $intentional_error passed and $failed failed\n";
 
# to run this script, type the following at the terminal command line prompt
# > perl testw.pl
# then the result should be the following two lines
# 3 tested
# 2 + 1 passed and 0 failed
