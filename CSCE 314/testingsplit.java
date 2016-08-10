class testingsplit
{
    public static void main (String args[])
    {
        String testing = "testing ; testing ; testing";
        String[] split = testing.split(";");
        System.out.println(split[0] + split[1] + split[2]);
    }
}