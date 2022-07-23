LC_ALL=C perl -e 'for( my $i=0; $i < 128; $i++) {
print (sprintf("%c is %d %x\t\t\%c is %d %x\n", $i, $i, $i, $i + 128, $i +128, $i + 128));
}' > test_bytes.txt
