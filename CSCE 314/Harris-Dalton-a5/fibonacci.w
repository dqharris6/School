var t1 = 0;
var t2 = 1;

var input = 6;
var count = 0;

print t1;
print " ";
print t2;
print " ";

while (count<input)
{
    var display=t1+t2;
    t1=t2;
    t2=display;
    count = count+1;
    print display;
    print " ";
}